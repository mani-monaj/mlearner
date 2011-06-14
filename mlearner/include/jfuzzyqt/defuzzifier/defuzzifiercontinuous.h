/****************************************************************
Copyright (C) 2009 Marco Estanqueiro, Aleksey Myasnikov
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
 * \file defuzzifiercontinuous.h
 * \class DefuzzifierContinuous
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief FIXME
 */
#ifndef DEFUZZIFIERCONTINUOUS_H
#define DEFUZZIFIERCONTINUOUS_H

#include "defuzzifier.h"

namespace jfuzzyqt{

class DefuzzifierContinuous : public Defuzzifier
{
    Q_OBJECT

public:
    const static int DEFAULT_NUMBER_OF_POINTS = 100;

    DefuzzifierContinuous();
    ~DefuzzifierContinuous();

    double getStepSize()const;
    int getLength()const;
    void setValue(double valueX, double valueY);
    int getIndex(double d)const;
    double getValue(double x)const;
    void reset();
    void setMin(double min);
    void setMax(double max);
protected:
    /**
     * Step size between each element in 'values[]'
     * 			stepSize = (max - min) / values.length
     */
    double stepSize;
    /**
     * Funcion values: A generic continuous function
     * 			y = f(x)
     * where x : [min, max]
     * Values are stored in 'values[]' array.
     * Array's index is calculated as:
     * 			index = (x - min) / (max - min) * (values.length)
     */
    double values[DEFAULT_NUMBER_OF_POINTS];
};

};

#endif // DEFUZZIFIERCONTINUOUS_H
