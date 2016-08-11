#include "MethodWidget.h"
#include "ui_MethodWidget.h"

MethodWidget::MethodWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MethodWidget)
{
    ui->setupUi(this);
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
