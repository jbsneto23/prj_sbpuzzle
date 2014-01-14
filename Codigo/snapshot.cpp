#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

#include "block.h"

using namespace std;

#include "snapshot.h"

Snapshot::Snapshot(int r, int c, int** b, vector<Block> bks): blocks(bks)
{
    rows = r;
    columns = c;
    board = new int*[rows];
    stringstream ss;
    ss.str("");
    ss.clear();
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

Snapshot::Snapshot(bool html_mode, int r, int c, int** b, vector<Block> bks, queue<string> m, int numBlock, string directionMove, int qtdMoves): blocks(bks), moves(m)
{
    rows = r;
    columns = c;
    board = new int*[rows];
    stringstream ss;
    ss.str("");
    ss.clear();
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
    if(html_mode){
        if(numBlock == 0){
            ss << "<h4>Bloco X " << directionMove << " " <<  qtdMoves << (qtdMoves == 1 ? " posição" : " posições") << "</h4>" << endl;
        } else {
            ss << "<h4>Bloco " << numBlock  << " " << directionMove << " " <<  qtdMoves << (qtdMoves == 1 ? " posição" : " posições") << "</h4>" << endl;
        }
        ss << to_html() << endl;
    } else {
        if(numBlock == 0){
            ss << "Bloco X " << directionMove << " " <<  qtdMoves << (qtdMoves == 1 ? " posicao" : " posicoes");
        } else {
            ss << "Bloco " << numBlock  << " " << directionMove << " " <<  qtdMoves << (qtdMoves == 1 ? " posicao" : " posicoes");
        }
    }
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

string Snapshot::to_html()
{
    bool* signals = new bool[blocks.size()];
    memset(signals, false, sizeof(bool) * blocks.size());
    stringstream ss;
    ss << "<table border=\"5\" cellspacing=\"5\">" << endl;
    ss << "<tbody>" << endl;
    for(int i = 0; i < rows; i++){
        ss << "<tr>" << endl;
        for(int j = 0; j < columns; j++){
            if(board[i][j] < 0){
                ss << "<td bgcolor=\"#87CEFA\" height=\"50\" width=\"50\"></td>" << endl;
            } else if(board[i][j] == 0){
                if(!signals[0]){
                    ss << "<td bgcolor=\"green\" align=\"center\" height=\"50\" width=\"50\"";
                    if(blocks.at(0).get_width() > 1){
                        ss << " colspan=\"" << blocks.at(0).get_width() << "\"";
                    }
                    if(blocks.at(0).get_height() > 1){
                        ss << " rowspan=\"" << blocks.at(0).get_height() << "\"";
                    }
                    ss << ">X</td>" << endl;
                    signals[0] = true;
                }
            } else {
                if(!signals[board[i][j]]){
                    ss << "<td bgcolor=\"yellow\" align=\"center\" height=\"50\" width=\"50\"";
                    if(blocks.at(board[i][j]).get_width() > 1){
                        ss << " colspan=\"" << blocks.at(board[i][j]).get_width() << "\"";
                    }
                    if(blocks.at(board[i][j]).get_height() > 1){
                        ss << " rowspan=\"" << blocks.at(board[i][j]).get_height() << "\"";
                    }
                    ss << ">" << board[i][j] << "</td>" << endl;
                    signals[board[i][j]] = true;
                }
            }
        }
        ss << "</tr>" << endl;
    }
    ss << "</tbody>" << endl;
    ss << "</table>" << endl;
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
