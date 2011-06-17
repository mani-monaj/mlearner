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

#include "mfuzzyaclearner.h"

MFuzzyACLearner::MFuzzyACLearner()
{
}

void MFuzzyACLearner::loadV()
{
    v = 0.0;
    for (int i = 0; i < numOfRules; i++)
    {
        v += (o[i] * phi[i]);
    }
}


// Virtual Functions

void MFuzzyACLearner::newEpisode()
{

    eCrtitic->decayTraces(0.0);
    for (int i = 0; i < action.numOfSingletons; i++)
    {
        eActor[i]->decayTraces(0.0);
    }

    loadFIS();
    loadPhi();
    loadV();
    updateAndSelectLocalActions(epsilon, noiseWeight);
    action.val = selectGlobalAction();

    // TODO : Should we reset some other vars like rulesLearningRates???


    for (int i = 0; i < numOfRules; i++)
    {
        ruleLearningRates[i] = learningRate;
    }


}

void MFuzzyACLearner::beforeStep()
{
    ;// Clean!
}

void MFuzzyACLearner::afterStep()
{
    updateAdaptiveLearningRates();
    updateAndSelectLocalActions(epsilon, noiseWeight);
    /* Based on Joufe[98] it is said to update ETs before
      Final Action Selection. But my method is better
      because it uses replace traces
      Needs more tests
    */         
    action.val = selectGlobalAction();
    updateEligibilityTraces();
}

void MFuzzyACLearner::step(double reward, bool isTerminal, bool useRewardModel)
{
    double oldV = v;

    loadFIS();
    loadPhi();
    loadV();

    delta = reward  - oldV;
    //if (!isTerminal) delta += (discountFactor * v);
    delta += (discountFactor * v);

    //qDebug() << delta;

    //update rule

    for (int i = 0; i < eCrtitic->getNumOfNonZeroTraces(); i++)
    {
        int index = eCrtitic->getIndexOfNonZeroTrace(i);
        o[index] +=
                (ruleLearningRates[index]
                 * delta * eCrtitic->getNonZeroTrace(i));
    }

    for (int i = 0; i < action.numOfSingletons; i++)
    {
        for (int j = 0; j < eActor[i]->getNumOfNonZeroTraces(); j++)
        {
            w[eActor[i]->getIndexOfNonZeroTrace(j)][i] +=
                    (delta * eActor[i]->getNonZeroTrace(j));
        }
    }

    // Again
    loadV();

}

void MFuzzyACLearner::stepExploit()
{
    loadFIS();
    loadPhi();
    //loadV();

    updateAndSelectLocalActions(0.0, 0.0);
    action.val = selectGlobalAction();
}
