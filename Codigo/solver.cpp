#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

#include "solver.h"

#include "block.h"
#include "puzzle.h"
#include "snapshot.h"
#include "hashtable.h"
#include "solver.h"

Snapshot* Solver::solve(Snapshot* snap, bool html_mode)
{
    int rows = snap->get_rows();
    int columns = snap->get_columns();
    HashTable table(rows, columns);
    table.insert(snap->get_key(), snap);
    queue<string> fila;
    fila.push(snap->get_key());
    while(!fila.empty()){
        string key = fila.front();
        fila.pop();
        Snapshot* ss = table.get(key);
        int** original_board = ss->get_board();

        // Copiando o conteudo
        int** board = new int*[rows];
        for(int i = 0; i < rows; i++){
            board[i] = new int[columns];
            copy(original_board[i], original_board[i] + columns, board[i]);
        }

        // Tentativas de movimentação
        for(int i = 0; i < ss->get_blocks().size(); i++){
            Block block = ss->get_blocks().at(i);
            int r = block.get_row();
            int c = block.get_column();
            int w = block.get_width();
            int h = block.get_height();

            // Tentar mover horizontalmente
            if(block.get_direction() == 'a' || block.get_direction() == 'h'){
                // movendo para Leste
                int qtd = 0;
                int initC = c;
                bool tryIt = true;
                int column = initC + w;
                while(tryIt && column < columns){
                    bool empty = true;
                    for(int k = r; k < r + h; k++){
                        if(board[k][column] != -1){
                            empty = false;
                        }
                    }
                    if(empty){
                        // deixando a antiga coluna Livre
                        for(int k = r; k < r + h; k++){
                            board[k][initC] = -1;
                        }
                        // ocupando a coluna seguinta
                        for(int k = r; k < r + h; k++){
                            board[k][column] = i;
                        }
                        qtd += 1;
                        Block novoBlock(block.get_number(), block.get_row(), block.get_column() + qtd, block.get_width(), block.get_height(), block.get_direction());
                        vector<Block> novoBlocks(ss->get_blocks());
                        novoBlocks.at(i) = novoBlock;
                        Snapshot* novoSs = new Snapshot(html_mode, rows, columns, board, novoBlocks, ss->get_moves(), i, "Leste", qtd);
                        if(novoSs->is_solution()){
                            return novoSs; // solução
                        } else {
                            if(table.insert(novoSs->get_key(), novoSs)){
                                fila.push(novoSs->get_key());
                            }
                            column += 1;
                            initC += 1;
                        }
                    } else {
                        tryIt = false;
                    }
                }

                // voltando o tabuleiro ao estado inicial
                if(qtd > 0){
                    for(int k = 0; k < rows; k++){
                        copy(original_board[k], original_board[k] + columns, board[k]);
                    }
                }

                // movendo para Oeste
                tryIt = true;
                qtd = 0;
                initC = c;
                column = initC - 1;
                while(tryIt && column >= 0){
                    bool empty = true;
                    for(int k = r; k < r + h; k++){
                        if(board[k][column] != -1){
                            empty = false;
                        }
                    }
                    if(empty){
                        // ocupando a coluna anterior
                        for(int k = r; k < r + h; k++){
                            board[k][column] = i;
                        }
                        // liberando a coluna anti
                        for(int k = r; k < r + h; k++){
                            board[k][initC + w - 1] = -1;
                        }
                        qtd += 1;
                        Block novoBlock(block.get_number(), block.get_row(), block.get_column() - qtd, block.get_width(), block.get_height(), block.get_direction());
                        vector<Block> novoBlocks(ss->get_blocks());
                        novoBlocks.at(i) = novoBlock;
                        Snapshot* novoSs = new Snapshot(html_mode, rows, columns, board, novoBlocks, ss->get_moves(), i, "Oeste", qtd);
                        if(table.insert(novoSs->get_key(), novoSs)){
                            fila.push(novoSs->get_key());
                        }
                        column -= 1;
                        initC -= 1;
                    } else {
                        tryIt = false;
                    }
                }

                // voltando o tabuleiro ao estado inicial
                if(qtd > 0){
                    for(int k = 0; k < rows; k++){
                        copy(original_board[k], original_board[k] + columns, board[k]);
                    }
                }

            }

            // Tentar mover verticalmente
            if(block.get_direction() == 'a' || block.get_direction() == 'v'){
                // movendo para Norte
                int qtd = 0;
                int initR = r;
                bool tryIt = true;
                int row = initR - 1;
                while(tryIt && row >= 0){
                    bool empty = true;
                    for(int k = c; k <  c + w; k++){
                        if(board[row][k] != -1){
                            empty = false;
                        }
                    }
                    if(empty){
                        // ocupando a linha de cima
                        for(int k = c; k <  c + w; k++){
                            board[row][k] = i;
                        }
                        // liberando a linha de cima
                        for(int k = c; k <  c + w; k++){
                            board[initR + h - 1][k] = -1;
                        }
                        qtd += 1;
                        Block novoBlock(block.get_number(), block.get_row() - qtd, block.get_column(), block.get_width(), block.get_height(), block.get_direction());
                        vector<Block> novoBlocks(ss->get_blocks());
                        novoBlocks.at(i) = novoBlock;
                        Snapshot* novoSs = new Snapshot(html_mode, rows, columns, board, novoBlocks, ss->get_moves(), i, "Norte", qtd);
                        if(table.insert(novoSs->get_key(), novoSs)){
                            fila.push(novoSs->get_key());
                        }
                        row -= 1;
                        initR -= 1;
                    } else {
                        tryIt = false;
                    }
                }

                // voltando o tabuleiro ao estado inicial
                if(qtd > 0){
                    for(int k = 0; k < rows; k++){
                        copy(original_board[k], original_board[k] + columns, board[k]);
                    }
                }

                // movendo para Sul
                qtd = 0;
                initR = r;
                row = initR + h;
                while(tryIt && row < rows){
                    bool empty = true;
                    for(int k = c; k <  c + w; k++){
                        if(board[row][k] != -1){
                            empty = false;
                        }
                    }
                    if(empty){
                        // liberando a linha de cima
                        for(int k = c; k <  c + w; k++){
                            board[initR][k] = -1;
                        }
                        // ocupando a linha de baixo
                        for(int k = c; k <  c + w; k++){
                            board[row][k] = i;
                        }
                        qtd += 1;
                        Block novoBlock(block.get_number(), block.get_row() + qtd, block.get_column(), block.get_width(), block.get_height(), block.get_direction());
                        vector<Block> novoBlocks(ss->get_blocks());
                        novoBlocks.at(i) = novoBlock;
                        Snapshot* novoSs = new Snapshot(html_mode, rows, columns, board, novoBlocks, ss->get_moves(), i, "Sul", qtd);
                        if(table.insert(novoSs->get_key(), novoSs)){
                            fila.push(novoSs->get_key());
                        }
                        row += 1;
                        initR += 1;
                    } else {
                        tryIt = false;
                    }
                }

                // voltando o tabuleiro ao estado inicial
                if(qtd > 0){
                    for(int k = 0; k < rows; k++){
                        copy(original_board[k], original_board[k] + columns, board[k]);
                    }
                }

            }
        }
    }
    return NULL;
}

void Solver::solve_puzzle(string puzzle_file)
{
    Puzzle puzzle(puzzle_file);
    Snapshot* snap = new Snapshot(puzzle.get_rows(), puzzle.get_columns(), puzzle.get_board(), puzzle.get_blocks());

    cout << "Quebra-Cabeca de Blocos Deslizantes" << endl;
    cout << snap->to_string() << endl;

    if(snap->is_solution()){
        cout << "A peca alvo ja esta na posicao alvo neste tabuleiro."<< endl;
    } else {
        Snapshot* solution = solve(snap, false);
        if(solution != NULL){
            cout << endl << "Solucao:" << endl;
            int i = 1;
            queue<string> jogadas(solution->get_moves());
            while(jogadas.size() > 0){
                string str = jogadas.front();
                jogadas.pop();
                cout << i << ". " << str << endl;
                i++;
            }
            cout << endl << solution->to_string() << endl;
            //cout << endl << solucao->to_html() << endl;
        } else {
            cout << "Este Quebra-Cabeca nao tem solucao!" << endl;
        }
    }
}

void Solver::solve_puzzle_html(string puzzle_file)
{
    Puzzle puzzle(puzzle_file);

    string html_file_name = "";
    int i = 0;
    while(i < puzzle_file.length() && puzzle_file[i] != '.'){
        html_file_name = html_file_name + puzzle_file[i];
        i++;
    }
    html_file_name = html_file_name + "_solucao.html";
    ofstream file(html_file_name.c_str());

    Snapshot* snap = new Snapshot(puzzle.get_rows(), puzzle.get_columns(), puzzle.get_board(), puzzle.get_blocks());

    file << "<html>" << endl << "<head><title>Solução do Quebra-Cabeça de Blocos Deslizantes</title><head>" << endl << "<body>" << endl;
    file << "<h2>Quebra-Cabeça de Blocos Deslizantes</h2>" << endl;
    file << snap->to_html() << endl;

    if(snap->is_solution()){
        file << "<h3>A peça alvo já está na posição alvo neste tabuleiro</h3>"<< endl;
    } else {
        Snapshot* solution = solve(snap, true);
        if(solution != NULL){
            file << "<h3>Solução: </h3>" << endl;
            int i = 1;
            queue<string> jogadas(solution->get_moves());
            file << "<ol>" << endl;
            while(jogadas.size() > 0){
                string str = jogadas.front();
                jogadas.pop();
                file << "<li>" << str << "</li>" << endl;
                i++;
            }
            file << "</ol> <br />" << endl;
        } else {
            file << "<h3>Este Quebra-Cabeça não tem solução!</h3>" << endl;
        }
    }
    file << "</body>" << endl << "</html>";
    file.close();
    cout << endl << "O arquivo '" << html_file_name << "' que contem a solucao para o Quebra-Cabeca foi gerado." << endl << endl;
}
