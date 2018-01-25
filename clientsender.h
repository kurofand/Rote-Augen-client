#ifndef CLIENTSENDER_H
#define CLIENTSENDER_H

#include <QObject>
#include <QTcpSocket>
#include <fstream>
#include <vector>

#include "screenmain.h"
class ClientSender : public QObject
{
    Q_OBJECT
public:
	QString name;
    explicit ClientSender(QObject *parent = 0);

    void sendRequest(quint8 comm);
private:
	QTcpSocket *sok;
    QString host="127.0.0.1";
	quint16 port=111;//just unused port
	quint32 blockSize=0;
    ScreenMain *scrMain;
    static const quint8 onSetClientName=2;
    static const quint8 onSetClientActive=1;
    static const quint8 onClientDisable=3;
	static const quint8 onClientAnswer=4;
	static const quint8 onRequestName=5;
	static const quint8 onStartClient=6;
	static const quint8 onSendPicture=7;


private slots:
    void onSockReadyRead();
public slots:
	void onSendPic(QPixmap *pic);

};

#endif // CLIENTSENDER_H
