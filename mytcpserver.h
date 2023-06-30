#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();

public slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotServerRead();

private:
    QTcpServer *mTcpServer;
    QMap<QString, QString> productTypes;
    QMap<QString, int> productPrices;
    QMap<QString, QString> productManufacturers;

    void readDataFromFile();
    void processRequest(const QString& request, QTcpSocket* socket);
    void sendResponse(const QString& response, QTcpSocket* socket);
};

#endif // MYTCPSERVER_H
