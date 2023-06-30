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

    if (!mTcpServer->listen(QHostAddress::Any, 2323)) {
        qDebug() << "Server is not started";
    } else {
        qDebug() << "Server is started";
    }
    handleMaxPrice();
    handleExpensive();
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

void MyTcpServer::processRequest(const QString& request, QTcpSocket* socket)
{
    QString response;
    QStringList parts = request.split("&");
    if (parts.size() >= 2) {
        QString command = parts[0];

        if (command == "max_price") {
            handleMaxPrice();

        } else if (command == "expensive_in_type") {
            ///
        } else if (command == "max_price_in_type") {
           ///

        } else if (command == "expensive") {
            handleExpensive();

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

void MyTcpServer::handleMaxPrice()
{
    QString filePath = "products.csv"; // Путь к CSV-файлу
    QList<QStringList> products; // Список товаров из CSV-файла

    // Открываем CSV-файл для чтения
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // Создаем поток для чтения CSV-файла
        QTextStream in(&file);
        while (!in.atEnd())
        {
            // Читаем строку из CSV-файла
            QString line = in.readLine();

            // Разделяем строку на поля с помощью разделителя (например, запятая)
            QStringList fields = line.split(',');

            // Добавляем поля в список товаров
            products.append(fields);
        }

        file.close();
    }
    else
    {
        qDebug() << "Failed to open file:" << file.errorString();
        return;
    }

    // Находим самые дорогие товары
    double maxPrice = 0.0;
    QStringList maxPriceProducts;

    for (const QStringList& product : products)
    {
        if (product.size() >= 2)
        {

            double price = product[2].toDouble();
            if (price > maxPrice)
            {
                maxPrice = price;
                maxPriceProducts = product;
            }
        }
    }

    // Выводим информацию о самых дорогих товарах
    qDebug() << "Max Price Products:";
    for (const QString& field : maxPriceProducts)
    {
        qDebug() << field;
    }
}


void MyTcpServer::handleExpensive()
{
    QString filePath = "products.csv"; // Путь к CSV-файлу
    QList<QStringList> products; // Список товаров из CSV-файла

    // Открываем CSV-файл для чтения
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file:" << file.errorString();
        return;
    }

    // Создаем поток для чтения CSV-файла
    QTextStream in(&file);
    while (!in.atEnd())
    {
        // Читаем строку из CSV-файла
        QString line = in.readLine();

        // Разделяем строку на поля с помощью разделителя (например, запятая)
        QStringList fields = line.split(',');

        // Добавляем поля в список товаров
        products.append(fields);
    }

    file.close();

    // Вычисляем среднюю цену всех товаров
    double averagePrice = 0.0;
    int count = 0;

    for (const QStringList& product : products)
    {
        if (product.size() >= 2)
        {
            bool ok;
            double price = product[2].toDouble(&ok);
            if (ok)
            {
                averagePrice += price;
                count++;
            }
        }
    }

    if (count > 0)
    {
        averagePrice /= count;

        // Выводим товары, дороже средней цены
        qDebug() << "Expensive Products:";
        for (const QStringList& product : products)
        {
            if (product.size() >= 2)
            {
                bool ok;
                double price = product[2].toDouble();
                if (price > averagePrice)
                {
                    qDebug() << product.join(",");
                }
            }
        }
    }
    else
    {
        qDebug() << "No products found";
    }
}

