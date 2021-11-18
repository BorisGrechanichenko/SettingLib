# SettingLib
## Что это такое?

Библиотека предоставляет расширенные по сравнению со стандартным QSettings возможности для работы с конфигурационными файлами. Она позволяет
- программное создание "словарей" настроек с указанием группы, идентификатора и значения по умолчанию, позволяющее локализовать все необходимые литералы в одном файле
- отсутствие необходимости приводить получаемое значение из QVariant к нужному типу данных - тип автоматически определяется по значению по умолчанию
- генерация файла со значениями по умолчанию при его отсутствии
- поддержка файла в актуальном состоянии - удаление неиспользуемых параметров
- статические методы установки и чтения параметров из "словаря"

## Установка
Библиотека устанавливается в каталог заданный переменной окружения QT_LIB_DEV при выполнении _make install_

## Включение в проект
Включение библиотеки можно выполнить двумя способами.

Добавление в проектный файл библиотеки с помощью включения _settingsLibInc.pri_ из папки QT_LIB_DEV :
```
QT_LIB_DEV = $$(QT_LIB_DEV)
include($$QT_LIB_DEV/settingsLibInclude.pri)
```
Подключение непосредственно исходных кодов с помощью включения _settingsLib.pri_ :
```
SETTINGS_LIB = ..... # путь к каталогу с исходными кодами библиотеки
include($$SETTINGS_LIB/settingsLib.pri)
```

## Использование
Для создания своего конфигурационного файла нужно воспользоваться шаблонным классом _ISettings_ и фабрикой для создания экземпляров настроек.

### H-файл _ServerSettings.h_

Нужно подключить фабрику и базовый класс настроек
```
#include "ISettings.h"
#include "SettingFactory.h"
```
Сначала создаются экземпляры настроек, которые в дальнейшем будет использоваться во всем остальном проекте

```
static auto CONNECT_TYPE = SettingsFactory::MakeSetting( "Main", "ConnectType", "Serial" );
static auto SERVER_IP = SettingsFactory::MakeSetting( "Network", "Ip", "127.0.0.1" );
static auto SERVER_PORT = SettingsFactory::MakeSetting( "Network", "Port", 9012 );
static auto COM_PORT = SettingsFactory::MakeSetting( "Com", "Port", "COM1" );
static auto COM_BAUD_RATE = SettingsFactory::MakeSetting( "Com", "BaudRate", 57600 );
static auto RHM_CONFIG = SettingsFactory::MakeSetting( "RHM", "Path", QString( "Config\\PXM" ) );
static auto RHM_INI = SettingsFactory::MakeSetting( "RHM", "Config", QString( "Config\\PXM.ini" ) );
static auto RADIO_CONFIG = SettingsFactory::MakeSetting( "Radio", "Path", QString( "Config\\Radio" ) );
static auto RADIO_INI = SettingsFactory::MakeSetting( "Radio", "Config", QString( "Config\\Radio.ini" ) );
```
В данном случае _SERVER_PORT_ и _COM_BAUD_RATE_ заданы как численные значения, остальные как строки. Символьные значения автоматически переводятся из _const char*_ в _QString_.

После этого добавляется класс, определяющий расположение конкретного файла настроек

```
class ServerSettingsClass
{
public:
    static QString                          SettingsDir();
    static QString                          SettingsPath();
};
```
и создается специализация шаблона ISettings для этого класса:
```
typedef ISettings< ServerSettingsClass >    ServerSettings;
```

### CPP-файл ServerSettings.cpp

В cpp-файле нужно создать "словарь" из экземпляров настроек, созданных в заголовочном файле

```
template<>
QList< BasicSetting* >                      ServerSettings::settingsList = QList< BasicSetting* >();

template<>
QList< BasicSetting * >                     ServerSettings::InitSettingsList()
{
    return
    {
        MakeSettingObject( CONNECT_TYPE ),
        MakeSettingObject( SERVER_IP ),
        MakeSettingObject( SERVER_PORT ),
        MakeSettingObject( COM_PORT ),
        MakeSettingObject( COM_BAUD_RATE ),
        MakeSettingObject( RHM_CONFIG ),
        MakeSettingObject( RHM_INI ),
        MakeSettingObject( RADIO_CONFIG ),
        MakeSettingObject( RADIO_INI )
    };
}
```
и определить расположение самого файла
```
QString                                     ServerSettingsClass::SettingsDir()
{
    return qApp->applicationDirPath() + "/config";
}
 
QString                                     ServerSettingsClass::SettingsPath()
{
    return SettingsDir() + "/server.ini";
}
```
### Примечание
Для сохранения конфигурационного файла в стандартное системное расположение можно воспользоваться QStandardPaths. Например, так:
```
QString                                     ServerSettingsClass::SettingsDir()
{
    return QStandardPaths::writableLocation( QStandardPaths::GenericDataLocation ) + "/config";
}
``` 

### Использование в проекте
В нужный модуль включается _ServerSettings.h_ и выполняются требуемые манипуляции с настройками

Пример использования
```
#include "ServerSettings.h"
 
......
int port = ServerSettings::Get( SERVER_PORT );
......
ServerSettings::Set( SERVER_PORT, 9013 );
.....
```
