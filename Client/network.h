#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

class Network;


class NetworkDestroyer
{
private:
    Network* pInstance;
public:
    ~NetworkDestroyer() {
        delete this->pInstance;
    }
    void initialize(Network * p) {
        this->pInstance = p;
    }
};


class Network: public QObject {
private:
    static Network* pInstance;
    void initTCP();
    static QTcpSocket* tcpInstance;
    static NetworkDestroyer destroyer;
protected:

    Network();
    Network(const Network&) = delete;
    Network& operator = (Network &) = delete;

    ~Network();
    friend class NetworkDestroyer;
public:
    static Network* getInstance() {
        if (!pInstance) {
            pInstance = new Network();
            destroyer.initialize(pInstance);
        }
        return pInstance;
    }

    QJsonObject doRequest(QVariantMap request);

};

#endif // NETWORK_H
