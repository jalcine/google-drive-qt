#include "settingsmanager.h"
#include "share/defs.h"
#include "share/enums.h"
#include "share/debug.h"
#include <QString>
#include <QStringList>
#include <QDir>

SettingsManager::SettingsManager(QObject *parent) :
    QSettings("ICS", "Google Drive File Manager", parent)
{
}

void SettingsManager::saveAccountInfo(AccountInfo::Data &data)
{
    beginGroup(ACCOUNTS_GROUP);

    int count = childGroups().count();

    beginGroup(data.email);

    setValue(NAME_KEY, data.name);
    setValue(DOMAIN_SHARING_POLICY_KEY, data.domainSharingPolicy);
    setValue(PERMISSION_ID_KEY, data.permissionId);
    setValue(QUOTA_BYTES_TOTAL_KEY, data.quotaBytesTotal);
    setValue(QUOTA_BYTES_USED_KEY, data.quotaBytesUsed);
    setValue(QUOTA_BYTES_USED_IN_TRASH_KEY, data.quotaBytesUsedInTrash);
    setValue(ACCESS_TOKEN_KEY, data.accessToken);

    if(!data.refreshToken.isEmpty())
    {
        setValue(REFRESH_TOKEN_KEY, data.refreshToken);
    }

    if(!contains(ACCOUNT_LETTER_KEY))
    {
        setValue(ACCOUNT_LETTER_KEY, QChar('a' + count));
    }

    endGroup();
    endGroup();
}

QString SettingsManager::accountDisc(const QString &accountName)
{
    return getValueFromGroup(ACCOUNTS_GROUP + QString("/") + accountName, ACCOUNT_LETTER_KEY, QString("a")).toString();
}

QMap<QString, QString> SettingsManager::accountsWithLetters(void)
{    
    beginGroup(ACCOUNTS_GROUP);

    QMap<QString, QString> accountsMap;
    QStringList accountsList(childGroups());

    foreach(QString account, accountsList)
    {
        beginGroup(account);

        QString letter = value(ACCOUNT_LETTER_KEY).toString();
        accountsMap[letter] = account;

        endGroup();
    }

    endGroup();

    return accountsMap;
}

int SettingsManager::currentPanel(void)
{
    return getValueFromGroup(COMMON_GROUP, CURRENT_PANEL_KEY, LEFT_PANEL_VALUE).toInt();
}

void SettingsManager::setCurrentPanel(int panelNum)
{
    setValueInGroup(COMMON_GROUP, CURRENT_PANEL_KEY, panelNum);
}

void SettingsManager::setInitialLoading(bool initLoad)
{
    setValueInGroup(COMMON_GROUP, INIT_LOAD_KEY, initLoad);
}

bool SettingsManager::initialLoading(void)
{
    return getValueFromGroup(COMMON_GROUP, INIT_LOAD_KEY, false).toBool();
}

void SettingsManager::setCurrentFolderPath(int panelNum, const QString &path)
{
    setValueForCurrentPanel(panelNum, CURRENT_FOLDER_PATH_KEY, path);
}

QString SettingsManager::currentFolderPath(int panelNum)
{
    return getValueForCurrentPanel(panelNum, CURRENT_FOLDER_PATH_KEY).toString();
}

void SettingsManager::setCurrentFolderURL(int panelNum, const QString &url)
{
    setValueForCurrentPanel(panelNum, CURRENT_FOLDER_URL_KEY, url);
}

QString SettingsManager::currentFolderURL(int panelNum)
{
    return getValueForCurrentPanel(panelNum, CURRENT_FOLDER_URL_KEY, GET_FULL_ROOT_CONTENT).toString();
}

void SettingsManager::setPathesURLs(int panelNum, QStringList pathes)
{
    setValueForCurrentPanel(panelNum, PATHES_URLS_KEY, pathes);
}

QStringList SettingsManager::pathesURLs(int panelNum)
{
    return getValueForCurrentPanel(panelNum, PATHES_URLS_KEY).toStringList();
}

void SettingsManager::setValueForCurrentPanel(int panelNum, const QString &key, const QVariant &val)
{
    QString accountGroup(ACCOUNTS_GROUP + QString("/") + currentAccount(currentPanel()));
    setValueInGroup(accountGroup, key + QString::number(panelNum), val);
}

QVariant SettingsManager::getValueForCurrentPanel(int panelNum, const QString &key, const QVariant &defaultVal)
{
    QString accountGroup(ACCOUNTS_GROUP + QString("/") + currentAccount(currentPanel()));
    return getValueFromGroup(accountGroup, key + QString::number(panelNum), defaultVal);
}

bool SettingsManager::isWorkDirSet(void)
{
    return exists(COMMON_GROUP, WORK_DIR_KEY);
}

QString SettingsManager::workDir(void)
{
    return getValueFromGroup(COMMON_GROUP, WORK_DIR_KEY).toString();
}

void SettingsManager::setWorkDir(const QString &workDrName)
{
    setValueInGroup(COMMON_GROUP, WORK_DIR_KEY, workDrName);
}

QString SettingsManager::accessToken(void)
{
    QString accountGroup(ACCOUNTS_GROUP + QString("/") + currentAccount(currentPanel()));
    return getValueFromGroup(accountGroup, ACCESS_TOKEN_KEY).toString();
}

QString SettingsManager::refreshToken(void)
{
    QString accountGroup(ACCOUNTS_GROUP + QString("/") + currentAccount(currentPanel()));
    return getValueFromGroup(accountGroup, REFRESH_TOKEN_KEY).toString();
}

void SettingsManager::setCurrentAccount(int panelNum, const QString &name)
{
    setValueInPanelGroup(panelNum, CURRENT_ACCOUNT_KEY, name);
}

QString SettingsManager::currentAccount(int panelNum)
{
    return getValueFromPanelGroup(panelNum, CURRENT_ACCOUNT_KEY).toString();
}

void SettingsManager::saveRegistration(const QString &scope, const QString &clientId, const QString &clientSecret, const QString &redirectUri)
{
    setValueInGroup(COMMON_GROUP, SCOPE_KEY, scope);
    setValueInGroup(COMMON_GROUP, CLIENT_ID_KEY, clientId);
    setValueInGroup(COMMON_GROUP, CLIENT_SECRET_KEY, clientSecret);
    setValueInGroup(COMMON_GROUP, REDIRECT_URI_KEY, redirectUri);
}

void SettingsManager::savePanelHeaderState(int panelNum, QByteArray values)
{
    setValueInPanelGroup(panelNum, PANEL_HEADER_STATE, values);
}

QByteArray SettingsManager::restorePanelHeaderState(int panelNum)
{
    return getValueFromPanelGroup(panelNum, PANEL_HEADER_STATE).toByteArray();
}

QString SettingsManager::scope(void)
{
    return getValueFromGroup(COMMON_GROUP, SCOPE_KEY).toString();
}

QString SettingsManager::clientId(void)
{
    return getValueFromGroup(COMMON_GROUP, CLIENT_ID_KEY).toString();
}

QString SettingsManager::clientSecret(void)
{
    return getValueFromGroup(COMMON_GROUP, CLIENT_SECRET_KEY).toString();
}

QString SettingsManager::redirectUri(void)
{
    return getValueFromGroup(COMMON_GROUP, REDIRECT_URI_KEY).toString();
}

bool SettingsManager::isAnyAccount(void)
{
    beginGroup(ACCOUNTS_GROUP);
    bool is = childGroups().count() > 0;
    endGroup();

    return is;
}

void SettingsManager::setValueInPanelGroup(int panelNum, const QString &key, const QVariant &val)
{
    beginGroup(PANEL_GROUP + QString::number(panelNum));
    setValue(key, val);
    endGroup();
}

QVariant SettingsManager::getValueFromPanelGroup(int panelNum, const QString &key, const QVariant &defaultVal)
{
    beginGroup(PANEL_GROUP + QString::number(panelNum));
    QVariant val(value(key, defaultVal));
    endGroup();

    return val;
}

void SettingsManager::setValueInGroup(const QString &group, const QString &key, const QVariant &val)
{
    beginGroup(group);
    setValue(key, val);
    endGroup();
}

QVariant SettingsManager::getValueFromGroup(const QString &group, const QString &key, const QVariant &defaultVal)
{
    beginGroup(group);
    QVariant val(value(key, defaultVal));
    endGroup();

    return val;
}

bool SettingsManager::exists(const QString &group, const QString &key)
{
    beginGroup(group);
    bool is =  contains(WORK_DIR_KEY);
    endGroup();

    return is;
}




