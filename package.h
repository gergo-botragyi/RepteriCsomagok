#ifndef PACKAGE_H
#define PACKAGE_H

#include <iostream>

/// @brief Objects of this class are "packages" that go from their starting point to their destination.\\\n
/// @brief Each package has a unique id.
/// @param done indicates if the package has arrived to its destination
class Package{
    int id;
    char start, destination;
    bool done = false;

    public:
        /// @brief Default constructor (id: -1, start and destination: \0, done: default false)
        Package():id(-1), start('\0'), destination('\0'){}

        /// @brief Constructor for the package
        /// @param id package id
        /// @param start starting junction's name
        /// @param destination destination junction's name
        /// @param done default set to false
        Package(int id, char start, char destination):id(id), start(start), destination(destination){}

        /// @brief Copy constructor
        /// @param p the package object to copy
        Package(const Package& p):id(p.id), start(p.start), destination(p.destination), done(p.done){}

        /// @brief Assigns the values of the other package to this object
        /// @param p the other package object
        /// @returns A reference to this object
        Package& operator=(const Package& p);

        /// @param p the other package object
        /// @return True if the two packages match
        bool operator==(const Package& p)const;

        /// @param p the other package object
        /// @return True if the two packages don't match
        bool operator!=(const Package& p)const;

        /// @brief Returns true if the package has arrived
        bool arrived()const{return done;} //tesztelni

        /// @brief Sets the arrived value of the package to true
        void setArrived(){done = true;}

        /// @brief Returns the package's id
        int getId()const{return id;}

        /// @brief Returns the package's starting junction's name
        char getStart()const{return start;}

        /// @brief Returns the package's destination junction's name
        char getDest()const{return destination;}

        /// @brief Displays the package's id, starting and destination point with a tab in the beginning for readability
        /// @param os the ostream where to write
        /// @returns A reference to the ostream
        std::ostream& display(std::ostream& os);
};

#endif