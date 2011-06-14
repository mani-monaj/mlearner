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
 * \file defuzzifierdiscrete.h
 * \class DefuzzifierDiscrete
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief FIXME
 */
#ifndef DEFUZZIFIERDISCRETE_H
#define DEFUZZIFIERDISCRETE_H

#include <QHash>
#include <QList>
#include <QString>
#include "defuzzifier.h"

namespace jfuzzyqt{

class DefuzzifierDiscrete : public Defuzzifier
{
    Q_OBJECT

public:
    DefuzzifierDiscrete();
    ~DefuzzifierDiscrete();
    QList<double> values()const;
    double getDiscreteValue(double x)const;
    void setPoint(double x, double y);
    void reset();

private:
    QHash<QString, double> discreteValues;

};

};

#endif // DEFUZZIFIERDISCRETE_H
