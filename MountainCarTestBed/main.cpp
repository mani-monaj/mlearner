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

#include <QtCore/QCoreApplication>

#include <QTimer>
#include <QTime>
#include <QDebug>
#include <math.h>

#include "cmountaincarenv.h"
#include "../mlearner/include/mtilesarsalearner.h"
#include "../mlearner/include/mtileqlearner.h"
#include "../mlearner/include/mfuzzyaclearner.h"
#include "../mlearner/include/mfuzzyqlearner.h"
#include "profiler.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    srand(QTime(0,0,0).secsTo(QTime::currentTime()));

    CProfiler *p = new CProfiler();
    CProfiler *fuzzyP = new CProfiler();

    CMountainCarEnv* mcEnv = new CMountainCarEnv(-1.2, 0.5, -0.07, 0.07);
    MFuzzyQLearner *fl = new MFuzzyQLearner();
    //MFuzzyACLearner *fl = new MFuzzyACLearner();
    //MTileSarsaLearner *fl = new MTileSarsaLearner();
    //MTileQLearner *fl = new MTileQLearner();


    /* Tile */


//    fl->addStateVariable("pos", -1.2, 0.5, 8);
//    fl->addStateVariable("vel", -0.07, 0.07, 8);
//    fl->initAction("acc",-1,1,3);
//    fl->initLearner(10, 1.0, 0.5, 0.9, 0.01, 0.5, 0.01 );



    /* Fuzzy */


    /* Notes on learning Rates
       Ka = 0.5 * learningRate;
       the more learning rate (or Ka) , the more danger to fall into local min

       learningRate, Ka, ep, nw
       FACL (BEST) : 0.05 - 0.025, 0, 1.5
       FQL (BEST) : 0.002 - 0.001, 0, 3.0
       FQL (BEST - 15 Khordad) : 0.01 - 0.005, 0, 3.0
    */



    fl->addStateVariable("pos", -1.2, 0.5, 5);
    fl->addStateVariable("vel", -0.07, 0.07, 5);
    fl->initAction("acc",-1,1,3);


    fl->initLearner(
                0.95,
                0.01,
                0.8,
                0.9,
                0.0,
                3.0, //2.5
                0.00001,
                0.005, //0.01
                0.05,
                0.2);


    double totalLearningSteps = 0.0;
    double totalExploitingSteps = 0.0;
    double totalLearningSuccess = 0.0;
    double totalExploitingSuccess = 0.0;
    double totalLearningEpisodes = 0.0;
    double totalExploitingEpisodes = 0.0;

    double sumTimeFuzzy = 0.0;
    double countTimeFuzzy = 0.0;

    int mainProbe = p->putProbe("main");
    for (int run = 0; run < 30; run++)
    {
        // Reset Everything for a new run
        fl->resetAllVars();
        for (int phases = 0; phases < 2; phases++)
        {
            bool isLearning = (phases == 0);
            long int s = 0;
            long int r = 0;
            double as = 0;
            double ar = 0;

            if (isLearning) qDebug() << "Performing Run " << run << " ...";

            if (isLearning)
            {
                qDebug() << "Learning ... ";
            }
            else
            {

//                qDebug() << "*** Saving To File ***";
//                fl->saveLearnerToFile("./fuzzy.ml");
//                qDebug() << "*** Resset Everything ***";
//                delete fl;
//                fl = new MFuzzyQLearner();
//                qDebug() << "*** Load From File ***";
//                fl->initLearnerFromFile("./fuzzy.ml");
                qDebug() << "Exploiting ... ";
            }

            int sCount = 0;
            int maxsCount = 0;
            bool sucRuns = false;

            int episode = 0;

            //while (((isLearning) && (episode < 200)) || ((!isLearning) && (episode < 100) ))
            while (((isLearning) && (sCount < 40) && (episode < 5000)) || ((!isLearning) && (episode < 100) ))
            {
                mcEnv->initRand();

                fl->setStateVariableValue("pos", mcEnv->getX());
                fl->setStateVariableValue("vel", mcEnv->getV());

                fl->newEpisode();

                bool isGoal = false;
                int step = 0;
                while ((!isGoal) && (++step < 1000))
                {
                    //int action = (int) fl->getActionRealValue();
                    int action = fl->getActionSingetonValue() - 1;

                    if (isLearning) fl->beforeStep();
                    mcEnv->setAcc(action);
                    mcEnv->update();
                    isGoal = (mcEnv->getX() >= 0.49);

                    fl->setStateVariableValue("pos", mcEnv->getX());
                    fl->setStateVariableValue("vel", mcEnv->getV());
                    if (isLearning)
                    {
                        int dummy = fuzzyP->putProbe("fuzzy");
                        double reward = (isGoal) ? 0.0 : -1.0;
                        //reward += ((drand48() - 0.5) * 2.0);

                        if (!isGoal)
                        {
                            if (drand48() >= 0.51)
                            {
                                reward = 0.0;
                            }
                            //reward += ((drand48() - 0.5) * 2.0);
                        }
                        else
                        {
                            if (drand48() >= 0.1)
                            {
                                reward = -1.0;
                            }
                        }
                        //qDebug() << reward <<  isGoal;
                        //reward = drand48();
                        fl->step( reward, isGoal, true);
                        fl->afterStep();
                        sumTimeFuzzy += fuzzyP->takeProbe(dummy);
                        countTimeFuzzy += 1.0;
                    }
                    else
                    {
                        fl->stepExploit();
                    }
                }

                if (isLearning)
                {
                    totalLearningSteps += step;
                }
                else
                {
                    totalExploitingSteps += step;
                }
                s += step;
                as += step;

                if (isGoal)
                {
                    r++;
                    ar = ar + 1.0;
                    sucRuns = true;
                    sCount++;
                    if (sCount > maxsCount)
                    {
                        maxsCount = sCount;
                    }
                    if (isLearning)
                    {
                        totalLearningSuccess += 1.0;
                    }
                    else
                    {
                        totalExploitingSuccess += 1.0;
                    }
                }
                else
                {                    
                    sCount = 0;
                    sucRuns = false;
                }

                int intervals = 5;
                if ((episode % intervals == 0) && (episode > 0))
                {
                    //qDebug() << "Last " << intervals << " Episodes Steps mean : " << s / intervals << " Success Rate (%) : " << (r / (double) intervals) * 100.0 << " A-Steps Mean : " << as / (episode+1) << " A-Rate (%) : " << (ar / (episode+1)) * 100.0 << "Successive :" << sCount;
                    //qDebug() <<  s / intervals << (r / (double) intervals) * 100.0  << as / (episode+1) <<  (ar / (episode+1)) * 100.0;
                    qDebug() <<  s / intervals << "," << (r / (double) intervals) * 100.0;
                    s = 0;
                    r = 0;
                }
                episode++;                
            }

            if (isLearning)
            {
                totalLearningEpisodes += episode;
            }
            else
            {
                totalExploitingEpisodes += episode;
            }

            qDebug() << "Episodes: " << episode  << "A-Steps Mean : " << as / double(episode) << " A-Rate (%) : " << (ar / double(episode)) * 100.0 << "Max Successive :" << maxsCount;
            if (isLearning)
            {
                qDebug() << "Mean Time FRL per Step : " << sumTimeFuzzy /countTimeFuzzy;
                sumTimeFuzzy = 0.0;
                countTimeFuzzy = 0.0;
            }
        }
    }

    qDebug() << "Learning Summary";
    qDebug() << "Mean Steps: " << totalLearningSteps / totalLearningEpisodes << "Mean Success: " << totalLearningSuccess / totalLearningEpisodes;
    qDebug() << "Exploiting Summary";
    qDebug() << "Mean Steps: " << totalExploitingSteps / totalExploitingEpisodes << "Mean Success: " << totalExploitingSuccess / totalExploitingEpisodes;
    qDebug() << "Compound: ";
    qDebug() << "Mean Steps: " << (totalLearningSteps+totalExploitingSteps) / (totalLearningEpisodes+totalExploitingEpisodes) << "Mean Success: " << (totalLearningSuccess+totalExploitingSuccess) / (totalExploitingEpisodes+totalLearningEpisodes);
    qDebug() << "Time : " << p->takeProbe(mainProbe);

    delete fl;
    QTimer::singleShot(1000, &a, SLOT(quit()));
    return a.exec();
}
