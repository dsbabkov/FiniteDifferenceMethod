#pragma once

#include "AbstractSolver.h"

class ImplicitSolver: public AbstractSolver
{
    Q_OBJECT
    Q_DISABLE_COPY(ImplicitSolver)

public:
    ImplicitSolver();
    virtual ~ImplicitSolver() override;

    virtual void solve() override;

private:
    void computeAnswerRatios();
    arma::mat tridiagonalMatrix() const;
    arma::vec subDiagonal() const;
    arma::vec mainDiagonal() const;
    arma::vec superDiagonal() const;
    arma::vec answer() const; // TODO: переименовать. Это ветор констант в СЛАУ d

private:
    double leftAnswerRatio;
    double rightAnswerRatio;
};
