/****************************************************************
Copyright (C) 2009 Marco Estanqueiro
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
 * \file defuzzifiercenterofgravitysingletons.h
 * \class DefuzzifierCenterOfGravitySingletons
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief FIXME
 */
#ifndef DEFUZZIFIERCENTEROFGRAVITYSINGLETONS_H
#define DEFUZZIFIERCENTEROFGRAVITYSINGLETONS_H

#include "defuzzifierdiscrete.h"
#include "../rule/variable.h"
#include <QString>
#include <QList>
#include <QVariant>

namespace jfuzzyqt{

class DefuzzifierCenterOfGravitySingletons : public DefuzzifierDiscrete
{
    Q_OBJECT

public:
    DefuzzifierCenterOfGravitySingletons();
    ~DefuzzifierCenterOfGravitySingletons();
    QVariant defuzzify()const;
    QString getName()const;
private:

};

};

#endif // DEFUZZIFIERCENTEROFGRAVITYSINGLETONS_H
