#include <string>
#include <iostream>
#include <sstream>
#include <list>
#include <fstream>

#include "block.h"

using namespace std;

#include "puzzle.h"

Puzzle::Puzzle(string file_name)
{
    ifstream file(file_name.c_str(), ifstream::in);
    if(file.is_open()){
        string buffer;
        stringstream ss;
        // lendo o tamanho do tabuleiro
        getline(file, buffer);
        ss << buffer;
        ss >> rows >> columns;
        if(rows > 0 && rows <= MAX_SIZE && columns > 0 && columns <= MAX_SIZE){
            // inicializando a matriz
            board = new int*[rows];
            for(int i = 0; i < rows; i++){
                board[i] = new int[columns];
                for(int j = 0; j < columns; j++){
                    board[i][j] = -1;
                }
            }
        } else {
            cerr << "sbpuzzle: erro ao ler as dimensoes do tabuleiro, a primeira linha do arquivo '" << file_name << "' deve conter dois numeros inteiros positivos entre 1 e 80." << endl;
            file.close();
            exit(-1);
        }
        int r, c, w, h;
        char d;
        int number = 0;
        while(!file.eof() && number <= 127){
            // limpando ss
            ss.str("");
            ss.clear();
            // lendo a próxima linha
            getline(file, buffer);
            if(buffer.empty()){
                continue;
            }
            ss << buffer;
            ss >> r >> c >> w >> h >> d;
            if(r < 1 || r > rows || c < 1 || c > columns){
                cerr << "sbpuzzle: o bloco representado pela linha '" << buffer << "' esta fora do tabuleiro, portanto sera descartado." << endl;
            } else {
                if(w < 1 || w > rows || h < 1 || h > columns){
                    cerr << "sbpuzzle: o bloco representado pela linha '" << buffer << "' esta com dimensoes negativas ou que ultrapassam o tabuleiro, portanto sera descartado." << endl;
                } else {
                    if((r - 1 + h) > rows || (c - 1 + w) > columns){
                        cerr << "sbpuzzle: o bloco representado pela linha '" << buffer << "' esta com dimensoes que ultrapassam o tabuleiro, portanto sera descartado." << endl;
                    } else {
                        if(d != 'a' && d != 'h' && d != 'v'){
                            cerr << "sbpuzzle: o bloco representado pela linha '" << buffer << "' nao possui uma direcao de deslocamento valida, portanto sera descartado." << endl;
                        } else {
                            bool valido = true;
                            for(int i = r - 1; i < r - 1 + h; i++){
                                for(int j = c - 1; j < c - 1 + w; j++){
                                    if(board[i][j] != -1){
                                        valido = false;
                                    }
                                }
                            }
                            if(valido){
                                Block block = Block(number, r - 1, c - 1, w, h, d);
                                blocks.push_back(block);
                                for(int i = r - 1; i < r - 1 + h; i++){
                                    for(int j = c - 1; j < c - 1 + w; j++){
                                        board[i][j] = number;
                                    }
                                }
                                number++;
                            } else {
                                cerr << "sbpuzzle: o bloco representado pela linha '" << buffer << "' esta sobrepondo outro bloco, portanto sera descartado." << endl;
                            }
                        }
                    }
                }
            }
        }
        if(number == 0){
            cerr << "sbpuzzle: nenhum bloco foi considerado valido." << endl;
            exit(-1);
        }
    } else {
        cerr << "sbpuzzle: erro ao ler o arquivo '" << file_name << "'." << endl;
        file.close();
        exit(-1);
    }

}

Puzzle::~Puzzle()
{
    // desalocando a matriz
    for(int i = 0; i < rows; i++){
        delete[] board[i];
    }
    delete[] board;
}

int Puzzle::get_rows()
{
    return rows;
}

int Puzzle::get_columns()
{
    return columns;
}

int** Puzzle::get_board()
{
    return board;
}

vector<Block> Puzzle::get_blocks()
{
    return blocks;
}
