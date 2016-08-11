#pragma once

#include "MethodWidget.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private slots:
    void calculateTotalTime();

private:
    void setupMethodNames();
    void setupLayout();
    void setupConnections();

private:
    Ui::MainWindow *ui;
    MethodWidget explicitMethodWidget;
    MethodWidget implicitMethodWidget;
};
