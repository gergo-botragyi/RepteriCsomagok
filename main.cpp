#include <iostream>
#include <limits>
#include "main.h"
#include "belt.h"
#include "controlcenter.h"
#include "junction.h"
#include "package.h"
#include "path.h"
#include "io.h"
#include "memtrace.h"
#include "gtest_lite.h"

using std::cout;

bool duplicateJunction(const char name, List<Junction>& junctions){
    return junctions.findJunctionByChar(name) != nullptr;
}

void addBelt(const Belt& b, List<Junction>& junctions){
    junctions.findJunctionByChar(b.getStart())->getItem().addBelt(b);
    junctions.findJunctionByChar(b.getEnd())->getItem().setReachable();
}

void addPackage(const Package& p, List<Junction>& junctions){
    junctions.findJunctionByChar(p.getStart())->getItem().addPackage(p);
}

void testAllJunctions(List<Junction>& junctions){ //Only works if the addBelt function from main was used
    char j = '\0';
    for (size_t i = 0; i < junctions.size(); i++)
    {
        if(!junctions[i].getItem().getHasBelt() || !junctions[i].getItem().getReachable()) 
            j = junctions[i].getItem().getName();
    }

    if(j != '\0'){
        throw std::runtime_error(std::string("Error: The following junction has no belt or is not reachable from anywhere: ") + j);
    }
}

/// @brief Tests the package, belt and junction classes and makes a lists of junctions
void test1(){
    TEST(test1, basics){
        Package p1(1, 'A', 'B');
        Package p2(2, 'B', 'C');
        Package p3(3, 'C', 'B');

        Package p4;
        p4 = p3;
        
        Belt ab(1, 'A', 'B');
        Belt ac(2, 'A', 'C');
        Belt bc(3, 'B', 'C');
        Belt ca(4, 'C', 'A');

        Belt cpy;
        cpy = ca;
        
        Junction A('A');
        Junction B('B');
        Junction C('C');
        
        A.addBelt(ab);
        A.addBelt(ac);
        B.addBelt(bc);
        C.addBelt(ca);

        if(cpy != ca) C.addBelt(cpy);

        A.getBelt(0).addPackage(Package(4, 'A', 'B'));
        cout << "Number of packages on belt '" << A.getBelt(0).getId() << "': " << A.getBelt(0).getNOfPackages() << "\n";

        cout << "Package on belt:";
        A.getBelt(0).getPackage(0).display(cout);

        cout << "Package removed from belt:";
        A.getBelt(0).removePackage().display(cout);
        
        A.addPackage(p1);
        B.addPackage(p2);
        C.addPackage(p3);

        if(p3 != p4) C.addPackage(p4);
        
        List<Junction> junctions;
        try
        {
            junctions.remove(A);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }

        junctions.add(A);
        junctions.add(B);
        junctions.add(C);

        try
        {
            cout << junctions[4].getItem().getName();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }

        cout << "\nJunctions:\n";
        displayJunctions(junctions, cout);
        
    }ENDM
}

/// @brief tests the BFS algorithm
void test2(){
    TEST(test2, BFS){
        Junction A('A');
        Junction B('B');
        Junction C('C');
        Junction D('D');
        Junction E('E');
        Junction F('F');

        A.addBelt(Belt(1, 'A', 'B'));
        A.addBelt(Belt(2, 'A', 'C'));
        B.addBelt(Belt(3, 'B', 'C'));
        C.addBelt(Belt(4, 'C', 'A'));
        C.addBelt(Belt(5, 'C', 'D'));
        D.addBelt(Belt(6, 'D', 'E'));
        E.addBelt(Belt(7, 'E', 'B'));

        List<Junction> junctions;

        try
        {
            junctions.pop();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        junctions.add(A);
        junctions.add(B);
        junctions.add(C);
        junctions.add(D);
        junctions.add(E);
        
        junctions.add(F);
        junctions.remove(F);

        try
        {
            junctions.remove(F);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        

        bfs alg(A);
        alg.createTable(junctions);
        alg.display();
    }ENDM
}

/// @brief Test of path
void test3(){
    TEST(test3, path){
        char stops[] = {'a', 'b', 'c'};
        Path p1(1, stops);
        p1.addStop('d');

        List<char> pathStops = p1.getStops();
        cout << "Path " << p1.getID() << "\nStops: ";

        for (size_t i = 0; i < pathStops.size(); i++)
        {
            cout << pathStops[i].getItem() << " ";
        }

        cout << "\nCurrent stop: '" << p1[0] << "'. Next stop: '" << p1.nextStop('a') << "'\n";

        Path p2;
        p2 = p1;
        p2.addStop('e');
        cout << "Path p2: next stop from 'd': " << p2.nextStop('d') << "\n";
        
    }ENDM
}

/// @brief Test of making a path from the table element of a bfs object
void test4(){
    TEST(test4, bfsPath){
        Junction A('A');
        Junction B('B');
        Junction C('C');
        Junction D('D');
        
        A.addBelt(Belt(1, 'A', 'B'));
        B.addBelt(Belt(2, 'B', 'C'));
        C.addBelt(Belt(3, 'C', 'D'));
        
        List<Junction> junctions; junctions.add(A); junctions.add(B); junctions.add(C); junctions.add(D);

        try
        {
            junctions.remove(5);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        bfs alg(A);
        alg.createTable(junctions);
        alg.display();
        List<char> stops = alg.makePath('D');
        
        cout << "Path from " << alg.getJunction() << " to 'D': " << stops << "\n";
        
    }ENDM
}

/// @brief Controllcenter test
void test5(){
    TEST(test5, CC){
        Junction A('A');
        Junction B('B');
        Junction C('C');
        Junction D('D');
        List<Junction> junctions; junctions.add(A); junctions.add(B); junctions.add(C); junctions.add(D);
        
        addBelt(Belt(1, 'A', 'B'), junctions);
        addBelt(Belt(2, 'B', 'C'), junctions);
        addBelt(Belt(3, 'C', 'D'), junctions);
        addBelt(Belt(4, 'D', 'A'), junctions);

        Package packOne(1,'A','B');
        addPackage(packOne, junctions);
        addPackage(Package(2,'B','C'), junctions);
        addPackage(Package(3,'C','D'), junctions);
        addPackage(Package(4,'D','A'), junctions);
        addPackage(Package(5,'A','B'), junctions);

        Package noGoPack(6,'A','A');
        noGoPack.setArrived();
        addPackage(noGoPack, junctions);
        
        testAllJunctions(junctions);
        
        CC controller;
        
        for (size_t i = 0; i < junctions.size(); i++)
        {
            controller.makeBFS(junctions, i);
        }

        initializePaths(junctions, controller);

        try
        {
            controller.makePath('E', 'D', 3);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        

        cout << "\n";
        Belt& nextB = controller.nextBelt(packOne.getId(), 'A', junctions[0].getItem().getBeltList() );
        cout << "Next belt for package '"<< packOne.getId() << "': belt '" << nextB.getId() << "'\n";
        
        junctions[0].getItem().send(packOne, nextB);
        cout << "Package sent to belt.\n";
        
        cout << "\n";
        displayAllPackages(junctions, cout);
        cout << "Check if every package has arrived: " << std::boolalpha << controller.allDone(junctions) << "\n";
        
    }ENDM
}

/// @brief Console input test (writes data to test_output.txt)
void test6(){
    TEST(test6, console_input){
        List<Junction> junctions;

        std::istream& is = std::cin;

        readConsole(junctions, cout, is);
        testAllJunctions(junctions);

        displayJunctions(junctions, cout);

        write(junctions, "standard_output.txt");
    }ENDM
}

void inputErrors(List<Junction>& junctions){
    try
    {
        processBelt(junctions,1, "A");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        processBelt(junctions,1, "X,A");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        processBelt(junctions,1, "A,X");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    try
    {
        processPackage(junctions, "1,A,B,C");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    try
    {
        readFile(junctions, "nemletezofile.txt");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

/// @brief File input test (Reads data from test_adatok.txt, writes to test_output.txt)
void test7(){
    TEST(test7,file_input){
        List<Junction> junctions;

        readFile(junctions, "test_adatok.txt");

        inputErrors(junctions);

        testAllJunctions(junctions);

        displayJunctions(junctions, cout);

        write(junctions, "test_output.txt");
    }ENDM
}

/// @brief Whole input test
void test8(){
    TEST(test8, input){
        List<Junction> junctions;
        read(junctions);
        
        testAllJunctions(junctions);

        displayJunctions(junctions, cout);
    }ENDM
}

/// @brief Simulates the whole process of getting packages to their destination junction.\\\n
/// @brief Reads an input from the console (either directly from there or a given file). 
/// @brief Processes the data and stores it in a list. 
/// @brief Makes the bfs objects for all junctions and creates a path for all packages.
/// @brief Sends the packages from junction to junction through belts until they are at their destination.\\\n
/// @brief Also displays the whole process.
void simulation(){
    CC controllcenter;
    List<Junction> junctions;

    read(junctions);
    testAllJunctions(junctions);

    cout << "Initialized\n"; 
    displayJunctions(junctions, cout);

    for (size_t i = 0; i < junctions.size(); i++)
    {
        controllcenter.makeBFS(junctions, i);
    }

    initializePaths(junctions, controllcenter);

    displayAllPackages(junctions, cout);

    //runs until every package has arrived to its destination
    while(!controllcenter.allDone(junctions)){

        simulationStep(junctions, controllcenter);
    }

    cout << "\nDone\n"; 
    displayJunctions(junctions, cout);

    write(junctions);
}

void initializePaths(List<Junction>& junctions, CC& controllcenter){
    //Creates a path for every package
    for (size_t i = 0; i < junctions.size(); i++)
    {
        Junction& currJunc = junctions[i].getItem();
        for (int j = 0; j < currJunc.getNOfPackages(); j++)
        {
            Package& currPack = currJunc.getPackage(j);

            if(!controllcenter.hasPath(currPack.getId())){
                controllcenter.makePath(currJunc.getName(), currPack.getDest(), currPack.getId());
            }
        }
    }
}

void simulationStep(List<Junction>& junctions, CC& controllcenter){
    for (size_t i = 0; i < junctions.size(); i++)
    {
        Junction& currJunction = junctions[i].getItem();
        
        stepBelts(junctions, currJunction);
        
        Package currPack = currJunction.getNextPackage();
        
        if(currPack.getId() != -1){ //if there's no next package it gives back a default with an id of -1
            
            Belt& nextBelt = controllcenter.nextBelt(currPack.getId(), currJunction.getName(), currJunction.getBeltList());
            
            currJunction.send(currPack, nextBelt);
            displayAllPackages(junctions, cout);
        }
    }
}

void stepBelts(List<Junction>& junctions, Junction& currJunction){
    for (int j = 0; j < currJunction.getNOfBelts(); j++)
    {
        Belt& currBelt = currJunction.getBelt(j);
        Package currPack = currBelt.removePackage();
        if(currPack.getId() != -1){ //if there's no package on the belt it gives back a default with an id of -1
            Junction& endJunction = junctions.findJunctionByChar(currBelt.getEnd())->getItem();

            if(currPack.getDest() == endJunction.getName()) currPack.setArrived();
            endJunction.addPackage(currPack);
            displayAllPackages(junctions, cout);
        }
    }
}

int main(){
    #ifdef CPORTA

    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();

    #endif

    #ifdef INPTESZT

    test8();
    
    #endif

    #if !defined(CPORTA) && !defined(INPTESZT)
    
    simulation();

    #endif

    return 0;
}
