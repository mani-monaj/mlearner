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
 * \file ruleexpression.h
 * \class RuleExpression
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief General rule expression term
 * E.g.: "(temp IS hot AND pressure IS high) OR pressure IS low"
 */
#ifndef RULEEXPRESSION_H
#define RULEEXPRESSION_H

#include <QObject>
#include <QVariant>

namespace jfuzzyqt{

using namespace jfuzzyqt;
class RuleConnectionMethod;
class RuleTerm;

class RuleExpression : public QObject
{
    Q_OBJECT

public:
    enum term_t{RULETERM = 0, RULEEXPRESSION = 1, UNDEF = -1};

    RuleExpression(QObject *parent=NULL);
    ~RuleExpression();
    const RuleConnectionMethod* getRuleConnectionMethod()const;
    bool isNegated()const;
    RuleTerm* getTerm1Rule()const;
    RuleTerm* getTerm2Rule()const;
    RuleExpression* getTerm1Expression()const;
    RuleExpression* getTerm2Expression()const;
    void addTerm1Rule(RuleTerm *ruleTerm);
    void addTerm2Rule(RuleTerm *ruleTerm);
    void addTerm1Expression(RuleExpression *ruleExpression);
    void addTerm2Expression(RuleExpression *ruleExpression);
    void setRuleConnectionMethod(const RuleConnectionMethod* ruleConnectionMethod);
    QString toString()const;
    RuleExpression::term_t getTerm1Type()const;
    RuleExpression::term_t getTerm2Type()const;
    void reset();
    double evaluate();
    QStringList getVariableList()const;

private:
    bool negated; ///<Is it negated?
    const RuleConnectionMethod* ruleConnectionMethod; ///<How are term1 and term2 connected?
    union term1_t///<Term can be a either a 'RuleTerm' or 'RuleExpression'
    {
        RuleTerm *ruleTerm;
        RuleExpression *ruleExpression;
    } term1,term2;
    term_t term1Type;
    term_t term2Type;
};

};

#endif // RULEEXPRESSION_H
