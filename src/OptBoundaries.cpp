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

#include "OptBoundaries.h"

namespace cppOpt
{

OptBoundaries::OptBoundaries()
{

}

//------------------------------------------------------------------------------

OptBoundaries::~OptBoundaries()
{

}

//------------------------------------------------------------------------------

void OptBoundaries::add_boundary(OPT_T min, OPT_T max, const std::string &name)
{
    OptBoundary temp(min, max, name);
    add_boundary(temp);
}

//------------------------------------------------------------------------------

void OptBoundaries::add_boundary(const OptBoundary &optBoundary)
{
    optBoundaries.push_back(optBoundary);
}

//------------------------------------------------------------------------------

std::string OptBoundaries::to_string() const
{
    std::string out("");

    for(const auto &boundary : optBoundaries)
        out += boundary.name + " ";

    return out;
}

//------------------------------------------------------------------------------

size_t OptBoundaries::size() const
{
    return optBoundaries.size();
}

//------------------------------------------------------------------------------

std::vector<OptBoundary>::iterator OptBoundaries::begin()
{
    return optBoundaries.begin();
}

//------------------------------------------------------------------------------

std::vector<OptBoundary>::iterator OptBoundaries::end()
{
    return optBoundaries.end();
}

//------------------------------------------------------------------------------

const std::vector<OptBoundary>::const_iterator OptBoundaries::cbegin() const
{
    return optBoundaries.cbegin();
}

//------------------------------------------------------------------------------

const std::vector<OptBoundary>::const_iterator OptBoundaries::cend() const
{
    return optBoundaries.cend();
}

//------------------------------------------------------------------------------

} // namespace cppOpt
