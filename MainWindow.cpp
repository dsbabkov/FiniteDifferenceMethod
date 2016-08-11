#include "ExplicitSolver.h"
#include "ImplicitSolver.h"
#include "MainWindow.h"
#include <QSplitter>
#include <QtDebug>
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupMethodNames();
    setupLayout();
    setupConnections();
    setupSolvers();
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

void MainWindow::solveExplicit()
{
    solve(explicitMethodWidget.solver());
}

void MainWindow::solveImplicit()
{
    solve(implicitMethodWidget.solver());
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

    connect(&explicitMethodWidget, &MethodWidget::solvePressed, this, &MainWindow::solveExplicit);
    connect(&implicitMethodWidget, &MethodWidget::solvePressed, this, &MainWindow::solveImplicit);
}

void MainWindow::setupSolvers()
{
    explicitMethodWidget.setSolver(std::make_unique<ExplicitSolver>());
    implicitMethodWidget.setSolver(std::make_unique<ImplicitSolver>());
}

InputParameters MainWindow::inputParameters() const
{
    return{
        ui->fragmentCountSpn->value(),
        ui->timeStepSpn->value(),
        ui->timeStepCountSpn->value()
    };
}

void MainWindow::solve(AbstractSolver *solver)
{
    qDebug() << "Calculation started";
    solver->setInputParameters(inputParameters());
    solver->solve();
    qDebug() << "Calculation finished";
}
