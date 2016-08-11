#include "InputParameters.h"

InputParameters::InputParameters()
    : fragmentCount{}
    , timeStep{}
    , timeStepCount{}
{

}

InputParameters::InputParameters(int fragmentCount, double timeStep, int timeStepCount)
    : fragmentCount{fragmentCount}
    , timeStep{timeStep}
    , timeStepCount{timeStepCount}
{

}
