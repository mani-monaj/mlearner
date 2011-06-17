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

#include "mtileqlearner.h"

#include <QDebug>

MTileQLearner::MTileQLearner()
{
}

void MTileQLearner::newEpisode()
{
    e->decayTraces(0.0);
    loadF();
    loadQ();
}

void MTileQLearner::beforeStep()
{
    if (withProbability(epsilon))
    {
        action.val = rand() % action.numOfSingletons;
        e->decayTraces(0.0);
    }
    else
    {
        action.val = argMax();
        e->decayTraces(discountFactor * etLambda);
    }


    // Optionally clear other traces
    for (int a = 0; a < action.numOfSingletons; a++)
        if (a != action.val)
            for (int j = 0; j < numOfTiles; j++) e->clearTrace(F[a][j]);

    for (int j=0; j < numOfTiles; j++)
    {
        //e[F[action.val][j]] += 1.0; // accumulating traces
        e->setTrace(F[action.val][j], 1.0);
        //e[F[action.val][j]] = 1.0; // replace traces
    }
}

void MTileQLearner::afterStep()
{
    ; // Clean again!
}

void MTileQLearner::step(double reward, bool isTerminal, bool useRewardModel)
{
    loadF();

    if (useRewardModel)
    {
        updateRewardModel(action.val, reward);
        loadRewardModel(action.val);
        //qDebug() << "New Reward for this State-Action Pair  Is: " << rewardExpectedVal[action.val];

        reward = rewardExpectedVal[action.val];
    }

    double delta = reward - Q[action.val];


    loadQ();

    action.val = argMax();

    if (!isTerminal) delta += discountFactor * Q[action.val];

    float temp = (learningRate / numOfTiles) * delta;
    for (int i = 0; i < e->getNumOfNonZeroTraces(); i++)                 // update theta (learn)
    {
        theta[e->getIndexOfNonZeroTrace(i)] += (temp * e->getNonZeroTrace(i));
    }

    loadQ(action.val);

}

void MTileQLearner::stepExploit()
{
    loadF();
    loadQ();
    action.val = decide(0.0);
}


