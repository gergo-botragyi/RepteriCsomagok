#ifndef PATH_H
#define PATH_H

#include <stdexcept>
#include "package.h"
#include "list.h"

/// @brief Objects of this class store a package's path that it follows to its destination.
class Path{
    int packageId;
    List<char> stops;

    public:
        /// @brief Default constructor (package id -1, empty stops list)
        Path():packageId(-1),stops(List<char>()){}

        /// @brief Constructor for path
        /// @param id the package id
        /// @param newStops a char array of the stops
        template<size_t n>
        Path(int id, const char (&newStops)[n]):packageId(id), stops(List<char>()){
            for (size_t i = 0; i < n; i++)
            {
                stops.add(newStops[i]);
            }
        }

        /// @brief Constructor for path
        /// @param id the package id
        /// @param newStops a list of the stops
        Path(int id, List<char> newStops):packageId(id), stops(newStops){}

        /// @brief Assigns the values of the other path to this object
        /// @param p the other path object
        /// @returns A reference to this object
        Path& operator=(const Path& p);
        
        /// @param p the other patch object
        /// @returns True if the two path objects are the same
        bool operator==(const Path& p)const{return packageId == p.packageId;}

        /// @param p the other patch object
        /// @returns True if the two path objects are not the same
        bool operator!=(const Path& p)const{return packageId != p.packageId;}

        /// @param i index
        /// @returns The 'i'th element of the stops
        char operator[](size_t i){
            return stops[i].getItem();
        }

        /// @brief Adds a stop to the stops list
        /// @param stop the name of the stop
        void addStop(char stop);

        /// @brief Returns the next stop after the current stop in the list
        /// @param current the current stop
        char nextStop(char current)const;

        /// @brief Returns the package id
        int getID()const{return packageId;}

        /// @brief Returns the list of the stops
        List<char> getStops()const{return stops;}
};

#endif