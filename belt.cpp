#include "belt.h"
#include "memtrace.h"

Belt& Belt::operator=(const Belt& b){
    if(this != &b){
        id = b.id;
        start = b.start;
        end = b.end;
        packages = b.packages;
    }
    return *this;
}

Package Belt::removePackage(){
    if(packages.size() > 0){
        return packages.pop();
    } 
    return Package(); //default package (id: -1)
} 