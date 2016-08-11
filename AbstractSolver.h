#pragma once

#include "ISolver.h"
#include "InputParameters.h"

class AbstractSolver: public ISolver
{
public:
    AbstractSolver();

    InputParameters inputParameters() const;
    void setInputParameters(const InputParameters &inputParameters);

private:
    InputParameters inputParameters_;
};
