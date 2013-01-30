#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QString>

class JSONParser
{
public:
    JSONParser();

public:   
    QString getValue(const QString &jsonStr, const QString &key);
    QStringList getParams(const QString &jsonStr, const QStringList &pathValues, const QString &key);

private:
    QString getToken(const QString &object, const QString &key, const QString &endDivider);
    int getTokenEnd(const QString &object, int beginPos);

private:
    int continuePos;
};

#endif // JSONPARSER_H
