#include "samplewindow.h"

#include <QApplication>
#include <qt-easy-logger/logger.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 格式化输出：https://github.com/hanjianqiao/qt-easy-logger
    qInstallMessageHandler(h::Logger::messageHandler);

    SampleWindow w;
    w.show();
    return a.exec();
}
