#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

#include "sbpuzzle.h"

// ------------------------ block.cpp ------------------------
Block::Block()
{
    //ctor
}

Block::Block(int n, int r, int c, int w, int h, char d)
{
    set_number(n);
    set_row(r);
    set_column(c);
    set_width(w);
    set_height(h);
    set_direction(d);
}

Block::~Block()
{
    //dtor
}

int Block::get_number()
{
    return number;
}

void Block::set_number(int n)
{
    number = n;
}

int Block::get_row()
{
    return row;
}

void Block::set_row(int r)
{
    row = r;
}

int Block::get_column()
{
    return column;
}

void Block::set_column(int c)
{
    column = c;
}

int Block::get_width()
{
    return width;
}

void Block::set_width(int w)
{
    width = w;
}

int Block::get_height()
{
    return height;
}

void Block::set_height(int h)
{
    height = h;
}

char Block::get_direction()
{
    return direction;
}

void Block::set_direction(char d)
{
    direction = d;
}
// --------------------------------------------------------

// ----------------------------- puzzle.cpp -----------------------------
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
// --------------------------------------------------------------------

// --------------------------- snapshot.cpp ---------------------------
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
                ss << "<td height=\"50\" width=\"50\"></td>" << endl;
            } else if(board[i][j] == 0){
                if(!signals[0]){
                    ss << "<td align=\"center\" height=\"50\" width=\"50\"";
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
                    ss << "<td align=\"center\" height=\"50\" width=\"50\"";
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
// ------------------------------------------------------------------

// -------------------------- hashtable.h --------------------------
HashTable::HashTable(int r, int c)
{
    rows = r;
    columns = c;
    length = rows * columns;
    table = new Node*[length];
    for(int i = 0; i < length; i++){
        table[i] = NULL;
    }
    s = 0;
}

HashTable::~HashTable()
{
    for(int i = 0; i < length; i++){
        Node* pt = table[i];
        while(pt != NULL){
            Node* temp = pt;
            pt = pt->next;
            delete temp;
        }
    }
    delete[] table;
}

int HashTable::hash(string str)
{
    int soma = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    while(k < str.size()){
        if(str[k] != '.' && str[k] != '*'){
            string num = "";
            num = num + str[k];
            int n = atoi(num.c_str());
            soma = soma + ((i + 1) * (j + 1) * n);
        } else {
            if(str[k] == '.'){
                soma = soma + ((i + 1) * (j + 1) * (-1));
            } else {
                string num = "";
                k = k + 1;
                while(str[k] != '*'){
                    num = num + str[k];
                    k++;
                }
                int n = atoi(num.c_str());
                soma = soma + ((i + 1) * (j + 1) * n);
            }
        }
        k = k + 1;
        if(j < (columns - 1)){
            j++;
        } else {
            j = 0;
            i++;
        }
    }
    return abs(soma) % length;
}

bool HashTable::insert(string key, Snapshot* shot)
{
    int index = hash(key);
    Node* pt = table[index];
    Node* ante = NULL;
    while(pt != NULL){
        if(strcmp(key.c_str(), pt->shot->get_key().substr(0, key.size()).c_str()) == 0){
            return false;
        } else {
            ante = pt;
            pt = pt->next;
        }
    }
    Node* node = new Node;
    node->key = key;
    node->shot = shot;
    node->next = NULL;
    if(ante != NULL){
        ante->next = node;
    } else {
        table[index] = node;
    }
    s++;
    return true;
}

Snapshot* HashTable::get(string key)
{
    int index = hash(key);
    Node* pt = table[index];
    while(pt != NULL){
        if(strcmp(key.c_str(), pt->shot->get_key().substr(0, key.size()).c_str()) == 0){
            return pt->shot;
        } else {
            pt = pt->next;
        }
    }
    return NULL;
}

int HashTable::size()
{
    return s;
}

void HashTable::print_content()
{
    for(int i = 0; i < length; i++){
        if(table[i] != NULL){
            cout << "Indice: " << i << endl;
            Node* pt = table[i];
            while(pt != NULL){
                cout << pt->shot->to_string() << endl;
                pt = pt->next;
            }
            cout << "-----------" << endl;
        }
    }
}
// -----------------------------------------------------------------

Snapshot* sbpuzzle::solve(Snapshot* snap, bool html_mode)
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
                bool tentar = true;
                int coluna = initC + w;
                while(tentar && coluna < columns){
                    bool livre = true;
                    for(int k = r; k < r + h; k++){
                        if(board[k][coluna] != -1){
                            livre = false;
                        }
                    }
                    if(livre){
                        // deixando a antiga coluna livre
                        for(int k = r; k < r + h; k++){
                            board[k][initC] = -1;
                        }
                        // ocupando a coluna seguinta
                        for(int k = r; k < r + h; k++){
                            board[k][coluna] = i;
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
                            coluna += 1;
                            initC += 1;
                        }
                    } else {
                        tentar = false;
                    }
                }

                // voltando o tabuleiro ao estado inicial
                if(qtd > 0){
                    for(int k = 0; k < rows; k++){
                        copy(original_board[k], original_board[k] + columns, board[k]);
                    }
                }

                // movendo para Oeste
                tentar = true;
                qtd = 0;
                initC = c;
                coluna = initC - 1;
                while(tentar && coluna >= 0){
                    bool livre = true;
                    for(int k = r; k < r + h; k++){
                        if(board[k][coluna] != -1){
                            livre = false;
                        }
                    }
                    if(livre){
                        // ocupando a coluna anterior
                        for(int k = r; k < r + h; k++){
                            board[k][coluna] = i;
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
                        coluna -= 1;
                        initC -= 1;
                    } else {
                        tentar = false;
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
                bool tentar = true;
                int linha = initR - 1;
                while(tentar && linha >= 0){
                    bool livre = true;
                    for(int k = c; k <  c + w; k++){
                        if(board[linha][k] != -1){
                            livre = false;
                        }
                    }
                    if(livre){
                        // ocupando a linha de cima
                        for(int k = c; k <  c + w; k++){
                            board[linha][k] = i;
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
                        linha -= 1;
                        initR -= 1;
                    } else {
                        tentar = false;
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
                linha = initR + h;
                while(tentar && linha < rows){
                    bool livre = true;
                    for(int k = c; k <  c + w; k++){
                        if(board[linha][k] != -1){
                            livre = false;
                        }
                    }
                    if(livre){
                        // liberando a linha de cima
                        for(int k = c; k <  c + w; k++){
                            board[initR][k] = -1;
                        }
                        // ocupando a linha de baixo
                        for(int k = c; k <  c + w; k++){
                            board[linha][k] = i;
                        }
                        qtd += 1;
                        Block novoBlock(block.get_number(), block.get_row() + qtd, block.get_column(), block.get_width(), block.get_height(), block.get_direction());
                        vector<Block> novoBlocks(ss->get_blocks());
                        novoBlocks.at(i) = novoBlock;
                        Snapshot* novoSs = new Snapshot(html_mode, rows, columns, board, novoBlocks, ss->get_moves(), i, "Sul", qtd);
                        if(table.insert(novoSs->get_key(), novoSs)){
                            fila.push(novoSs->get_key());
                        }
                        linha += 1;
                        initR += 1;
                    } else {
                        tentar = false;
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

void sbpuzzle::solve_puzzle(string puzzle_file)
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

void sbpuzzle::solve_puzzle_html(string puzzle_file)
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

int main(int argc, char *argv[])
{
    if(argc > 1){
        string arg1 = argv[1];
        if(arg1.compare("-h") == 0){
            if(argc > 2){
                sbpuzzle::solve_puzzle_html(argv[2]);
            } else {
                cerr << "sbpuzzle: nenhum arquivo de entrada foi passado como argumento." << endl;
            }
        } else {
            sbpuzzle::solve_puzzle(arg1);
        }
    } else {
        cerr << "sbpuzzle: nenhum arquivo de entrada foi passado como argumento." << endl;
    }
    return 0;
}
