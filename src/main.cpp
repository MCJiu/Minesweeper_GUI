#include <include/mainwindow.h>

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("扫雷");
    w.setWindowIcon(QIcon(":/global/pic/icon.jpg"));
    w.show();
    return a.exec();
}
