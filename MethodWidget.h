#pragma once

#include <QWidget>
#include <AbstractSolver.h>
#include "ResultsModel.h"
#include <memory>

namespace Ui {
class MethodWidget;
}

class MethodWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MethodWidget(QWidget *parent = nullptr);
    ~MethodWidget();

    void setMethodName(const QString &name);

    AbstractSolver *solver() const;
    void setSolver(std::unique_ptr<AbstractSolver> solverPtr);

signals:
    void solvePressed() const;

private slots:
    void redirectResults();

protected:
    void changeEvent(QEvent *e);

private:
    void setupConnections();

private:
    Ui::MethodWidget *ui;
    std::unique_ptr<AbstractSolver> solver_;
    ResultsModel resultsModel_;
};
