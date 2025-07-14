#ifndef CONTROLLCENTER_H
#define CONTROLLCENTER_H

#include "package.h"
#include "path.h"
#include "belt.h"
#include "bfs.h"
#include "junction.h"
#include "bfsData.h"
#include "list.h"

/// @brief Objects of this class store package's paths and also junction's bfs objects.
class CC{
    List<Path> paths;
    List<bfs> bfsArray;

    public:
        /// @brief Constructor of the controllcenter class (empty path and bfs lists)
        CC(): 
            paths(List<Path>()), 
            bfsArray(List<bfs>())
        {}

        /// @brief Checks if the package with the given packageID has a path
        /// @param packageID 
        /// @returns True if the package has a path already
        bool hasPath(int packageID)const; //tesztelni
        
        /// @brief Searches for the belt object where the package should go from the given junction
        /// @param packageID 
        /// @param junction the current junction where the package is
        /// @param belts list of the belts that the package can go to from the current junction
        /// @return A reference to the belt
        Belt& nextBelt(int packageID, char junction, List<Belt>& belts); //tesztelni
        
        /// @brief Makes a bfs object and its table for the 'i'th element of the list of junctions
        /// @param junctions list of junctions
        /// @param i index of element
        void makeBFS(List<Junction>& junctions, size_t i); //tesztelni

        /// @brief Makes a path for a given package from the starting junction to the destination
        /// @param junction starting junction name
        /// @param destination destination junction name
        /// @param packageId 
        void makePath(char junction, char destination, int packageId); //tesztelni

        /// @param junctions list of junctions
        /// @return True if every package has arrived to its destination
        bool allDone(List<Junction>& junctions)const; //tesztelni
};

#endif