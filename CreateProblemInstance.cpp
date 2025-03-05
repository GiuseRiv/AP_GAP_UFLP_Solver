#include <fstream>
#include <sstream>
#include <memory>
#include <stdexcept>
#include "ProblemInstance.h"
#include "Instances/AP_Instance.h"
#include "Instances/GAP_Instance.h"
#include "Instances/UFLP_Instance.h"
#include "CreateProblemInstance.h"


//overload dell'operatore>> per leggere da input l'enum problemtype
std::istream& operator>>(std::istream& in, ProblemType &pt) {
    std::string token;
    in >> token;
    if (token == "AP" || token == "ap")
        pt = ProblemType::AP;
    else if (token == "GAP" || token == "gap")
        pt = ProblemType::GAP;
    else if (token == "UFLP" || token == "uflp")
        pt = ProblemType::UFLP;
    else {
        in.setstate(std::ios::failbit);
        throw std::invalid_argument("Tipo di problema non riconosciuto: " + token);
    }
    return in;
}

// Funzione globale per creare un'istanza del problema
std::shared_ptr<ProblemInstance> CreateProblemInstance(ProblemType problem, const std::string& filename) {
    switch (problem) {
        case AP: {
            // recuperare name e matrix da file (capire se dichiarare prima variabili filename, etc e chiamare la funzione void con reference, o fare diventare la funzione senza input e che torna in output i valori)
            std::string name;
            std::vector<std::vector<int>> costMatrix;
            // Creare un'istanza di AP_Instance
            readAPInstanceFromFile(filename, name, costMatrix); //name e costMatrix verranno aggiornati con i valori nella funzione (in quanto vengono passate in input come referenze)
                                                                      
                                                         
            return std::make_shared<AP_Instance>(name, costMatrix); //ritorna un puntatore a un oggetto AP_Instance con quel nome e quella matrice
            break;
        }
        case GAP: {
            // Creare un'istanza di GAP_Instance
            std::string name;
            std::vector<std::vector<int>> costMatrix;
            std::vector<std::vector<int>> resourceMatrix;
            std::vector<int> maxResources;
            readGAPInstanceFromFile(filename, name, costMatrix, resourceMatrix, maxResources);


            return std::make_shared<GAP_Instance>(name, costMatrix, resourceMatrix, maxResources);
            break;
        }
        case UFLP: {
            // Creare un'istanza di UFLP_Instance (con dichiarazione delle variabili)
            std::string name;
            std::vector<std::vector<int>> costMatrix;
            std::vector<int> openingCosts;

            readUFLPInstanceFromFile(filename, name, costMatrix, openingCosts);

            return std::make_shared<UFLP_Instance>(name, costMatrix, openingCosts);
            break;
        }
            
        default:
            throw std::invalid_argument("Tipo di problema non supportato");
    }
    return nullptr;
}



//funzione helper per recuperare name e matrix istanza AP
void readAPInstanceFromFile(const std::string& filename, std::string& name, std::vector<std::vector<int>>& costMatrix) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Impossibile aprire il file: " + filename);
    }

    //viene utilizzata una chiave (key) per localizzare correttamente le porzioni di testo rispetto alle variabili alle quali devono essere assegnate
    int n;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        iss >> key;

        if (key == "NAME:") {
            iss >> name;
            std::cout << "Nome istanza letto: " << name << std::endl;
        } else if (key == "n:") {
            iss >> n;
            std::cout << "Dimensione della matrice letta: " << n << "x" << n << std::endl;
        } else if (key == "c_ij:") {
            std::cout << "Inizio lettura matrice..." << std::endl;
            costMatrix.resize(n, std::vector<int>(n));
            for (int i = 0; i < n; ++i) {
                if (!std::getline(file, line)) {
                    throw std::runtime_error("Errore nella lettura della riga della matrice.");
                }
                std::istringstream rowStream(line);
                for (int j = 0; j < n; ++j) {
                    if (!(rowStream >> costMatrix[i][j])) {
                        throw std::runtime_error("Errore nel parsing della matrice alla riga " + std::to_string(i) + ", colonna " + std::to_string(j));
                    }
                }
            }
            std::cout << "Matrice letta con successo." << std::endl;
            for (const auto& row : costMatrix) {
                for (const auto& value : row) {
                    std::cout << value << " ";
                }
                std::cout << std::endl;
            }
        }
    }
}



void readGAPInstanceFromFile(const std::string& filename, std::string& name, std::vector<std::vector<int>>& costMatrix, std::vector<std::vector<int>>& resourceMatrix, std::vector<int>& maxResources) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Impossibile aprire il file: " + filename);
    }

    int n;
    int m;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        iss >> key;

        if (key == "NAME:") {
            iss >> name;
            std::cout << "Nome istanza letto: " << name << std::endl;
        } else if (key == "m:") {
            iss >> m;
            std::cout << "numero di agenti: " << m << std::endl;
        } else if (key == "n:") {
            iss >> n;
            std::cout << "numero di compiti: " << n << std::endl;
        } else if (key == "c_ij:") {
            std::cout << "Inizio lettura matrice costi..." << std::endl;
            costMatrix.resize(m, std::vector<int>(n));
            for (int i = 0; i < m; ++i) {
                if (!std::getline(file, line)) {
                    throw std::runtime_error("Errore nella lettura della riga della matrice costi.");
                }
                std::istringstream rowStream(line);
                for (int j = 0; j < n; ++j) {
                    if (!(rowStream >> costMatrix[i][j])) {
                        throw std::runtime_error("Errore nel parsing della matrice alla riga " + std::to_string(i) + ", colonna " + std::to_string(j));
                    }
                }
            }
            std::cout << "Matrice costi letta con successo." << std::endl;
        } else if (key == "r_ij:") {
            std::cout << "Inizio lettura matrice risorse..." << std::endl;
            resourceMatrix.resize(m, std::vector<int>(n));
            for (int k = 0; k < m; ++k) {
                if (!std::getline(file, line)) {
                    throw std::runtime_error("Errore nella lettura della riga della matrice risorse.");
                }
                std::istringstream rowStream(line);
                for (int l = 0; l < n; ++l) {
                    if (!(rowStream >> resourceMatrix[k][l])) {
                        throw std::runtime_error("Errore nel parsing della matrice alla riga " + std::to_string(k) + ", colonna " + std::to_string(l));
                    }
                }
            }
            std::cout << "Matrice risorse letta con successo." << std::endl;
           // for (const auto& row : resourceMatrix) {
           //     for (const auto& value : row) {
           //         std::cout << value << " ";
           //     }
           //     std::cout << std::endl;
           // }
        } else if (key=="b_i:") {
            if (!std::getline(file, line)) {
                throw std::runtime_error("Errore nella lettura delle risorse massime.");
            }
            std::istringstream rowStream(line);
            maxResources.resize(m);
            for (int indexx = 0; indexx < m; ++indexx) {
                if (!(rowStream >> maxResources[indexx])) {
                    throw std::runtime_error("Errore nel parsing delle risorse massime all'indice " + std::to_string(indexx));
                }
            }
            std::cout << "Risorse massime lette con successo." << std::endl;
        }
    }
}





void readUFLPInstanceFromFile(const std::string& filename, std::string& name, std::vector<std::vector<int>>& costMatrix, std::vector<int>& openingCosts) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Impossibile aprire il file: " + filename);
    }

    int n;
    int m;
    std::string line;
    while (std::getline(file, line)) {
    //viene utilizzata una chiave (key) per localizzare correttamente le porzioni di testo rispetto alle variabili alle quali devono essere assegnate
        std::istringstream iss(line);
        std::string key;
        iss >> key;

        //se da file si legge "NAME:" ciò che ne segue fino alla prossima key viene immagazzinato nella variabile name
        if (key == "NAME:") {
            iss >> name;
            std::cout << "Nome istanza letto: " << name << std::endl;
        } else if (key == "m:") {
            iss >> m;
            std::cout << "numero di depositi potenziali: " << m << std::endl;
        } else if (key == "n:") {
            iss >> n;
            std::cout << "numero di clienti: " << n << std::endl;
        } else if (key == "c_ij:") {
            //lettura matrice costi
            std::cout << "Inizio lettura matrice costi..." << std::endl;
            costMatrix.resize(m, std::vector<int>(n));
            for (int i = 0; i < m; ++i) {
                if (!std::getline(file, line)) {
                    throw std::runtime_error("Errore nella lettura della riga della matrice costi.");
                }
                std::istringstream rowStream(line);
                for (int j = 0; j < n; ++j) {
                    if (!(rowStream >> costMatrix[i][j])) {
                        throw std::runtime_error("Errore nel parsing della matrice alla riga " + std::to_string(i) + ", colonna " + std::to_string(j));
                    }
                }
            }
            std::cout << "Matrice costi letta con successo." << std::endl;
           
        } else if (key=="f_i:") {
            if (!std::getline(file, line)) {
                throw std::runtime_error("Errore nella lettura dei costi di apertura deposito.");
            }
            std::istringstream rowStream(line);
            openingCosts.resize(m);
            for (int indexx = 0; indexx < m; ++indexx) {
                if (!(rowStream >> openingCosts[indexx])) {
                    throw std::runtime_error("Errore nel parsing dei costi di apertura deposito all'indice " + std::to_string(indexx));
                }
            }
            std::cout << "costi di apertura deposito letti con successo." << std::endl;
        }

}
}