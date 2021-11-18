HEADER_FILES += \
    $$PWD/ApplicationSetting.h \
    $$PWD/ISettings.h \
    $$PWD/BasicSetting.h \
    $$PWD/SettingDescription.h \
    $$PWD/SettingFactory.h

INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/BasicSetting.cpp

HEADERS += \
    $${HEADER_FILES}
