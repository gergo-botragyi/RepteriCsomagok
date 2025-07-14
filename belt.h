#ifndef BELT_H
#define BELT_H

#include "package.h"
#include "list.h"

/// @brief Objects of this class are "belts" between two junctions.\\\n
/// @brief Every belt has a unique id, a starting and an ending point 
/// @brief and also a list of packages currently "on" the belt
class Belt{
    int id;
    char start, end;
    List<Package> packages;

    public:
        /// @brief A basic belt object (ID -1)
        Belt():id(-1), start('\0'), end('\0'), packages(List<Package>(0)){}

        /// @brief A belt object that connects to junctions
        /// @param id the belt id
        /// @param start the starting junction's name
        /// @param end the ending junction's name
        Belt(int id, char start, char end):id(id), start(start), end(end), packages(List<Package>(0)){}

        /// @brief Copy constructor of belt
        /// @param b the belt object to copy
        Belt(const Belt& b):id(b.id), start(b.start), end(b.end), packages(b.packages){}
        
        /// @brief Returns the id of the belt
        int getId()const{return id;}

        /// @brief Returns the starting junction's name of the belt
        char getStart()const{return start;}

        /// @brief Returns the ending junction's name of the belt
        char getEnd()const{return end;}
        
        /// @brief Copies a belt object
        /// @param b the belt object to copy
        /// @return A reference to this object
        Belt& operator=(const Belt& b);

        /// @brief Checks if the two belts are the same (have the same id)
        /// @param b the belt object to check
        /// @return True if the two id's match
        bool operator==(const Belt& b)const{return id == b.id;}

        /// @brief Checks if the two belts are not the same (don't have the same id)
        /// @param b the belt object to check
        /// @return True if the two id's don't match
        bool operator!=(const Belt& b)const{return id != b.id;}

        /// @brief Adds a package to the belts package list
        /// @param p the package to add to the list
        void addPackage(const Package& p){packages.add(p);}

        /// @brief Removes the returns the first element of the packages list
        /// @returns The first element of the packages list or a generic package (ID -1) if the list is empty
        Package removePackage(); //TESZT

        /// @brief Returns the number of packages stored in the list
        size_t getNOfPackages()const{return packages.size();}

        /// @brief Returns the 'i'th element of the packages list
        /// @param i index
        /// @returns A reference to the object
        Package& getPackage(size_t i){return packages[i].getItem();}
};

#endif