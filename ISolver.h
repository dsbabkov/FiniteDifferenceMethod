#pragma once

class ISolver
{
public:
    virtual ~ISolver();

    virtual void solve() = 0;
};
