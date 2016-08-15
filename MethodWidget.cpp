#include "MethodWidget.h"
#include <QtDebug>
#include "ui_MethodWidget.h"

MethodWidget::MethodWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MethodWidget)
    , solver_{nullptr}
{
    ui->setupUi(this);

    ui->resultTableView->setModel(&resultsModel_);

    setupConnections();
}

MethodWidget::~MethodWidget()
{
    delete ui;
}

void MethodWidget::setMethodName(const QString &name)
{
    ui->groupBox->setTitle(name);
}

void MethodWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MethodWidget::setupConnections()
{
    connect(ui->solveBtn, &QPushButton::clicked, this, &MethodWidget::solvePressed);
    connect(ui->solveBtn, &QPushButton::clicked, [&](){resultsModel_.setInputParameters(solver_->inputParameters());});
}

AbstractSolver *MethodWidget::solver() const
{
    return solver_.get();
}

void MethodWidget::setSolver(std::unique_ptr<AbstractSolver> solverPtr)
{
    solver_ = std::move(solverPtr);
    qDebug() << connect(solver_.get(), &AbstractSolver::solved, this, &MethodWidget::redirectResults);
}

void MethodWidget::redirectResults()
{
    resultsModel_.setResults(solver_->results());
}
