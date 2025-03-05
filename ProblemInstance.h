//Rappresentare un'istanza di un problema computazionale: Ogni oggetto di tipo ProblemInstance incapsula i dati e le informazioni necessarie per rappresentare un problema concreto da risolvere.
//Gestire i dati del problema: Le informazioni che caratterizzano il problema (es. variabili, condizioni iniziali) saranno memorizzate come attributi della classe.

#ifndef PROBLEM_INSTANCE_H
#define PROBLEM_INSTANCE_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

class ProblemInstance {

protected:
    //membro instanceName per identificare le istanze
    std::string instanceName;
    
    //int m, n; //rappresentano il numero di agenti e di compiti, ho scelto di non istanziarli come membri della classe istance, verranno recuperati direttamente dalla matrice dei costi

public:

    //constructor con il nome istanza
    ProblemInstance(const std::string &name) : instanceName(name) {}

    //constructor per una eventuale istanza vuota 
    ProblemInstance() : instanceName("IstanzaVuota") {}

    //destructor virtuale (per le classi concrete)
    virtual ~ProblemInstance() = default;

    //copy const (rule of three)
    ProblemInstance(const ProblemInstance &other) : instanceName(other.instanceName) {}

    //funzione che torna il nome dell'istanza 
    std::string getName() const {
        return instanceName;
    }


    // Metodo virtuale puro per stampare i dettagli dell'istanza
    virtual void print(std::ostream &os) const = 0;


};

#endif