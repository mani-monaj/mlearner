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
 * \file optimizationparameters.h
 * \class OptimizationParameters
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \date 2009/04
 * \version 1.08
 * \brief Class OptimizationParameters provide access to values
 */
#ifndef OPTIMIZATION_PARAMETERS_H
#define OPTIMIZATION_PARAMETERS_H

#include <QObject>
#include "value.h"

namespace jfuzzyqt{

class OptimizationParameters : public QObject
{
    Q_OBJECT

public:

    OptimizationParameters(QObject* parent);
    ~OptimizationParameters();

    Value* getValue(int index)const;
    int size()const;

protected:
    QList<Value*> parameters;
};

};

#endif // OPTIMIZATION_PARAMETERS_H
