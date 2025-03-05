#include "UFLP_Solution.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>

UFLP_Solution::UFLP_Solution(const std::vector<int>& soluzione) : soluzione(soluzione) {}


//NB le soluzioni sono espresse con indici per depositi e clienti che partono da 0 (il primo cliente è cliente 0)
std::ostream& UFLP_Solution::print(std::ostream& os) const {
    os << "Soluzione all'istanza UFLP:" << std::endl;
    for (size_t i = 0; i < soluzione.size(); i++) {
        os << "Cliente " << i << " -> Deposito " << soluzione[i] << std::endl;
    }
    return os;  
}
