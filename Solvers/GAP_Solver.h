#ifndef GAP_SOLVER_H
#define GAP_SOLVER_H

#include "../ProblemSolver.h"
#include "../ProblemSolution.h"
#include "../Instances/GAP_Instance.h"
#include "../Solutions/GAP_Solution.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>

class GAP_Solver : public ProblemSolver {

public:

      // Costruttore (esplicitato ma superfluo)
      GAP_Solver() = default;

      // Distruttore virtuale di default
      virtual ~GAP_Solver() = default;

    //metodo che contiene l'algoritmo di risoluzione vero e proprio
    std::shared_ptr<ProblemSolution> solve(const std::shared_ptr<ProblemInstance>& instance) override;


};

#endif