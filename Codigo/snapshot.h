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
* A classe Snapshot representa um estado do tabuleiro, gaurdando todas as posi��es dos blocos e todas as movimenta��es feitas at� se chegar neste estado.
*
* @author Jo�o
* @author Ingrid
*/
class Snapshot
{
    public:

        /**
        *
        * Construtor utilizado para gerar um Snapshot (fotografia) do estado inicial.
        *
        * @param r N�mero de linhas do tabuleiro.
        * @param c N�mero de colunas do tabuleiro.
        * @param b Matriz que representa o tabuleiro.
        * @param bks Lista de blocos.
        */
        Snapshot(int r, int c, int** b, vector<Block> bks); // construtor para o primeiro estado do tabuleiro (inicio)

        /**
        *
        * Construtor utilizado para gerar um Snapshot (fotografia) de um estado do tabuleiro gerado a partir da movimenta��o de um bloco.
        *
        * @param r N�mero de linhas do tabuleiro.
        * @param c N�mero de colunas do tabuleiro.
        * @param b Matriz que representa o tabuleiro.
        * @param bks Lista de blocos.
        * @param m Fila de movimentos (deve ser passado a fila do Snapshot que partiu esse estado).
        * @param numBlock N�mero do blovo que se moveu.
        * @param directionMove Dire��o pra qual o bloco se moveu.
        * @param qtd Quantidade de posi��es que o bloco se moveu.
        */
        Snapshot(bool html_mode, int r, int c, int** b, vector<Block> bks, queue<string> m, int numBlock, string directionMove, int qtd);

        /**
        *
        * Destrutor que libera a mem�ria alocada pela classe Snapshot.
        *
        */
        virtual ~Snapshot();

        /**
        *
        * Fun��o que retorna o tabuleiro em ASCII.
        *
        * @return o tabuleiro em modo texto.
        */
        string to_string(); // retorna o tabuleiro em ascii

        /**
        *
        * Fun��o que retorna o tabuleiro em HTML.
        *
        * @return o HTML de uma tabela contendo os dados do tabuleiro.
        */
        string to_html(); // retorna o tabuleiro em html (somente a parte table).

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

        /**
        *
        * Fun��o que recupera a fila de movimentos feitos at� se chegar neste estado.
        *
        * @return a fila de movimento.
        */
        queue<string> get_moves();

        /**
        *
        * Fun��o que recupera a chave de um snapshot, que sua matriz de tabuleiro representada na forma row-major.
        *
        * @return a chave do snapshot.
        */
        string get_key();

        /**
        *
        * Fun��o que verifica se o snapshot � uma solu��o, ou seja, se o bloco-alvo atingiu a posi��o-alvo.
        *
        * @return true se o snapshot atual � a solu��o, e false, caso contr�rio.
        */
        bool is_solution(); // verifica se esse snapshot � um solu��o, ou seja, verifica se a pe�a alvo chegou a aresta da direita
    protected:
    private:
        string key; // chave da tabela hash que � construida no construtor
        int rows;
        int columns;
        int** board;
        vector<Block> blocks;
        queue<string> moves; // jogadas
};
#endif // SNAPSHOT_H
