#pragma once

#include "SettingDescription.h"

class SettingsFactory
{
public:

    template < typename T >
    static SettingDescription< T >          MakeSetting( QString group, QString name, T defaultValue )
    {
        return SettingDescription< T >( group, name, defaultValue);
    }

    static SettingDescription< QString >    MakeSetting( QString group, QString name, const char * defaultValue )
    {
        return MakeSetting< QString >( group, name, QString( defaultValue ) );
    }

private:
    SettingsFactory()
    {
    }
};

