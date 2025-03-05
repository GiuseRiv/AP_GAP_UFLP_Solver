
#ifndef UFLP_INSTANCE_H
#define UFLP_INSTANCE_H

#include "../ProblemInstance.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>

class UFLP_Instance : public ProblemInstance {

public: 

    //costruttore di istanza
    UFLP_Instance(const std::string &name, const std::vector <std::vector <int>> &costMatrix, const std::vector<int> &openingCost);

    // Distruttore virtuale di default
    virtual ~UFLP_Instance() = default;

    //ritorna la matrice dell'istanza
    const std::vector<std::vector<int>>& getCostMatrix() const;
    //ritorna il vettore di costi di apertura deposito
    const std::vector<int>& getOpeningCost() const;
    //ritorna numero clienti
    int getClientsN();
    int getDepositsN();

    //metodo per printare la matrice di costi
    void print(std::ostream& os) const override;

private: 
    //membro privato: nome istanza
    std::string name;
    //membro privato: matrice di costi
    std::vector<std::vector <int>> costMatrix;
    //membro privato: costi apertura
    std::vector<int> openingCost;
    //come per AP e GAP, non ho la necessità di trattare numero clienti e depositi come membri, verranno recuperati dalla matrice
};

#endif