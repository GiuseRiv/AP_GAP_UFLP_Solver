//Rappresentare una soluzione: Ogni classe derivata di ProblemSolution incapsulerà la soluzione di un particolare tipo di problema.
//Interfaccia di visualizzazione: La classe fornisce il metodo print(), che consente di stampare la soluzione in un formato appropriato.


#ifndef PROBLEM_SOLUTION_H
#define PROBLEM_SOLUTION_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

class ProblemSolution {

public: 
    // Distruttore virtuale
    virtual ~ProblemSolution() {}

   
    // Metodo virtuale puro per stampare la soluzione
    virtual std::ostream& print(std::ostream& os) const = 0;

};



#endif