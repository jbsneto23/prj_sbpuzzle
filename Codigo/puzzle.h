#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include "block.h"

using namespace std;

#ifndef PUZZLE_H
#define PUZZLE_H

class Puzzle
{
    public:
        static const int MAX_SIZE = 80; // tamanho m�ximo que o tabuleiro pode ter (linhas e colunas)
        /** Default constructor */
        Puzzle(string file);
        /** Default destructor */
        virtual ~Puzzle();
        int get_rows();
        int get_columns();
        int** get_board();
        vector<Block> get_blocks();
    protected:
    private:
        int rows; // numero de linhas
        int columns; // numero de colunas
        int** board; // matriz que representa o tabuleiro: -1 representa os espa�os vazios, 0 representa a pe�a alvo, 1..127 s�o os outros blocos
        vector<Block> blocks; // lista de blocos (pe�as) que tamb�m est�o representadas no tabuleiro
};

#endif // PUZZLE_H
