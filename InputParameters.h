#pragma once

struct InputParameters
{
    InputParameters();
    InputParameters(int fragmentCount, double timeStep, int timeStepCount);

    int fragmentCount;
    double timeStep;
    int timeStepCount;
};
