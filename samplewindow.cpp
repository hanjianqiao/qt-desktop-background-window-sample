#include <QApplication>
#include <QStyle>
#include <QScreen>
#include <QMovie>
#include <QVBoxLayout>
#include <qt-desktop-background-window/desktopbackgroundwindow.h>
#include "samplewindow.h"

MainBody::MainBody(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *rootLayout = new QVBoxLayout(this);
    QPushButton *exitButton = new QPushButton("退出请按我，强制退出有BUG！", this);
    rootLayout->addWidget(exitButton);
    QObject::connect(exitButton, &QPushButton::clicked, this, [](){
        qApp->exit(0);
    });

    // 初始化
    h::DesktopBackgroundWindowManager::initialize();
    auto dbwm = h::DesktopBackgroundWindowManager::singleton();

    // 支持多屏幕，给每个屏幕设置壁纸
    auto screens = dbwm->screens();
    for(const auto &screen : screens){
        /*
         * 当前版本，建议使用下面的顺序来创建。
         * 因为调用 void DesktopBackgroundWindowManager::setScreenBackgroundWidget(QScreen *toScreen, QWidget *w);
         * 这个函数之后，框架会把w指向的QWidget的size设置成与其相应的屏幕大小。
         * 这个时候向w内填充其他控件，能更好地匹配size
        */

        // 第一步，创建一个QWidget，是任意你想显示的内容
        QLabel *label = new QLabel(nullptr);
        label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


        // 第二步，将其设置为背景widget
        dbwm->setScreenBackgroundWidget(screen, label);

        // 第三步，初始化你的背景widget

        if(false){
            // 例子一：设置静态图片
            label->setPixmap(QPixmap(":/images/robot.jpg").scaled(label->size(), Qt::IgnoreAspectRatio));
        }else{
            // 例子二：设置动态图片
            QMovie *movie = new QMovie(":/images/rainbowCat.gif");
            movie->setScaledSize(label->size());
            label->setMovie(movie);
            movie->start();
        }

    }
}

SampleWindow::SampleWindow(QWidget *parent)
    : FramelessWindow(parent)
{
    QWidget *body = new MainBody(this);
    setTitleBarAndBodyWidget(new h::FramelessWindowDefaultTitleBar(this), body);
    resize(1024, 768);
}

SampleWindow::~SampleWindow() {}
