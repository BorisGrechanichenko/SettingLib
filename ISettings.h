#pragma once

#include <QDir>

#include "ApplicationSetting.h"

template < class SettingsClass >
class ISettings
{
public:
    template< typename C, typename T >
    static C                                Get( SettingDescription< T > setting )
    {
        QVariant result( GetApplicationSetting< T >( setting ).GetParameter() );

        return result.value< C >();
    }

    template< typename T >
    static T                                Get( SettingDescription< T > setting )
    {
        return Get< T, T >( setting );
    }

    template< typename T, typename C >
    static void                             Set( SettingDescription< T > setting, C value )
    {
        QVariant temp(value);

        GetApplicationSetting< T >( setting ).SetParameter( temp.value< T >() );
    }

    template< typename T >
    static ApplicationSetting< T >          GetApplicationSetting( SettingDescription< T > setting )
    {
        if( settingsList.isEmpty() )
        {
            settingsList = InitSettingsList();
            GenerateDefaultSettingsFile();
            CleanUnusedSettings();
        }

        return ApplicationSetting< T >( setting, SettingsClass::SettingsPath() );
    }
    template < typename T >
    static ApplicationSetting< T > *        MakeSettingObject( SettingDescription< T > setting )
    {
        return new ApplicationSetting< T >( setting, SettingsClass::SettingsPath() );
    }
    static QList< BasicSetting * >          InitSettingsList();

protected:
    static void                             GenerateDefaultSettingsFile()
    {
        QDir().mkpath( SettingsClass::SettingsDir() );

        for( auto setting: settingsList )
        {
            setting->Init();
        }
    }
    static void                             CleanUnusedSettings()
    {
        QSettings settingsObject( SettingsClass::SettingsPath(), QSettings::IniFormat );

        QStringList usedKeys;
        for( auto usedSetting : settingsList )
        {
            usedKeys.append( usedSetting->FullName() );
        }

        QStringList allKeys = settingsObject.allKeys();
        for( QString key : allKeys )
        {
            if( !usedKeys.contains( key ) )
            {
                settingsObject.remove( key );
            }
        }
    }

protected:
    static QList< BasicSetting* >          settingsList;
};
