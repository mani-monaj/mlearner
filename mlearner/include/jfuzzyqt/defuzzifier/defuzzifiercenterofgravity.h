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
 * \file defuzzifiercenterofgravity.h
 * \class DefuzzifierCenterOfGravity
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief FIXME
 */
#ifndef DEFUZZIFIERCENTEROFGRAVITY_H
#define DEFUZZIFIERCENTEROFGRAVITY_H

#include "defuzzifiercontinuous.h"
#include "../rule/variable.h"
#include <QString>
#include <QList>
#include <QVariant>

namespace jfuzzyqt{

class DefuzzifierCenterOfGravity : public DefuzzifierContinuous
{
    Q_OBJECT

public:
    DefuzzifierCenterOfGravity();
    ~DefuzzifierCenterOfGravity();
    QVariant defuzzify()const;
    QString getName()const;
private:

};

};

#endif // DEFUZZIFIERCENTEROFGRAVITYSINGLETONS_H
