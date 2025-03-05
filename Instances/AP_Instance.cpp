#include "AP_Instance.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>



//costruttore (membri: nome istanza e matrice costi, nome istanza in realtà e superfluo, la matrice dei costi identifica univocamente l'istanza)
AP_Instance::AP_Instance(std::string &name, std::vector <std::vector <int>> &costMatrix) : ProblemInstance(name), costMatrix(costMatrix) {}

//ritorna la matrice di costi
const std::vector<std::vector<int>>& AP_Instance::getCostMatrix() const {
        return costMatrix;
    }


//printa il nome istanza e la matrice di costi
void AP_Instance::print(std::ostream& os) const {
        std::cout << "current instance:" << getName() << std::endl;

        for (const auto& row : costMatrix) {
            for (auto& cost : row) {
                os << cost << " ";
            }
            os << std::endl;
        }
    }