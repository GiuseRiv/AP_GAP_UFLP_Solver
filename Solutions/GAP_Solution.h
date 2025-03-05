#ifndef GAP_SOLUTION_H
#define GAP_SOLUTION_H

#include "../ProblemSolver.h"
#include "../ProblemSolution.h"
#include "../Instances/GAP_Instance.h"
#include "../Solutions/GAP_Solution.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>

class GAP_Solution : public ProblemSolution {

public:
    //costruttore
    GAP_Solution(const std::vector<int>& soluzione);
    // Distruttore virtuale di default
    virtual ~GAP_Solution() = default;

    //metodo per printare la soluzione
    std::ostream& print(std::ostream& os) const override;

private:
    //unico membro della classe: contiene la soluzione sotto forma di vettore di assegnamento
    std::vector<int> soluzione;

};


#endif