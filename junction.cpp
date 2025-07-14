#include <stdexcept>
#include <iostream>
#include "junction.h"
#include "package.h"
#include "belt.h"
#include "memtrace.h"
#include "list.h"

Package Junction::getNextPackage()const{
    listItem<Package>* p = packages.first();
    while(p != nullptr && p->getItem().arrived()){
        p = p->getNext();
    }

    if(p == nullptr){
        return Package();
    }else{
        return p->getItem();
    }
}

Junction& Junction::operator=(const Junction& j){
    if(this != &j){
        name = j.name;
        belts = j.belts;
        packages = j.packages;
        reachable = j.reachable;
        hasBelt = j.hasBelt;
    }
    return *this;
}

bool Junction::existingBelt(const Belt& b)const{
    return belts.search(b);
}

bool Junction::existingPackage(const Package& p)const{
    return packages.search(p);
}

void Junction::addPackage(const Package& p){
    if(existingPackage(p)) return;
    packages.add(p);
}

void Junction::addBelt(const Belt& b){
    if(existingBelt(b) || b.getStart() == b.getEnd()) return;
    belts.add(b);
    setHasBelt();
}

std::ostream& Junction::display(std::ostream& os){
    os << "Name: " << name << "\n";

    os << "Belts:\n";
    for (size_t i = 0; i < belts.size(); i++)
    {
        os << belts[i].getItem().getId() << " " << belts[i].getItem().getStart() << " " << belts[i].getItem().getEnd() << "\n";
    }

    os << "Packages:\n";
    for (size_t j = 0; j < packages.size(); j++)
    {
        os << packages[j].getItem().getId() << " " << packages[j].getItem().getStart() << " " << packages[j].getItem().getDest() << "\n";
    }
    return os;
}

void Junction::send(const Package& p, Belt& b){
    b.addPackage(p);
    packages.remove(p);
}

Package& Junction::getPackage(size_t i){
    return packages[i].getItem();
}