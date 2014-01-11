#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

#include "snapshot.h"

Snapshot::Snapshot(int r, int c, int** b, vector<Block> bks): blocks(bks)
{
    rows = r;
    columns = c;
    board = new int*[rows];
    stringstream ss;
    for(int i = 0; i < rows; i++){
        board[i] = new int[columns];
        for(int j = 0; j < columns; j++){
            board[i][j] = b[i][j]; // copiando o conteudo de b
            // montando a string key (que representa a matriz na forma row major e tambem é a chave na tabela hash)
            if(board[i][j] > 9){
                ss << "*" << board[i][j] << "*";
            } else if(board[i][j] < 0){
                ss << ".";
            } else {
                ss << board[i][j];
            }
        }
    }
    key = ss.str();
}

Snapshot::Snapshot(int r, int c, int** b, vector<Block> bks, queue<string> m, int numBlock, string directionMove, int qtdMoves): blocks(bks), moves(m)
{
    rows = r;
    columns = c;
    board = new int*[rows];
    stringstream ss;
    for(int i = 0; i < rows; i++){
        board[i] = new int[columns];
        for(int j = 0; j < columns; j++){
            board[i][j] = b[i][j]; // copiando o conteudo de b
            // montando a string key (que representa a matriz na forma row major e tambem é a chave na tabela hash)
            if(board[i][j] > 9){
                ss << "*" << board[i][j] << "*";
            } else if(board[i][j] < 0){
                ss << ".";
            } else {
                ss << board[i][j];
            }
        }
    }
    key = ss.str();
    // Adicionando a jogada a fila de jogadas moves
    ss.str("");
    ss.clear();
    ss << "Bloco " << numBlock << " " << directionMove << " " <<  (qtdMoves == 1 ? "posicao" : "posicoes");
    moves.push(ss.str());
}


Snapshot::~Snapshot()
{
    // desalocando a matriz
    for(int i = 0; i < rows; i++){
        delete[] board[i];
    }
    delete[] board;
}

string Snapshot::to_string()
{
    stringstream ss;
    for(int i = 0; i < columns + 2; i++){ // inicio do tabuleiro
        ss << "*";
    }
    ss << endl;
    for(int i = 0; i < rows; i++){
        ss << "*";
        for(int j = 0; j < columns; j++){
            if(board[i][j] < 0){
                ss << ".";
            } else if(board[i][j] == 0){
                ss << "X";
            } else {
                ss << board[i][j];
            }
        }
        ss << "*" << endl;
    }
    for(int i = 0; i < columns + 2; i++){ // final do tabuleiro
        ss << "*";
    }
    return ss.str();
}

int Snapshot::get_rows()
{
    return rows;
}

int Snapshot::get_columns()
{
    return columns;
}

int** Snapshot::get_board()
{
    return board;
}

vector<Block> Snapshot::get_blocks()
{
    return blocks;
}

queue<string> Snapshot::get_moves()
{
    return moves;
}

string Snapshot::get_key()
{
    return key;
}

bool Snapshot::is_solution()
{
    int j = columns - 1;
    // percorre a ultima coluna e verifica se tem alguma posição com o valor 0 (que é o valor da peça alvo)
    for(int i = 0; i < rows; i++){
        if(board[i][j] == 0){
            return true;
        }
    }
    return false;
}
