#include "screenmain.h"
#include "ui_screenmain.h"
//я решил, что лучше будет перетащить создание класса скриншотов в сокет - так будет явно проще
//контролировать его командами от сервера
//вопрос только в том как теперь передать команду серверу, хотя если сделать статик функцию,
//то сокрее всего можно будет вызвать напрямую
ScreenMain::ScreenMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ScreenMain)
{
    ui->setupUi(this);
    timer=new QTimer();
    timer->setSingleShot(false);
    connect(timer,SIGNAL(timeout()),this,SLOT(take()));
    name="local";//name will receive from server
    //окромя всего тут надо будет отправить запрос серверу на получение от него интервала

}

ScreenMain::~ScreenMain()
{
    delete ui;
}

void ScreenMain::run(quint32 interval)
{
/*    if(timer->isActive())
		timer->stop();*/
	this->stop();
    timer->setInterval(interval*1000);
    timer->start();
}

bool ScreenMain::stop()
{
	try
	{
		if(timer->isActive())
		{
			timer->stop();
			return true;
		}
		else
			return false;
	}
	catch(...)
	{
		return false;
	}
}

void ScreenMain::setName(QString name)
{
    this->name=name;
}

void ScreenMain::take()
{
    pixmap=QPixmap::grabWindow(QApplication::desktop()->winId());
    QString format="png";
    QDateTime datetime=QDateTime::currentDateTime();
    QString fileName=QDir::currentPath()+"/"+name+datetime.toString()+"."+format;
    qDebug()<<fileName;
    if(!pixmap.isNull())
        if(pixmap.save(fileName, format.toAscii()))
		{
            qDebug()<<"success";
			QImage img;
			img.load(fileName, "PNG");
			emit(sendPicToSocket(img, datetime));
		}
        else
            qDebug()<<"failed";
}
