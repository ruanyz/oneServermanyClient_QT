#include "widget.h"
#include "client.h"
#include "form.h"
#include <QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    Form a1;
    Form a2;
    Form a3;
    a1.show();
    a2.show();
    a3.show();

    return a.exec();
}
