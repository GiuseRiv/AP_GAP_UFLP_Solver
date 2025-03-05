#include "AP_Solution.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>

AP_Solution::AP_Solution(const std::vector<int>& soluzione) : soluzione(soluzione) {}

//NB le soluzioni sono espresse con indici per agenti e compiti che partono da 0 (il primo agente è agente 0)
std::ostream& AP_Solution::print(std::ostream& os) const {
    os << "Soluzione all'istanza AP:" << std::endl;
    for (size_t i = 0; i < soluzione.size(); i++) {
        os << "Agente " << i << " -> Compito " << soluzione[i] << std::endl;
    }
    return os;  
}



