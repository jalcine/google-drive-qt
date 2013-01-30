#-------------------------------------------------
#
# Project created by QtCreator 2012-04-25T16:14:50
#
#-------------------------------------------------

QT += core gui webkit network xml

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

TARGET = gdfm
TEMPLATE = app

SOURCES += core/main.cpp
SOURCES += network/operations/children.cpp
SOURCES += network/operations/operation.cpp
SOURCES += network/operations/download.cpp
SOURCES += network/operations/upload.cpp
SOURCES += network/operations/copy.cpp
SOURCES += network/operations/move.cpp
SOURCES += network/operations/rename.cpp
SOURCES += network/operations/delete.cpp
SOURCES += network/operations/create.cpp
SOURCES += network/operations/share.cpp
SOURCES += network/auth.cpp
SOURCES += gui/forms/authdialog.cpp
SOURCES += settings/settingsmanager.cpp
SOURCES += settings/accountinfo.cpp
SOURCES += gui/accountsmanager.cpp
SOURCES += network/queries.cpp
SOURCES += gui/forms/filepanel.cpp
SOURCES += gui/forms/sharedialog.cpp
SOURCES += gui/forms/createfolderdialog.cpp
SOURCES += gui/forms/mainwindow.cpp
SOURCES += core/driveengine.cpp
SOURCES += parsers/xmlparser.cpp
SOURCES += gui/items.cpp
SOURCES += network/resmanager.cpp
SOURCES += parsers/xmlhandler.cpp
SOURCES += network/downloadmanager.cpp
SOURCES += gui/forms/settingsdialog.cpp
SOURCES += share/commontools.cpp
SOURCES += network/uploadmanager.cpp
SOURCES += network/networkmanager.cpp
SOURCES += gui/forms/progressbardialog.cpp
SOURCES += network/contentmanager.cpp
SOURCES += network/operations/operationsmanager.cpp
SOURCES += parsers/jsonparser.cpp
SOURCES += gui/filestransferui.cpp
SOURCES += gui/contentui.cpp
SOURCES += gui/checkui.cpp
SOURCES += gui/controls/toolbar.cpp
SOURCES += gui/controls/combobox.cpp
SOURCES += gui/controls/spacer.cpp
SOURCES += gui/tools/painterhelper.cpp

HEADERS += gui/forms/mainwindow.h
HEADERS += network/operations/children.h
HEADERS += network/operations/operation.h
HEADERS += network/operations/download.h
HEADERS += network/operations/upload.h
HEADERS += network/operations/copy.h
HEADERS += network/operations/move.h
HEADERS += network/operations/rename.h
HEADERS += network/operations/delete.h
HEADERS += network/operations/create.h
HEADERS += network/operations/share.h
HEADERS += network/auth.h
HEADERS += gui/forms/authdialog.h
HEADERS += settings/settingsmanager.h
HEADERS += settings/accountinfo.h
HEADERS += gui/accountsmanager.h
HEADERS += network/queries.h
HEADERS += gui/forms/filepanel.h
HEADERS += gui/forms/sharedialog.h
HEADERS += share/defs.h
HEADERS += share/debug.h
HEADERS += share/enums.h
HEADERS += gui/forms/createfolderdialog.h
HEADERS += core/driveengine.h
HEADERS += parsers/xmlparser.h
HEADERS += gui/items.h
HEADERS += network/resmanager.h
HEADERS += network/downloadmanager.h
HEADERS += gui/forms/settingsdialog.h
HEADERS += share/commontools.h
HEADERS += network/uploadmanager.h
HEADERS += gui/forms/progressbardialog.h
HEADERS += network/networkmanager.h
HEADERS += parsers/xmlhandler.h
HEADERS += network/contentmanager.h
HEADERS += network/operations/operationsmanager.h
HEADERS += share/singleton.h
HEADERS += parsers/jsonparser.h
HEADERS += gui/filestransferui.h
HEADERS += gui/contentui.h
HEADERS += gui/checkui.h
HEADERS += gui/controls/toolbar.h
HEADERS += gui/controls/combobox.h
HEADERS += gui/controls/spacer.h
HEADERS += gui/tools/painterhelper.h

FORMS += gui/forms/mainwindow.ui
FORMS += gui/forms/authdialog.ui
FORMS += gui/forms/filepanel.ui
FORMS += gui/forms/sharedialog.ui
FORMS += gui/forms/createfolderdialog.ui
FORMS += gui/forms/settingsdialog.ui
FORMS += gui/forms/progressbardialog.ui

RESOURCES += resource.qrc
