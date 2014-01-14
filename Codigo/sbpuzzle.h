#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

#ifndef SBPUZZLE_H
#define SBPUZZLE_H

// ------------------------ block.h ------------------------
class Block
{
    public:
        Block(int n, int r, int c, int w, int h, char d);
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
        int number; // numero do bloco: 0 se for a pe�a alvo e > 0 se for outra pe�a
        int row; // linha
        int column; // coluna
        int width; // largura
        int height; // altura
        char direction; // dire��o
};
// ---------------------------------------------------------

// ----------------------------- puzzle.h -----------------------------
class Puzzle
{
    public:
        static const int MAX_SIZE = 80; // tamanho m�ximo que o tabuleiro pode ter (linhas e colunas)
        Puzzle(string file);
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
// --------------------------------------------------------------------

// --------------------------- snapshot.h ---------------------------
class Snapshot
{
    public:
        Snapshot(int r, int c, int** b, vector<Block> bks); // construtor para o primeiro estado do tabuleiro (inicio)
        Snapshot(bool html_mode, int r, int c, int** b, vector<Block> bks, queue<string> m, int numBlock, string directionMove, int qtd);
        virtual ~Snapshot();
        string to_string(); // retorna o tabuleiro em ascii
        string to_html(); // retorna o tabuleiro em html (somente a parte table).
        int get_rows();
        int get_columns();
        int** get_board();
        vector<Block> get_blocks();
        queue<string> get_moves();
        string get_key();
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
        HashTable(int r, int c);
        virtual ~HashTable();
        int hash(string key);
        bool insert(string key, Snapshot* shot); // true se key n�o estiver na tabela (a inser��o � feita) e false caso key j� exista (nada � feito)
        Snapshot* get(string key); // retorna ponteiro para objeto Snapshot se key estiver na tabela e NULL caso key n�o esteja na tabela
        int size();
        void print_content(); // imprime o conteudo da hashtable
    protected:
    private:
        int rows;
        int columns;
        int length; // tamanho da tabela hash
        int s; // numero de elementos na tabela hash
        Node** table;
};
// -----------------------------------------------------------------

/**
*
* Classe principal do programa, respons�vel por ler o arquivo de entrada e retornar a solu��o do quebra-cabe�a.
*
* @author Jo�o
* @author Ingrid
*/
class sbpuzzle
{
    public:

        /**
        *
        * Fun��o que recebe o Snapshot do estado inicial de um quebra-cabe�a e retorna o Snapshot da solu��o deste quebra-cabe�a ou NULL caso n�o tenha solu��o.
        *
        * @param shot Snapshot do estado inicial do quebra-cabe�a.
        * @param html_mode Flag que indica se o resultado das mens�gens deve ser em ASCII ou em HTML.
        * @return Snapshot da solu��o ou NULL caso o quebra-cabe�a n�o tenha solu��o.
        */
        static Snapshot* solve(Snapshot* shot, bool html_mode);

        /**
        *
        * Fun��o que recebe o arquivo de entrada de um quebra-cabe�a, soluciona-o e imprime na tela os resultados.
        *
        * @param puzzle_file Nome do arquivo que cont�m as informa��es do quebra-cabe�a.
        */
        static void solve_puzzle(string puzzle_file);

        /**
        *
        * Fun��o que recebe o arquivo de entrada de um quebra-cabe�a, soluciona-o e gera um documento HTML com os resultados.
        *
        * @param puzzle_file Nome do arquivo que cont�m as informa��es do quebra-cabe�a.
        */
        static void solve_puzzle_html(string puzzle_file);
    protected:
    private:
};

#endif // SBPUZZLE_H
