#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "io.h"
#include "main.h"
#include "belt.h"
#include "bfs.h"
#include "bfsData.h"

using std::cout;
using std::cin;
using std::string;

void read(List<Junction>& junctions){
    cout << "Read from file: 0, read from console: 1\n";

    int inp;
    cin >> inp;
    switch (inp)
    {
        case 0:
            readFile(junctions, readFilename());
            break;
        
        case 1:
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            readConsole(junctions, cout, cin);
            break;
    
        default:
            cout << "Invalid argument. Try again!\n";
            break;
    }
}

void readConsole(List<Junction>& junctions, std::ostream& os, std::istream& is){

    readJunctions(junctions, os, is);
    
    readBelts(junctions, os, is);
    
    readPackages(junctions, os, is);
}

void processJunction(List<Junction>& junctions, char name){
    if(!duplicateJunction(name, junctions)){
        junctions.add(Junction(name));
    }
}

void processBelt(List<Junction>& junctions, int id, string line){
    if(line.length() < 3 || line[1] != ',' || !isalpha(line[0]) || !isalpha(line[2])){
        throw std::runtime_error("Error: Invalid input.");
    }

    if(junctions.findJunctionByChar(line[0]) == nullptr){
        std::cerr << "Starting junction missing from list for belt: ID:" << id << ", starting at:" << line[0] << ", belt skipped!\n";
        return;
    }

    if(junctions.findJunctionByChar(line[2]) == nullptr){
        std::cerr << "Ending junction missing from list for belt: ID:" << id << ", ending at:" << line[2] << ", belt skipped!\n";
        return;
    }

    addBelt(Belt(id, line[0], line[2]), junctions);
}

void processPackage(List<Junction>& junctions, string line){
    if(line.length() != 5 || line[1] != ',' || line[3] != ',' || !std::isdigit(line[0]) || !std::isalpha(line[2]) || !std::isalpha(line[4])){
        throw std::runtime_error("Error: Invalid input.");
    }

    int id = line[0] - '0'; //conversion to number
    char start = line[2];
    char end = line[4];

    addPackage(Package(id, start, end), junctions);
}

void readJunctions(List<Junction>& junctions, std::ostream& os, std::istream& is){
    os << "Enter the junctions' names separated by commas: ";

    string line;
    getline(is, line);
    linuxInput(line);

    if(is.fail()) failedIstream(is);

    std::stringstream ss(line);
    string token;
    while(std::getline(ss, token, ','))
    {
        if(token.length() != 1 || !std::isalpha(token[0])){
            throw std::runtime_error("Error: Invalid input.");
        }

        processJunction(junctions, token[0]);
    }
}

void readBelts(List<Junction>& junctions, std::ostream& os, std::istream& is){
    os << "Enter the belts line by line in the following format: 'starting junction's name','ending junction's name'\n"
    << "If you don't wish to enter any more belts press enter in a new line.\n";

    string line;
    getline(is, line);
    linuxInput(line);

    int j = 0;
    while(!line.empty())
    {
        if(is.fail()) failedIstream(is);

        processBelt(junctions, j++, line);
        getline(is, line);
    }
}

void readPackages(List<Junction>& junctions, std::ostream& os, std::istream& is){
    os << "Enter the packages line by line in the following format: 'id number','starting junction's name','destination junction's name'\n"
    << "If you don't wish to enter any more packages press enter in a new line.\n";

    string line;
    getline(is, line);
    linuxInput(line);

    while(!line.empty())
    {
        if(is.fail()) failedIstream(is);

        processPackage(junctions, line);

        getline(is, line);
    }
}

void failedIstream(std::istream& is){
    is.clear();
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    throw std::runtime_error("Error: Incorrect input format!");
}

void linuxInput(std::string& line){
    line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
}

string readFilename(){
    cout << "The format of the file should be the following:\n"
    << "Junctions: 'name' (one per line, letters of the alphabet)\n"
    << "Belts: 'starting junction's name','ending junction's name' (one per line)\n"
    << "Packages: 'id number','starting junction's name','destination junction's name' (one per line)\n\n"
    << "Please enter the file name "
    << "(format: 'C:\\asd\\asd.txt' or 'C:/asd/asd.txt' or '.\\asd.txt' or if it's in the same folder 'asd.txt'):\n";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    string name;
    getline(cin, name);
    if(cin.fail()) failedIstream(cin);

    return name;
}

void readFile(List<Junction>& junctions, string fileName){
    std::ifstream f(fileName);
    if(!f.is_open()) throw std::runtime_error("Error: The file doesn't exist or can't be opened!");

    parseStream(junctions, f);

    f.close();
}

void parseStream(List<Junction>& junctions, std::ifstream& f){
    string line;
    int j = 0;
    while(getline(f, line)){
        if(line.empty()) continue;
        linuxInput(line);

        if(isdigit(line[0])){
            processPackage(junctions, line);
        }else if(line.length() > 1 && line[1] == ','){//first character not digit and has a comma in the second space
            processBelt(junctions, j++, line);
        }else if(line.length() == 1 && isalpha(line[0])){//first character not digit and is only one character
            processJunction(junctions, line[0]);
        }else{
            throw std::runtime_error("Error: Incorrect input format: " + line);
        }
    }
}

void displayJunctions(List<Junction>& junctions, std::ostream& os){
    for (size_t i = 0; i < junctions.size(); i++)
    {
        junctions[i].getItem().display(os);
    }
}

void displayAllPackages(List<Junction>& junctions, std::ostream& os){
    for (size_t i = 0; i < junctions.size(); i++)
    {
        Junction& currJunc = junctions[i].getItem();
        os << "Packages at junction: " << currJunc.getName() << "\n";

        for (int j = 0; j < currJunc.getNOfPackages(); j++)
        {
            currJunc.getPackage(j).display(os);
        }

        for (int k = 0; k < currJunc.getNOfBelts(); k++)
        {
            Belt& currBelt = currJunc.getBelt(k);
            os << "\tPackages at belt: " << currBelt.getId() << ", going from: " << currBelt.getStart() << ", to: " << currBelt.getEnd() << "\n";

            for (size_t l = 0; l < currBelt.getNOfPackages(); l++)
            {
                os << "\t";
                currBelt.getPackage(l).display(os);
            }
            
        }
        os << "\n";
    }
    os << "-----------------------------------------------------------\n";
}

void write(List<Junction>& junctions, string fileName){
    if(fileName.empty()){
        cout << "Please enter the name of the file where the data should be written ";
        cout << "(format: 'C:\\asd\\asd.txt' or 'C:/asd/asd.txt' or '.\\asd.txt' or if it's in the same folder 'asd.txt'):\n";
        getline(cin, fileName);
        if(cin.fail()) failedIstream(cin);
    }

    std::ofstream f(fileName);
    if(!f.is_open()) throw std::runtime_error("Error: Can't open the file!");

    displayAllPackages(junctions, f);

    f.close();
}
