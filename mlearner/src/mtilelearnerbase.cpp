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

#include "mtilelearnerbase.h"

#include <QDebug>

MTileLearnerBase::MTileLearnerBase()
{
}

MTileLearnerBase::~MTileLearnerBase()
{
    //qDebug() << "Running Destructer of MTDLearnerTile()";
    delete Q;
    delete theta;

    for (int i = 0; i < action.numOfSingletons; i++)
    {
        delete [] F[i];
    }
    delete [] F;
    delete  e;

    delete rewardExpectedVal;
    delete rewardModelCount;
    delete rewardModelTheta;
}

void MTileLearnerBase::initLearner(unsigned int _tiles, double _discountFactor, double _learningRate, double _etLambda, double _epsilon, double _maxNonZeroTracesRatio, double _minTraceTreshhold)
{
    int i;
    numOfTiles = _tiles;
    maxNonZeroTracesRatio = _maxNonZeroTracesRatio;
    minTraceTreshhold = _minTraceTreshhold;
    setDiscountFacor(_discountFactor);
    setLearningRate(_learningRate);
    setLambda(_etLambda);
    setEpsilon(_epsilon);

    memorySize = numOfTiles;

    for (i = 0; i < this->numOfStateVars; i++)
    {
        memorySize = memorySize * this->stateVars[i].nSeg;
    }

    Q = new float[this->action.numOfSingletons];
    theta = new float[memorySize];

    F = new int*[action.numOfSingletons];
    for (i = 0; i < action.numOfSingletons; i++)
    {
        F[i] = new int[numOfTiles];
    }

    e = new CEligibiltyTrace(memorySize, (int) (maxNonZeroTracesRatio * memorySize), minTraceTreshhold);
    //e = new CEligibiltyTrace(memorySize, 1000, minTraceTreshhold);

    rewardExpectedVal = new float[this->action.numOfSingletons];
    rewardModelCount = new float[memorySize];
    rewardModelTheta = new float[memorySize];

    resetAllVars();

    loadF();
    loadQ();
}

// TODO: Reward Model
void MTileLearnerBase::initLearnerFromFile(QString fileName, bool quiet)
{
    if (!quiet)
    {
        qDebug() << "Reading input file " << fileName << "as MLearner Tile file...";
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Load Failed!";
        return;
    }
    QDataStream ds(&file);

    int type = readHeader(ds, quiet);

    if (type != _M_TYPE_TILE)
    {
        qDebug() << "Invalid File Type!";
        file.close();
        return;
    }

    qint32 _numOfTiles;
    double _discountFactor, _learningRate, _etLambda, _epsilon, _maxNZTR, _minTT;
    qlonglong _memorySize;

    ds >> _numOfTiles >> _discountFactor >> _learningRate >> _etLambda >> _epsilon >> _maxNZTR >> _minTT;

    if (!quiet)
    {
        qDebug() << "**** Summary ****";
        qDebug() << "Num Of Tiles : " << _numOfTiles;
        qDebug() << "Discount Factor : " << _discountFactor;
        qDebug() << "Learning Rate : " << _learningRate;
        qDebug() << "Labmda : " << _etLambda;
        qDebug() << "Epsilon : " << _epsilon;
        qDebug() << "Max Non Zero ET Ratio :" << _maxNZTR;
        qDebug() << "Min ET Threshold : " << _minTT;
    }

    initLearner(_numOfTiles, _discountFactor, _learningRate, _etLambda, _epsilon, _maxNZTR, _minTT);

    ds >> _memorySize;

    if (!quiet)
    {
        qDebug() << "Memory Size : " << _memorySize;
    }

    if (_memorySize != memorySize)
    {
        qDebug() << "Something critical is wrong in file!";
        file.close();
        return;
    }

    for (long int i = 0; i < memorySize; i++)
    {
        ds >> theta[i];
    }

    if (!quiet)
    {
        qDebug() << "File successfully loaded and the learner has been initialized.";
    }

    file.close();
}

void MTileLearnerBase::saveLearnerToFile(QString fileName, bool quiet)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Save Failed!";
        return;
    }
    QDataStream ds(&file);

    if (!quiet)
    {
        qDebug() << "Writing Tile Learner Date into : " << fileName;
    }
    /* Writing Header Commons(implemented in base) */
    saveHeader(ds, _M_TYPE_TILE, quiet);

    /* Writing Tile Learner specific Data */
    ds << (qint32) numOfTiles;
    ds << (double) discountFactor;
    ds << (double) learningRate;
    ds << (double) etLambda;
    ds << (double) epsilon;
    ds << (double) maxNonZeroTracesRatio;
    ds << (double) minTraceTreshhold;

    /* Writing Theta (Experience) */
    ds << (qlonglong) memorySize;

    for (long int i = 0; i < memorySize; i++)
    {
        ds << (double) theta[i];
    }

    file.close();

}

void MTileLearnerBase::resetAllVars()
{
    for (int i = 0; i < memorySize; i++)
    {
        theta[i] = 0.0;
        rewardModelTheta[i] = 0.0;
        rewardModelCount[i] = 0.0;
    }
    e->decayTraces(0.0);

}

int MTileLearnerBase::decide(double epsilon)
{
    int a = argMax();
    if (withProbability(epsilon)) a = rand() % action.numOfSingletons;
    return a;
}

void MTileLearnerBase::loadQ()
{
    for (int a = 0; a < action.numOfSingletons; a++)
    {
        Q[a] = 0.0;
        for (int j = 0; j < numOfTiles; j++)
        {
            Q[a] += theta[F[a][j]];
        }
    }
}

void MTileLearnerBase::loadQ(int a)
{
    Q[a] = 0.0;
    for (int j = 0; j < numOfTiles; j++)
    {
        Q[a] += theta[F[a][j]];
    }
}

void MTileLearnerBase::loadRewardModel(int a)
{
    rewardExpectedVal[a] = 0.0;
    for (int j = 0; j < numOfTiles; j++)
    {
        rewardExpectedVal[a] += rewardModelTheta[F[a][j]];
    }
}

void MTileLearnerBase::updateRewardModel(int a, double reward)
{

    loadRewardModel(a);
    //qDebug() << "Curren Reward for this State-Action Pair  Is: " << rewardExpectedVal[action.val];
    double count = 0.0;
    for (int j = 0; j < numOfTiles; j++)
    {
        count += rewardModelCount[F[a][j]];
    }

    count = count + 1.0;

    if (round(count) == 1.0)
    {
        for (int j = 0; j < numOfTiles; j++)
        {
            rewardModelTheta[F[a][j]] = reward / numOfTiles;
        }
    }
    else
    {

        double newval = (rewardExpectedVal[a] + ((reward - rewardExpectedVal[a]) / count)) /  numOfTiles;
        for (int j = 0; j < numOfTiles; j++)
        {
            rewardModelTheta[F[a][j]] =  newval;
        }
    }

    count = count / numOfTiles;
    for (int j = 0; j < numOfTiles; j++)
    {
        rewardModelCount[F[a][j]] = count;
    }

}

// Feature Set
void MTileLearnerBase::loadF()
{
    // Compute feature sets for current state
    float* state_vars = new float[numOfStateVars];
    for (int i = 0; i < numOfStateVars; i++)
    {
        state_vars[i] = (float) (stateVars[i].val / stateVars[i].width);
    }
    for (int a = 0; a < action.numOfSingletons; a++)
    {
        GetTiles(&F[a][0],numOfTiles,state_vars,numOfStateVars,memorySize,a);

    }

    delete state_vars;
}

// Returns index (action) of largest entry in Q array, breaking ties randomly
int MTileLearnerBase::argMax()
{
    int best_action = 0;
    float best_value = Q[0];
    int num_ties = 1;                    // actually the number of ties plus 1
    for (int a = 1; a < action.numOfSingletons; a++)
    {
        float value = Q[a];
        if (value >= best_value)
            if (value > best_value)
            {
                best_value = value;
                best_action = a;
            }
            else
            {
                num_ties++;
                if (0 == rand() % num_ties)
                {
                    best_value = value;
                    best_action = a;
                }
            }
    };
    return best_action;
}
