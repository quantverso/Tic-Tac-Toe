#ifndef QUANTVERSO_CLOCK_H
#define QUANTVERSO_CLOCK_H

//--------------------------------------------------------------------------------------------------

#include <chrono>

using namespace std::chrono;
using Time = time_point<high_resolution_clock>;
using Elapsed = duration<float>;

//--------------------------------------------------------------------------------------------------

class Clock
{
public:
    float ElapsedTime();
    float Count();
    void Reset();

private:
    Time    first{ high_resolution_clock::now() };
    Time    last{ first };
    Time    current{ first };
    Elapsed elapsed{ Elapsed::zero() };
};

//--------------------------------------------------------------------------------------------------

inline float Clock::ElapsedTime()
{
    elapsed = Elapsed((current = high_resolution_clock::now()) - last);
    last = current;
    return elapsed.count();
}

//--------------------------------------------------------------------------------------------------

inline float Clock::Count()
{
    elapsed = Elapsed(high_resolution_clock::now() - first);
    return elapsed.count();
}

//--------------------------------------------------------------------------------------------------

inline void Clock::Reset()
{
    first = high_resolution_clock::now();
}

//--------------------------------------------------------------------------------------------------

#endif
