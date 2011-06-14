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

#ifndef MTDLearnerFuzzy_H
#define MTDLearnerFuzzy_H

#include "mtdlearnerbase.h"
#include "eligibiltytrace.h"

#include "jfuzzyqt/fcl/fclparser.h"
#include "jfuzzyqt/functblock.h"
#include "jfuzzyqt/defuzzifier/defuzzifiercenterofgravity.h"
#include "jfuzzyqt/defuzzifier/defuzzifiercenterofgravitysingletons.h"
#include "jfuzzyqt/rule/ruleblock.h"

#include "jfuzzyqt/membership/continuous/membershipfunctiongauss.h"
#include "jfuzzyqt/membership/discrete/membershipfunctionsingleton.h"
#include "jfuzzyqt/membership/continuous/membershipfunctiontrian.h"
#include "jfuzzyqt/membership/continuous/membershipfunctiontrap.h"

#include "jfuzzyqt/connection/ruleconnectionmethod.h"
#include "jfuzzyqt/connection/or/ruleconnectionmethodormax.h"
#include "jfuzzyqt/connection/and/ruleconnectionmethodandproduct.h"

#include "jfuzzyqt/accumulation/ruleaccumulationmethodsum.h"
#include "jfuzzyqt/accumulation/ruleaccumulationmethodmax.h"
#include "jfuzzyqt/activation/ruleactivationmethodproduct.h"
#include "jfuzzyqt/activation/ruleactivationmethodmin.h"


class MFuzzyLearnerBase : public MTDLearnerBase
{
public:
    MFuzzyLearnerBase();
    ~MFuzzyLearnerBase(); // Move to Protected if this class converted to abstract class


    /**
     * @brief
     *
     * @param _discountFactor The discount factor
     * @param _learningRate The learning rate
     * @param _etLambdaCritic The Eligibility Traces discount factor for Critic (FACL) and general for (FQL)
     * @param _etLambdaActor The Eligibility Traces discount factor for Actor (FACL), no use in FQL
     * @param _epsilon The directed exploration factor
     * @param _noiseWeight The undirected exploration factor
     * @param _minTraceTreshhold The minimum threshold for non-zero trace value
     * @param _ka The Ka constant for delta-bar-delta heurisitic
     * @param _phiConstant The phi constatnt for delta-bar-delta heuristic
     * @param _thetaConstant The theta constant for delta-bar-delta heuristic
     */
    void initLearner(double _discountFactor, double _learningRate, double _etLambdaCritic, double _etLambdaActor, double _epsilon, double _noiseWeight, double _minTraceTreshhold, double _ka, double _phiConstant, double _thetaConstant);

    // Virtuals
    void initLearnerFromFile(QString fileName, bool quiet = true);
    void saveLearnerToFile(QString fileName, bool quiet = true);
    void resetAllVars();

protected:

    // Common Variable
    int numOfRules;
    double delta;           // TD Error
    double** w;             // Quality factor for each action in each rule
    long int** n;            // Number of each action selection in each episode
    double* o;              // Consequent Singleton for each rule
    double* alpha;           // Rule Truth Values
    double* phi;            // Normalized Rule Truth Values    
    double Ka;              // Adaptive Learning Rate Constant
    double etLambdaActor;   // In FACL we have two lambdas for Eligibility Traces
    double noiseWeight;     // Noise Weight for Undirected Exploration
    double* ruleLearningRates;  // Adaptive Learning Rate for each rule
    double* sigma;         // Integrator for both TD Error and FIS Truth values
    double* sigmaBar;       // Geomatric Average of Sigmas
    double  phiConstant;    // Geomatric Average Constant
    double  thetaConstant;  // Heuristic Adaptive Learning Rate Cooficient
    int* Ut;                // e-Greedy Action selected for each rule
    double* valUt;          // e-Greedy Action Value for each rule

    CEligibiltyTrace* eCrtitic;     // Critic Eligibility Traces
    CEligibiltyTrace** eActor;       // Actor Eligibility Traces

    double**  tracesActor;
    double* tracesCritic;

    FCLParser* fuzzyParser;      // The parser is used in order to build rules based on QStrings
    FunctBlock* fuzzyBlock;         // The Main Fuzzy Function Block
    Variable**   fuzzyVars;          // Fuzzy Variable Array
    Variable* fuzzyOutput;           // Fuzzy Output (Dummy! for now)
    Defuzzifier* fuzzyDefuzz;
    RuleBlock* fuzzyRuleBlock;

    // Specific Variables

    double v;               // Value Function (FACL)
    double Q;               // Q Function (QL)
    double optimalQ;        // Q* Function (QL)

    double getEEAction(int i, int a, double eps, double sf);

    // Double e-Greedy action selection based on weights
    void updateAndSelectLocalActions(double directedExplorationWeight, double undirectedExplorationWeight);
    int selectGlobalAction();

    void updateAdaptiveLearningRates();
    void updateEligibilityTraces();

    void loadFIS();
    void loadPhi();

};

#endif // MTDLearnerFuzzy_H
