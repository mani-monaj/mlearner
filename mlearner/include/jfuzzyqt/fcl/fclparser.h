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
 * \file fclparser.h
 * \class FCLParser
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 1.08
 * \brief FIXME
 */
#ifndef FCLPARSER_H
#define FCLPARSER_H

#include "../functblock.h"
#include "../rule/ruleexpression.h"
#include <QString>
#include <QTextStream>
#include <QObject>

namespace jfuzzyqt{

class FCLParser : public QObject
{
    Q_OBJECT

public:
    FCLParser();
    FCLParser(QObject *parent);
    FCLParser(const FCLParser &parser);
    ~FCLParser();
    QString readLine(QTextStream &in);
    void loadFunctBlock(QTextStream &in,FunctBlock& funcBlock);

//private:
    void loadVarInput(QTextStream& in, FunctBlock& funcBlock);
    void loadVarOutput(QTextStream& in, FunctBlock& funcBlock);
    void loadDefuzzify(QTextStream& in, FunctBlock& funcBlock, const QString& varName);
    void loadFuzzify(QTextStream& in, FunctBlock& funcBlock, const QString& name);
    RuleBlock* loadRuleBlock(QTextStream& in, FunctBlock& funcBlock, const QString& name);
    Rule* loadRule(FunctBlock& funcBlock,
                   const QString &rule,
                   const QString &name,
                   const RuleConnectionMethod *AND,
                   const RuleConnectionMethod *OR );
    RuleAccumulationMethod* createAccumulationMethod(const QString& type);
    RuleExpression* loadRuleIf(FunctBlock& funcBlock,
                               QString ruleif,
                               const RuleConnectionMethod *AND,
                               const RuleConnectionMethod *OR );

};

};

#endif // FCLPARSER_H
