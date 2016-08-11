#include "AbstractSolver.h"

AbstractSolver::AbstractSolver()
{

}

InputParameters AbstractSolver::inputParameters() const
{
    return inputParameters_;
}

void AbstractSolver::setInputParameters(const InputParameters &inputParameters)
{
    inputParameters_ = inputParameters;
}
