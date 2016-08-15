#pragma once

#include "ISolver.h"
#include "InputParameters.h"
#include <armadillo>
#include <QObject>

class AbstractSolver: public QObject, public ISolver
{
    Q_OBJECT
public:
    AbstractSolver();

    InputParameters inputParameters() const;
    void setInputParameters(const InputParameters &inputParameters);
    void echoResults() const;

    arma::mat results() const;

signals:
    void solved() const;

protected:
    void clearResults();
    void writeInitialField();
    void writeLastTimeLayerInternalValues(const arma::vec &values);
    void createTimeLayer();

    double coordinateStep() const;
    double x(int nodeNumber) const;
    double at(arma::uword row, arma::uword column) const;
    double atLastRow(arma::uword column) const;
    double atPreLastRow(arma::uword column) const;

private:
    void writeBorderValues(arma::uword timeStepNumber);
    static double leftBorderCondition();
    static double rightBorderCondition();

private:
    InputParameters inputParameters_;
    arma::mat results_;
};
