/*
mLearner - Qt based continues state space reinforcement learning library
Copyright (C) 2011, Mani Monajjemi (www.manionline.org)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "mfuzzylearnerbase.h"



MFuzzyLearnerBase::MFuzzyLearnerBase()
{
    ;
}

MFuzzyLearnerBase::~MFuzzyLearnerBase()
{
    //qDebug() << "Destructor of MTDLearnerFuzzy";
    for (int i = 0; i < numOfRules; i++)
    {
        delete [] w[i];
        delete [] n[i];
    }

    delete [] n;
    delete [] w;
    delete [] o;
    delete [] alpha;
    delete [] phi;
    delete [] Ut;
    delete [] valUt;
    delete [] sigma;
    delete [] sigmaBar;
    delete [] ruleLearningRates;

    for (int i = 0; i < numOfStateVars; i++)
    {
        delete fuzzyVars[i];
    }
    delete [] fuzzyVars;
    delete fuzzyOutput;

    delete fuzzyRuleBlock;
    delete fuzzyBlock;
    delete fuzzyParser;

    for (int i = 0; i < action.numOfSingletons; i++)
    {
        delete eActor[i];
    }
    delete [] eActor;

    delete eCrtitic;
}

void MFuzzyLearnerBase::initLearner(
        double _discountFactor,
        double _learningRate,
        double _etLambdaCritic,
        double _etLambdaActor,
        double _epsilon,
        double _noiseWeight,
        double _minTraceTreshhold,
        double _ka,
        double _phiConstant,
        double _thetaConstant
        )
{
    QString nameHelper;

    setDiscountFacor(_discountFactor);
    setLearningRate(_learningRate);
    setLambda(_etLambdaCritic);
    this->etLambdaActor = _etLambdaActor;
    setEpsilon(_epsilon);
    this->noiseWeight = _noiseWeight;
    this->Ka = _ka;
    this->phiConstant = _phiConstant;
    this->thetaConstant = _thetaConstant;
    this->minTraceTreshhold = _minTraceTreshhold;

    numOfRules = 1;
    for (int i = 0; i < this->numOfStateVars; i++)
    {
        // This +1 must be well documented
        numOfRules *= (stateVars.at(i).nSeg + 1);
    }

    w = new double*[numOfRules];
    for (int i = 0; i < numOfRules; i++)
    {
        w[i] = new double[action.numOfSingletons];
    }

    o = new double[numOfRules];
    phi = new double[numOfRules];    
    alpha = new double[numOfRules];

    n = new long int* [numOfRules];
    for (int i = 0; i < numOfRules; i++)
    {
        n[i] = new long int[action.numOfSingletons];
    }

    Ut = new int[numOfRules];
    valUt = new double[numOfRules];
    sigma = new double[numOfRules];
    sigmaBar = new double[numOfRules];
    ruleLearningRates = new double[numOfRules];

    // Eligibility Traces
    eCrtitic = new CEligibiltyTrace(numOfRules, numOfRules, minTraceTreshhold);

    eActor = new CEligibiltyTrace*[action.numOfSingletons];
    for (int i = 0; i < action.numOfSingletons; i++)
    {
        eActor[i] = new CEligibiltyTrace(numOfRules, numOfRules, minTraceTreshhold);
    }

    resetAllVars();


    // Begin of the fuzzy part based on jFuzzyQt Library

    fuzzyParser = new FCLParser();
    fuzzyBlock = new FunctBlock(NULL);

    fuzzyVars = new Variable*[numOfStateVars];
    for (int i = 0; i < numOfStateVars; i++)
    {
        nameHelper = stateVars.at(i).name;
        if (nameHelper.isEmpty())
        {
            qWarning("Input (State) Variables must have name!");
            qWarning("Nothing probably works");
            nameHelper.sprintf("state%d",i);

        }
        fuzzyVars[i] = new Variable(fuzzyBlock, nameHelper);
        fuzzyBlock->addVariable(nameHelper, fuzzyVars[i]);
    }

    nameHelper = action.name;
    if (nameHelper.isEmpty())
    {
        nameHelper = "Out";
    }
    fuzzyOutput = new Variable(fuzzyBlock, nameHelper);
    fuzzyBlock->addVariable(nameHelper, fuzzyOutput);


    // Space Partitioning Input State Variables Using Membership functions
    double step, center, gsigma;
    double left, right;
    for (int i = 0; i < numOfStateVars; i++)
    {
        step = (stateVars.at(i).max - stateVars.at(i).min) / ((double) stateVars.at(i).nSeg);
        gsigma = step / 3.0;

        for (int j = 0; j <= stateVars.at(i).nSeg; j++)
        {
            center = (j * step) + stateVars.at(i).min;
            left = center - step;
            right = center + step;
            nameHelper.sprintf("ip%d%d",i,j); // Input Partition

            /*

              Some Notes on shape of membership functions,
              It seems that evenly places triangular MFs over space
              is the best choice, because there's no bias over input space,
              Both Guassian and Trapziodal work worse!
            */
            //qDebug() << "Adding GMF for " << i << " #" << j << " name: " << nameHelper << " (" << center << "," << gsigma << ")";

            /*
            fuzzyBlock->setVariable(
                    fuzzyVars[i]->getName(),
                    new LinguisticTerm(
                            fuzzyBlock,
                            nameHelper,
                            new MembershipFunctionGauss(fuzzyBlock, center, gsigma)
                            )
                    );            
            */


            fuzzyBlock->setVariable(
                    fuzzyVars[i]->getName(),
                    new LinguisticTerm(
                            fuzzyBlock,
                            nameHelper,
                            new MembershipFunctionTrian(fuzzyBlock, left, center, right)
                            //new MembershipFunctionTrap(fuzzyBlock, left, center - (step / 2.0), center + (step / 2.0), right)
                            )
                            );

        }
    }

    // Partioning Output Variable


    for (int j = 0; j < numOfRules; j++)
    {
        nameHelper.sprintf("o%d",j); // Output Partition
        //qDebug() << "Action Singleton " << " #" << j << " name: " << nameHelper << " @ " << o[j];
        fuzzyBlock->setVariable(
                fuzzyOutput->getName(),
                new LinguisticTerm(
                        fuzzyBlock,
                        nameHelper,
                        new MembershipFunctionSingleton(fuzzyBlock, o[j])
                        //new MembershipFunctionTrian(fuzzyBlock, (center-step > action.min) ? center-step : action.min, center, (center+step < action.max) ? center + step : action.max)
                        )
                );

    }

    // Defuzzifier
    fuzzyDefuzz = fuzzyBlock->createDefuzzifier("cogs");
    fuzzyBlock->setDefuzzifier(fuzzyOutput->getName(), fuzzyDefuzz);

    // Rule Block (Configuration for TS Type 0 FIS)
    fuzzyRuleBlock = new RuleBlock(fuzzyBlock);

    RuleConnectionMethod *AND = new RuleConnectionMethodAndProduct();
    RuleConnectionMethod *OR = new RuleConnectionMethodOrMax();

    fuzzyRuleBlock->addRuleAccumulationMethod(new RuleAccumulationMethodSum(fuzzyBlock)); // [MAX|BSUM|NSUM|PROBOR|SUM]
    //fuzzyRuleBlock->addRuleAccumulationMethod(new RuleAccumulationMethodMax(fuzzyBlock)); // [MAX|BSUM|NSUM|PROBOR|SUM]
    fuzzyRuleBlock->setRuleConnectionMethodAnd(AND); // [MIN|BDIF|PROD]
    fuzzyRuleBlock->setRuleConnectionMethodOr(OR); // [MAX|ASUM|BSUM]
    fuzzyRuleBlock->addRuleActivationMethod(new RuleActivationMethodProduct(fuzzyBlock)); // [MIN|PROD]
    //fuzzyRuleBlock->addRuleActivationMethod(new RuleActivationMethodMin(fuzzyBlock)); // [MIN|PROD]

    // Rule Generation Part
    QString ruleText;
    int* index = new int[numOfStateVars];
    for (int i = 0; i < numOfStateVars; i++)
    {
        index[i] = 0;
    }


    for (int r = 0; r < numOfRules; r++)
    {
        ruleText = "IF ";
        for (int i = 0; i < numOfStateVars; i++)
        {
            nameHelper.sprintf("ip%d%d",i,index[i]); // Input Partition
            ruleText.append(" ("+stateVars.at(i).name+" IS "+nameHelper+") ");
            if (i < (numOfStateVars - 1))
            {
                ruleText.append(" AND ");
            }
        }


        // We Actually Do not need to consider Outputs in FIS
        // However I do it to test the FIS
        // If we want to use the FIS output, we should update all rules in each step
        // Instead we just use the rules activation
        // And calculate output outside the FIS block using simple weigthed average

        //ruleText.append(" THEN " + action.name + " IS " + QString::number(o[r]));
        nameHelper.sprintf("o%d",r); // Output Partition
        ruleText.append(" THEN " + action.name + " IS " + nameHelper + ";");
        //qDebug() << ruleText.toLower();
        fuzzyRuleBlock->addRule(*(fuzzyParser->loadRule(*fuzzyBlock, ruleText.toLower(), QString::number(r), AND, OR)));

        // Count in a way that all combination of variables and MFs are generated
        int i = 0;
        bool doLoop = true;
        while ((i < numOfStateVars) && (doLoop == true))
        {
            doLoop = false;
            index[i]++;
            if (index[i] > stateVars.at(i).nSeg)
            {
                index[i] = 0;
                doLoop = true;
                i++;
            }
        }

    }

    delete [] index;

    // Finally Add the Rule Block to the Fuzzy Function Block

    fuzzyBlock->addRuleBlock(fuzzyRuleBlock);

    //qDebug() << fuzzyBlock->toString();

}

void MFuzzyLearnerBase::saveLearnerToFile(QString fileName, bool quiet)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Save Failed!";
        return;
    }
    QDataStream ds(&file);

    if (!quiet)
    {
        qDebug() << "Writing Fuzzy Learner Date into : " << fileName;
    }

    /* Writing Header Commons(implemented in base) */
    saveHeader(ds, _M_TYPE_FUZZY, quiet);

    /* Writing Tile Learner specific Data */

    ds << (double) discountFactor;
    ds << (double) learningRate;
    ds << (double) etLambda;
    ds << (double) etLambdaActor;
    ds << (double) epsilon;
    ds << (double) noiseWeight;
    ds << (double) minTraceTreshhold;
    ds << (double) Ka;
    ds << (double) phiConstant;
    ds << (double) thetaConstant;

    /* Writing W and O (Experiences) */
    ds << (qint32) numOfRules;

    for (int i = 0; i < numOfRules; i++)
    {
        for (int j = 0; j < action.numOfSingletons; j++)
        {            
            ds << (double) w[i][j];
        }
    }

    for (int i = 0; i < numOfRules; i++)
    {
        ds << (double) o[i];
    }

    file.close();

}

void MFuzzyLearnerBase::initLearnerFromFile(QString fileName, bool quiet)
{
    if (!quiet)
    {
        qDebug() << "Reading input file " << fileName << "as MLearner Fuzzy file...";
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Load Failed!";
        return;
    }
    QDataStream ds(&file);

    int type = readHeader(ds, quiet);

    if (type != _M_TYPE_FUZZY)
    {
        qDebug() << "Invalid File Type!";
        file.close();
        return;
    }

    qint32 _numOfRules;
    double _discountFactor, _learningRate, _etLambda, _etLambdaActor, _epsilon, _noiseWeight, _minTT, _Ka, _phiConstant, _thetaConstant;

    ds >> _discountFactor >> _learningRate >> _etLambda >> _etLambdaActor >> _epsilon >> _noiseWeight >>  _minTT >> _Ka >> _phiConstant >> _thetaConstant;

    if (!quiet)
    {
        qDebug() << "**** Summary ****";
        qDebug() << "Discount Factor : " << _discountFactor;
        qDebug() << "Learning Rate : " << _learningRate;
        qDebug() << "Labmda[Critic] : " << _etLambda;
        qDebug() << "Labmda Actor : " << _etLambdaActor;
        qDebug() << "Epsilon : " << _epsilon;
        qDebug() << "Noise Weight : " << _noiseWeight;
        qDebug() << "Min ET Threshold : " << _minTT;
        qDebug() << "Ka : " << _Ka;
        qDebug() << "Phi(Constant) : " << _phiConstant;
        qDebug() << "Theta(Constant) : " << _thetaConstant;
    }

    initLearner(_discountFactor, _learningRate, _etLambda, _etLambdaActor, _epsilon, _noiseWeight, _minTT, _Ka, _phiConstant, _thetaConstant);

    ds >> _numOfRules;

    if (!quiet)
    {
        qDebug() << "Number of Rules : " << _numOfRules;
    }

    if (_numOfRules != numOfRules)
    {
        qDebug() << "Something critical is wrong in file!";
        file.close();
        return;
    }

    for (int i = 0; i < numOfRules; i++)
    {
        for (int j = 0; j < action.numOfSingletons; j++)
        {
            ds >> w[i][j];
        }
    }

    for (int i = 0; i < numOfRules; i++)
    {
        ds >> o[i];
    }

    if (!quiet)
    {
        qDebug() << "File successfully loaded and the learner has been initialized.";
    }

    file.close();
}

void MFuzzyLearnerBase::resetAllVars()
{
    v = Q = optimalQ = 0.0;    
    eCrtitic->decayTraces(0.0);
    for (int i = 0; i < action.numOfSingletons; i++)
    {
        eActor[i]->decayTraces(0.0);
    }

    for (int i = 0; i < numOfRules; i++)
    {
        o[i] = 0.0;
        phi[i] = 0.0;
        alpha[i] = 0.0;
        Ut[i] = 0;
        valUt[i] = 0.0;
        sigma[i] = 0.0;
        sigmaBar[i] = 0.0;
        ruleLearningRates[i] = learningRate;

        for (int j = 0; j < action.numOfSingletons; j++)
        {
            w[i][j] = 0.0;
            n[i][j] = 0;
        }
    }
}


void MFuzzyLearnerBase::loadFIS()
{

    for (int i = 0; i < numOfStateVars; i++)
    {
        fuzzyBlock->setValue(stateVars.at(i).name, stateVars.at(i).val);
    }

    fuzzyBlock->evaluate();
}

void MFuzzyLearnerBase::loadPhi()
{
    /* From Inside of evaluate() from jFuzzyQt */

    int count;
    double sum, dos;
    QHashIterator<QString, RuleBlock*> j(fuzzyBlock->getRuleBlocks());
    while (j.hasNext()) {
        j.next();
        j.value()->evaluate();
        count = 0;
        sum = 0.0;
        for (QLinkedList<Rule>::iterator i = j.value()->rules.begin(); i != j.value()->rules.end(); ++i)
        {
            //qDebug() << "Degree of Support : " << QString::number(i->getDegreeOfSupport(), 6, 4);
            //qDebug() << i->toString();
            dos = i->getDegreeOfSupport();
            alpha[count] = dos;
            count++;
            sum += dos;
            //qDebug() << count << QString::number(dos, 6, 2);
        }
    }

    for (count = 0; count < numOfRules; count++)
    {
        //qDebug() << count << QString::number(alpha[count], 6, 2) << QString::number(phi[count], 6, 2);
        phi[count] = alpha[count] / sum;
    }
}

double MFuzzyLearnerBase::getEEAction(int i, int a, double eps, double sf)
{
    //qDebug() << i << a << eps;
    // The first term is exploition term
    // The Second term is "Directed" Exploration (eps)
    // The Third term is "Undirected" Explration (sf)
    /*
        Refering to Joufe[1998] undirected exploration must be done using a exponential distribution
        Here I use the simpler uniform distribution
        If ever wanted to change the distro, please note that
        in calculating sf (in parent function), there must be a division
        to maximum value of distribution, here it is omitted because it is 1.0
        TODO: More research on distribution
    */
    return w[i][a] + (eps / exp(double(n[i][a]))) + (sf * (double(rand()) / RAND_MAX));
}

void MFuzzyLearnerBase::updateAndSelectLocalActions(double directedExplorationWeight, double undirectedExplorationWeight)
{

    // First Level - Action Selection for each [ACTIVATED] Rule

    double ee;
    int br;

    for (int i = 0; i < numOfRules; i++)
    {
        //qDebug() << "First Step for Rule" << i;
        if (alpha[i] == 0)
        {
            Ut[i] = -1000.0;
            valUt[i] = -1e10;
            continue;
        }

        double minW = w[i][0];
        double maxW = w[i][0];

        for (int j = 1; j < action.numOfSingletons; j++)
        {
            if (w[i][j] < minW) minW = w[i][j];
            if (w[i][j] > maxW) maxW = w[i][j];
        }

        // Undirected exploration factor (very important)

        double compiledUndirectedExplorationWeight = 0.0;
        if (undirectedExplorationWeight != 0.0)
        {
            compiledUndirectedExplorationWeight = (minW == maxW) ? 1.0 : (undirectedExplorationWeight * (maxW - minW));
        }

        Ut[i] = 0;
        valUt[i] = getEEAction(i, 0, directedExplorationWeight, compiledUndirectedExplorationWeight);
        //qDebug() << "Rule : " << i << "Action : " << 0 << valUt[0];
        br = 1;
        for (int j = 1; j < action.numOfSingletons; j++)
        {
            //qDebug() << "First Step for Rule" << i << "Action" << j;

            ee = getEEAction(i, j, undirectedExplorationWeight, compiledUndirectedExplorationWeight);
            //qDebug() << "Rule : " << i << "Action : " << j << ee;
            if (ee >= valUt[i])
            {
                if (ee > valUt[i])
                {
                    Ut[i] = j;
                    valUt[i] = ee;
                }
                else
                // This style is inspired by Sutton work from his tile coding example
                // When there are two equal values, the selection must be unbiased
                {
                    br++;
                    if (0 == rand() % br)
                    {
                        Ut[i] = j;
                        valUt[i] = ee;
                    }
                }
            }
        }
        //qDebug() << "R: " << i << "BA:" << Ut[i] << "BAV:" << valUt[i] << "AL:" << alpha[i] << "NET: " << alpha[i] * valUt[i];
    }


}

int MFuzzyLearnerBase::selectGlobalAction()
{
    int bestA;
    double valueBestA;

    int startingRule = 0;
    while ((startingRule < numOfRules) && (alpha[startingRule] == 0.0))
    {
        startingRule++;
    }

    bestA = Ut[startingRule];
    valueBestA = valUt[startingRule] * alpha[startingRule];
    n[startingRule][Ut[startingRule]]++;

    int br = 1;
    double ee;
    for (int i = startingRule+1; i < numOfRules; i++)
    {
        //qDebug() << "Second Step for Rule" << i;
        if (alpha[i] == 0.0) continue;
        n[i][Ut[i]]++;
        ee = valUt[i] * alpha[i];
        if (ee >= valueBestA)
        {
            if (ee > valueBestA)
            {
                bestA = Ut[i];
                valueBestA = ee;
            }
            else
            {
                br++;
                if (0 == rand() % br)
                {
                    bestA = Ut[i];
                    valueBestA = ee;
                }
            }
        }
    }
    //qDebug() << "Best :" << bestA << valueBestA;

    return bestA;
}

void MFuzzyLearnerBase::updateAdaptiveLearningRates()
{
    // Adaptive Learning Rate (End of Loop)
    // Based on Joufe Delta-Bar-Delta Heuristic (I renamed delta to sigma : sigma-bar-sigma)
    // Believe me these Greek letters are of no use ^.^
    // TODO : Only use valid traces

    double sigmaBarMemory;
    for (int i = 0; i < numOfRules; i++)
    {
        if (alpha[i] == 0.0) continue;

        //if (etLambda != 0.0)
        //{  // FACL
            sigma[i] = delta * eCrtitic->getTrace(i);
        //}
        //else // FQL
        //{
        //    sigma[i] = delta * alpha[i];
        //}
        sigmaBarMemory = sigmaBar[i];
        sigmaBar[i] = (phiConstant * sigmaBarMemory) + ( (1.0 - phiConstant) * sigma[i]);

        double prod = sigmaBarMemory * sigma[i];

        if (prod > 0.0)
        {
            ruleLearningRates[i] += Ka;
        }
        else if (prod < 0.0)
        {
            ruleLearningRates[i] *= (1.0 - thetaConstant);
        }

    }
}

void MFuzzyLearnerBase::updateEligibilityTraces()
{
    //if (etLambda != 0.0)
    //{
        eCrtitic->decayTraces(discountFactor * etLambda);
        for (int i = 0; i < numOfRules; i++)
        {
            if (alpha[i] == 0.0) continue;
            eCrtitic->setTrace(i, alpha[i] + eCrtitic->getTrace(i));
        }
    //}

    for (int j = 0; j < action.numOfSingletons; j++)
    {
        eActor[j]->decayTraces(etLambdaActor);
    }

    // Replacing Traces for Actor

    // Remove Other Traces

    for (int j = 0; j < action.numOfSingletons; j++)
    {
        if (j != action.val)
        {
            for (int i = 0; i < numOfRules; i++)
            {
                // The following skip is necessary?
                //if (alpha[i] == 0.0) continue;
                eActor[j]->clearTrace(i);
            }
        }
    }
    
    // Replace Traces
    for (int i = 0; i < numOfRules; i++)
    {
        if (alpha[i] == 0.0) continue;
        eActor[Ut[i]]->setTrace(i, 1.0);
        //double c = eActor[Ut[i]]->getTrace(i);
        //eActor[Ut[i]]->setTrace(i, alpha[i] + c);
    }
}
