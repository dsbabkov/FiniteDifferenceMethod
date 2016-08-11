#pragma once

#include "InputParameters.h"
#include "MethodWidget.h"
#include <QMainWindow>
#include <QSettings>

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
    void solveExplicit();
    void solveImplicit();

private:
    void setupMethodNames();
    void setupLayout();
    void setupConnections();
    void setupSolvers();

    void loadSettings();
    void saveSettings();

    InputParameters inputParameters() const;

    void solve(AbstractSolver *solver);

private:
    Ui::MainWindow *ui;

    MethodWidget explicitMethodWidget;
    MethodWidget implicitMethodWidget;

    QSettings settings_;
};
