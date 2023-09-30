#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer> //tcp сервер (прослушивание канала, сигнал о подключении - все, что уже готово)
#include <QTcpSocket>
#include <QVector>

//в cpp пишем все include
#include <QtNetwork> //указание порта, хоста
#include <QByteArray> //передаются биты
#include <QDebug> //вывод в консоль
#include <QRandomGenerator>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:

    explicit MyTcpServer(QObject *parent = nullptr); //конструктор
    //уничтожает экземпляра сервера и чистит памяти

    ~MyTcpServer(); //деструктор
public slots: //вызывается в случае срабатывания какого-либо сигнала


    // функция установки соединения с сервером
    void slotNewConnection();

    // функция отключения от сурвера
    void slotClientDisconnected();
    //чтение данных из активного сокета
    void slotServerRead();
    void sendToClient(int pos, QString otvet);
    //void slotReadClient();
private:
    int liveclients = 0;

    QTcpServer * mTcpServer;
    QVector<QTcpSocket *> mTcpSocket;
    int server_status;

};
#endif
