#ifndef COMMONTOOLS_H
#define COMMONTOOLS_H

#include <QNetworkRequest>
#include <QTreeWidget>
#include <QString>

class CommonTools
{
public:
    static void setHeader(const QString &accessToken, QNetworkRequest &request);
    static void msg(const QString &str, QWidget *parent = 0);
    static int errorMsg(const QString &caption, const QString &text, QWidget *parent = 0);
    static void logToFile(const QString &fileName, const QByteArray &bytes);
    static QByteArray loadFromFile(const QString &fileName);
    static bool fileFromURLExists(const QString &url);
    static QString getFileNameFromURL(const QString &url);
    static QString getIDFromURL(const QString &url);
};

#endif // COMMONTOOLS_H
