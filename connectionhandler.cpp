#include "connectionhandler.h"

using namespace std;

ConnectionHandler::ConnectionHandler(QString WebhookURL, QObject *parent)
    : QObject{parent}
{
    this->manager = new QNetworkAccessManager();
    this->WebhookURL = QUrl(WebhookURL);

    QObject::connect(manager, &QNetworkAccessManager::finished,
                     this, &ConnectionHandler::onFinished);
    QObject::connect(this, &ConnectionHandler::sent,
                     this, &ConnectionHandler::goConsole);
}

ConnectionHandler::~ConnectionHandler()
{
    QObject::disconnect(manager, &QNetworkAccessManager::finished,
                        this, &ConnectionHandler::onFinished);
    delete manager;
}

void ConnectionHandler::sendMessage(QString message) {
    QNetworkRequest req(WebhookURL);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject obj;
    obj["content"] = message;
    QJsonDocument doc(obj);
    QByteArray data = doc.toJson();

    manager->post(req, data);
}

void ConnectionHandler::onFinished(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();

    if(reply->error()) {
        cout << QString::fromUtf8(data).toStdString();
        return;
    }

    if(data.length() == 0) {
        emit this->sent();
        return;
    }

    cout << QString::fromUtf8(data).toStdString();
}

void ConnectionHandler::goConsole()
{
    string part1;
    string part2;
    cout << "[*] Message: ";
    cin >> part1;
    getline(cin, part2);

    string result = part1 + part2;
    this->sendMessage(QString::fromStdString(result));
}
