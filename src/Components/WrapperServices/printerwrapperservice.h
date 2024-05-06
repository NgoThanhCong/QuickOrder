#ifndef PRINTERWRAPPERSERVICE_H
#define PRINTERWRAPPERSERVICE_H

#include <QDebug>
#include "iwrapperservice.h"
#include <windows.h>
#include <QLibrary>
#include <QtConcurrent>
#include <QThreadPool>

extern "C" {

typedef void* (__cdecl *InitPrinterFunc          )  (const TCHAR*);
typedef int   (__cdecl *OpenPortFunc             )  (void*, const TCHAR*);
typedef int   (__cdecl *GetPrinterStateFunc      )  (void*,unsigned int*);
typedef int   (__cdecl *SetRelativeHorizontalFunc)	(void* hPrinter,int position);
typedef int   (__cdecl *PrintTextSFunc			 )	(void* hPrinter,const char* data);
typedef int   (__cdecl *PrintAndFeedLineFunc     )	(void* hPrinter);
typedef int   (__cdecl *PrintBarCodeFunc         )	(void* hPrinter,int bcType,const char* bcData,int width,int height,int alignment,int hriPosition);
typedef int   (__cdecl *CutPaperFunc             )	(void* hPrinter,int cutMode);
typedef int   (__cdecl *CutPaperWithDistanceFunc )	(void* hPrinter,int distance);
typedef int   (__cdecl *PrinterInitializeFunc    )  (void* hPrinter);
typedef int   (__cdecl *ReleasePrinterFunc       )  (void* hPrinter);
typedef int   (__cdecl *PrintSymbolFunc          )  (void* hPrinter,int type,const char* data,int errLevel,int width,int height,int alignment);

}

#define PrinterService PrinterWrapperService::getIntance()
#define LIBRARY_NAME "printer.sdk.dll"
#define LINE_SIZE 32
#define DURATION_NORMAL 3
#define DURATION_ABNORMAL 1

enum PRINTER_STATUS : unsigned int{
    PRINTER_READY,
    PRINTER_FEED_BTN_IS_PRESSED,
    PRINTER_IS_OUT_OF_PAPER,
    PRINTER_ERROR_CONDITION,
    PRINTER_ERROR,
};

#define PRINT_SYMBOL_TYPE "[PRINT_SYMBOL_TYPE]"

class PrinterWrapperService : public IWrapperService
{
    Q_OBJECT
    explicit PrinterWrapperService(QObject *parent = nullptr);
    static PrinterWrapperService* m_instance;

public:
    void init();
    static PrinterWrapperService* getIntance(){
        if(m_instance == nullptr){
            m_instance = new PrinterWrapperService();
        }
        return m_instance;
    }

    bool initializedPrinter();
    bool printText(QStringList data);
    bool closePrinter();

    bool isConnected() const;
    void setIsConnected(bool newIsConnected);

    QString PrinterStatusToText(unsigned char status);
    void setPrinterStatus(unsigned int newPrinterStatus);

    PRINTER_STATUS printerStatus() const;

signals:
    void onPrinterStatusChanged(int);

private:
    InitPrinterFunc initPrinter = nullptr;
    OpenPortFunc openPort = nullptr;
    GetPrinterStateFunc getPrinterState = nullptr;
    PrinterInitializeFunc printerInitialize = nullptr;
    PrintTextSFunc printTextS = nullptr;
    PrintAndFeedLineFunc printAndFeedLine = nullptr;
    PrintBarCodeFunc printBarCode = nullptr;
    CutPaperWithDistanceFunc cutPaperWithDistance = nullptr;
    SetRelativeHorizontalFunc setRelativeHorizontal = nullptr;
    ReleasePrinterFunc releasePrinter = nullptr;
    PrintSymbolFunc printSymbol = nullptr;

    void checkingPrinterStatus();
    void updatePrinterstatus();

    QLibrary m_lib;
    void* m_printer;
    bool m_isConnected;
    PRINTER_STATUS m_printerStatus;
};

#endif // PRINTERWRAPPERSERVICE_H
