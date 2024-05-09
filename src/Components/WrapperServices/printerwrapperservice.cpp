#include "printerwrapperservice.h"

PrinterWrapperService* PrinterWrapperService::m_instance = nullptr;

PrinterWrapperService::PrinterWrapperService(QObject *parent)
    : IWrapperService{parent}, m_isConnected(false) , m_printerStatus(PRINTER_ERROR)
{}

void PrinterWrapperService::init()
{
    qDebug() << __FUNCTION__;
    m_lib.setFileName(LIBRARY_NAME);  //
    if(m_lib.load()){
        initPrinter = reinterpret_cast<InitPrinterFunc>(m_lib.resolve("InitPrinter"));
        openPort = reinterpret_cast<OpenPortFunc>(m_lib.resolve("OpenPort"));
        getPrinterState = reinterpret_cast<GetPrinterStateFunc>(m_lib.resolve("GetPrinterState"));
        printerInitialize = reinterpret_cast<PrinterInitializeFunc>(m_lib.resolve("PrinterInitialize"));
        printTextS = reinterpret_cast<PrintTextSFunc>(m_lib.resolve("PrintTextS"));
        printAndFeedLine = reinterpret_cast<PrintAndFeedLineFunc>(m_lib.resolve("PrintAndFeedLine"));
        printBarCode = reinterpret_cast<PrintBarCodeFunc>(m_lib.resolve("PrintBarCode"));
        cutPaperWithDistance = reinterpret_cast<CutPaperWithDistanceFunc>(m_lib.resolve("CutPaperWithDistance"));
        setRelativeHorizontal = reinterpret_cast<SetRelativeHorizontalFunc>(m_lib.resolve("SetRelativeHorizontal"));
        releasePrinter = reinterpret_cast<ReleasePrinterFunc>(m_lib.resolve("ReleasePrinter"));
        printSymbol = reinterpret_cast<PrintSymbolFunc>(m_lib.resolve("PrintSymbol"));
        qDebug() << "[PRINTER] Load Functions Done";
    }else{
        qCritical() << "[PRINTER][LIBRARY][CAN NOT LOAD]";
    }

    checkingPrinterStatus();
}

bool PrinterWrapperService::initializedPrinter()
{
    qDebug() << "[PRINTER] Try " << __FUNCTION__;
    if(initPrinter && openPort && getPrinterState){
        m_printer = initPrinter(QString("").toStdWString().c_str());  // convert ve kieu M_printer nhan vao
        int result = openPort(m_printer, QString("USB,").toStdWString().c_str()); //
        if(result == 0){
            qDebug() << "[PRINTER] openPort OK";
            unsigned int temp_status = 2;
            result = getPrinterState(m_printer, &temp_status);
            if(result == 0){
                qDebug() << __FUNCTION__ << "[PRINTER] get Status Done :" << PrinterStatusToText(temp_status);
                setPrinterStatus(temp_status);
            }else{
                setPrinterStatus(PRINTER_ERROR);
            }

        }
        return true;
    }
    return false;
}

bool PrinterWrapperService::printText(QStringList data)
{
    if(m_isConnected && printerInitialize &&
        printAndFeedLine && printTextS)
    {
        printerInitialize(m_printer);
        foreach (const QString& line, data) {
            if(line == "\n"){
                printAndFeedLine(m_printer);
            }else{
                printTextS(m_printer, line.toStdString().c_str());
            }
        }
        printAndFeedLine(m_printer);
        return true;
    }else{
        qDebug() << "[PRINTER] Can not Print Text";
    }
    return false;
}

bool PrinterWrapperService::closePrinter()
{
    if(releasePrinter != nullptr && m_printer){
        releasePrinter(m_printer);
        return true;
    }
    return false;
}

bool PrinterWrapperService::isConnected() const
{
    return m_isConnected;
}

void PrinterWrapperService::setIsConnected(bool newIsConnected)
{
    m_isConnected = newIsConnected;
}

QString PrinterWrapperService::PrinterStatusToText(unsigned char status)
{

    QString text;
    if (status == 0x12) {
        text = "Ready";
    } else if ((status & 0x08) > 0) {
        text = "Feed button has been pressed";
    } else if ((status & 0x20) > 0) {
        text = "Printer is out of paper";
    } else if ((status & 0x40) > 0) {
        text = "Error condition";
    } else {
        text = "Error";
    }
    return text;
}

void PrinterWrapperService::setPrinterStatus(unsigned int newPrinterStatus)
{
    PRINTER_STATUS temp = PRINTER_ERROR;
    if (newPrinterStatus == 0x12) {
        temp = PRINTER_READY;
        setIsConnected(true);
    } else if ((newPrinterStatus & 0x08) > 0) {
        temp = PRINTER_FEED_BTN_IS_PRESSED;
    } else if ((newPrinterStatus & 0x20) > 0) {
        temp = PRINTER_IS_OUT_OF_PAPER;
    } else if ((newPrinterStatus & 0x40) > 0) {
        temp = PRINTER_ERROR_CONDITION;
    } else {
        temp = PRINTER_ERROR;
        setIsConnected(false);
        closePrinter();
    }

    if(temp != m_printerStatus){
        m_printerStatus = temp;
        emit onPrinterStatusChanged(m_printerStatus);
    }
}

void PrinterWrapperService::checkingPrinterStatus()
{
    qDebug() << "[PRINTER] checkingPrinterStatus" << __FUNCTION__;
    QtConcurrent::run(QThreadPool::globalInstance(),[=](){
        while(true){
            qDebug() << "[PRINTER] checkingPrinterStatus" << getPrinterState;
            if(m_isConnected){
                updatePrinterstatus();
            }else{
                initializedPrinter();
            }
            QThread::sleep(m_isConnected ? DURATION_NORMAL : DURATION_ABNORMAL);
        }
    });
}

void PrinterWrapperService::updatePrinterstatus()
{
    qDebug() << __FUNCTION__;
    if(getPrinterState){
        unsigned int temp_status = 2;
        int result = getPrinterState(m_printer, &temp_status);
        qDebug() << __FUNCTION__ << "[PRINTER] get Status Done :" << PrinterStatusToText(temp_status) << " - " << result;
        if(result == 0){
            setPrinterStatus(temp_status);
        }else{
            qDebug() << __FUNCTION__ << "[PRINTER] failed to call getPrinterState";
            setPrinterStatus(PRINTER_ERROR);
        }
    }
}

PRINTER_STATUS PrinterWrapperService::printerStatus() const
{
    return m_printerStatus;
}
