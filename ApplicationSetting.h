#pragma once

#include "BasicSetting.h"
#include "SettingDescription.h"

template < class T >
class ApplicationSetting:
    public BasicSetting
{
public:
    ApplicationSetting
    (
            SettingDescription< T >         description,
            const QString                   path
    ) :
        BasicSetting( description.group, description.name, description.defaultValue, path )
    {
    }
    T                                       GetParameter()
    {
        return settings->value( fullName, defaultValue ).template value< T >();
    }
};
