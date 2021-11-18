#pragma once

#include <QString>

struct SettingIdentifier
{
    SettingIdentifier( QString group, QString name ):
        group( group ),
        name( name )
    {
    }

    QString                                 group;
    QString                                 name;
};

template < class T >
struct SettingDescription : public SettingIdentifier
{
    SettingDescription( QString group, QString name, T defaultValue ):
        SettingIdentifier( group, name ),
        defaultValue( defaultValue )
    {
    }

    T                                       defaultValue;
};
