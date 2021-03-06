/*
    Copyright (c) 2015 Martin Buck
    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation the rights to
    use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
    and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
    DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
    OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
  * \brief first example showing the usage of the threshold accepting algorithm
  *        to find the minimum of x^2
  */

#include <cmath>
#include <iostream>

#include "cppOpt.h"

using namespace cppOpt;

//define your own calculation
auto toOptimize = [](OptCalculation<double>& optCalculation) {
    //defined x^2 as function to be optimised
    optCalculation.result = pow(optCalculation.get_parameter("X"), 2);
};

using namespace std;

int main() {
    //setup the optimisation
    //define your boundaries
    OptBoundaries<double> optBoundaries;
    optBoundaries.add_boundary({-5.0, 5.0, "X"});

    //number of calculations
    unsigned int maxCalculations = 300;

    //we want to find the minimum
    OptTarget optTarget = OptTarget::MINIMIZE;

    //how fast the algorithm slows down
    //http://comisef.wikidot.com/concept:thresholdaccepting
    double coolingFactor = 0.95;

    //the starting threshold
    //should be somewhere close to the difference of BEST_VALUE - WORST_VALUE
    //so 25 - 0 => 25 => 20 in this case
    //http://comisef.wikidot.com/concept:thresholdaccepting
    double threshold = 20;

    //how much the threshold changes each iteration
    //should be similar to the cooling factor
    //http://comisef.wikidot.com/concept:thresholdaccepting
    double thresholdFactor = 0.92;

    //define your coordinator
    OptCoordinator<double, false> coordinator(
        maxCalculations,
        toOptimize,
        optTarget,
        0);

    //add threshold accepting as child
    coordinator.add_child(make_unique<OptThresholdAccepting<double>>(
        optBoundaries,
        optTarget,
        0,
        coolingFactor,
        threshold,
        thresholdFactor));

    //let's go
    coordinator.run_optimisation();

    //print result
    OptCalculation<double> best = coordinator.get_best_calculation();
    cout << best.to_string_header() << endl;
    cout << best.to_string_values() << endl;

    return 0;
}
