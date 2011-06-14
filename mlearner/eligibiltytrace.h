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

#ifndef ELIGIBILTYTRACE_H
#define ELIGIBILTYTRACE_H

#include <QList>

/**
 * @brief Implementation of smart eligibity traces
 * Eligibility trace matrix is a sparse matrix with lots of elements approx. equals to zero.
 * This class is implemented based on Sutton's idea (Intro RL Book) to keep track of non-zero traces
 * with help of inverse pointers.
 * The count of & pointers to non-zero traces are always memorized
 * The init/update/decay function update these pointers and the values.
 */
class CEligibiltyTrace
{
public:
    /**
     * @brief  The constructor initialize the eligiblity traces
     *
     * @param _maxSize The maximum (total) size of eligibility traces matrix
     * @param _maxNonZeroTraces The maximum number of non-zero traces to memorize
     * @param _minTreshhold The threshold for considering non-zero traces
     */
    CEligibiltyTrace(int _maxSize, int _maxNonZeroTraces, double _minTreshhold);
    ~CEligibiltyTrace();

    int getNumOfNonZeroTraces();
    int getIndexOfNonZeroTrace(int index);
    double getTrace(int index);
    double getNonZeroTrace(int index);

    void clearTrace(int index);
    void clearExistingTrace(int index, int loc);
    void decayTraces(double rate);
    void setTrace(int index, double val);

    void debug();

private:
    int size;
    double* traces;
    int* nonZeroTracesInverse;
    int* nonZeroTraces;
    double minTreshhold;
    int numOfNonZeroTraces;
    int maxNonZeroTraces;

    QList<int> indexOfNonZeroTraces;

    void increaseMinTrace();
};

#endif // ELIGIBILTYTRACE_H
