#ifndef IP_H
#define IO_H

#include "list.h"
#include "junction.h"

/// @brief The menu for reading the input
/// @param junctions list of junctions to read the data to
void read(List<Junction>& junctions);

/// @brief Reads from the console
/// @param junctions list of junctions to read the data to
void readConsole(List<Junction>& junctions, std::ostream& os, std::istream& is);

/// @brief Cleares the cin and throws an exception
void failedIstream(std::istream& is);

/// @brief Removes all '\r' from the string
/// @param line string to check
void linuxInput(std::string& line); 

/// @brief Reads the file name from the console.
/// @returns The file name string
std::string readFilename();

/// @brief Reads from a file
/// @param junctions list of junctions to read the data to
/// @param fileName name of the file to read the data from
void readFile(List<Junction>& junctions, std::string fileName);

/// @brief Parses an ifstream and reads stores all the data
/// @param junctions list of junctions
/// @param f ifstream
void parseStream(List<Junction>& junctions, std::ifstream& f);

/// @brief Creates a junction object from the given name if it's not a duplicate
/// @param junctions list of junctions to read the data to
/// @param name the name of the new junction
void processJunction(List<Junction>& junctions, char name);

/// @brief Creates a belt object
/// @param junctions list of junctions to read the data to
/// @param line should be formatted as 'starting junction's name','ending junction's name'
/// @param id the belt id
void processBelt(List<Junction>& junctions, int id, std::string line);

/// @brief Creates a package object
/// @param junctions list of junctions to read the data to
/// @param line should be formatted as 'package id','starting junction's name','destination junction's name'
void processPackage(List<Junction>& junctions, std::string line);

/// @brief Reads all the junctions from the console
/// @param junctions list of junctions
void readJunctions(List<Junction>& junctions, std::ostream& os, std::istream& is);

/// @brief Reads all the belts from the console
/// @param junctions list of junctions
void readBelts(List<Junction>& junctions, std::ostream& os, std::istream& is);

/// @brief Reads all the packages from the console
/// @param junctions list of packages
void readPackages(List<Junction>& junctions, std::ostream& os, std::istream& is);

/// @brief Displays all the junctions in the list
/// @param junctions 
/// @param os the ostream object for the Junction::display() function
void displayJunctions(List<Junction>& junctions, std::ostream& os);

/// @brief Displays all the packages in a given list of junctions \\\n
/// @brief (The packages at the junctions as well as the ones on the belts)
/// @param junctions the list of junctions
/// @param os the ostream object where the data is displayed
void displayAllPackages(List<Junction>& junctions, std::ostream& os);

/// @brief Writes all the data from a given junction list to a file (if filename not given, it reads it from the console)
/// @param junctions the junction list
/// @param fileName the name of the file (format should be 'C:\\asd\\asd' or 'C:/asd/asd')
void write(List<Junction>& junctions, std::string fileName = "");
#endif