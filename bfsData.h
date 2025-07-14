#ifndef BFSDATA_H
#define BFSDATA_H

#include <iostream>
#include "list.h"

/// @brief Objects of this class store data which is used in the bfs class's table. 
class bfsData{
    int distance;
    char prev;
    char junction;

    public:

        /// @brief Default constructor (distance 0, previous *, junction \0)
        bfsData():distance(0), prev('*'){junction = '\0';}

        /// @brief Constructor of the bfsData class
        /// @param junctionName this junction's name
        /// @param distance distance from the starting junction
        /// @param previous the previous junction's name where this was visited from
        bfsData(char junctionName, int distance, char previous):distance(distance), prev(previous), junction(junctionName){}

        /// @brief Copy cosntructor
        /// @param d the bfsData object to copy
        bfsData(const bfsData& d):distance(d.distance), prev(d.prev), junction(d.junction){}

        /// @brief Assigns the values of the given bfsData object to this one
        /// @param d the bfsData object to copy
        /// @returns A reference to this object
        bfsData& operator=(const bfsData& d){
            if(this != &d){
                junction = d.junction;
                distance = d.distance;
                prev = d.prev;
            }
            return *this;
        }

        /// @param data the bfsData object to check
        /// @return True if the two objects are the same
        bool operator==(const bfsData& data)const{
            return 
                junction == data.junction && 
                distance == data.distance && 
                prev == data.prev;
        }

        /// @param data the bfsData object to check
        /// @return True if the two objects are not the same
        bool operator!=(const bfsData& data)const{
            return 
                junction != data.junction || 
                distance != data.distance || 
                prev != data.prev;
        }

        /// @brief Returns the junction's name
        char getJunction()const{return junction;}

        /// @brief Returns the distance from the starting junction
        int getDistance()const{return distance;}

        /// @brief Returns the previous junction's name 
        char getPrev()const{return prev;}

        /// @brief Sets the distance to the given number
        /// @param d new distance
        void setDistance(int d){distance = d;}

        /// @brief Sets the previous junction's name to the given name
        /// @param p the new name
        void setPrev(char p){prev = p;}

        /// @brief Outputs the junction's name, the distance and the previous junction's name to the given output stream
        /// @returns The output stream
        std::ostream& display(std::ostream& os)const{
            os << junction << "\t" << distance << "\t" << prev << "\n";
            return os;
        }
};

#endif