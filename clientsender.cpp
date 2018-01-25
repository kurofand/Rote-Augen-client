#include "clientsender.h"

ClientSender::ClientSender(QObject *parent) :
    QObject(parent)
{
    sok=new QTcpSocket(this);
	connect(sok, SIGNAL(readyRead()), this, SLOT(onSockReadyRead()));
    std::ifstream settingFile;
    try
    {
        settingFile.open("setting.ini");
        if(settingFile.is_open())
        {
            std::vector <QString> fileStrings;
            std::string line;
            while(getline(settingFile, line))
                if(line[0]!='#')
                    fileStrings.push_back(QString::fromStdString(line));
            if(fileStrings.size()==2)
            {
                this->host=fileStrings[0];
                this->port=fileStrings[1].toShort();
            }
        }
    }
    catch(...)
    {
        qDebug()<<"File read error";
    }
    sok->connectToHost(this->host, this->port);
}

void ClientSender::sendRequest(quint8 comm)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
	out<<(quint16)0;
    out<<comm;
    out<<" ";
    out.device()->seek(0);
	out<<(quint32)(block.size()-sizeof(quint32));
    sok->write(block);
}

void ClientSender::onSockReadyRead()
{
    QDataStream in(sok);
	qDebug()<<sok->bytesAvailable();
    if(blockSize==0)
    {
		if(sok->bytesAvailable()<(int)sizeof(quint16))
            return;
        in>>blockSize;
		qDebug()<<"block size now "<<blockSize;
    }
	if(sok->bytesAvailable()<(int)sizeof(quint16))
	{
		qDebug()<<sok->bytesAvailable();
				  qDebug()<<sizeof(quint16);
        return;
	}
    else
        blockSize=0;
    quint8 command;
    in>>command;
	qDebug()<<"Received command "<<command;
    switch(command)
    {
    case onSetClientName:
    {
        QString name;
        in>>name;
		qDebug()<<"request name";
		if(scrMain!=NULL)
		{
			qDebug()<<name;
            scrMain->setName(name);
		}
        break;
    }
    case onSetClientActive:
    {
        scrMain=new ScreenMain();
		connect(scrMain, SIGNAL(sendPicToSocket(QPixmap*)), this, SLOT(onSendPic(QPixmap*)));
		QString mes;
		in>>mes;
		if(scrMain)
		{
			QByteArray block;
			QDataStream out(&block, QIODevice::WriteOnly);
			out<<(quint32)0;
			out<<onClientAnswer;
			out<<true;
			out<<onRequestName;
			out.device()->seek(0);
			out<<(quint32)(block.size()-sizeof(quint32));
			sok->write(block);
		}
        break;
    }
	case onStartClient:
	{
		quint32 sec;
		in>>sec;
		QByteArray block;
		QDataStream out(&block, QIODevice::WriteOnly);
		out<<(quint32)0;
		if(sec!=0)
		{
			out<<onClientAnswer<<true<<onStartClient;
			scrMain->run(sec);
		}
		else
			out<<onClientAnswer<<false<<onStartClient;
		out.device()->seek(0);
		out<<(quint32)(block.size()-sizeof(quint32));
		sok->write(block);

		break;
	}
	case onClientDisable:
	{
		QString trash;
		in>>trash;
		QByteArray block;
		QDataStream out(&block, QIODevice::WriteOnly);
		out<<(quint32)0;
		out<<onClientAnswer;
		out<<scrMain->stop()<<onClientDisable;
		out.device()->seek(0);
		out<<(quint32)(block.size()-sizeof(quint32));
		sok->write(block);
		break;
	}
    }
}

void ClientSender::onSendPic(QPixmap *pic)
{
	qDebug()<<"send pic";
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);
	out<<(quint32)0;
	out<<onSendPicture;
	out<<*pic;
	out.device()->seek(0);
	out<<(quint32)(block.size()-sizeof(quint32));
	qDebug()<<(quint32)(block.size()-sizeof(quint32));
	sok->write(block);

}
