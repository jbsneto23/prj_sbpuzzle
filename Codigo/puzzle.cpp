#include <string>
#include <iostream>
#include <sstream>
#include <list>
#include <fstream>

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
        cout << buffer << endl;
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

        // inicializando a lista de pe�as
        blocks = list<Block>;

        int r, c, w, h;
        char d;
        // lendo a pe�a alvo
        bool alvo = false;
        while(!file.eof() && !alvo){
            // limpando ss
            ss.str("");
            ss.clear();
            // lendo a pr�xima linha
            getline(file, buffer);
            ss << buffer;
            ss >> r >> c >> w >> h >> d;
            if(r < 1 || r > rows || c < 1 || c > columns){
                cerr << "sbpuzzle: o bloco representado pela linha '" << buffer << "' esta fora do tabuleiro, portanto sera descartado." << endl;
            } else {
                if(w < 1 || w > rows || h < 1 || h > columns){
                    cerr << "sbpuzzle: o bloco representado pela linha '" << buffer << "' esta com dimensoes negativas ou que ultrapassam o tabuleiro, portanto sera descartado." << endl;
                } else {
                    if((r - 1 + h) > rows || (c - 1 + w) > columns){
                        cout << (r - 1 + h) << "   " << (c - 1 + w) << endl;
                        cerr << "sbpuzzle: o bloco representado pela linha '" << buffer << "' esta com dimensoes que ultrapassam o tabuleiro, portanto sera descartado." << endl;
                    } else {
                        if(d != 'a' && d != 'h' && d != 'v'){
                            cerr << "sbpuzzle: o bloco representado pela linha '" << buffer << "' nao possui uma direcao de deslocamento valida, portanto sera descartado." << endl;
                        } else {
                            alvo = true;
                            for(int i = r - 1; i < r - 1 + h; i++){
                                for(int j = c - 1; j < c - 1 + w; j++){
                                    if(board[i][j] != -1){
                                        alvo = false;
                                    }
                                }
                            }
                            if(alvo){
                                Block blockAlvo = Block(0, r, c, w, h, d);
                                blocks.push_back(blockAlvo);
                                for(int i = r - 1; i < r - 1 + h; i++){
                                    for(int j = c - 1; j < c - 1 + w; j++){
                                        board[i][j] = 0;
                                    }
                                }
                            } else {
                                cerr << "sbpuzzle: o bloco representado pela linha '" << buffer << "' esta sobrepondo outro bloco, portanto sera descartado." << endl;
                            }
                        }
                    }
                }
            }
        }
        if(!alvo){
            cerr << "sbpuzzle: nenhum bloco foi considerado valido." << endl;
            exit(-1);
        }
        // lendo os blocos restantes
        int number = 1;
        while(!file.eof() && number <= 127){
            // limpando ss
            ss.str("");
            ss.clear();
            // lendo a pr�xima linha
            getline(file, buffer);
            ss << buffer;
            ss >> r >> c >> w >> h >> d;
            if(r < 1 || r > rows || c < 1 || c > columns){
                cerr << "sbpuzzle: o bloco representado pela linha '" << buffer << "' esta fora do tabuleiro, portanto sera descartado." << endl;
            } else {
                if(w < 1 || w > rows || h < 1 || h > columns){
                    cerr << "sbpuzzle: o bloco representado pela linha '" << buffer << "' esta com dimensoes negativas ou que ultrapassam o tabuleiro, portanto sera descartado." << endl;
                } else {
                    if((r - 1 + h) > rows || (c - 1 + w) > columns){
                        cout << (r - 1 + h) << "   " << (c - 1 + w) << endl;
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
                                Block block = Block(number, r, c, w, h, d);
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
        cout << to_string() << endl;
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

string Puzzle::to_string()
{
    stringstream ss;
    for(int i = 0; i < rows + 2; i++){ // inicio do tabuleiro
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
    for(int i = 0; i < rows + 2; i++){ // final do tabuleiro
        ss << "*";
    }
    return ss.str();
}

int main()
{
    Puzzle puzzle = Puzzle("/Users/joaosouza/Documents/Mestrado/Repositorios/prj_sbpuzzle/Codigo/tabuleiro01.data");
    cout << puzzle.get_rows() << "  " << puzzle.get_columns() << endl;
//    cout << puzzle.to_string() << endl;
//    stringstream ss;
//    string teste = "23 3      56";
//    ss << teste;
//    int a, b;
//    char c;
//    ss >> a >> b >> c;
//    cout << a << " " << b << " " << c << endl;
    return 0;
}
