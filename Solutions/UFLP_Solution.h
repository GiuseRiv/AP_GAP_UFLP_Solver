#ifndef UFLP_SOLUTION_H
#define UFLP_SOLUTION_H

#include "../ProblemSolver.h"
#include "../ProblemSolution.h"
#include "../Instances/GAP_Instance.h"
#include "../Solutions/GAP_Solution.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>

class UFLP_Solution : public ProblemSolution {

public:
    //costruttore
    UFLP_Solution(const std::vector<int>& soluzione);
    // Distruttore virtuale di default
    virtual ~UFLP_Solution() = default;

    //metodo per printare la soluzione
    std::ostream& print(std::ostream& os) const override;

private:
    //unico membro della classe: contiene la soluzione sotto forma di vettore di assegnamento
    std::vector<int> soluzione;

};


#endif