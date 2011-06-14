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

#ifndef CMOUNTAINCARENV_H
#define CMOUNTAINCARENV_H

enum MCE_States {
    MCE_None,
    MCE_BoundMinX,
    MCE_BoundMaxX,
    MCE_BoundMinV,
    MCE_BoundMaxV
};

class CMountainCarEnv
{
public:
    CMountainCarEnv(double _xMin, double _xMax, double _vMin, double _vMax);
    double getX();
    double getV();
    double getH();
    void setX(double _x);
    void setV(double _v);
    void setAcc(short int _a);
    bool update();
    MCE_States getState();

    void initRand();

private:
    double v, oldV;
    double x, oldX;
    double vMin;
    double vMax;
    double xMin;
    double xMax;
    short int a;
    MCE_States lastState;

    void applyBound();

};

#endif // CMOUNTAINCARENV_H
