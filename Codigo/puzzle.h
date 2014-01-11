#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

#ifndef PUZZLE_H
#define PUZZLE_H


class Puzzle
{
    public:
        static const int MAX_SIZE = 80; // tamanho máximo que o tabuleiro pode ter (linhas e colunas)
        /** Default constructor */
        Puzzle(string file);
        /** Default destructor */
        virtual ~Puzzle();
        string to_string(); // retorna o tabuleiro em ascii
        int get_rows();
        int get_columns();
        int** get_board();
    protected:
    private:
        int rows; // numero de linhas
        int columns; // numero de colunas
        int** board; // matriz que representa o tabuleiro: -1 representa os espaços vazios, 0 representa a peça alvo, 1..127 são os outros blocos
        vector<Block> blocks; // lista de blocos (peças) que também estão representadas no tabuleiro


};

#endif // PUZZLE_H
