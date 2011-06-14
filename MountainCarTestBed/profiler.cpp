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

#include "profiler.h"
#include <sys/time.h>
#include <sys/types.h>
#include <stdio.h>
/**
 * @brief
 *
*/
CProfiler::CProfiler()
{
    id = 1;
}

/**
 * @brief
 *
 * @return double
*/
double CProfiler::getTime()
{
    timeval tim;
    gettimeofday(&tim, NULL);
    return tim.tv_sec+(tim.tv_usec/1000000.0);
}

/**
 * @brief
 *
 * @param name
 * @return int
*/
int CProfiler::putProbe(QString name)
{
    CTimeProbe t;
    t.time = getTime();
    t.id = id;
    t.name = name;
    probes.append(t);    
    id ++;    
    return id-1;
}

/**
 * @brief
 *
 * @return double
*/
double CProfiler::elapesed()
{
    return getTime() - probes.last().time;
}

/**
 * @brief
 *
 * @param id
 * @return double
*/
double CProfiler::takeProbe(int id)
{
    for (int i=0;i<probes.count();i++)
    {
        if (probes[i].id==id)
        {
            CTimeProbe t = probes.takeAt(i);
            t.time = getTime() - t.time;
            elapesedProbes.append(t);
            return t.time;
        }
    }
    return -1;
}

/**
 * @brief
 *
 * @param i
 * @return QString
*/
QString CProfiler::getProbeName(int i)
{
    if (i<probes.count() && i>=0)
    {
        return probes[i].name;
    }
    else return QString("Wrong Probe");
}

/**
 * @brief
 *
 * @param i
 * @return int
*/
int CProfiler::getProbeID(int i)
{
    if (i==-1) return probes.last().time;
    if (i<probes.count() && i>=0)
    {
        return probes[i].id;
    }
    else return -1;
}

/**
 * @brief
 *
 * @param i
 * @return double
*/
double CProfiler::getProbeTime(int i)
{
    if (i==-1) return probes.last().time;
    if (i<probes.count() && i>=0)
    {
        return probes[i].time;
    }
    else return -1;
}

/**
 * @brief
 *
 * @return int
*/
int CProfiler::probeCount()
{
    return probes.count();
}

