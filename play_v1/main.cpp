#include "widget.h"
#include "connection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!CreatConnection())
        return 1;

    Widget w;
    w.setWindowIcon(QIcon(":/image/image/cloudmusic.png"));
    w.setWindowTitle("XinMusic");
    w.setWindowFlag(Qt::FramelessWindowHint);
    //w.resolve_lrc("123");
    w.show();

    return a.exec();
}
