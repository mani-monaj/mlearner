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

#include "cmountaincarenv.h"

#include "math.h"

#include <QDebug>
#include <QtDebug>

CMountainCarEnv::CMountainCarEnv(double _xMin, double _xMax, double _vMin, double _vMax)
{
    this->xMin = _xMin;
    this->xMax = _xMax;
    this->vMin = _vMin;
    this->vMax = _vMax;

    x = oldX = 0.0;
    v = oldV = 0.0;
    a = 0;

    this->lastState = MCE_None;
}

void CMountainCarEnv::initRand()
{
    this->setX( (double(rand() / (double(RAND_MAX)) * (xMax - xMin))) + xMin );
    this->setV( (double(rand() / (double(RAND_MAX)) * (vMax - vMin))) + vMin );

    //this->setX(-0.5);
    //this->setV(0.0);
}

double CMountainCarEnv::getX()
{
    return this->x;
}

double CMountainCarEnv::getV()
{
    return this->v;
}

double CMountainCarEnv::getH()
{
    return sin(3.0 * x);
}

void CMountainCarEnv::applyBound()
{
    lastState = MCE_None;
    if (x <= xMin)
    {
        x = xMin;
        v = 0.0;
        lastState = MCE_BoundMinX;
    }
    else if (x >= xMax)
    {
        x = xMax;
        v = 0.0;
        lastState = MCE_BoundMaxX;
    }
    if (v < vMin)
    {
        v = vMin;
        lastState =  MCE_BoundMinV;
    }
    else if (v > vMax)
    {
        v = vMax;
        lastState=  MCE_BoundMaxV;
    }
}

void CMountainCarEnv::setX(double _x)
{
    this->oldX = x;
    this->x = _x;
    applyBound();
}

void CMountainCarEnv::setV(double _v)
{
    this->oldV = v;
    this->v = _v;
    applyBound();
}

void CMountainCarEnv::setAcc(short int _a)
{
    if ((_a == -1) || (_a ==0) || (_a == 1))
    {
        this->a = _a;
    }
    else
    {
        this->a = 0.0;
        qWarning("Invalid Acc Value! Reset to zero.");
    }
}

MCE_States CMountainCarEnv::getState()
{
    return this->lastState;
}

bool CMountainCarEnv::update()
{
    double vNew = v - (0.0025 * cos(3.0 * x))+ (0.001 * double(a));
    this->v = vNew;
    if (this->v < vMin) this->v = vMin;
    if (this->v > vMax) this->v = vMax;

    double xNew = x + v;
    this->x = xNew;
    if (this->x < xMin)
    {
        this->x = xMin;
        this->v = 0.0;
    }
    if (this->x > xMax)
    {
        this->x = xMax;
    }

    return (lastState == MCE_None);
}
