#include "Utilities.h"
#include <QDebug>

Misc::Utilities &Misc::Utilities::getInstance()
{
    static Utilities instance;
    return instance;
}

void Misc::Utilities::applyRadius(QWindow *window, int radius)
{
    QRect r(QPoint(), window->geometry().size());
    QRect rb(0, 0, 2 * radius, 2 * radius);

    QRegion region(rb, QRegion::Ellipse);
    rb.moveRight(r.right());
    region += QRegion(rb, QRegion::Ellipse);
    rb.moveBottom(r.bottom());
    region += QRegion(rb, QRegion::Ellipse);
    rb.moveLeft(r.left());
    region += QRegion(rb, QRegion::Ellipse);
    region += QRegion(r.adjusted(radius, 0, -radius, 0), QRegion::Rectangle);
    region += QRegion(r.adjusted(0, radius, 0, -radius), QRegion::Rectangle);
    window->setMask(region);
}

void Misc::Utilities::loadFont(const QApplication &app)
{
    int ret = -1;
    ret = QFontDatabase::addApplicationFont(":/fonts/Noto_Sans/NotoSans-Black.ttf");
    if(ret<0)qDebug()<<"loadfontfailedNotoSans-Black.ttf";
    ret = QFontDatabase::addApplicationFont(":/fonts/Noto_Sans/NotoSans-BlackItalic.ttf");
    if(ret<0)qDebug()<<"loadfontfailedNotoSans-BlackItalic.ttf";
    ret = QFontDatabase::addApplicationFont(":/fonts/Noto_Sans/NotoSans-Bold.ttf");
    if(ret<0)qDebug()<<"loadfontfailedNotoSans-Bold.ttf";
    ret = QFontDatabase::addApplicationFont(":/fonts/Noto_Sans/NotoSans-BoldItalic.ttf");
    if(ret<0)qDebug()<<"loadfontfailedNotoSans-BoldItalic.ttf";
    ret = QFontDatabase::addApplicationFont(":/fonts/Noto_Sans/NotoSans-ExtraBold.ttf");
    if(ret<0)qDebug()<<"loadfontfailedNotoSans-ExtraBold.ttf";
    ret = QFontDatabase::addApplicationFont(":/fonts/Noto_Sans/NotoSans-ExtraBoldItalic.ttf");
    if(ret<0)qDebug()<<"loadfontfailedNotoSans-ExtraBoldItalic.ttf";
    ret = QFontDatabase::addApplicationFont(":/fonts/Noto_Sans/NotoSans-ExtraLight.ttf");
    if(ret<0)qDebug()<<"loadfontfailedNotoSans-ExtraLight.ttf";
    ret = QFontDatabase::addApplicationFont(":/fonts/Noto_Sans/NotoSans-ExtraLightItalic.ttf");
    if(ret<0)qDebug()<<"loadfontfailedNotoSans-ExtraLightItalic.ttf";
    ret = QFontDatabase::addApplicationFont(":/fonts/Noto_Sans/NotoSans-Italic.ttf");
    if(ret<0)qDebug()<<"loadfontfailedNotoSans-Italic.ttf";
    ret = QFontDatabase::addApplicationFont(":/fonts/Noto_Sans/NotoSans-Light.ttf");
    if(ret<0)qDebug()<<"loadfontfailedNotoSans-Light.ttf";
    ret = QFontDatabase::addApplicationFont(":/fonts/Noto_Sans/NotoSans-LightItalic.ttf");
    if(ret<0)qDebug()<<"loadfontfailedNotoSans-LightItalic.ttf";
    ret = QFontDatabase::addApplicationFont(":/fonts/Noto_Sans/NotoSans-Medium.ttf");
    if(ret<0)qDebug()<<"loadfontfailedNotoSans-Medium.ttf";
    ret = QFontDatabase::addApplicationFont(":/fonts/Noto_Sans/NotoSans-MediumItalic.ttf");
    if(ret<0)qDebug()<<"loadfontfailedNotoSans-MediumItalic.ttf";
    ret = QFontDatabase::addApplicationFont(":/fonts/Noto_Sans/NotoSans-Regular.ttf");
    if(ret<0)qDebug()<<"loadfontfailedNotoSans-Regular.ttf";
    ret = QFontDatabase::addApplicationFont(":/fonts/Noto_Sans/NotoSans-SemiBold.ttf");
    if(ret<0)qDebug()<<"loadfontfailedNotoSans-SemiBold.ttf";
    ret = QFontDatabase::addApplicationFont(":/fonts/Noto_Sans/NotoSans-SemiBoldItalic.ttf");
    if(ret<0)qDebug()<<"loadfontfailedNotoSans-SemiBoldItalic.ttf";
    ret = QFontDatabase::addApplicationFont(":/fonts/Noto_Sans/NotoSans-Thin.ttf");
    if(ret<0)qDebug()<<"loadfontfailedNotoSans-Thin.ttf";
    ret = QFontDatabase::addApplicationFont(":/fonts/Noto_Sans/NotoSans-ThinItalic.ttf");
    if(ret<0)qDebug()<<"loadfontfailedNotoSans-ThinItalic.ttf";

    app.setFont(QFont("Noto Sans"));//default
}

QString Misc::Utilities::string2has(QString in){
    in = in.append(SEED_VALUE);
    QCryptographicHash encrypt(QCryptographicHash::Sha3_256);
    encrypt.addData(in.toLocal8Bit());
    QByteArray arr = encrypt.result().toHex();
    return QString::fromLocal8Bit(arr);
}

QString Misc::Utilities::copyFile(QString sourceFilePath, const QString &destinationFolderPath) {
    QString formmatedSrc = sourceFilePath.remove("file:///");
    QDir destinationFolder(destinationFolderPath);
    if (!destinationFolder.exists()) {
        if (!destinationFolder.mkpath(".")) {
            qDebug() << "Failed to create destination folder";
            return "";
        }
    }
    QString hashFile = getFileHash(formmatedSrc);
    qDebug() << formmatedSrc << "[" << hashFile << "]";
    QString destinationFilePath = destinationFolderPath + "/" + hashFile + ".png";
    if(!QFile::exists(destinationFilePath)){
        qDebug() << "File exsited";
        if (!QFile::copy(formmatedSrc, destinationFilePath)) {
            qDebug() << "Failed to copy file";
            return "";
        }
    }
    qDebug() << "File copied successfully to" << destinationFilePath;
    return hashFile.append(".png");
}

QString Misc::Utilities::getFileHash(const QString &filePath) {
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file";
        return "";
    }

    QCryptographicHash hash(QCryptographicHash::Sha256);

    if (!hash.addData(&file)) {
        qDebug() << "Failed to hash file";
        return "";
    }

    QByteArray result = hash.result();

    return result.toHex();
}

QString Misc::Utilities::formatFloat(float input, int digit)
{
    return QString::number(input, 'f', digit);
}

QString Misc::Utilities::convertVietnameseToEnglish(QString str)
{
    str.replace(QRegExp("[àáạảãâầấậẩẫăằắặẳẵ]"), "a");
    str.replace(QRegExp("[èéẹẻẽêềếệểễ]"), "e");
    str.replace(QRegExp("[ìíịỉĩ]"), "i");
    str.replace(QRegExp("[òóọỏõôồốộổỗơờớợởỡ]"), "o");
    str.replace(QRegExp("[ùúụủũưừứựửữ]"), "u");
    str.replace(QRegExp("[ỳýỵỷỹ]"), "y");
    str.replace(QRegExp("[đ]"), "d");
    str.replace(QRegExp("[ÀÁẠẢÃÂẦẤẬẨẪĂẰẮẶẲẴ]"), "A");
    str.replace(QRegExp("[ÈÉẸẺẼÊỀẾỆỂỄ]"), "E");
    str.replace(QRegExp("[ÌÍỊỈĨ]"), "I");
    str.replace(QRegExp("[ÒÓỌỎÕÔỒỐỘỔỖƠỜỚỢỞỠ]"), "O");
    str.replace(QRegExp("[ÙÚỤỦŨƯỪỨỰỬỮ]"), "U");
    str.replace(QRegExp("[ỲÝỴỶỸ]"), "Y");
    str.replace(QRegExp("[Đ]"), "D");
    str.remove(QRegExp("[\u0300\u0301\u0303\u0309\u0323]")); // ̀ ́ ̃ ̉ ̣
    str.remove(QRegExp("[\u02C6\u0306\u031B]")); // ˆ ̆ ̛  Â, Ê, Ă, Ơ, Ư

    str.replace(QRegExp(" + "), " ");
    str = str.trimmed();

    str.remove(QRegExp("[!@%^*()+=<>?/,.:;'\",&#[\\]~$`{}|\\\\-]"));
    return str;
}

void Misc::Utilities::writeCsv(const QList<QStringList> &data, const QString &fileName)
{
    // Open the file
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString filePath = desktopPath +"/"+fileName;
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        qDebug() << "Could not open file for writing:" << file.errorString();
        return;
    }

    QTextStream out(&file);

    for (const auto &row : data) {
        QStringList formattedRow;
        for (const auto &item : row) {
            QString formattedItem = item;
            if (item.contains(',')) {
                formattedItem = "\"" + item + "\"";
            }
            formattedRow.append(formattedItem);
        }
        out << formattedRow.join(",") << "\n";
    }
    file.close();
}

void Misc::Utilities::writeCsv(const QStringList &data)
{
    QDate currentDate = QDate::currentDate();
    QString fileName = currentDate.toString("yyyy-MM-dd") + ".csv";
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString filePath = desktopPath + QDir::separator() + fileName;
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error: Failed to open file for writing:" << file.errorString();
        return;
    }
    QTextStream out(&file);
    out.setCodec("UTF-16");
    for (const QString &line : data) {
        out << line << "\n";
    }
    file.close();

    qDebug() << "CSV file saved to:" << filePath;
}
