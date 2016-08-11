#include "MainWindow.h"
#include <QSplitter>
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupMethodNames();
    setupLayout();
    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::calculateTotalTime()
{
    ui->totalTimeLbl->setText(QString::number(ui->timeStepSpn->value() * ui->timeStepCountSpn->value()));
}

void MainWindow::setupMethodNames()
{
    explicitMethodWidget.setMethodName("Явная схема");
    implicitMethodWidget.setMethodName("Неявная схема");
}

void MainWindow::setupLayout()
{
    QSplitter *splitter = new QSplitter(this);
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    splitter->addWidget(&implicitMethodWidget);
    splitter->addWidget(&explicitMethodWidget);
    ui->mainLayout->addWidget(splitter, ui->mainLayout->rowCount(), 0, 1, ui->mainLayout->columnCount());

    splitter->setContentsMargins(0, 0, 0, 0);
}

void MainWindow::setupConnections()
{
    connect(ui->timeStepSpn, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &MainWindow::calculateTotalTime);
    connect(ui->timeStepCountSpn, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::calculateTotalTime);
}
