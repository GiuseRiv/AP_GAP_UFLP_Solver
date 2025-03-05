#include "GAP_Solver.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <random>



//IMPLEMENTAZIONE: CON SOLVE GAP VENGONO GENERATI 1000 ASSEGNAMENTI RANDOMICI MA CHE RISPETTA I VINCOLI, TRA QUESTI SI SCEGLIE IL MIGLIORE





std::shared_ptr<ProblemSolution> GAP_Solver::solve(const std::shared_ptr<ProblemInstance>& instance) {
    std::cout << "inizio risoluzione" << std::endl;
    
    // Casting da istanza astratta a istanza specifica del GAP
    auto gapInstance = std::dynamic_pointer_cast<GAP_Instance>(instance);
    if (!gapInstance) {
        throw std::invalid_argument("L'istanza non è valida per il problema GAP.");
    }
    std::cout << "casting effettuato" << std::endl;
    
    // Ottenimento matrici e i parametri
    auto costMatrix = gapInstance->getCostMatrix();
    auto resMatrix = gapInstance->getResourceMatrix();
    auto maxRes = gapInstance->getMaxResources();
    int m = gapInstance->getAgentsN();
    int n = gapInstance->getJobsN();
    
    // Numero di soluzioni randomiche da generare
    const int numIterations = 1000;
    
    // Variabili per memorizzare la migliore soluzione trovata
    std::vector<int> bestSolution;
    int bestCost = std::numeric_limits<int>::max();
    
    // Inizializzazione del generatore di numeri casuali
    std::random_device rd;
    std::mt19937 rng(rd());
    
    // Ciclo per generare soluzioni randomiche
    for (int iter = 0; iter < numIterations; iter++) {
        // Copia della capacità residua per ogni agente (all'inizio uguale a maxRes)
        std::vector<int> remaining_capacity = maxRes;
        std::vector<int> currentSolution(n, -1);
        bool soluzioneValida = true;
        
        // Generazione di un assegnamento random per ciascun compito
        for (int i = 0; i < n; i++) {
            std::vector<int> agentiPlausibili;
            for (int j = 0; j < m; j++) {
                if (remaining_capacity[j] >= resMatrix[j][i]) {
                    agentiPlausibili.push_back(j);
                }
            }
            
            if (agentiPlausibili.empty()) {
                // Se per il compito i non esiste un agente che può eseguirlo, la soluzione non è valida
                soluzioneValida = false;
                break;
            }
            
            // Selezione casuale di un agente tra quelli plausibili
            std::uniform_int_distribution<int> dist(0, agentiPlausibili.size() - 1);
            int agent = agentiPlausibili[dist(rng)];
            currentSolution[i] = agent;
            remaining_capacity[agent] -= resMatrix[agent][i];
        }
        
        // Se l'assegnamento corrente non è valido, saltiamo alla prossima iterazione
        if (!soluzioneValida) {
            continue;
        }
        
        // Calcolo del costo totale della soluzione corrente
        int currentCost = 0;
        for (int i = 0; i < n; i++) {
            int agent = currentSolution[i];
            currentCost += costMatrix[agent][i];
        }
        
        // Aggiornamento della migliore soluzione trovata finora
        if (currentCost < bestCost) {
            bestCost = currentCost;
            bestSolution = currentSolution;
        }
    }
    
    // Verifica se è stata trovata almeno una soluzione valida
    if (bestSolution.empty()) {
        std::cerr << "Nessuna soluzione ammissibile trovata." << std::endl;
        return nullptr;
    }
    
    std::cout << "Miglior costo trovato: " << bestCost << std::endl;
    return std::make_shared<GAP_Solution>(bestSolution);
}
