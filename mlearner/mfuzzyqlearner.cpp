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

#include "mfuzzyqlearner.h"

MFuzzyQLearner::MFuzzyQLearner()
{
}

double MFuzzyQLearner::findMaxWeightinRule(int r)
{
    double max = w[r][0];
    for (int i = 1; i < action.numOfSingletons; i++)
    {
        if (w[r][i] > max)
        {
            max = w[r][i];
        }
    }
    return max;
}

void MFuzzyQLearner::loadQ()
{
    Q = 0.0;
    double sum = 0.0;
    for (int i = 0; i < numOfRules; i++)
    {
        if (alpha[i] == 0.0) continue;
        Q += alpha[i] * w[i][Ut[i]];
        sum += alpha[i];
    }

    Q = Q / sum;
}

void MFuzzyQLearner::loadOptimalQ()
{
    optimalQ = 0.0;
    double sum = 0.0;
    for (int i = 0; i < numOfRules; i++)
    {
        if (alpha[i] == 0.0) continue;
        optimalQ += alpha[i] * findMaxWeightinRule(i);
        sum += alpha[i];
    }

    optimalQ = optimalQ / sum;
}

void MFuzzyQLearner::newEpisode()
{
    //qDebug() << "Learner New Episode!";

    setLambda(0.0); // For FQL this must be zero, only Actor ET is used

    eCrtitic->decayTraces(0.0);
    for (int i = 0; i < action.numOfSingletons; i++)
    {
        eActor[i]->decayTraces(0.0);
    }

    loadFIS();
    loadPhi();
    //loadOptimalQ();
    updateAndSelectLocalActions(epsilon, noiseWeight);
    action.val = selectGlobalAction();
    loadQ();    

    // TODO : Should we reset some other vars like rulesLearningRates???
}

void MFuzzyQLearner::beforeStep()
{
    ; // Clean
}

void MFuzzyQLearner::afterStep()
{
    updateAdaptiveLearningRates();    
    updateAndSelectLocalActions(epsilon, noiseWeight);
    //updateEligibilityTraces();
    action.val = selectGlobalAction();
    updateEligibilityTraces();
    loadQ();
}

void MFuzzyQLearner::step(double reward, bool isTerminal, bool useRewardModel)
{
    loadFIS();
    loadPhi();
    loadOptimalQ();

    delta = reward - Q;

    // TODO : Is it correct?
    //if (!isTerminal) delta += (discountFactor * optimalQ);
    delta += (discountFactor * optimalQ);

    for (int i = 0; i < action.numOfSingletons; i++)
    {
        for (int j = 0; j < eActor[i]->getNumOfNonZeroTraces(); j++)
        {
            int index = eActor[i]->getIndexOfNonZeroTrace(j);
            w[index][i] +=
                    (ruleLearningRates[index] *
                    delta * eActor[i]->getNonZeroTrace(j));
        }
    }
}

void MFuzzyQLearner::stepExploit()
{
    loadFIS();
    loadPhi();
    //loadQ();
    //loadOptimalQ();

    updateAndSelectLocalActions(0.0, 0.0);
    action.val = selectGlobalAction();
}
