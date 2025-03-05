#ifndef AP_SOLUTION_H
#define AP_SOLUTION_H

#include "../ProblemSolver.h"
#include "../ProblemSolution.h"
#include "../Instances/AP_Instance.h"
#include "../Solutions/AP_Solution.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>

class AP_Solution : public ProblemSolution {

public:
    //costruttore 
    AP_Solution(const std::vector<int>& soluzione);
    // Distruttore virtuale di default
    virtual ~AP_Solution() = default;


    //metodo per printare la soluzione
    std::ostream& print(std::ostream& os) const override;

private:
    //unico membro della classe: contiene la soluzione sotto forma di vettore di assegnamento
    std::vector<int> soluzione;

};


#endif