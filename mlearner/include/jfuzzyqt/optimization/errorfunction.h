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
 * \file errorfunction.h
 * \class ErrorFunction
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \date 2009/05
 * \version 1.08
 * \brief Class OptimizationParameters provide access to values
 */
#ifndef ERROR_FUNCTION_H
#define ERROR_FUNCTION_H

#include "../../include/jfuzzyqt.h"
#include <QList>
#include <QHash>

namespace jfuzzyqt{

class ErrorFunction : public QObject
{
    Q_OBJECT
public:
    ErrorFunction(QObject*parent);
    ErrorFunction(QObject*parent,const QString& fileUri);
    void append(QHash<QString, double>sample);
    double evaluate(JFuzzyQt&model)const;
    int samplesSize()const;
private:
    QList<QHash<QString, double> > samples;
};

};

#endif // ERROR_FUNCTION_H
