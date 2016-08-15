#include "AbstractSolver.h"
#include <QtDebug>

using arma::uword;

AbstractSolver::AbstractSolver()
    : inputParameters_{}
    , results_{}
{

}

InputParameters AbstractSolver::inputParameters() const
{
    return inputParameters_;
}

void AbstractSolver::setInputParameters(const InputParameters &inputParameters)
{
    inputParameters_ = inputParameters;
}

void AbstractSolver::echoResults() const
{
    std::cout << results_;
}

void AbstractSolver::clearResults()
{
    results_.clear();
}

void AbstractSolver::writeInitialField()
{
    const arma::uword nodeCount = static_cast<arma::uword>(inputParameters_.fragmentCount + 1);
    if (results_.is_empty() || results_.n_cols != nodeCount){
        results_.resize(1, nodeCount);
    }

    for (arma::uword i = 1; i < nodeCount - 1; ++i){
        results_.at(0, i) = 0;
    }
    writeBorderValues(0);
}

void AbstractSolver::writeLastTimeLayerInternalValues(const arma::vec &values)
{
    if (values.n_elem + 2 != results_.n_cols){
        qCritical() << "Wrong values vector size got";
        return;
    }

    arma::subview_row<double> rowView = results_.row(results_.n_rows - 1);
    for (uword i = 0; i < values.n_elem; ++i){
        rowView(i + 1) = values(i);
    }
}

void AbstractSolver::writeBorderValues(uword timeStepNumber)
{
    results_.at(timeStepNumber, 0) = leftBorderCondition();
    results_.at(timeStepNumber, results_.n_cols - 1) = rightBorderCondition();
}

void AbstractSolver::createTimeLayer()
{
    const uword newRowNumber = results_.n_rows;
    results_.resize(newRowNumber + 1, results_.n_cols);
    writeBorderValues(newRowNumber);
}

double AbstractSolver::coordinateStep() const
{
    return 1.0 / inputParameters_.fragmentCount;
}

double AbstractSolver::x(int nodeNumber) const
{
    return coordinateStep() * nodeNumber;
}

double AbstractSolver::at(uword row, uword column) const
{
    return results_(row, column);
}

double AbstractSolver::atLastRow(arma::uword column) const
{
    const uword row = results_.n_rows - 1;
    return at(row, column);
}

double AbstractSolver::atPreLastRow(arma::uword column) const
{
    const uword row = results_.n_rows - 2;
    return at(row, column);
}

double AbstractSolver::leftBorderCondition()
{
    return 0;
}

double AbstractSolver::rightBorderCondition()
{
    return 1.7281;
}

arma::mat AbstractSolver::results() const
{
    return results_;
}
