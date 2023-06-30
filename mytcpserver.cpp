#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>
#include <QFile>

MyTcpServer::~MyTcpServer()
{
    mTcpServer->close();
}

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection, this, &MyTcpServer::slotNewConnection);

    if (!mTcpServer->listen(QHostAddress::Any, 33333)) {
        qDebug() << "Server is not started";
    } else {
        qDebug() << "Server is started";
    }

    readDataFromFile();
}

void MyTcpServer::slotNewConnection()
{
    QTcpSocket* socket = mTcpServer->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
    connect(socket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);

    socket->write("Connected to the server\r\n");
}

void MyTcpServer::slotServerRead()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket)
        return;

    while (socket->canReadLine()) {
        QString request = QString::fromUtf8(socket->readLine()).trimmed();
        processRequest(request, socket);
    }
}

void MyTcpServer::slotClientDisconnected()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket)
        return;

    socket->close();
    socket->deleteLater();
}

void MyTcpServer::readDataFromFile()
{

    QFile file("C:/Users/negr/Desktop/exam_30_06/tovar.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        if (fields.size() == 4) {
            QString name = fields[0];
            QString type = fields[1];
            int price = fields[2].toInt();
            QString manufacturer = fields[3];

            productTypes[name] = type;
            productPrices[name] = price;
            productManufacturers[name] = manufacturer;
        }
    }

    file.close();
}

void MyTcpServer::processRequest(const QString& request, QTcpSocket* socket)
{
    QString response;
    QStringList parts = request.split("&");
    if (parts.size() >= 2) {
        QString command = parts[0];
        QString argument = parts[1];

        if (command == "max_price") {
            // Получение самых дорогих товаров
            // TODO: Реализовать логику для самых дорогих товаров
        } else if (command == "expensive_in_type") {
            // Получение товаров заданного типа, которые дороже, чем среднее по этому типу
            // TODO: Реализовать логику для товаров, дороже среднего по типу
        } else if (command == "max_price_in_type") {
            // Получение самых дорогих товаров заданного типа
            // TODO: Реализовать логику для самых дорогих товаров по типу
        } else if (command == "expensive") {
            // Получение товаров, которые дороже, чем средняя цена
            // TODO: Реализовать логику для товаров, дороже средней цены
        } else {
            response = "Unknown command";
        }
    } else {
        response = "Invalid request";
    }

    sendResponse(response, socket);
}

void MyTcpServer::sendResponse(const QString& response, QTcpSocket* socket)
{
    if (socket && socket->isOpen()) {
        socket->write(response.toUtf8());
        socket->write("\r\n");
    }
}
