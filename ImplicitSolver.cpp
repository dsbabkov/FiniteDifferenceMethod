#include "ImplicitSolver.h"
#include "TridiagonalMatrixAlgorithm.h"
#include <iostream>

using arma::uword;

ImplicitSolver::ImplicitSolver()
    : leftAnswerRatio{}
    , rightAnswerRatio{}
{

}

ImplicitSolver::~ImplicitSolver()
{

}

void ImplicitSolver::solve()
{
    clearResults();
    writeInitialField();
    computeAnswerRatios();

    const arma::mat &tdm = tridiagonalMatrix();

    for (int i = 1; i <= inputParameters().timeStepCount; ++i){
        createTimeLayer();
        const arma::vec &internalValues = solveTridiagonal(tdm, answer());
        writeLastTimeLayerInternalValues(internalValues);
    }
    emit solved();
}

void ImplicitSolver::computeAnswerRatios()
{
    leftAnswerRatio = -subDiagonal()(0);
    rightAnswerRatio = -superDiagonal().tail(1)(0); //last in superDiagonal
}

arma::mat ImplicitSolver::tridiagonalMatrix() const
{
    const arma::vec &a = subDiagonal();
    const arma::vec &b = mainDiagonal();
    const arma::vec &c = superDiagonal();

    arma::mat result(b.n_elem, b.n_elem);
    result.zeros();

    const uword lastNodeNumber = b.n_elem - 1;
    for (uword j = 1; j < lastNodeNumber; ++j){
        result(j, j - 1) = a(j);
        result(j, j) = b(j);
        result(j, j + 1) = c(j);
    }

    result(0, 0) = b(0);
    result(0, 1) = c(0);

    result(lastNodeNumber, lastNodeNumber - 1) = a(lastNodeNumber);
    result(lastNodeNumber, lastNodeNumber) = b(lastNodeNumber);

    return result;
}

arma::vec ImplicitSolver::subDiagonal() const
{
    uword internalNodeCount = static_cast<uword>(inputParameters().fragmentCount - 1);
    arma::vec result(internalNodeCount);

    for (uword i = 0; i < internalNodeCount; ++i){
        double e = exp(x(static_cast<int>(i) + 1));
        double tmp = (1 + e);
        double coostep = coordinateStep();
        tmp /= pow(coostep, 2);
        tmp += 0.5 / coordinateStep();
        result(i) = tmp;
    }
    return result;

}

arma::vec ImplicitSolver::mainDiagonal() const
{
    uword internalNodeCount = static_cast<uword>(inputParameters().fragmentCount - 1);
    arma::vec result(internalNodeCount);

    for (uword i = 0; i < internalNodeCount; ++i){
        double e = exp(x(static_cast<int>(i) + 1));
        result(i) = -(2 * (1 + e) / pow(coordinateStep(), 2) + e + 1 / inputParameters().timeStep);
    }
    return result;
}

arma::vec ImplicitSolver::superDiagonal() const
{
    uword internalNodeCount = static_cast<uword>(inputParameters().fragmentCount - 1);
    arma::vec result(internalNodeCount);

    for (uword i = 0; i < internalNodeCount; ++i){
        double e = exp(x(static_cast<int>(i) + 1));
        result(i) = (1 + e) / pow(coordinateStep(), 2) - 1.0 / (2 * coordinateStep());
    }
    return result;
}

arma::vec ImplicitSolver::answer() const
{
    uword internalNodeCount = static_cast<uword>(inputParameters().fragmentCount - 1);
    arma::vec result(internalNodeCount);

    for (uword i = 0; i < internalNodeCount; ++i){
        double e = exp(x(static_cast<int>(i) + 1));
        result(i) = -atPreLastRow(i + 1) / inputParameters().timeStep + e;
    }


    result(0) += leftAnswerRatio * atLastRow(0);
    result(internalNodeCount - 1) += rightAnswerRatio * atLastRow(static_cast<uword>(inputParameters().fragmentCount));

    return result;
}
