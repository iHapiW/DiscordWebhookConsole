#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <iostream>
#include <string>

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class ConnectionHandler : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionHandler(QString WebhookURL, QObject *parent = nullptr);
    ~ConnectionHandler();
    void sendMessage(QString message);

signals:
    void sent();

public slots:
    void onFinished(QNetworkReply* reply);
    void goConsole();

private:
    QNetworkAccessManager* manager;
    QUrl WebhookURL;
};

#endif
