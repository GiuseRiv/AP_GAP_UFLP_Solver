

#ifndef AP_INSTANCE_H
#define AP_INSTANCE_H

#include "../ProblemInstance.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>

class AP_Instance : public ProblemInstance {

public: 

    //costruttore di istanza
    AP_Instance(std::string &name, std::vector <std::vector <int>> &costMatrix);

    // Distruttore virtuale di default
    virtual ~AP_Instance() = default;

    //ritorna la matrice dell'istanza
    const std::vector<std::vector<int>>& getCostMatrix() const;

    //metodo per printare la matrice di costi
    void print(std::ostream& os) const override;

private: 
    //membro privato: matrice di costi
    std::vector<std::vector <int>> costMatrix;

};

#endif