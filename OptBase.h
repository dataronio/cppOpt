#ifndef OPTBASE_H
#define OPTBASE_H

#include <vector>
#include <mutex>
#include <queue>
#include <limits>

#include "defines.h"
#include "OptValue.h"
#include "OptBoundary.h"

#ifdef DEBUG
    #include <iostream>
#endif

//class OptValue; //forward reference


class OptBase
{
private:
    ///@todo all static members need a mutex
    static std::mutex
        mutexQueueTodo,
        mutexQueueCalculated,
        mutexQueueFinished;

    static std::queue<OptValue>
        queueTodo,
        queueCalculated,
        queueFinished;

    std::mutex
        mutexPreviousCalculations;

protected:

    std::vector<OptValue>
        previousCalculations;

    OptValue
        bestCalculation;

    const std::vector<OptBoundary>
        optBoundaries;

    const unsigned int
        maxCalculations;

    unsigned int
        currentCalculation;

    const OptTarget
        optTarget;

    T
        targetValue;



    virtual OptValue get_next_value() = 0;

public:
    ///@todo OptValues should be OptBoundaries
    OptBase(const std::vector<OptBoundary> &optBoundaries,
            unsigned int maxCalculations,
            OptTarget optTarget = MINIMIZE);
    ~OptBase();

    bool optimise(); ///@todo make it clear that this should be run in a loop

    void add_finished_calculation(const OptValue &optValue);

    T bad_value() const;

    bool result_better(const OptValue &result, const OptValue &other) const;

    ///@todo some / all of these should maybe be made private / protected
    static void push_todo(const OptValue &optValue);
    static void push_calculated(const OptValue &optValue);
    static void push_finished(const OptValue &optValue);

    static OptValue pop_todo();
    static OptValue pop_calculated();
    static OptValue pop_finished();
};

#endif // OPTBASE_H
