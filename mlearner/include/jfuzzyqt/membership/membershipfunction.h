/****************************************************************
Copyright (C) 2009 Marco Estanqueiro
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
in file LICENSE along with this program.  If not, see
<http://www.gnu.org/licenses/>
****************************************************************/
/*!
 * \file membershipfunction.h
 * \class MembershipFunction
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief FIXME
 */
#ifndef MEMBERSHIPFUNCTION_H
#define MEMBERSHIPFUNCTION_H

#include "../optimization/optimizationparameters.h"
#include <QString>
#include <QObject>

namespace jfuzzyqt{

class MembershipFunction : public OptimizationParameters
{
    Q_OBJECT

public:
    enum MembershipType
    {
        FunctionContinuous,FunctionCosine,FunctionDifferenceSigmoidal,
        FunctionDiscrete,FunctionFunction,FunctionGaussian,
        FunctionGenBell,FunctionGenericSingleton,FunctionPieceWiseLinear,
        FunctionSigmoidal,FunctionSingleton,FunctionTrapetzoidal,
        FunctionTriangular
    };

    MembershipFunction(QObject* parent, MembershipType type);
    ~MembershipFunction();

    virtual bool checkParameters(QString& errors) const = 0;
    virtual void estimateUniverse() = 0;
    virtual double membership(double index) const = 0;
    double getUniverseMax();
    double getUniverseMin();
    bool isDiscrete()const;
    virtual QString getName()const = 0;
    virtual QString toString()const = 0;

protected:
    double* universeMax; ///< Universe max (range max)
    double* universeMin; ///< Universe min (range min)
    bool discrete;
    MembershipType type;
};

};

#endif // MEMBERSHIPFUNCTION_H
