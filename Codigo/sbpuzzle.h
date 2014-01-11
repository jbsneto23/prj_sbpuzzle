#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

#ifndef SBPUZZLE_H
#define SBPUZZLE_H

// ------------------------ block.h ------------------------
class Block
{
    public:
        /** Default constructor */
        Block();
        Block(int n, int r, int c, int w, int h, char d);
        /** Default destructor */
        virtual ~Block();
        int get_number();
        void set_number(int n);
        int get_row();
        void set_row(int r);
        int get_column();
        void set_column(int c);
        int get_width();
        void set_width(int w);
        int get_height();
        void set_height(int h);
        char get_direction();
        void set_direction(char d);
    protected:
    private:
        int number; // numero do bloco: 0 se for a peça alvo e > 0 se for outra peça
        int row; // linha
        int column; // coluna
        int width; // largura
        int height; // altura
        char direction; // direção
};
// ---------------------------------------------------------

// ----------------------------- puzzle.h -----------------------------
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
        vector<Block> get_blocks();
        string rowMajor();
        int hash(string str);
        int hash();
    protected:
    private:
        int rows; // numero de linhas
        int columns; // numero de colunas
        int** board; // matriz que representa o tabuleiro: -1 representa os espaços vazios, 0 representa a peça alvo, 1..127 são os outros blocos
        vector<Block> blocks; // lista de blocos (peças) que também estão representadas no tabuleiro


};
// --------------------------------------------------------------------

// --------------------------- snapshot.h ---------------------------
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
// ------------------------------------------------------------------

// -------------------------- hashtable.h --------------------------
typedef struct Node {
    string key;
    Snapshot* shot;
    Node* next;
} Node;

class HashTable
{
    public:
        /** Default constructor */
        HashTable(int r, int c);
        /** Default destructor */
        virtual ~HashTable();
        int hash(string key);
        bool insert(string key, Snapshot* shot); // true se key não estiver na tabela (a inserção é feita) e false caso key já exista (nada é feito)
        Snapshot* get(string key); // retorna ponteiro para objeto Snapshot se key estiver na tabela e NULL caso key não esteja na tabela
        int size();
    protected:
    private:
        int rows;
        int columns;
        int length; // tamanho da tabela hash
        int s; // numero de elementos na tabela hash
        Node** table;
};
// -----------------------------------------------------------------

class sbpuzzle
{
    public:
        /** Default constructor */
        sbpuzzle();
        /** Default destructor */
        virtual ~sbpuzzle();
    protected:
    private:
};

#endif // SBPUZZLE_H
