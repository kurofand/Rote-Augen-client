#include "screenmain.h"
#include <QApplication>
#include "clientsender.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    ScreenMain w;
	ClientSender cs;

//	w.show();
//    w.setVisible(false);
//    w.run(5);

    return a.exec();
}
