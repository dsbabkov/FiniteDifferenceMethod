#include "ImplicitSolver.h"

using arma::uword;

ImplicitSolver::ImplicitSolver()
{

}

ImplicitSolver::~ImplicitSolver()
{

}

void ImplicitSolver::solve()
{
    clearResults();
    writeInitialField();

    for (int i = 1; i <= inputParameters().timeStepCount; ++i){
        createTimeLayer();
        const SystemOfLinearEquations &tdm = makeSystemOfLinearEquations();
        const arma::vec &internalValues = arma::solve(tdm.matrix, tdm.vector);
        writeLastTimeLayerInternalValues(internalValues);
    }
    emit solved();
}

SystemOfLinearEquations ImplicitSolver::makeSystemOfLinearEquations() const
{
    SystemOfLinearEquations result;

    const arma::vec &a = subDiagonal();
    const arma::vec &b = mainDiagonal();
    const arma::vec &c = superDiagonal();
    const arma::vec &d = answer();

    result.matrix.set_size(b.n_elem, b.n_elem);
    result.matrix.zeros();
    result.vector = d;

    const uword lastNodeNumber = b.n_elem - 1;
    for (uword j = 1; j < lastNodeNumber; ++j){
        result.matrix(j, j - 1) = a(j);
        result.matrix(j, j) = b(j);
        result.matrix(j, j + 1) = c(j);
    }

    result.matrix(0, 0) = b(0);
    result.matrix(0, 1) = c(0);

    result.matrix(lastNodeNumber, lastNodeNumber - 1) = a(lastNodeNumber);
    result.matrix(lastNodeNumber, lastNodeNumber) = b(lastNodeNumber);

    result.vector(0) -= a(0) * atLastRow(0);
    result.vector(lastNodeNumber) -= c(lastNodeNumber) * atLastRow(static_cast<uword>(inputParameters().fragmentCount));

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
    return result;
}
