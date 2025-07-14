#include "package.h"
#include "path.h"
#include "belt.h"
#include "bfs.h"
#include "bfsData.h"
#include "controlcenter.h"
#include "junction.h"
#include "list.h"

bool CC::hasPath(int packageID)const{
    for (size_t i = 0; i < paths.size(); i++)
    {
        if(paths[i].getItem().getID() == packageID) return true;
    }
    return false;
}

Belt& CC::nextBelt(int packageID, char junction, List<Belt>& belts){
    listItem<Path>* p = paths.first(); //Searches for the path of the package
    while(p->getItem().getID() != packageID){
        p = p->getNext();
    }

    char next = p->getItem().nextStop(junction);

    listItem<Belt>* b = belts.first(); //Searches for the belt that goes to the next stop
    while(b->getItem().getEnd() != next){
        b = b->getNext();
    }

    return b->getItem();
}

void CC::makeBFS(List<Junction>& junctions, size_t i){
    bfs curr(junctions[i].getItem());
    curr.createTable(junctions);
    curr.display();
    bfsArray.add(curr);
}

void CC::makePath(char junction, char destination, int packageId){
    listItem<bfs>* curr = bfsArray.first();
    while(curr != nullptr && curr->getItem().getJunction() != junction){
        curr = curr->getNext();
    }
    if(curr == nullptr){ throw std::invalid_argument("Error: The starting junction for the path doesn't exist!");}

    paths.add(Path(packageId, curr->getItem().makePath(destination)));
}

bool CC::allDone(List<Junction>& junctions)const{
    for (size_t i = 0; i < junctions.size(); i++)
    {   
        Junction& currJunction = junctions[i].getItem(); 
        for (int j = 0; j < currJunction.getNOfBelts(); j++)
        {
            if(currJunction.getBelt(j).getNOfPackages() != 0) return false; //If one belt has at least one package on it, it can't end
        }

        //If every package this junction has has arrived to its destination 
        //or if there are no packages here, getNextPackage returns a default package with an id of -1
        if(junctions[i].getItem().getNextPackage().getId() != -1){
            return false;
        }
    }
    return true;
}
