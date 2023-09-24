#ifndef CLIENTFUNCTIONS_H
#define CLIENTFUNCTIONS_H
#include <network.h>
#include <QJsonObject>
#include <QSettings>
#include <QVariantMap>


bool login(QString login, QString password);

bool register_account(QString login, QString password);

QString getStat();

QJsonArray getAllStat();

QVariantMap getTask(int taskType);

bool checkTask(int taskId, QString answer);

bool save_setting(QString param_name, QString param_value);

QString load_setting(QString param_name);

bool reset_settings();


#endif // CLIENTFUNCTIONS_H
