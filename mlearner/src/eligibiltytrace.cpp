/*
mLearner - Qt based continues state space reinforcement learning library
Copyright (C) 2011, Mani Monajjemi (www.manionline.org)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "eligibiltytrace.h"

#include <QDebug>

CEligibiltyTrace::CEligibiltyTrace(int _maxSize, int _maxNonZeroTraces, double _minTreshhold)
{
    this->size = _maxSize;
    this->minTreshhold = _minTreshhold;
    this->maxNonZeroTraces = _maxNonZeroTraces;

    traces = new double[this->size];
    nonZeroTraces = new int[this->maxNonZeroTraces];
    nonZeroTracesInverse = new int[this->size];

    for (int i = 0; i < size; i++)
    {
        traces[i] = 0.0;
    }

    numOfNonZeroTraces = 0;
}

CEligibiltyTrace::~CEligibiltyTrace()
{
    //qDebug() << "Running Destructer of CEligibilityTrace()";
    delete [] traces;
    delete [] nonZeroTraces;
    delete [] nonZeroTracesInverse;
}

int CEligibiltyTrace::getNumOfNonZeroTraces()
{
    return numOfNonZeroTraces;
}

int CEligibiltyTrace::getIndexOfNonZeroTrace(int index){
    return nonZeroTraces[index];
}

double CEligibiltyTrace::getTrace(int index)
{
    return traces[index];
}

double CEligibiltyTrace::getNonZeroTrace(int index)
{
    return traces[nonZeroTraces[index]];
}

void CEligibiltyTrace::clearTrace(int index)
{
    if (!(traces[index] == 0.0))
    {
        clearExistingTrace(index , nonZeroTracesInverse[index]);
    }
}

void CEligibiltyTrace::clearExistingTrace(int index, int loc)
{
    traces[index] = 0.0;
    numOfNonZeroTraces--;
    nonZeroTraces[loc] = nonZeroTraces[numOfNonZeroTraces];
    nonZeroTracesInverse[nonZeroTraces[loc]] = loc;
}

void CEligibiltyTrace::decayTraces(double rate)
{
    for (int loc = numOfNonZeroTraces - 1; loc >= 0; loc--)
    {
        int f = nonZeroTraces[loc];
        traces[f] *= rate;
        if (traces[f] < minTreshhold)
        {
            clearExistingTrace(f,loc);
        }
    }
}

void CEligibiltyTrace::setTrace(int index, double val)
{
    if (traces[index] >= minTreshhold)
    {
        traces[index] = val;         // trace already exists
    }
    else
    {
        while (numOfNonZeroTraces >= maxNonZeroTraces)
        {
            increaseMinTrace(); // ensure room for new trace
        }
       traces[index] = val;
       nonZeroTraces[numOfNonZeroTraces] = index;
       nonZeroTracesInverse[index] = numOfNonZeroTraces;
       numOfNonZeroTraces++;
    }
}

void CEligibiltyTrace::increaseMinTrace()
{
    minTreshhold += (0.1 * minTreshhold);
    qDebug() << "Changing Minimum Trace Treshhold to : " << minTreshhold;
    for (int loc = numOfNonZeroTraces - 1; loc >= 0; loc--)
    {
        int f = nonZeroTraces[loc];
        if (traces[f] < minTreshhold) clearExistingTrace(f,loc);
    }
}

void CEligibiltyTrace::debug()
{
    qDebug() << "Num Of Non Zero Traces : " << numOfNonZeroTraces;

    for (int i = 0; i < numOfNonZeroTraces; i++)
    {
        qDebug() << i << nonZeroTraces[i] << traces[nonZeroTraces[i]];
    }
}
