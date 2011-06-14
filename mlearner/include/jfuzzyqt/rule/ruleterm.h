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
 * \file ruleterm.h
 * \class RuleTerm
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief FIXME
 */
#ifndef RULETERM_H
#define RULETERM_H

#include "variable.h"
#include "../membership/membershipfunction.h"
#include <QObject>
#include <QString>

namespace jfuzzyqt{

class RuleTerm : public QObject
{
    Q_OBJECT

public:
    RuleTerm(QObject* parent=NULL);
    RuleTerm(QObject* parent, Variable* variable, const QString& term, bool negated);
    ~RuleTerm();
    Variable* getVariable()const;
    void setVariable(Variable* variable);
    const MembershipFunction* getMembershipFunction();
    const QString& getName()const;
    void setName(const QString &name);
    bool isNegated() const;
    bool isValid() const;
    void setNegated(const bool& value);
    QString toString()const;
    double getMembership()const;

private:
    /** Is it negated? */
    bool negated;
    /** RuleTerm's name */
    QString termName;
    /** Variable */
    Variable* variable;

};

};

#endif // RULETERM_H
