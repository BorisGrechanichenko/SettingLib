#-------------------------------------------------
#
# Project created by QtCreator 2018-11-09T12:53:00
#
#-------------------------------------------------
QT_LIB_DEV = $$(QT_LIB_DEV)

isEmpty( QT_LIB_DEV ): error( QT_LIB_DEV not defined )

CONFIG(debug,debug|release): LIB_SUFFIX = d

QT       -= gui

TARGET = $$qtLibraryTarget$${TARGET}$${QT_MAJOR_VERSION}$${LIB_SUFFIX}
TEMPLATE = lib

DEFINES += SETTINGSLIB_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11

CONFIG += debug_and_release
CONFIG += build_all

include(settingsLib.pri)

FOLDER_SETTINGS = settingsLib
PATH_SETTINGS = $$(QT_LIB_DEV)/include/$${FOLDER_SETTINGS}
PATH_LIB = $$(QT_LIB_DEV)/lib/$${FOLDER_SETTINGS}

target.path = $${PATH_LIB}

headers.files = $${HEADER_FILES}
headers.path = $${PATH_SETTINGS}

exports.files = $${PWD}/settingsLibInclude.pri
exports.path  = $$(QT_LIB_DEV)

INSTALLS += target \
    headers \
    exports

DISTFILES += \
    settingsLibInclude.pri
