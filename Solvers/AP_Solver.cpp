#include "AP_Solver.h"

#include <string>
#include <vector>
#include <memory>
#include <iostream>

//MIGLIORAMENTI A SOLVE:
//                      GESTIONE ECCEZIONI (The implementation does not handle edge cases, such as:

//An empty cost matrix.

//A non-square cost matrix (the Hungarian Algorithm requires a square matrix).

//A matrix with all infinite values (indicating no possible assignments).)



std::shared_ptr<ProblemSolution> AP_Solver::solve(const std::shared_ptr<ProblemInstance>& instance) { 

        auto apInstance = std::dynamic_pointer_cast<AP_Instance>(instance);
        //Se il puntatore passato alla funzione solve non è un'istanza di AP_Instance, il dynamic_cast restituirà nullptr, e il controllo if (!apInstance) catturerà questo caso.
        if (!apInstance) {
            throw std::invalid_argument("L'istanza non è valida per il problema di assegnamento (AP).");
        }

        //assegno la matrice a matrix
        auto Matrix = apInstance->getCostMatrix();
        //Se la matrice non è quadrata da errore
        if (Matrix.size() != Matrix[0].size()) {
            throw std::invalid_argument("La matrice deve essere quadrata.");
        }
        //assegno il numero di agenti (che coincide a quello delle operazioni) a n
        auto n = Matrix.size();
        

        std::vector<int> u, v, p, way;
        
        //vettore di potenziali
        u.assign(n + 1, 0);
        //vettore di potenziali
        v.assign(n + 1, 0);
        //p contiente gli assegnamenti
        p.assign(n + 1, 0);
        way.assign(n + 1, 0);


        //ALGORITMO
        //ALGORITMO UNGHERESE, complessità lineare O(n^3)
        for (size_t i = 1; i <= n; i++) {
            p[0] = i;
            //variabile che indica la colonna corrente
            int j0 = 0;
            //vettore con i valori minimi
            std::vector<int> minv(n + 1, INT_MAX);
            //tiene traccia delle colonne già assegnate
            std::vector<bool> used(n + 1, false);
            do {
                //marca la colonna come usata
                used[j0] = true;
                //riga relativa alla colonna
                int i0 = p[j0];
                int delta = INT_MAX, j1;
                //itera le colonne j
                for (size_t j = 1; j <= n; j++) {
                    //se la colonna j non è ancora stata usata calcola il costo ridotto
                    if (!used[j]) {
                        int cur = Matrix[i0 - 1][j - 1] - u[i0] - v[j];
                        if (cur < minv[j]) {
                            minv[j] = cur;
                            way[j] = j0;
                        }
                        if (minv[j] < delta) {
                            delta = minv[j];
                            j1 = j;
                        }
                    }
                }
                for (size_t j = 0; j <= n; j++) {
                    if (used[j]) {
                        u[p[j]] += delta;
                        v[j] -= delta;
                    } else {
                        minv[j] -= delta;
                    }
                }
                j0 = j1;
            } while (p[j0] != 0);
            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }
        std::vector<int> assignment(n);
        for (size_t j = 1; j <= n; ++j) {
            assignment[p[j] - 1] = j - 1;
        }
        return std::make_shared<AP_Solution>(assignment);
        
        
       
    }


