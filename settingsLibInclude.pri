FOLDER_SETTINGS = settingsLib
CONFIG(debug,debug|release): LIB_SUFFIX = d

isEmpty( QT_LIB_DEV ): {
    win32: QT_LIB_DEV = $${system('echo %QT_LIB_DEV%')}
    else: QT_LIB_DEV = $${system('echo $QT_LIB_DEV')}
}

isEmpty( QT_LIB_DEV ): error( QT_LIB_DEV not defined )

INCLUDEPATH += \
    $$(QT_LIB_DEV)/include/$${FOLDER_SETTINGS}
DEPENDPATH  += \
    $$(QT_LIB_DEV)/include/$${FOLDER_SETTINGS}

LIBS += -L$$(QT_LIB_DEV)/lib/$${FOLDER_SETTINGS} -lsettingsLib$${QT_MAJOR_VERSION}$${LIB_SUFFIX}

HEADERS += $$(QT_LIB_DEV)/include/$${FOLDER_SETTINGS}/*.h
