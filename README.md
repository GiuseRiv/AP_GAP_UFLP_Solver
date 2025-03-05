# AP_GAP_UFLP_Solver



This project provides efficient solutions for three types of computational problems: AP (Assignment Problem), GAP (Generalized Assignment Problem), and UFLP (Uncapacitated Facility Location Problem).


# AP (Assignment Problem):

Pairs elements from two different sets of equal size.
Each possible pair has an associated cost.
The goal is to minimize the total assignment cost.


# GAP (Generalized Assignment Problem):

Given a set of agents (M = {1, ..., m}) and tasks (N = {1, ..., n}), let c_ij be the cost of assigning task j to agent i.
Performing a task consumes a certain amount of resource; let r_ij be the resource consumed by agent i for task j, and let b_i be the maximum resource available for agent i.
The problem is to assign all tasks while minimizing total cost and ensuring resource limits are respected.


# UFLP (Uncapacitated Facility Location Problem):

Given a set of potential facilities (M = {1, ..., m}) and customers (N = {1, ..., n}), let f_i be the fixed cost to open facility i and c_ij be the transportation cost to serve customer j from facility i (if opened).
The goal is to decide which facilities to open and how to assign customers so that the sum of fixed opening costs and transportation costs is minimized.

----- INPUT DATA FORMATS -----

AP: 
Example input file: 
NAME: AP_5-1 
n: 5 
c_ij:
36 46 34 25 29
12 33 26 10 32
34 23 36 34 21
10 42 25 24 16
39 19 24 16 50


Explanation: 
• The string after "NAME:" represents the instance name. • The integer after "n:" indicates the number of agents and tasks. • After "c_ij:", each row lists the cost (integer) for assigning task j to agent i.


GAP: Example input file: 
NAME: GAP_5_10-1
m: 5
n: 10
c_ij:
36 46 34 25 29 17 15 29 38 50
12 33 26 10 32 49 46 44 41 49
34 23 36 34 21 39 48 37 34 10
10 42 25 24 16 31 11 25 21 43
39 19 24 16 50 20 39 11 26 40
r_ij:
15 8 11 16 24 8 19 9 15 7
8 10 7 23 20 9 7 11 21 9
22 9 13 12 22 7 10 8 15 12
6 5 24 24 24 23 8 8 6 18
23 19 18 17 25 14 15 12 11 5
b_i:
30 30 30 30 30

Explanation: 
• The string after "NAME:" represents the instance name. • The integers after "m:" and "n:" are the number of agents and tasks, respectively. • The rows after "c_ij:" list the assignment costs. • The rows after "r_ij:" list the resource consumption values. • The row after "b_i:" lists the maximum resource available for each agent.


UFLP: 
Example input file: 
NAME: UFLP_4_3-1
m: 4
n: 3
c_ij:
130   120   80
140   100   50
130   90    140
100   120   150
f_i:
300   400   150   200

Explanation: • The string after "NAME:" represents the instance name. • The integers after "m:" and "n:" are the number of potential facilities and customers, respectively. • The rows after "c_ij:" list the transportation costs from facility i to customer j. • The row after "f_i:" lists the fixed cost associated with opening each facility.

----- PROJECT ORGANIZATION -----

The project is divided into three main groups: instances, solvers, and solutions. Interfaces and implementations are separated into .h and .cpp files for a modern and clean organization.

Directory structure: instances/ apInstance.h apInstance.cpp gapInstance.h gapInstance.cpp uflpInstance.h uflpInstance.cpp solutions/ apSolution.h apSolution.cpp gapSolution.h gapSolution.cpp uflpSolution.h uflpSolution.cpp solvers/ apSolver.h apSolver.cpp gapSolver.h gapSolver.cpp uflpSolver.h uflpSolver.cpp main-cpp CreateProblemInstance.h CreateProblemInstance.cpp ProblemSolution.h ProblemSolver.h ProblemInstance.h

----- ABSTRACT ENTITIES -----

ProblemInstance: Represents a problem instance with all the essential data (e.g., for AP: instance name, number of agents/tasks, cost matrix; for GAP: additional resource matrix and constraints; for UFLP: plus facility opening costs). It includes getter methods to access instance data.

ProblemSolver: Contains the algorithm to solve the problem. This abstract class has a "solve" method that is overridden in the subclasses with a problem-specific algorithm.

ProblemSolution: Stores the solution as an assignment vector. It includes a "print" method that outputs the solution vector to the console.

----- FILE DATA READING -----

The function CreateProblemInstance handles reading instance data from a file and creates a pointer to a ProblemInstance based on the input. It uses a switch-case structure based on the variable "problemType" (determined from the input) to instantiate an AP, GAP, or UFLP instance.

Helper functions (one per problem type) are used to read the data and update the relevant variables. An overloaded ">>" operator is provided to read a string (representing the problem type) from the command line and convert it into an enum.

----- SOLUTION APPROACHES -----

AP: Uses the Hungarian algorithm to solve the assignment problem with a complexity of O(n^3).

GAP: Generates multiple random but acceptable solutions (satisfying constraints) using a loop with up to 1000 iterations.

For each iteration, tasks are randomly assigned to available agents based on resource availability.
The solution with the lowest cost is selected.
UFLP: Follows a similar approach to GAP.

First, facilities are randomly chosen to be opened (each with a 50% chance via a coin toss).
Next, each customer is assigned to the open facility with the minimum transportation cost.
The total cost (opening plus assignment costs) is calculated, and if it is lower than the best found so far, the best solution is updated.
----- HIGH-LEVEL FLOW -----

Input Problem Type: The program prompts the user to enter the problem type (AP, GAP, UFLP). The input string is converted into an enum using an overloaded ">>" operator in CreateProblemInstance.

Input File Name: The user is prompted to provide the name of the text file containing the instance data.

Instance Creation: CreateProblemInstance opens the file and creates a shared pointer to the appropriate ProblemInstance (AP, GAP, or UFLP) based on the file data.

Problem Solving: The corresponding solver is called (using a switch-case) to solve the instance and generate a solution vector.

Display and Save the Solution: The solution is displayed using the print method of the ProblemSolution subclass and saved to a text file named "soluzione<instanceName>.txt".

----- EXCEPTION HANDLING -----

Minimal exception handling is implemented at both low levels (e.g., during data reading in CreateProblemInstance) and at higher levels (in main.cpp).

----- COMPILATION -----

A makefile is provided to facilitate project compilation.
