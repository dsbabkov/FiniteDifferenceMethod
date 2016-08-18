#include "ExplicitSolver.h"

using arma::uword;

ExplicitSolver::ExplicitSolver()
{

}

ExplicitSolver::~ExplicitSolver()
{

}

void ExplicitSolver::solve()
{
    clearResults();
    writeInitialField();

    for (int i = 1; i <= inputParameters().timeStepCount; ++i){
        createTimeLayer();
        computeLayer();
    }

    emit solved();
}

void ExplicitSolver::computeLayer()
{
    arma::vec intervalValues(static_cast<uword>(inputParameters().fragmentCount - 1));
    for (uword j = 1; j < static_cast<uword>(inputParameters().fragmentCount); ++j){
        intervalValues(j - 1) = computedValue(j);
    }
    writeLastTimeLayerInternalValues(intervalValues);
}

double ExplicitSolver::computedValue(arma::uword j) const
{
    double e = exp(x(static_cast<int>(j)));
    double u = atPreLastRow(j);
    return inputParameters().timeStep * ((1 + e) * d2UdX2(j) - dUdX(j) + e * (u + 1)) + u;
}

double ExplicitSolver::dUdX(arma::uword j) const
{
    return (atPreLastRow(j+1) - atPreLastRow(j-1)) / (2 * coordinateStep());
}

double ExplicitSolver::d2UdX2(arma::uword j) const
{
    return (atPreLastRow(j+1) - 2 * atPreLastRow(j) + atPreLastRow(j-1)) / pow(coordinateStep(), 2);
}
