#include <iostream>
#include "package.h"
#include "memtrace.h"

bool Package::operator==(const Package& p)const{
    if(this == &p) return true;
    return (
        id==p.id && 
        start == p.start && 
        destination == p.destination &&
        done == p.done
    );
}

bool Package::operator!=(const Package& p)const{
    return(
        id != p.id ||
        start != p.start ||
        destination != p.destination ||
        done != p.done
    );
}

Package& Package::operator=(const Package& p){
    if(this != &p){
        id = p.id;
        start = p.start;
        destination = p.destination;
        done = p.done;
    }
    return *this;
}

std::ostream& Package::display(std::ostream& os){
    return os << "\t" << id << " " << start << " " << destination << "\n";
}