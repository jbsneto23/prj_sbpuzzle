#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

#ifndef SNAPSHOT_H
#define SNAPSHOT_H


class Snapshot
{
    public:
        /** Default constructor */
        Snapshot(int r, int c, int** b, vector<Block> bks); // construtor para o primeiro estado do tabuleiro (inicio)
        Snapshot(int r, int c, int** b, vector<Block> bks, queue<string> m, int numBlock, string directionMove, int qtd);
        /** Default destructor */
        virtual ~Snapshot();
        string to_string(); // retorna o tabuleiro em ascii
        int get_rows();
        int get_columns();
        int** get_board();
        vector<Block> get_blocks();
        queue<string> get_moves();
        string get_key();
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
