#include "Testing.h"
#include "BinarySearchTree.h"
#include "Student.h"
#include <set>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace std;

// Допоміжна функція для генерації випадкового імені
string generateRandName() {
    string name = "";
    for (int i = 0; i < 8; i++) {
        name += (char)('A' + rand() % 26);
    }
    return name;
}

bool testBinarySearchTree() {
    srand(time(NULL));
    const int iters = 80000;
    const int keysAmount = iters * 2;
    const int itersToRangeQueries = 100;

    vector<Student> dataPool;
    for(int i = 0; i < keysAmount; ++i) {
        dataPool.push_back({generateRandName(), (double)(rand() % 100) / 10, true, 0});
    }

    vector<Student> dataToInsert(iters);
    vector<Student> dataToErase(iters);
    vector<Student> dataToFind(iters);
    vector<pair<Student, Student>> dataToRangeQueries;

    for (int i = 0; i < iters; i++) {
        dataToInsert[i] = dataPool[rand() % keysAmount];
        dataToErase[i] = dataPool[rand() % keysAmount];
        dataToFind[i] = dataPool[rand() % keysAmount];
    }

    for (int i = 0; i < itersToRangeQueries; i++) {
        Student minData = {generateRandName()};
        Student maxData = {generateRandName()};
        if (maxData < minData) swap(minData, maxData);
        dataToRangeQueries.push_back({minData, maxData});
    }

    // --- My Binary Search Tree ---
    BinarySearchTree myTree;
    clock_t myStart = clock();
    for (int i = 0; i < iters; i++) {
        myTree.insert(dataToInsert[i]);
    }
    int myInsertSize = (int)myTree.size();
    int myTreeHeight = myTree.height();
    int optimalTreeHeight = (int)log2(myInsertSize + 1) + 1;

    for (int i = 0; i < iters; i++) {
        myTree.erase(dataToErase[i]);
    }
    int myEraseSize = myInsertSize - (int)myTree.size();
    
    int myFoundAmount = 0;
    for (int i = 0; i < iters; i++) {
        if (myTree.find(dataToFind[i])) myFoundAmount++;
    }
    clock_t myEnd = clock();
    float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;

    // --- STL Set ---
    set<Student> stlTree;
    clock_t stlStart = clock();
    for (int i = 0; i < iters; i++) {
        stlTree.insert(dataToInsert[i]);
    }
    int stlInsertSize = (int)stlTree.size();
    for (int i = 0; i < iters; i++) {
        stlTree.erase(dataToErase[i]);
    }
    int stlEraseSize = stlInsertSize - (int)stlTree.size();
    
    int stlFoundAmount = 0;
    for (int i = 0; i < iters; i++) {
        if (stlTree.find(dataToFind[i]) != stlTree.end()) stlFoundAmount++;
    }
    clock_t stlEnd = clock();
    float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;

    // --- Range Queries ---
    clock_t myRangeStart = clock();
    int myRangeFoundAmount = 0;
    for (int i = 0; i < itersToRangeQueries; i++) {
        myRangeFoundAmount += (int)myTree.findInRange(dataToRangeQueries[i].first, dataToRangeQueries[i].second).size();
    }
    clock_t myRangeEnd = clock();
    float myRangeTime = (float(myRangeEnd - myRangeStart)) / CLOCKS_PER_SEC;

    clock_t stlRangeStart = clock();
    int stlRangeFoundAmount = 0;
    for (int i = 0; i < itersToRangeQueries; i++) {
        auto low = stlTree.lower_bound(dataToRangeQueries[i].first);
        auto up = stlTree.upper_bound(dataToRangeQueries[i].second);
        stlRangeFoundAmount += (int)distance(low, up);
    }
    clock_t stlRangeEnd = clock();
    float stlRangeTime = (float(stlRangeEnd - stlRangeStart)) / CLOCKS_PER_SEC;

    // --- Output Results ---
    cout << "My BST: height = " << myTreeHeight << ", optimal height = " << optimalTreeHeight << endl;
    cout << "Time: " << myTime << "s, size: " << myInsertSize << " - " << myEraseSize 
         << ", found: " << myFoundAmount << endl;
    cout << "Range time: " << myRangeTime << "s, range found: " << myRangeFoundAmount << endl << endl;

    cout << "STL Set (RB-Tree):" << endl;
    cout << "Time: " << stlTime << "s, size: " << stlInsertSize << " - " << stlEraseSize 
         << ", found: " << stlFoundAmount << endl;
    cout << "Range time: " << stlRangeTime << "s, range found: " << stlRangeFoundAmount << endl << endl;

    if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize &&
        myFoundAmount == stlFoundAmount && myRangeFoundAmount == stlRangeFoundAmount) {
        cout << "The lab is completed: Results match STL!" << endl;
        return true;
    }
    
    cerr << "Error: Results do not match STL :(" << endl;
    return false;
}