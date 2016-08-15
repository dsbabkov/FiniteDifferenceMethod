#pragma once

#include "AbstractSolver.h"
#include <QObject>

class ExplicitSolver: public AbstractSolver
{
    Q_OBJECT
    Q_DISABLE_COPY(ExplicitSolver)

public:
    ExplicitSolver();
    virtual ~ExplicitSolver() override;

    virtual void solve() override;

private:
    void computeLayer();
    double computedValue(arma::uword j) const;
    double dUdX(arma::uword j) const;
    double d2UdX2(arma::uword j) const;
};
