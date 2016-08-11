#include "MethodWidget.h"
#include "ui_MethodWidget.h"

MethodWidget::MethodWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MethodWidget)
    , solver_{nullptr}
{
    ui->setupUi(this);
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
}

AbstractSolver *MethodWidget::solver() const
{
    return solver_.get();
}

void MethodWidget::setSolver(std::unique_ptr<AbstractSolver> solverPtr)
{
    solver_ = std::move(solverPtr);
}
