#include "screenmain.h"
#include "ui_screenmain.h"

ScreenMain::ScreenMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ScreenMain)
{
    ui->setupUi(this);
    timer=new QTimer();
    timer->setSingleShot(false);
    connect(timer,SIGNAL(timeout()),this,SLOT(take()));
    name="local";//name will receive from server
	pixmap=new QPixmap();
}

ScreenMain::~ScreenMain()
{
	delete pixmap;
    delete ui;
}

void ScreenMain::run(quint32 interval)
{
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
	*pixmap=QPixmap::grabWindow(QApplication::desktop()->winId());
	if(!pixmap->isNull())
		emit(sendPicToSocket(pixmap));
	else
		qDebug("Unexpected problems with screenshot");
}
