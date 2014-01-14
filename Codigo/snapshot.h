#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

#include "block.h"

using namespace std;

#ifndef SNAPSHOT_H
#define SNAPSHOT_H

/**
*
* A classe Snapshot representa um estado do tabuleiro, gaurdando todas as posições dos blocos e todas as movimentações feitas até se chegar neste estado.
*
* @author João
* @author Ingrid
*/
class Snapshot
{
    public:

        /**
        *
        * Construtor utilizado para gerar um Snapshot (fotografia) do estado inicial.
        *
        * @param r Número de linhas do tabuleiro.
        * @param c Número de colunas do tabuleiro.
        * @param b Matriz que representa o tabuleiro.
        * @param bks Lista de blocos.
        */
        Snapshot(int r, int c, int** b, vector<Block> bks); // construtor para o primeiro estado do tabuleiro (inicio)

        /**
        *
        * Construtor utilizado para gerar um Snapshot (fotografia) de um estado do tabuleiro gerado a partir da movimentação de um bloco.
        *
        * @param r Número de linhas do tabuleiro.
        * @param c Número de colunas do tabuleiro.
        * @param b Matriz que representa o tabuleiro.
        * @param bks Lista de blocos.
        * @param m Fila de movimentos (deve ser passado a fila do Snapshot que partiu esse estado).
        * @param numBlock Número do blovo que se moveu.
        * @param directionMove Direção pra qual o bloco se moveu.
        * @param qtd Quantidade de posições que o bloco se moveu.
        */
        Snapshot(bool html_mode, int r, int c, int** b, vector<Block> bks, queue<string> m, int numBlock, string directionMove, int qtd);

        /**
        *
        * Destrutor que libera a memória alocada pela classe Snapshot.
        *
        */
        virtual ~Snapshot();

        /**
        *
        * Função que retorna o tabuleiro em ASCII.
        *
        * @return o tabuleiro em modo texto.
        */
        string to_string(); // retorna o tabuleiro em ascii

        /**
        *
        * Função que retorna o tabuleiro em HTML.
        *
        * @return o HTML de uma tabela contendo os dados do tabuleiro.
        */
        string to_html(); // retorna o tabuleiro em html (somente a parte table).

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

        /**
        *
        * Função que recupera a fila de movimentos feitos até se chegar neste estado.
        *
        * @return a fila de movimento.
        */
        queue<string> get_moves();

        /**
        *
        * Função que recupera a chave de um snapshot, que sua matriz de tabuleiro representada na forma row-major.
        *
        * @return a chave do snapshot.
        */
        string get_key();

        /**
        *
        * Função que verifica se o snapshot é uma solução, ou seja, se o bloco-alvo atingiu a posição-alvo.
        *
        * @return true se o snapshot atual é a solução, e false, caso contrário.
        */
        bool is_solution(); // verifica se esse snapshot é um solução, ou seja, verifica se a peça alvo chegou a aresta da direita
    protected:
    private:
        string key; // chave da tabela hash que é construida no construtor
        int rows;
        int columns;
        int** board;
        vector<Block> blocks;
        queue<string> moves; // jogadas
};
#endif // SNAPSHOT_H
