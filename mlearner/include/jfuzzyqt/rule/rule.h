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
 * \file rule.h
 * \class Rule
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief FIXME
 */
#ifndef RULE_H
#define RULE_H

#include "ruleexpression.h"
#include "ruleterm.h"
#include "../accumulation/ruleaccumulationmethod.h"
#include "../activation/ruleactivationmethod.h"
#include "../optimization/optimizationparameters.h"
#include <QObject>
#include <QString>
#include <QLinkedList>

namespace jfuzzyqt{

class Rule : public OptimizationParameters
{
    Q_OBJECT

public:
    Rule(QObject *parent=NULL);
    Rule(const Rule &rule);
    Rule(QObject *parent, const QString& name);
    ~Rule();
    void addAntecedents(RuleExpression *antecedents);
    void addConsequent(RuleTerm* rt);
    const QString& getName()const;
    RuleExpression* getAntecedents()const;
    const QList<RuleTerm*> getConsequents()const ;
    QString toString() const;
    void setDegreeOfSupport(const double& degreeOfSupport);
    double getDegreeOfSupport(void);
    void reset();
    void evaluate (RuleActivationMethod* act,RuleAccumulationMethod* accu);
    double getWeight()const;
    void setWeight(double weight);

private:
    QString name;
    RuleExpression* antecedents;
    QList<RuleTerm*> consequents;
    double degreeOfSupport;
};

};

#endif // RULE_H
