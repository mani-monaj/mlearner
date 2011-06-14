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
 * \file fclruletree.h
 * \class FCLRuleTree
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief FIXME
 */
#ifndef FCLRULETREE_H
#define FCLRULETREE_H

#include "fclrulenode.h"
#include "../rule/ruleexpression.h"
#include "../functblock.h"
#include <QObject>
#include <QObject>
#include <QString>
#include <QList>

namespace jfuzzyqt{

class FCLRuleTree : public QObject
{
    Q_OBJECT

public:
    FCLRuleTree(QObject *parent);
    ~FCLRuleTree();
    void addExpression(QString exp);
    QString print()const;
    RuleExpression* getRuleExpression(FunctBlock &fb,
                                      const RuleConnectionMethod *AND,
                                      const RuleConnectionMethod *OR)const;
    FCLRuleNode* getRuleNode(const QString& exp)const;

private:
    FCLRuleNode* root;
    FCLRuleTree* parentTree;
    QHash<QString,FCLRuleNode*>subtrees;
    FCLRuleNode* insertNode(FCLRuleNode* root, FCLRuleNode* node);
    void insertNode(FCLRuleNode* node);
    void insertRight(FCLRuleNode* root, FCLRuleNode* node);
    void insertLeaveValues(QList<QString>&values);
};

};

#endif // FCLRULETREE_H
