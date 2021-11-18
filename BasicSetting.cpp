#include "BasicSetting.h"

BasicSetting::BasicSetting
(
    QString                                 group,
    QString                                 name,
    QVariant                                defaultValue,
    QString                                 path
):
    settings( new QSettings( path, QSettings::IniFormat ) ),
    groupName( group ),
    parameterName( name ),
    defaultValue( defaultValue )
{
    if( !groupName.isEmpty() )
        fullName = groupName + "/" + parameterName;
    else
        fullName = parameterName;
}

BasicSetting::~BasicSetting()
{
    if( settings )
        delete settings;
}

void                                        BasicSetting::SetParameter( QVariant value )
{
    settings->setValue( fullName, value );
}
void                                        BasicSetting::SetDefault()
{
    SetParameter( defaultValue );
}

QString                                     BasicSetting::FullName() const
{
    return fullName;
}

void                                        BasicSetting::Init()
{
    QVariant value = settings->value( fullName );
    if ( !value.isValid() )
    {
        SetDefault();
    }
}
