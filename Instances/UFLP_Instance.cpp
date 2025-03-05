#include "UFLP_Instance.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>




UFLP_Instance::UFLP_Instance(const std::string &name, const std::vector <std::vector <int>> &costMatrix, const std::vector <int> &openingCost) : ProblemInstance(name), costMatrix(costMatrix), openingCost(openingCost) {}

//printa il nome dell'istanza
void UFLP_Instance::print(std::ostream &os) const {
    os << "UFLP Instance: " << name << std::endl;
}

//metodi get
const std::vector<std::vector<int>>& UFLP_Instance::getCostMatrix() const {
    return costMatrix;
}

const std::vector<int>& UFLP_Instance::getOpeningCost() const {
    return openingCost;
}

int UFLP_Instance::getDepositsN() {
    return costMatrix.size();
}

int UFLP_Instance::getClientsN() {
    return costMatrix.empty() ? 0 : costMatrix[0].size();
}