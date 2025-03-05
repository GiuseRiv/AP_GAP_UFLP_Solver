#include "UFLP_Solver.h"

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <climits>
#include <random>


/*
ALTO LIVELLO
Generazione delle soluzioni randomiche
	•	Decidere casualmente quali depositi aprire.
	•	Assegnare ogni cliente a uno dei depositi aperti, scegliendo tra quelli con costo minore.
Calcolo del costo totale
	•	Sommare i costi fissi di apertura dei depositi scelti.
	•	Aggiungere i costi di trasporto per i clienti assegnati.
Ricerca della soluzione migliore
	•	Come nel solver GAP, iterare molte volte generando soluzioni randomiche.
	•	Aggiornare la soluzione migliore se si trova un costo inferiore.


BASSO LIVELLO
decidere casualmente quale depositi aprire
	•	metodo coin toss: per ogni deposito generare randomicamente 0 o 1, con 1 viene aperto, 0 resta chiuso
*/


std::shared_ptr<ProblemSolution> UFLP_Solver::solve(const std::shared_ptr<ProblemInstance>& instance) { 
    std::cout << "inizio risoluzione" << std::endl;
    
    // Casting da istanza astratta a istanza specifica UFLP
    auto uflpInstance = std::dynamic_pointer_cast<UFLP_Instance>(instance);
    if (!uflpInstance) {
        throw std::invalid_argument("L'istanza non è valida per il problema UFLP.");
    }
    std::cout << "casting effettuato" << std::endl;

    // Ottenimento matrici e i parametri
    auto costMatrix = uflpInstance->getCostMatrix();
    auto openingCost = uflpInstance->getOpeningCost();
    int n = uflpInstance->getClientsN();
    int m = uflpInstance->getDepositsN();
    
    // Numero di soluzioni randomiche da generare
    const int numIterations = 1000;

    
    //variabile che conterrà il risultato (posizione=deposito; valore in posizione=cliente assegnato)
    std::vector<int> bestAssegnamento(n, -1);
    
    
    // Inizializzazione del generatore di numeri casuali
    std::random_device rd;
    std::mt19937 rng(rd());

    //variabile che tiene in store il costo totale migliore
    int costoBestTOT = INT_MAX;

    

        // Ciclo per generare soluzioni randomiche
        for (int iter = 0; iter < numIterations; iter++) {

            //variabile che tiene in store il costo di apertura depositi
            int costoDep = 0;
            //variabile che tiene in store il costo totale
            int costoTOT = 0;
            //variabile che contiene gli assegnamenti "temporanei"
            std::vector<int> assegnamento(n, -1);


            //ciclo per determinare i depositi aperti
            std::vector<bool> openDeposits(m, false);
            for (int i = 0; i < m; i++) {
             openDeposits[i] = (std::uniform_int_distribution<int>(0, 1)(rng) == 1);
            }

            // Assicurarsi che almeno un deposito sia aperto
            if (std::none_of(openDeposits.begin(), openDeposits.end(), [](bool v) { return v; })) {
               openDeposits[std::uniform_int_distribution<int>(0, m - 1)(rng)] = true;
            }

            //calcolo dei costi di apertura
            for (int i = 0; i < m; i++) {
                if (openDeposits[i]) {
                    costoDep += openingCost[i];
                }
            }

            
            //variabile che tiene conto del costo totale
            int costoTotaleAssegnamento = 0;
            
            for (int j=0; j<n; j++) {
                //variabile che tiene conto del costo di assegnamento migliore
                int costoMinore = INT_MAX;
                //variabile che tiene conto del deposito migliore
                int depositoMigliore = -1;

                // Per ogni cliente j, esamina tutti i depositi aperti
                for (int i=0; i<m; i++) {
                    if (openDeposits[i] && costMatrix[i][j]<costoMinore) {
                        depositoMigliore=i;
                        costoMinore = costMatrix[i][j];
                    } 
                }
                assegnamento[j] = depositoMigliore;
                costoTotaleAssegnamento += costoMinore;
            }

            //calcolare costo totale sommando a costoTotAss i costi di apertura
            costoTOT = costoTotaleAssegnamento + costoDep;
            //se l'assegnamento ha un costo totale minore di quello in store aggiornare quello in store
            if (costoTOT < costoBestTOT) {
                costoBestTOT = costoTOT;
                bestAssegnamento = assegnamento;
            }
        }

    //ritorna l'assegnamento con costo minore
    std::cout << "Miglior costo trovato: " << costoBestTOT << std::endl;
    return std::make_shared<UFLP_Solution>(bestAssegnamento);
}


