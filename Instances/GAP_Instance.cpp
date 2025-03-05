#include "GAP_Instance.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>




GAP_Instance::GAP_Instance(const std::string &name, const std::vector <std::vector <int>> &costMatrix, const std::vector <std::vector <int>> &resourceMatrix, const std::vector <int> &maxResources) : ProblemInstance(name), costMatrix(costMatrix), resourceMatrix(resourceMatrix), maxResources(maxResources) {}

//printa il nome dell'istanza
void GAP_Instance::print(std::ostream &os) const {
    os << "GAP Instance: " << name << std::endl;
}

//metodi get
const std::vector<std::vector<int>>& GAP_Instance::getCostMatrix() const {
    return costMatrix;
}

const std::vector<std::vector<int>>& GAP_Instance::getResourceMatrix() const {
    return resourceMatrix;
}

const std::vector<int>& GAP_Instance::getMaxResources() const {
    return maxResources;
}

int GAP_Instance::getAgentsN() {
    return costMatrix.size();
}

int GAP_Instance::getJobsN() {
    return costMatrix.empty() ? 0 : costMatrix[0].size();
}