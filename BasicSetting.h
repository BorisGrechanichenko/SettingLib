#pragma once

#include <QSettings>
#include <QVariant>
#include <QStringList>

class BasicSetting
{
public:
    BasicSetting
    (
        QString                             group,
        QString                             name,
        QVariant                            defaultValue,
        QString                             path
    );
    virtual                                 ~BasicSetting();

    void                                    SetParameter( QVariant value );
    void                                    SetDefault();
    QString                                 FullName() const;
    virtual void                            Init();

protected:
    QSettings *                             settings;
    QString                                 groupName;
    QString                                 parameterName;
    QString                                 fullName;
    QVariant                                defaultValue;
};
