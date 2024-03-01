#ifndef SAMPLEWINDOW_H
#define SAMPLEWINDOW_H

#include <QWidget>
#include <qt-frameless-window/framelesswindow.h>

class MainBody : public QWidget
{
    Q_OBJECT
public:
    MainBody(QWidget *parent);
};

class SampleWindow : public h::FramelessWindow
{
    Q_OBJECT

public:
    SampleWindow(QWidget *parent = nullptr);
    ~SampleWindow();

};
#endif // SAMPLEWINDOW_H
