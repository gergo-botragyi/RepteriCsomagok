#include "memtrace.h"
#include "path.h"
#include "list.h"

void Path::addStop(char stop){
    stops.add(stop);
}

char Path::nextStop(char current)const{
    return stops.find(current)->getNext()->getItem();
}

Path& Path::operator=(const Path& p){
    if(this != &p){
        packageId = p.packageId;
        stops = p.stops;
    }
    return *this;
}
