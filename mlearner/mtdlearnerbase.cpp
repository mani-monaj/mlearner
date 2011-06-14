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

#include "mtdlearnerbase.h"
#include <cstdlib>

#include <QDebug>

MTDLearnerBase::MTDLearnerBase(){
    numOfStateVars = 0;
}

MTDLearnerBase::~MTDLearnerBase()
{
    //qDebug() << "Running Destructer of MTDLearnerBase()";
}

void MTDLearnerBase::initAction(QString name, double min, double max, int numOfSingletons)
{
    Q_ASSERT(max >= min);

    this->action.name = name;
    this->action.numOfSingletons = numOfSingletons;
    this->action.min = min;
    this->action.max = max;

    this->action.val = 0;
}

void MTDLearnerBase::setDiscountFacor(double val)
{
    this->discountFactor = val;
}

void MTDLearnerBase::setLearningRate(double val)
{
    this->learningRate = val;
}

void MTDLearnerBase::setLambda(double val)
{
    this->etLambda = val;
}

void MTDLearnerBase::setEpsilon(double val)
{
    this->epsilon = val;
}

double MTDLearnerBase::getEpsilon()
{
    return this->epsilon;
}

void MTDLearnerBase::addStateVariable(QString name, double min, double max, int nSeg)
{
    Q_ASSERT(max >= min);

    contVar var;
    var.name = name;
    var.min = min;
    var.max = max;
    var.nSeg = nSeg;
    var.width = (max - min) / (double(nSeg));
    var.val = var.oldVal = 0.0;

    this->stateVars.append(var);
    numOfStateVars++;
}

double MTDLearnerBase::getStateVariableValue(QString name)
{
    for (int i = 0; i < stateVars.size(); i++)
    {
        if (stateVars.at(i).name == name)
        {
            return stateVars.at(i).val;
        }
    }
    qWarning("State Variable not found to get value!");
    return 0.0;
}

void MTDLearnerBase::setStateVariableValue(QString name, double val)
{
    for (int i = 0; i < stateVars.size(); i++)
    {
        if (stateVars.at(i).name == name)
        {
            //Q_ASSERT(inBetween(val, stateVars.at(i).min, stateVars.at(i).max));
            if (!inBetween(val, stateVars.at(i).min, stateVars.at(i).max))
            {
                if (val < stateVars.at(i).min)
                {
                    double bufVal = val;
                    val = stateVars.at(i).min;
                    qWarning() << stateVars.at(i).name << " is smaller than min (" << bufVal << ") set to min " << val;
                }
                else if (val > stateVars.at(i).min)
                {
                    double bufVal = val;
                    val = stateVars.at(i).max;
                    qWarning() << stateVars.at(i).name << " is bigger than max (" << bufVal << ") set to max " << val;
                }
            }
            stateVars[i].oldVal = stateVars[i].val;
            stateVars[i].val = val;
            return;
        }
    }
   qWarning("State Variable not found to set value!");
}

unsigned int MTDLearnerBase::getActionSingetonValue()
{
    return this->action.val;
}

double MTDLearnerBase::getActionRealValue()
{
    return action.min + ((double(action.val)) * ((action.max - action.min) /  (double(action.numOfSingletons) - 1.0)));
}


bool MTDLearnerBase::inBetween(double val, double min, double max)
{
    return ((val >= min) && (val <= max));
}

bool MTDLearnerBase::withProbability(double p)
{
    return p >= (((float)rand()) / RAND_MAX);
}

void MTDLearnerBase::saveHeader(QDataStream &stream, int type, bool quiet)
{
    stream << _M_MAGIC;
    stream << _M_VERSION;
    stream << (qint32) type;

    /* Writing Out State Vars */
    stream << (qint32) numOfStateVars;
    for (int i = 0; i < numOfStateVars; i++)
    {
        stream << stateVars.at(i).name;
        stream << (double) stateVars.at(i).min;
        stream << (double) stateVars.at(i).max;
        stream << (double) stateVars.at(i).nSeg;
    }

    /* Writing Out Action */
    stream << action.name;
    stream << (double) action.min;
    stream << (double) action.max;
    stream << (qint32) action.numOfSingletons;
    if (!quiet)
    {
        qDebug() << "Header has been written.";
    }
}

int MTDLearnerBase::readHeader(QDataStream &stream, bool quiet)
{
    quint32 magic;
    qint32 version, type;

    QString name;
    double min, max, nSeg;
    qint32 nos, numOfSingletons;

    stream >> magic;
    if (!quiet)
    {
        qDebug() << "**** Header ****";
        qDebug() << "Magic : " << magic;
    }
    if (magic != _M_MAGIC)
    {
        qWarning() << "readHeader :: Invalid Data Stream (File) Format!";
        return 0;
    }

    stream >> version;
    stream >> type;
    if (!quiet) qDebug() << "Version : " << version << "Type : " << type;

    stream >> nos;
    if (!quiet) qDebug() << "Num of State Vars : " << nos;
    for (int i = 0; i < nos; i++)
    {
        stream >> name >> min >> max >> nSeg;
        if (!quiet) qDebug() << "Adding State Var :" << i << name << min << max << nSeg;
        addStateVariable(name, min, max, nSeg);
    }


    stream >> name >> min >> max >> numOfSingletons;
    if (!quiet) qDebug() << "Adding Action :" << name << min << max << numOfSingletons;
    initAction(name, min, max, numOfSingletons);

    return type;
}
