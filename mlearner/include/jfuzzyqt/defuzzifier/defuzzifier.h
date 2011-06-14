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
 * \file defuzzifier.h
 * \class Defuzzifier
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief FIXME
 */
#ifndef DEFUZZIFIER_H
#define DEFUZZIFIER_H

#include <QObject>
#include <QVariant>

namespace jfuzzyqt{

class Defuzzifier : public QObject
{
    Q_OBJECT

public:
    Defuzzifier();
    ~Defuzzifier();
    virtual QString getName()const = 0;
    virtual QVariant defuzzify()const = 0;
    virtual void reset() = 0;
    bool isDiscrete()const;
    void setDiscrete(const bool& value);
    virtual void setMin(double min);
    double getMin()const;
    virtual void setMax(double max);
    double getMax()const;

private:
    bool discrete;

protected:
    double min;
    double max;
};

};

#endif // DEFUZZIFIER_H
