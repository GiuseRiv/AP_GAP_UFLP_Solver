#include "ProblemInstance.h"
#include "ProblemSolver.h"
#include "ProblemSolution.h"
#include "Instances/AP_Instance.h"
#include "Solvers/AP_Solver.h"
#include "Solutions/AP_Solution.h"
#include "Instances/GAP_Instance.h"
#include "Solvers/GAP_Solver.h"
#include "Solutions/GAP_Solution.h"
#include "Instances/UFLP_Instance.h"
#include "Solvers/UFLP_Solver.h"
#include "Solutions/UFLP_Solution.h"
#include "CreateProblemInstance.h"

int main() {

//variabile che contiene il nome del file
std::string filename;
//tipo problemtype: AP, GAP, UFLP
ProblemType problemtype;


    
    std::cout << "Inserisci il tipo di problema (AP, GAP, UFLP): " << std::endl;
    try {
        std::cin >> problemtype;
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    std::cout << "inserici il nome del file (includi .txt): " << std::endl;
    std::cin >> filename;



        // Creare un'istanza 
        std::shared_ptr<ProblemInstance> currentInstance = CreateProblemInstance(problemtype, filename);
        std::cout << "Istanza creata con successo!" << std::endl;
        

        //risolvi e conserva la soluzione in ProblemSolution
        //è a questo livello che si va sul concreto; o meglio che viene riconosciuto il tipo problema e si applica il solver specifico (switch case per gestire)
        std::shared_ptr<ProblemSolver> solver;
        switch (problemtype) {
            default: {
                std::cerr << "Tipo di problema non riconosciuto!" << std::endl;
                return 1;
            }            
            case AP: {
                solver = std::make_shared<AP_Solver>();
                break;
            }
            case GAP: {
                solver = std::make_shared<GAP_Solver>();
                break;
            }
            case UFLP: {
                solver = std::make_shared<UFLP_Solver>();
                break;
            }
        }

        std::cout << "Inizio risoluzione del problema..." << std::endl;
        std::shared_ptr<ProblemSolution> currentSolution = solver->solve(currentInstance);
        std::cout << "Risoluzione completata." << std::endl;

        //printa la soluzione
        if (currentSolution) {
            currentSolution->print(std::cout);
        } else {
            std::cerr << "Nessuna soluzione trovata." << std::endl;
            return 1;
        }

         // Scrive la soluzione in un file di testo
        if (currentSolution) {
            std::ofstream outFile("solution_" + filename + ".txt");
        if (!outFile) {
            std::cerr << "Errore nell'apertura del file per scrivere la soluzione." << std::endl;
            return 1;
        }
        currentSolution->print(outFile);
        outFile.close();
        std::cout << "La soluzione è stata scritta su solution_" + filename + ".txt" << std::endl;
    }

}



