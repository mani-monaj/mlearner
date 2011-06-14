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
 * \file linguisticterm.h
 * \class LinguisticTerm
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief A linguistic term is an asociation between a termName and a membership function
 */
#ifndef LINGUISTICTERM_H
#define LINGUISTICTERM_H

#include <QString>
#include <QObject>

namespace jfuzzyqt {

class MembershipFunction;

class LinguisticTerm : public QObject
{
    Q_OBJECT

public:
    LinguisticTerm(QObject* parent=NULL);
    LinguisticTerm(QObject* parent,const QString& termName, MembershipFunction* membershipFunction);
    ~LinguisticTerm();
    const QString& getTermName() const;
    void setTermName(const QString& name);
    MembershipFunction* getMembershipFunction();
    bool loadFrom(const QString& qString);

private:
    QString termName;///<Terms's name
    MembershipFunction* membershipFunction;///< Membership function

};

} using namespace jfuzzyqt;

#endif // LINGUISTICTERM_H
