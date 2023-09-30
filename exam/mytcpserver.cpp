#include "mytcpserver.h"

QStringList login_pass = {"123++123"};
QVector<int> code = {0};

MyTcpServer::~MyTcpServer()
{
    mTcpServer->close();
    server_status=0;
}

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,
            this,&MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any,33333))
        qDebug() << "Dead";
    else{
        server_status=1;
        qDebug()<<"Not dead";
    }
}

void MyTcpServer::slotNewConnection()
{
    if (liveclients == 4) {
        return;
    }
    QTcpSocket * curr_Socket;
    curr_Socket = mTcpServer->nextPendingConnection();
    connect(curr_Socket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
    connect(curr_Socket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
    liveclients++;
    mTcpSocket.append(curr_Socket);
}

void MyTcpServer::slotServerRead(){


    QByteArray massive;
    QString clientask, serveranswer;
    int k=0,t=0;
    QTcpSocket *curr_Socket = (QTcpSocket*)sender();
    QStringList bufer;
    int random;
    while(curr_Socket->bytesAvailable()>0){
        massive = curr_Socket->readAll();
        clientask.append(massive);
    }
    massive.clear();
    for(int i = 0; i<mTcpSocket.size();i++){
        if(curr_Socket == mTcpSocket.at(i)){
            break;
        }
        k++;
    }

    serveranswer = clientask.trimmed();
    bufer = serveranswer.split(";");
    bufer.append(0);


    if(bufer[0]=="auth")
    {
        for(int i = 0; i<login_pass.size();i++)
        {
            QString buf2=login_pass[i];

            QStringList login=buf2.split("++");
            if (bufer[1]==login.at(0) && bufer[2]==login.at(1) && code.at(i)==0){
                serveranswer.clear();
                serveranswer.append("code:");

                random = rand() % 100+1;
                code[i]=random;
                serveranswer.append(QString::number(random));
                t++;
            }

            else if(bufer[1]==login.at(0) && bufer[2]==login.at(1) && bufer.at(3).toInt()==code.at(i))
            {
                serveranswer.clear();
                code[i]=0;
                t=i;
                serveranswer.append("auth+");

            }
            else
            {
                serveranswer.clear();
                code[i]=0;
                serveranswer.append("auth-");
            }
        }
    }
    else if(bufer[0]=="reg")
    {
        int p=0;
        for(int i = 0; i<login_pass.size();i++)
        {
            QString buf2=login_pass[i];

            QStringList login=buf2.split("++");
            if(bufer[1]==login.at(0) && bufer[2]==login.at(1))
            {
                serveranswer.clear();
                serveranswer.append("reg-");
                p=1;
                break;
            }

        }
        if(p==0){
            login_pass.append(bufer[1]+"++"+bufer[2]);
            code.append(0);
            serveranswer.clear();
            serveranswer.append("reg+");
        }

    }
    else if(bufer[0]=="querry"){
        //fun
    }

    sendToClient(k, serveranswer + "\n\r");

}

void MyTcpServer::sendToClient(int pos, QString otvet)
{
    for(int i = 0; i<mTcpSocket.size();i++)
    {
        if (i == pos){
            mTcpSocket[i]->write(otvet.toUtf8());
        }

    }

}

void MyTcpServer::slotClientDisconnected()
{
    QTcpSocket *curr_Socket = (QTcpSocket*)sender();

    for(int i = 0; i<mTcpSocket.count();i++){
        if(curr_Socket == mTcpSocket.at(i)){
            mTcpSocket.removeAt(i);
            qDebug()<<"slot delete";
            break;
        }
    }
}
