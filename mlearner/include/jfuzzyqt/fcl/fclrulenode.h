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
 * \file fclrulenode.h
 * \class FCLRuleNode
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief FIXME
 */
#ifndef FCLRULENODE_H
#define FCLRULENODE_H

#include "../rule/ruleexpression.h"
#include "../rule/ruleterm.h"
#include "../connection/ruleconnectionmethod.h"
#include "../connection/and/ruleconnectionmethodandmin.h"
#include "../connection/or/ruleconnectionmethodormax.h"
#include "../functblock.h"
#include <QObject>
#include <QString>

namespace jfuzzyqt{

class FCLRuleTree;

class FCLRuleNode : public QObject
{
    Q_OBJECT

public:
    FCLRuleNode(QObject *parent, const QString& oper);
    ~FCLRuleNode();
    bool isPriorThen(int priority);
    int getPriority();
    void setLeft(FCLRuleNode* node);
    bool hasRightMember()const;
    FCLRuleNode* getRight();
    void setRight(FCLRuleNode* node);
    QString print()const;
    void insertLeaveValues(QList<QString>&values, FCLRuleTree*rt);
    const QString& getOperator()const;
    RuleExpression* toRuleExpression(FunctBlock &fb, const RuleConnectionMethod *AND, const RuleConnectionMethod *OR)const;
    RuleTerm* toRuleTermLeft(FunctBlock &fb)const;
    RuleTerm* toRuleTermRight(FunctBlock &fb)const;

private:
    int priority;
    QString value1;
    QString value2;
    QString oper;
    FCLRuleNode* left;
    FCLRuleNode* right;
};

};

#endif // FCLRULENODE_H
