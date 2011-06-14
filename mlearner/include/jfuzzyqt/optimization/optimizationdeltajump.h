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
 * \file optimizationdeltajump.h
 * \class OptimizationDeltaJump
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \date 2009/05
 * \version 1.08
 * \brief Class OptimizationDeltaJump implement delta jump optimization
 */
#ifndef OPTIMIZATION_DELTA_JUMP_H
#define OPTIMIZATION_DELTA_JUMP_H

#include <QObject>
#include "errorfunction.h"
#include "value.h"
#include "../../include/jfuzzyqt.h"

namespace jfuzzyqt{

class OptimizationDeltaJump : public QObject
{
    Q_OBJECT

    ErrorFunction* erf;
    /** Fuzzy rule set's whose parameters we are optimizing */
    JFuzzyQt* model;
    int maxIterations;
    int maxLineSearchIterations;
    QList<Value*> valuesList;
public :
    OptimizationDeltaJump(JFuzzyQt* model,
                          ErrorFunction* erf,
                          QList<Value*> valuesList,
                          int maxLineSearchIterations = 20,
                          int maxIterations = 1000);
    void optimize(bool verbose);
private :
    double jump(int parameterNumber, double error0);
};

}

#endif // OPTIMIZATION_DELTA_JUMP_H
