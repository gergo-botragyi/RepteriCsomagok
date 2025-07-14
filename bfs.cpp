#include "memtrace.h"
#include "bfs.h"
#include "list.h"
#include "junction.h"

bfs& bfs::operator=(const bfs& newBFS){
    if(this != &newBFS){
        junction = newBFS.junction;
        table = newBFS.table;
    }
    return *this;
}

void bfs::createTable(List<Junction>& junctions){ //BFS algorithm
    if(table.size() != 0) return;

    tableInit(junctions);

    algorithm(junctions);
}

void bfs::tableInit(List<Junction>& junctions){
    //First it creates the table where it will store the bfsData objects (distance and previous junction for every junction)
    //The first junction is the starting point (distance: 0, no previous)
    table.add(bfsData(junction.getName(), 0, '*'));

    //For every other junction in the beginning distance is -1, previous is none
    listItem<Junction>* curr = junctions.first();
    for (size_t i = 0; i < junctions.size(); i++)
    {
        if(curr->getItem().getName() != junction.getName()){ //The starting point of the bfs is already in the table
            table.add(bfsData(curr->getItem().getName(), -1, '*'));
        }
        if(i<junctions.size()-1) curr = curr->getNext();
    }
}

void bfs::algorithm(List<Junction>& junctions){
    //toBeVisited list contains which junctions are to be visited by the algorithm
    //The neighbours of these junctions are added to the list
    //Active junction is the currently visitied one
    Junction active;
    List<Junction> toBeVisited;
    toBeVisited.add(junction);

    while(!toBeVisited.empty()){
        active = toBeVisited.pop(); //Active is the first element of the list (uses pop because it won't visit it again)
        listItem<bfsData>* activeTableData = table.findDataByChar(active.getName()); //Same active junction but the table element
        for (int i = 0; i < active.getNOfBelts(); i++) //Checks every one of it's neighbours
        {
            listItem<bfsData> *currentJunction = table.findDataByChar(active.getBelt(i).getEnd()); //Currently checked neighbour
            if(currentJunction->getItem().getDistance() == -1){ //Only needs to be visited if it hasn't been
                toBeVisited.add(junctions.findJunctionByChar(currentJunction->getItem().getJunction())->getItem()); //Current neighbour needs to be visited later

                currentJunction->getItem().setDistance( activeTableData->getItem().getDistance() + 1); //Distance is active junction's distance +1 because it is visited from there
                currentJunction->getItem().setPrev( activeTableData->getItem().getJunction()); //Previous is also the active junction
            }
        }
    }
}

void bfs::display()const{
    std::cout<<"\n";
    std::cout << "Junction\t" << "Distance\t" << "Previous\n";
    for (size_t i = 0; i < table.size(); i++)
    {
        table[i].getItem().display(std::cout);
    }
}


List<char> bfs::makePath(char destination)const{
    List<char> stops;
    listItem<bfsData>* active = table.findDataByChar(destination);
    
    while(active->getItem().getJunction() != junction.getName()){
        stops.add(active->getItem().getJunction());
        active = table.findDataByChar(active->getItem().getPrev());
    }
    stops.add(active->getItem().getJunction());

    stops.reverse();
    return stops;
}