#pragma once

#include "AbstractSolver.h"
#include <QObject>

struct SystemOfLinearEquations{
    arma::mat matrix;
    arma::vec vector;
};


class ImplicitSolver: public AbstractSolver
{
    Q_DISABLE_COPY(ImplicitSolver)

public:
    ImplicitSolver();
    virtual ~ImplicitSolver() override;

    virtual void solve() override;

private:
    SystemOfLinearEquations makeSystemOfLinearEquations() const;
    arma::vec subDiagonal() const;
    arma::vec mainDiagonal() const;
    arma::vec superDiagonal() const;
    arma::vec answer() const; // TODO: переименовать. Это ветор констант в СЛАУ d без учёта ГУ
};
