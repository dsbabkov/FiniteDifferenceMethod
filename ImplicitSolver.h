#pragma once

#include "AbstractSolver.h"

struct SystemOfLinearEquations{
    arma::mat matrix;
    arma::vec vector;
};


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
    SystemOfLinearEquations makeSystemOfLinearEquations() const;
    arma::mat tridiagonalMatrix() const;
    arma::vec subDiagonal() const;
    arma::vec mainDiagonal() const;
    arma::vec superDiagonal() const;
    arma::vec answer() const; // TODO: переименовать. Это ветор констант в СЛАУ d без учёта ГУ

private:
    double leftAnswerRatio;
    double rightAnswerRatio;
};
