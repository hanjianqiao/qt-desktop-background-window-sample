#ifndef SAMPLEWINDOW_H
#define SAMPLEWINDOW_H

#include <QWidget>
#include <qt-frameless-window/framelesswindow.h>

class SampleWindow : public h::FramelessWindow
{
    Q_OBJECT

public:
    SampleWindow(QWidget *parent = nullptr);
    ~SampleWindow();

};
#endif // SAMPLEWINDOW_H
