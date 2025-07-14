#ifndef BFS_H
#define BFS_H

#include "bfsData.h"
#include "list.h"
#include "junction.h"

/// @brief Objects of this class store the BFS algorithm's data. 
/// @brief Starting from a junction, the algorithm creates a table that include all other junctions 
/// @brief in the given list and calculates their distances from the starting junction 
/// @brief and where each junction is visited from. 
/// @brief From this table with a function the object can create a path to any other junction.
class bfs{
    Junction junction;
    List<bfsData> table;

    /// @brief Initializes the objects table (distance: 0, prev: *)
    /// @param junctions list of junctions 
    void tableInit(List<Junction>& junctions);

    /// @brief The BFS algorithm, fills the table with the distances and the previous names
    /// @param junctions list of junctions
    void algorithm(List<Junction>& junctions);

    public:
        /// @brief Default bfs object
        bfs():table(){}

        /// @brief A bfs object starting from the given junction with an empty table
        /// @param junction the junction where the algorithm will start from
        bfs(const Junction& junction): junction(junction), table(List<bfsData>()){}

        /// @brief Copy constructor of the bfs class
        /// @param newBFS the bfs object to copy
        bfs(const bfs& newBFS): junction(newBFS.junction), table(newBFS.table){}
        
        /// @brief Returns the junction's name where the algorithm has started
        char getJunction()const { return junction.getName();}
        
        /// @brief Assigns the values of the bfs object to this
        /// @param newBFS the bfs object to copy
        /// @returns A reference to this object
        bfs& operator=(const bfs& newBFS);

        /// @brief Checks if two bfs objects are the same (starting from the same junction)
        /// @param otherBFS the other bfs object to check
        /// @return True if the junctions match
        bool operator==(const bfs& otherBFS)const{return junction == otherBFS.junction;}

        /// @brief Checks if two bfs objects are not the same (starting from different junctions)
        /// @param otherBFS the other bfs object to check
        /// @return True if the junctions don't match
        bool operator!=(const bfs& otherBFS)const{return junction != otherBFS.junction;}

        /// @brief The algorithm creates the table containing which junctions are how far from the start junction
        /// @brief and the previous junction before them where they were discovered from
        /// @param junctions list of junctions  
        void createTable(List<Junction>& junctions);

        /// @brief Creates a path to the given destination 
        /// @brief from this object's starting junction based on this object's table
        /// @param destination the destination junction's name
        /// @return A list of junction names in the order of visiting them
        List<char> makePath(char destination)const;

        /// @brief Displays the table
        void display()const;

};

#endif