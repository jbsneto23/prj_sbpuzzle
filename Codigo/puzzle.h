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
* A classe Puzzle representa o quebra-cabeça. É responsável por ler o arquivo de entrada e validá-lo, gerando o estado inicial.
*
* @author João
* @author Ingrid
*/
class Puzzle
{
    public:
        static const int MAX_SIZE = 80; // tamanho máximo que o tabuleiro pode ter (linhas e colunas)

        /**
        *
        * Construtor que inicia o estado da classe Puzzle.
        *
        * @param file Nome do arquivo do tabuleiro.
        */
        Puzzle(string file);

        /**
        *
        * Destrutor que libera a memória alocada pela classe Puzzle.
        *
        */
        virtual ~Puzzle();

        /**
        *
        * Função que recupera o número de linhas de um tabuleiro.
        *
        * @return O número de linhas.
        */
        int get_rows();

        /**
        *
        * Função que recupera o número de colunas de um tabuleiro.
        *
        * @return O número de colunas.
        */
        int get_columns();

        /**
        *
        * Função recupera a matriz que representa o tabuleiro.
        *
        * @return Matriz de inteiros.
        */
        int** get_board();

        /**
        *
        * Função que recupera a lista de blocos do tabuleiro.
        *
        * @return A lista de blocos.
        */
        vector<Block> get_blocks();
    protected:
    private:
        int rows; // numero de linhas
        int columns; // numero de colunas
        int** board; // matriz que representa o tabuleiro: -1 representa os espaÁos vazios, 0 representa a peÁa alvo, 1..127 s„o os outros blocos
        vector<Block> blocks; // lista de blocos (peças) que tambem estão representadas no tabuleiro
};

#endif // PUZZLE_H
