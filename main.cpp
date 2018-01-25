#include "screenmain.h"
#include <QApplication>
#include "clientsender.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	ClientSender cs;

    return a.exec();
}
