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
 * \file ruleaccumulationmethod.h
 * \class RuleAccumulationMethod
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief Rule accumulation base method
 * From FCL's definition:
 * "The results of the rules are combined to obtain an overall result. The maximum algorithm is usually
 * used for accumulation.
 * Depending on the combination of operators in the individual steps, different inference strategies are
 * obtained. The best-known are the so-called MaxMin Inference and MaxProd Inference, which use the
 * maximum for accumulation and the minimum or the algebraic product for activation. In the case of the
 * MaxMin Inference, the membership functions of the Fuzzy Sets of the conclusions are limited to the
 * degree of accomplishment of the condition and then, in turn, combined to create a Fuzzy Set by
 * forming a maximum. In MaxProd Inference, in contrast, the membership functions of the Fuzzy Sets
 * of the conclusions are weighted, i.e. multiplied, with the degree of accomplishment of the condition
 * and then combined."
**/

#ifndef RULEACCUMULATIONMETHOD_H
#define RULEACCUMULATIONMETHOD_H

#include <QObject>
#include <QString>

namespace jfuzzyqt{

class RuleAccumulationMethod : public QObject
{
    Q_OBJECT

public:
    RuleAccumulationMethod(QObject* parent=NULL);
    RuleAccumulationMethod(QObject* parent, const QString& name);
    RuleAccumulationMethod(const RuleAccumulationMethod &ram);
    ~RuleAccumulationMethod();
    virtual double aggregate(double defuzzifierValue, double valueToAggregate) const = 0;
    const QString& getName()const;
    void setName(const QString &name);
    QString toString()const;
private:
    QString name;
};

};

#endif // RULEACCUMULATIONMETHOD_H
