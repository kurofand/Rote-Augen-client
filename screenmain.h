#ifndef SCREENMAIN_H
#define SCREENMAIN_H

#include <QMainWindow>
#include <QTimer>
#include <QFileDialog>
#include <QDateTime>
#include <QDesktopWidget>
#include <QDebug>


namespace Ui {
class ScreenMain;
}

class ScreenMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit ScreenMain(QWidget *parent = 0);
    ~ScreenMain();
	void run(quint32 interval);
	bool stop();
    void setName(QString name);

private:
    Ui::ScreenMain *ui;
    QTimer *timer;
	QPixmap *pixmap;
    QString name;
private slots:
    void take();

signals:
	void sendPicToSocket(QPixmap *pic);

};

#endif // SCREENMAIN_H
