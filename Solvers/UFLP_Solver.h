#ifndef UFLP_SOLVER_H
#define UFLP_SOLVER_H

#include "../ProblemSolver.h"
#include "../ProblemSolution.h"
#include "../Instances/UFLP_Instance.h"
#include "../Solutions/UFLP_Solution.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>

class UFLP_Solver : public ProblemSolver {

public:

      // Costruttore (desfault esplicitato)
      UFLP_Solver() = default;

      // Distruttore virtuale di default
      virtual ~UFLP_Solver() = default;

    //metodo che contiene l'algoritmo di risoluzione vero e proprio
    std::shared_ptr<ProblemSolution> solve(const std::shared_ptr<ProblemInstance>& instance) override;


};

#endif