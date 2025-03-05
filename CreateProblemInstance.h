#ifndef CREATE_PROBLEM_INSTANCE_H
#define CREATE_PROBLEM_INSTANCE_H

#include <fstream>
#include <sstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include "ProblemInstance.h"


// Enum per identificare il tipo di problema
enum ProblemType {
    AP,
    GAP,
    UFLP
};

//overload dell'operatore>> per leggere da input l'enum problemtype
std::istream& operator>>(std::istream& in, ProblemType &pt);

// Funzione per creare un'istanza del problema
std::shared_ptr<ProblemInstance> CreateProblemInstance(ProblemType problem, const std::string& filename);

// Funzione helper per leggere un'istanza AP da file
void readAPInstanceFromFile(const std::string& filename, std::string& name, std::vector<std::vector<int>>& costMatrix);

// Funzione helper per leggere un'istanza GAP
void readGAPInstanceFromFile(const std::string& filename, std::string& name, std::vector<std::vector<int>>& costMatrix, std::vector<std::vector<int>>& resourceMatrix, std::vector<int>& maxResources);

// Funzione helper per leggere un'istanza UFLP
void readUFLPInstanceFromFile(const std::string& filename, std::string& name, std::vector<std::vector<int>>& costMatrix, std::vector<int>& openingCosts);

#endif 