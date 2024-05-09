#pragma once

#include <QObject>
#include <QWindow>
#include <QApplication>
#include <QFontDatabase>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QDir>
#include <QDebug>
#include <QRegularExpression>
#include <QFile>
#include <QTextStream>
#include <QList>
#include <QStringList>
#include <QDate>
#include <QStandardPaths>

#include "../Components/const.h"

#define Utils Misc::Utilities::getInstance()

namespace Misc
{

class Utilities : public QObject
{
    Q_OBJECT

public:
    // clang-format off
    static Utilities &getInstance();
    Q_INVOKABLE void applyRadius(QWindow *window, int radius);
    void loadFont(const QApplication& app);

    QString string2has(QString in);
    static QString copyFile(QString sourceFilePath, const QString &destinationFolderPath);
    static QString getFileHash(const QString &filePath);
    static QString formatFloat(float input,int digit = 2);
    static QString getStoreImagePath(){
        QString imgPath =QCoreApplication::applicationDirPath().append("/").append("images");
        qDebug() << __FUNCTION__ << ": " << imgPath;
        return imgPath;
    }
    static QString formatPathImage(const QString& imgName){
        return QString("file:///").append(getStoreImagePath()).append("/").append(imgName);
    }

    static QString convertVietnameseToEnglish(QString str);

    static void writeCsv(const QStringList& data, const QString& postfix);

};
}
