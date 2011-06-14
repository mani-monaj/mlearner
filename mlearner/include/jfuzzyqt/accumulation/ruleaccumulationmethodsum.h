/****************************************************************
Copyright (C) 2009 Aleksey Myasnikov
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
 * \file ruleaccumulationmethodsum.h
 * \class RuleAccumulationMethodSum
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief FIXME
 */
#ifndef RULEACCUMULATIONMETHODSUM_H
#define RULEACCUMULATIONMETHODSUM_H

#include "ruleaccumulationmethod.h"
#include <QObject>

namespace jfuzzyqt{

class RuleAccumulationMethodSum : public RuleAccumulationMethod
{
    Q_OBJECT

public:
    RuleAccumulationMethodSum(QObject *parent=NULL);
    ~RuleAccumulationMethodSum();
    double aggregate(double defuzzifierValue, double valueToAggregate) const;
    QString toString()const;
private:

};

};

#endif // RULEACCUMULATIONMETHODSUM_H
