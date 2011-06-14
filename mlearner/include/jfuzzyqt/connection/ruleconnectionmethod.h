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
 * \file RuleConnectionMethod.h
 * \class RuleConnectionMethod
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief  Base for methods used to connect rule's antecedents
 * From FCL's specs:
 * "To fulfill de Morgan's Law, the algorithms for operators AND and OR shall be used pair-wise e.g.
 * MAX shall be used for OR if MIN is used for AND."
 * 			Operator OR 		Operator AND
 * 			MAX				MIN
 * 			ASUM				PROD
 * 			BSUM				BDIF
 */
#ifndef RULECONNECTIONMETHOD_H
#define RULECONNECTIONMETHOD_H

#include <QObject>
#include <QString>

namespace jfuzzyqt{

class RuleConnectionMethod : public QObject
{
    Q_OBJECT

public:
    RuleConnectionMethod(const QString& name="Undefined");
    ~RuleConnectionMethod();
    const QString& getName() const;
    void setName(const QString& name);
    virtual double connect(double antecedent1, double antecedent2)const = 0;
    virtual QString toString() const = 0;

private:
    QString name;
};

};

#endif // RULECONNECTIONMETHOD_H
