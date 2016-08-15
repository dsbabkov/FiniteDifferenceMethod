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
};
