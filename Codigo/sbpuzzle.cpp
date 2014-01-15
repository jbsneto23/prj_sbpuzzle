#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

#include "solver.h"

int main(int argc, char *argv[])
{
    if(argc > 1){
        string arg1 = argv[1];
        if(arg1.compare("-h") == 0){
            if(argc > 2){
                Solver::solve_puzzle_html(argv[2]);
            } else {
                cerr << "sbpuzzle: nenhum arquivo de entrada foi passado como argumento." << endl;
            }
        } else {
            Solver::solve_puzzle(arg1);
        }
    } else {
        cerr << "sbpuzzle: nenhum arquivo de entrada foi passado como argumento." << endl;
    }
    return 0;
}
