#ifndef MAIN_H
#define MAIN_H

#include "list.h"
#include "junction.h"
#include "belt.h"
#include "package.h"
#include "controlcenter.h"

/// @brief Tests if a junction name is present in the given list of junctions
/// @param name junction name
/// @param junctions list of junctions
/// @return True if name is present in list
bool duplicateJunction(const char name, List<Junction>& junctions);

/// @brief Adds a belt to the given list of junctions, 
/// @brief sets the hasBelt property of the starting junction and also the reachable property of the ending junction
/// @param b belt object to test
/// @param junctions list of junctions
void addBelt(const Belt& b, List<Junction>& junctions);

/// @brief Adds a package to the given list of junctions
/// @param p package object to test
/// @param junctions list of junctions
void addPackage(const Package& p, List<Junction>& junctions);

/// @brief Tests if all junctions in the given list are reachable from other junctions
/// @brief and have belts going to other junctions
/// @param junctions list of junctions
void testAllJunctions(List<Junction>& junctions);

/// @brief Initializes a path for every package
/// @param junctions list of junctions
/// @param controllcenter the controllcenter that stores tha paths
void initializePaths(List<Junction>& junctions, CC& controllcenter);

/// @brief Iterates through all of the junctions and their belts, sends packages if needed
/// @param junctions the list of junctions
/// @param controllcenter the controllcenter that stores the paths
void simulationStep(List<Junction>& junctions, CC& controllcenter);

/// @brief Iterates through every belt of a junction and sends packages
/// @param junctions the list of junctions
/// @param currJunction the current junction
void stepBelts(List<Junction>& junctions, Junction& currJunction);

void inputErrors(List<Junction>& junctions);

#endif