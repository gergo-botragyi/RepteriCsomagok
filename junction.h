#ifndef JUNCTION_H
#define JUNCTION_H

#include "package.h"
#include "belt.h"
#include "list.h"

/// @brief Objects of this class store packages and are connected to one another with belts.
class Junction{
    char name;
    List<Belt> belts;
    List<Package> packages;
    bool reachable = false;
    bool hasBelt = false;

    public:
        /// @brief Default constructor (name \0, empty belt and package lists, reachable and hasBelt false)
        Junction():name('\0'),belts(List<Belt>()), packages(List<Package>()){}

        /// @brief Constructor for a junction object
        /// @param name The junction's name
        Junction(char name): name(name), belts(List<Belt>()), packages(List<Package>()){}
        
        /// @brief Copy constructor for junction
        /// @param j the junction to copy
        Junction(const Junction& j):name(j.name), belts(j.belts), packages(j.packages), reachable(j.reachable), hasBelt(j.hasBelt){}

        /// @brief Returns the name of the junction
        char getName()const{return name;}

        /// @returns The next package in the list which hasn't arrived yet \\\n
        /// @returns If it has no packages or all of them have arrived it returns a basic package (ID -1)
        Package getNextPackage()const; //tesztelni

        /// @brief Returns the 'i'th element in the packages list
        /// @param i index
        Package& getPackage(size_t i);

        /// @brief Returns the 'i'th element in the belts list
        /// @param i index
        Belt& getBelt(size_t i){return belts[i].getItem();}

        /// @brief Return the whole packages list
        List<Belt>& getBeltList(){return belts;}

        /// @brief Assigns the values of the given junction to this object
        /// @param j the junction to copy
        /// @returns A reference to this object
        Junction& operator=(const Junction& j);

        /// @brief Checks if two junctions are the same (have the same name)
        /// @param j the other junction to check
        /// @returns True if the two names match
        bool operator==(const Junction& j)const{return name == j.name;}

        /// @brief Checks if two junctions are not the same (don't have the same name)
        /// @param j the other junction to check
        /// @returns True if the two names don't match
        bool operator!=(const Junction& j)const{return name != j.name;}

        /// @brief Returns the number of belts in the list
        int getNOfBelts()const {return belts.size();}

        /// @brief Returns the number of packages in the list
        int getNOfPackages()const{return packages.size();}

        /// @brief Adds the given belt to the belt list of this junction
        /// @param b the belt to add
        void addBelt(const Belt& b);

        /// @brief Adds a package to the package list of this junction
        /// @param p the package to add
        void addPackage(const Package& p);

        /// @brief Checks if a belt is already in the belts list
        /// @param b the belt object
        bool existingBelt(const Belt& b)const;

        /// @brief Checks if a package is already in the package list
        /// @param p the package object
        bool existingPackage(const Package& p)const;

        /// @brief Returns true if this junction is reachable from an other
        bool getReachable(){return reachable;} //ezeket tesztelni

        /// @brief Returns true if this junction has at least one belt 
        bool getHasBelt(){return hasBelt;}

        /// @brief Sets the reachable value to true
        void setReachable(){reachable = true;}

        /// @brief Sets the hasBelt value to true
        void setHasBelt(){hasBelt = true;}

        /// @brief Moves a package from the junction's packages list to the belt
        /// @param p the package object
        /// @param b the belt object
        void send(const Package& p, Belt& b); //tesztelni

        /// @brief Displays the junction's name, belts and packages to the given ostream
        /// @returns a reference given ostream
        std::ostream& display(std::ostream& os);
};

#endif