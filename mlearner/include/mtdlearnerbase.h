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

#ifndef MTDLearnerBase_H
#define MTDLearnerBase_H

#include <QString>
#include <QList>
#include <QFile>
#include <QDataStream>

#include <math.h>

#include "eligibiltytrace.h"

/* Constants for the header of save files */

#define _M_MAGIC        (quint32)0xAABBCCDD
#define _M_VERSION      (qint32)100
#define _M_TYPE_TILE    100
#define _M_TYPE_FUZZY   101

/**
 * @brief The continues variables struct
 *
 */
struct contVar
{
    QString name;
    double val;
    double oldVal;
    double min;
    double max;
    int nSeg;
    double width;
};

/*
Discrete Value:

min->max
maps to
0 -> (numOfSingletons - 1)

min : 0
max : numOfSingletons - 1
*/

/**
 * @brief Discrete Variables struct
 * min->max
 * maps to
 * 0 -> (numOfSingletons - 1)
 *
 * min : 0
 * max : numOfSingletons - 1
 *
*/
struct disVar
{
    QString name;
    int val;
    int numOfSingletons;
    double min;
    double max;
};

/**
 * @brief The base abstract class for implementing RL algoritthms
 *
 */
class MTDLearnerBase
{
public:
    MTDLearnerBase();

    /**
     * @brief  Initialization of discrete action of the learner
     *
     * @param name Name of the action
     * @param min Minimum Value
     * @param max Maximum Value
     * @param numOfSingletons Number of discrete values in [min,max]
     */
    void initAction(QString name, double min , double max,  int numOfSingletons);


    /**
     * @brief Add Input State Variable to learner
     *
     * @param name Name of the variable
     * @param min Minimum Value
     * @param max Maximum Value
     * @param nSeg Number of segments to consider between min and max
     */
    void addStateVariable(QString name, double min, double max,  int nSeg);

    /**
     * @brief Get the value of the state variable
     *
     * @param name
     */
    double getStateVariableValue(QString name);

    /**
     * @brief Set the value of the state variable
     *
     * @param name
     * @param val
     */
    void setStateVariableValue(QString name, double val);

    /**
     * @brief  Get the discrete value of the action var
     *
     */
    unsigned int getActionSingetonValue();


    /**
     * @brief Get the converted value between min,max of action
     *
     */
    double getActionRealValue();


    /**
     * @brief Set the discount factor
     *
     * @param val
     */
    void setDiscountFacor(double val);

    /**
     * @brief Set the learning rate
     *
     * @param val
     */
    void setLearningRate(double val);

    /**
     * @brief Set the recency factor
     * Fuzzy based methods use this as critic recency factor
     *
     * @param val
     */
    void setLambda(double val);


    /**
     * @brief Set the e-greedy exploration/exploition (undirected exploration) value
     *
     * @param val
     */
    void setEpsilon(double val);
    double getEpsilon();

    /**
     * @brief Virtual Abstract Function for start a new learning episode
     *
     */
    virtual void newEpisode() = 0;


    /**
     * @brief Virtual Abstract Function to run before learning update in each RL algorithm (see documentation)
     *
     */
    virtual void beforeStep() = 0;
    /**
     * @brief Virtual Abstract Function to run after learning update in each RL algorithm (see documentation)
     *
     */
    virtual void afterStep() = 0;

     /**
     * @brief Virtual Abstract Function to for learning update in each RL algorithm
     *
     * @param reward
     * @param isTerminal
     * @param useRewardModel
     */
    virtual void step(double reward, bool isTerminal, bool useRewardModel) = 0;


    /**
     * @brief Virtual Abstract Exploitation function to be used instead of step for pure (greedy) exploition
     *
     */
    virtual void stepExploit() = 0;


    /**
     * @brief Virtual Abstract function for initialization of learner from file
     *
     * @param fileName
     * @param quiet
     */
    virtual void initLearnerFromFile(QString fileName, bool quiet = true) = 0;

    /**
     * @brief Virtual Abstract function for saving all learner's info & data to file
     *
     * @param fileName
     * @param quiet
     */
    virtual void saveLearnerToFile(QString fileName, bool quiet = true) = 0;


    /**
     * @brief Virtual Abstract function to reset the learner vars for new run
     *
     */
    virtual void resetAllVars() = 0;

protected:
    ~MTDLearnerBase();
    QList<contVar> stateVars;
    disVar action;
    CEligibiltyTrace* e;

    double etLambda;
    double discountFactor;
    double learningRate;
    double epsilon;
    double minTraceTreshhold;


    int numOfStateVars;
    bool inBetween(double val, double min, double max);
    bool withProbability(double p);

    /**
     * @brief Common header generation function for saving to file
     *
     * @param stream
     * @param type
     * @param quiet
     */
    void saveHeader(QDataStream& stream, int type, bool quiet = true);


    /**
     * @brief Common header read function for reading from a file
     *
     * @param stream
     * @param quiet
     */
    int readHeader(QDataStream& stream, bool quiet = true);
};

#endif // MTDLearnerBase_H
