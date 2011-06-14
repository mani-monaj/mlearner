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

#ifndef PROFILER_H
#define PROFILER_H

#include <QString>
#include <QList>

/**
 * @brief
 *
*/
struct CTimeProbe
{
    double time;
    int id;
    QString name;
};

/**
 * @brief
 *
*/
class CProfiler
{
private:
    QList<CTimeProbe> probes;
    /**
     * @brief
     *
     * @return double
    */
    double getTime();
    int id;
public:
    QList<CTimeProbe> elapesedProbes;
    /**
     * @brief
     *
    */
    CProfiler();
    /**
     * @brief
     *
     * @param name
     * @return int
    */
    int putProbe(QString name);
    /**
     * @brief
     *
     * @return double
    */
    double elapesed();
    /**
     * @brief
     *
     * @param id
     * @return double
    */
    double takeProbe(int id);
    /**
     * @brief
     *
     * @param i
     * @return QString
    */
    QString getProbeName(int i);
    /**
     * @brief
     *
     * @param i
     * @return int
    */
    int getProbeID(int i);
    /**
     * @brief
     *
     * @param i
     * @return double
    */
    double getProbeTime(int i);
    /**
     * @brief
     *
     * @return int
    */
    int probeCount();
};

#endif // PROFILER_H
