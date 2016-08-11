#pragma once

#include "AbstractSolver.h"
#include <QObject>

class ImplicitSolver: public AbstractSolver
{
    Q_DISABLE_COPY(ImplicitSolver)

public:
    ImplicitSolver();
    virtual ~ImplicitSolver() override;

    virtual void solve() override;
};
