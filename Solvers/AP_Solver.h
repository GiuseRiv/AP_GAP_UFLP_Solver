#ifndef AP_SOLVER_H
#define AP_SOLVER_H

#include "../ProblemSolver.h"
#include "../ProblemSolution.h"
#include "../Instances/AP_Instance.h"
#include "../Solutions/AP_Solution.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>

class AP_Solver : public ProblemSolver {

public:

    // Costruttore (esplicitato ma superfluo)
    AP_Solver() = default;

    // Distruttore virtuale di default
    virtual ~AP_Solver() = default;

    //metodo che contiene l'algoritmo di risoluzione vero e proprio
    std::shared_ptr<ProblemSolution> solve(const std::shared_ptr<ProblemInstance>& instance) override;


};

#endif