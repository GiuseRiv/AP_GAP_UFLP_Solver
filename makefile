CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

SRC = \
    main.cpp \
    CreateProblemInstance.cpp \
    instances/AP_Instance.cpp \
    instances/GAP_Instance.cpp \
    instances/UFLP_Instance.cpp \
    solutions/AP_Solution.cpp \
    solutions/GAP_Solution.cpp \
    solutions/UFLP_Solution.cpp \
    solvers/AP_Solver.cpp \
    solvers/UFLP_Solver.cpp \
    solvers/GAP_Solver.cpp

OBJ = $(SRC:.cpp=.o)

# Define the final executable name
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
