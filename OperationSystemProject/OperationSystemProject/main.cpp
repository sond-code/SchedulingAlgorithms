//
//  main.cpp
//  OperationSystemProject
//
//  Created by Sondos Ali on 13/01/2023.
//

#include <iostream>
#include "Process.h"
using namespace std;

int main(){
    int numP;
    numberOfProcesses(&numP);
    Process p[numP];
    input_process(p, numP);
    Execute();
    average_function(numP);

    return 0;
}


//void fast_sort(int a[], int n) {
//    unordered_map<int, int> count;
//    for (int i = 0; i < n; i++) {
//        count[a[i]]++;
//    }
//    int index = 0;
//    for (auto &c : count) {
//        for (int i = 0; i < c.second; i++) {
//            a[index++] = c.first;
//        }
//    }
//}
