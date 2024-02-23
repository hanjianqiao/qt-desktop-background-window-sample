#include <QApplication>
#include <QStyle>
#include <QScreen>
#include <QMovie>
#include <QVBoxLayout>
#include <qt-desktop-background-window/desktopbackgroundwindow.h>
#include "samplewindow.h"

SampleWindow::SampleWindow(QWidget *parent)
    : FramelessWindow(parent)
{
    // 设置无边框窗口：https://github.com/hanjianqiao/qt-frameless-window
    h::FramelessWindowTitleBarControlWidget *titleBarControlWidget = new h::FramelessWindowTitleBarControlWidget(this);
    h::FramelessWindowTitleBar *titleBar = new h::FramelessWindowTitleBar(
        new h::FramelessWindowTitleBarContentWidget(
            "自定义壁纸例子",
            QApplication::style()->standardIcon(QStyle::SP_ComputerIcon),
            this),
        titleBarControlWidget,
        titleBarControlWidget->maximizeButton()
        );
    setTitleBar(titleBar);
    setMaximizeButton(titleBarControlWidget->maximizeButton());
    QVBoxLayout *rootLayout = new QVBoxLayout(this);
    rootLayout->addWidget(titleBar);    // 自定义标题栏，要求标题栏也是widget的一部分，所以需要添加到窗体布局合适位置
    // rootLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Preferred, QSizePolicy::MinimumExpanding));
    rootLayout->setContentsMargins(0, 0, 0, 0);
    QWidget *contentContainer = new QWidget(this);
    QVBoxLayout *contentContainerLayout = new QVBoxLayout(contentContainer);
    contentContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rootLayout->addWidget(contentContainer);

    QPushButton *exitButton = new QPushButton("退出请按我，强制退出有BUG！", this);
    contentContainerLayout->addWidget(exitButton);
    QObject::connect(exitButton, &QPushButton::clicked, this, [](){
        qApp->exit(0);
    });


    // 初始化
    h::DesktopBackgroundWindowManager::initialize();
    auto dbwm = h::DesktopBackgroundWindowManager::singleton();

    // 支持多屏幕，给每个屏幕设置壁纸
    auto screens = dbwm->screens();
    for(const auto &screen : screens){
        QLabel *label = new QLabel(nullptr);
        label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        // 将label设置为背景widget
        dbwm->setScreenBackgroundWidget(screen, label);

        // 1、 加载静态图片
        // label->setPixmap(QPixmap(":/images/robot.jpg").scaled(label->size(), Qt::IgnoreAspectRatio));

        // 2、 加载动图
        QMovie *movie = new QMovie(":/images/rainbowCat.gif");
        movie->setScaledSize(label->size());
        label->setMovie(movie);
        movie->start();
    }

}

SampleWindow::~SampleWindow() {}
