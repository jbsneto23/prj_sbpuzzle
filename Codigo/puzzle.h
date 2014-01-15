#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include "block.h"

using namespace std;

#ifndef PUZZLE_H
#define PUZZLE_H

/**
*
* A classe Puzzle representa o quebra-cabe�a. � respons�vel por ler o arquivo de entrada e valid�-lo, gerando o estado inicial.
*
* @author Jo�o
* @author Ingrid
*/
class Puzzle
{
    public:
        static const int MAX_SIZE = 80; // tamanho m�ximo que o tabuleiro pode ter (linhas e colunas)

        /**
        *
        * Construtor que inicia o estado da classe Puzzle.
        *
        * @param file Nome do arquivo do tabuleiro.
        */
        Puzzle(string file);

        /**
        *
        * Destrutor que libera a mem�ria alocada pela classe Puzzle.
        *
        */
        virtual ~Puzzle();

        /**
        *
        * Fun��o que recupera o n�mero de linhas de um tabuleiro.
        *
        * @return O n�mero de linhas.
        */
        int get_rows();

        /**
        *
        * Fun��o que recupera o n�mero de colunas de um tabuleiro.
        *
        * @return O n�mero de colunas.
        */
        int get_columns();

        /**
        *
        * Fun��o recupera a matriz que representa o tabuleiro.
        *
        * @return Matriz de inteiros.
        */
        int** get_board();

        /**
        *
        * Fun��o que recupera a lista de blocos do tabuleiro.
        *
        * @return A lista de blocos.
        */
        vector<Block> get_blocks();
    protected:
    private:
        int rows; // numero de linhas
        int columns; // numero de colunas
        int** board; // matriz que representa o tabuleiro: -1 representa os espa�os vazios, 0 representa a pe�a alvo, 1..127 s�o os outros blocos
        vector<Block> blocks; // lista de blocos (pe�as) que tambem est�o representadas no tabuleiro
};

#endif // PUZZLE_H
