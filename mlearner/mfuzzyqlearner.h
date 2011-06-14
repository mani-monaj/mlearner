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

#ifndef MFUZZYQLEARNER_H
#define MFUZZYQLEARNER_H

#include "mfuzzylearnerbase.h"

/*

  FQL is a compact version of FACL. It is also an off-poilicy learner.
  Nothing that uses output singletons will work here. It just uses the
  action weights.
*/

class MFuzzyQLearner : public MFuzzyLearnerBase
{
public:
    MFuzzyQLearner();

    // Virtual Functions

    void newEpisode();
    void beforeStep();
    void afterStep();
    void step(double reward, bool isTerminal, bool useRewardModel = false);
    void stepExploit();

private:

    double findMaxWeightinRule(int r);
    void loadQ();
    void loadOptimalQ();
};

#endif // MFUZZYQLEARNER_H
