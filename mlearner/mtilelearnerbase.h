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

#ifndef MTDLearnerTile_H
#define MTDLearnerTile_H

#include "mtdlearnerbase.h"
#include "tiles.hpp"

/**
 * @brief The base abstract class for RL algorithm using Tile Coding
 *
 */
class MTileLearnerBase : public MTDLearnerBase
{
public:
    MTileLearnerBase();


    /**
     * @brief  The learner initialization function
     *
     * @param _tiles Number of tiles to use for each variable
     * @param _discountFactor The discount factor
     * @param _learningRate The learning rate
     * @param _etLambda The recency factor
     * @param _epsilon The e-greedy's epsilon
     * @param _maxNonZeroTracesRatio What fraction of whole eligibility trace's matrix should be considered as non-zero traces
     * @param _minTraceTreshhold The minimum threshold for non-zero trace value
     */
    void initLearner(unsigned int _tiles, double _discountFactor, double _learningRate, double _etLambda, double _epsilon, double _maxNonZeroTracesRatio, double _minTraceTreshhold);

    // virtuals


    /**
     * @brief Reset all vars of tile (CMAC) learner
     *
     */
    void resetAllVars();


    /**
     * @brief This function reads all learner initialization and learning state (all matrix) from a file
     * If you want to use this function, there is no need to use initLearner() function.
     * @param fileName The file (path+filename)
     * @param quiet For enabling the debug dumps
     */
    void initLearnerFromFile(QString fileName, bool quiet = true);


    /**
     * @brief This function dumps all learner initialization and learning state (all matrix) into a file
     *
     * @param fileName The file (path+filename)
     * @param quiet For enabling the debug dumps
     */
    void saveLearnerToFile(QString fileName, bool quiet = true);

    //TODO: Document the private members
protected:
    ~MTileLearnerBase();
    void loadQ();
    void loadQ(int a);
    void loadF();
    int argMax();
    int decide(double epsilon = 0.0);
    void loadRewardModel(int a);
    void updateRewardModel(int a, double reward);

    int numOfTiles;
    long memorySize;
    double maxNonZeroTracesRatio;
    float* Q;
    float* theta;
    int** F;

    // Reward Model
    float* rewardModelTheta;
    float* rewardModelCount;
    float* rewardExpectedVal;

};

#endif // MTDLearnerTile_H


