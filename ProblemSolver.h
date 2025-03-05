
//Gestire il processo di soluzione: La classe dovrebbe gestire il ciclo di vita di un problema, ricevendo un'istanza del problema, applicando l'algoritmo e restituendo una soluzione.
//è a questo livello che si associa un solutore a una istanza specifica (quindi a questo livello viene applicata lo specifico metodo solve rispetto al tipo di problema)
//SOLVE: algoritmo di risoluzione;

#ifndef PROBLEM_SOLVER_H
#define PROBLEM_SOLVER_H

#include <memory>
#include "ProblemInstance.h"
#include "ProblemSolution.h"

class ProblemSolver {


    public:
    
    //constructor e copy di deafult (l'uso di share pointers rende superflua la definizione di constructor e copy specifici)

    // Distruttore virtuale //necessario?
    virtual ~ProblemSolver() = default;


    //prende un'istanza di un problema e restituisce la soluzione corrispondente.
    virtual std::shared_ptr<ProblemSolution> solve(const std::shared_ptr<ProblemInstance>& instance) = 0; 
        

};

#endif