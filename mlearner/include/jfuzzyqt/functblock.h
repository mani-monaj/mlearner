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
 * \file functblock.h
 * \class FunctBlock
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief FIXME
 */
#ifndef FUNCTBLOCK_H
#define FUNCTBLOCK_H

#include <QString>
#include <QHash>
#include <QDebug>
#include <QObject>
#include "rule/variable.h"
#include "rule/ruleblock.h"
#include "defuzzifier/defuzzifier.h"


namespace jfuzzyqt{

class FunctBlock : public QObject
{
	Q_OBJECT

public:
    FunctBlock(QObject* parent=NULL);
    FunctBlock(QObject* parent,const QString& name);
    FunctBlock(const FunctBlock &fb);
    ~FunctBlock();

    const QString& getName()const;
    void setName(const QString& name);
    Defuzzifier* createDefuzzifier(const QString& defuzzType);
    bool setValue(const QString& varName, const double& value);
    void evaluate();
    double getValue(const QString& varName)const;
    bool addVariable(const QString& varName, Variable* variable);
    bool variableExist(const QString& varName)const;
    bool setVariable(const QString& varName, LinguisticTerm* lt);
    Variable* getVariable(const QString& varName);
    bool setDefaultValue(const QString& varName,const double value);
    bool setDefuzzifier(const QString& varName, Defuzzifier* d);
    bool addRuleBlock(RuleBlock* rl);
    QHash<QString, RuleBlock*> getRuleBlocks()const;
    QHash<QString, Variable*> getVariables()const;
    bool checkHierarchy()const;
    QString toString()const;
    QList<Value*>getOptimizationParameters()const;

    QHash<QString, RuleBlock*> ruleBlocks; ///<Several RuleBlocks indexed by name
    QHash<QString, Variable*> variables; ///<Every variable is here (key: VariableName)
private:
    QString name; ///<Function block name

};

};

#endif // FUNCTBLOCK_H
