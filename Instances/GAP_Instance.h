#ifndef GAP_INSTANCE_H
#define GAP_INSTANCE_H

#include "../ProblemInstance.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>


class GAP_Instance : public ProblemInstance {

    public: 

    //costruttore istanza GAP, membri: nome istanza, matrice costi, matrice risorse, vettore limiti di risorse
    GAP_Instance(const std::string &name, const std::vector <std::vector <int>> &costMatrix, const std::vector <std::vector <int>> &resourceMatrix, const std::vector <int> &maxResources);

    // Distruttore virtuale di default
    virtual ~GAP_Instance() = default;

    //metodi get che ritornano i dati dell'istanza
    const std::vector<std::vector<int>>& getCostMatrix() const;
    const std::vector<std::vector<int>>& getResourceMatrix() const;
    const std::vector<int>& getMaxResources() const;
    int getAgentsN();
    int getJobsN();

    //metodo per printare l'istanza
    void print(std::ostream& os) const override;

    //membri privati dell'istanza (corrispondono ai dati dell'istanza specifica che la identificano)
private: 
    std::vector<std::vector <int>> costMatrix;
    std::vector<std::vector <int>> resourceMatrix;
    std::vector <int> maxResources;
    std::string name;
};


#endif