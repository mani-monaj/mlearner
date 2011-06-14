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
 * \file ruleactivationmethod.h
 * \class RuleActivationMethod
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief FIXME
 */
#ifndef RULEACTIVATIONMETHOD_H
#define RULEACTIVATIONMETHOD_H

#include "../rule/ruleterm.h"
#include "../accumulation/ruleaccumulationmethod.h"
#include <QObject>
#include <QString>
#include <QLinkedList>

namespace jfuzzyqt{

class RuleActivationMethod : public QObject
{
    Q_OBJECT

public:
    RuleActivationMethod(QObject *parent,const QString& name="");
    RuleActivationMethod(const RuleActivationMethod &ram);
    ~RuleActivationMethod();
    void setName(const QString& name);
    const QString& getName()const;
    virtual double imply(double degreeOfSupport, double membership)const = 0;
    void imply(RuleTerm* fuzzyRuleTerm, RuleAccumulationMethod* ruleAccumulationMethod, double degreeOfSupport);
    QString toString()const;

private:
    QString name;
};

};

#endif // RULEACTIVATIONMETHOD_H
