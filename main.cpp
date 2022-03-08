#include <iostream>
#include <string>

#include <QCoreApplication>

#include "connectionhandler.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    string URL;

    cout << "[*] Webhook URL: ";
    cin >> URL;

    ConnectionHandler handler(QString::fromStdString(URL));
    handler.goConsole();

    return a.exec();
}
