#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <list>

using namespace std;

#include "sbpuzzle.h"

// ------------------------ block.h ------------------------
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

// ----------------------------- puzzle.h -----------------------------
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
//        // lendo a peça alvo
//        bool alvo = false;
//        while(!file.eof() && !alvo){
//            // limpando ss
//            ss.str("");
//            ss.clear();
//            // lendo a próxima linha
//            getline(file, buffer);
//            ss << buffer;
//            ss >> r >> c >> w >> h >> d;
//            if(r < 1 || r > rows || c < 1 || c > columns){
//                cerr << "sbpuzzle: o bloco representado pela linha '" << buffer << "' esta fora do tabuleiro, portanto sera descartado." << endl;
//            } else {
//                if(w < 1 || w > rows || h < 1 || h > columns){
//                    cerr << "sbpuzzle: o bloco representado pela linha '" << buffer << "' esta com dimensoes negativas ou que ultrapassam o tabuleiro, portanto sera descartado." << endl;
//                } else {
//                    if((r - 1 + h) > rows || (c - 1 + w) > columns){
//                        cout << (r - 1 + h) << "   " << (c - 1 + w) << endl;
//                        cerr << "sbpuzzle: o bloco representado pela linha '" << buffer << "' esta com dimensoes que ultrapassam o tabuleiro, portanto sera descartado." << endl;
//                    } else {
//                        if(d != 'a' && d != 'h' && d != 'v'){
//                            cerr << "sbpuzzle: o bloco representado pela linha '" << buffer << "' nao possui uma direcao de deslocamento valida, portanto sera descartado." << endl;
//                        } else {
//                            alvo = true;
//                            for(int i = r - 1; i < r - 1 + h; i++){
//                                for(int j = c - 1; j < c - 1 + w; j++){
//                                    if(board[i][j] != -1){
//                                        alvo = false;
//                                    }
//                                }
//                            }
//                            if(alvo){
//                                Block blockAlvo = Block(0, r - 1, c - 1, w, h, d);
//                                blocks.push_back(blockAlvo);
//                                for(int i = r - 1; i < r - 1 + h; i++){
//                                    for(int j = c - 1; j < c - 1 + w; j++){
//                                        board[i][j] = 0;
//                                    }
//                                }
//                            } else {
//                                cerr << "sbpuzzle: o bloco representado pela linha '" << buffer << "' esta sobrepondo outro bloco, portanto sera descartado." << endl;
//                            }
//                        }
//                    }
//                }
//            }
//        }
//        if(!alvo){
//            cerr << "sbpuzzle: nenhum bloco foi considerado valido." << endl;
//            exit(-1);
//        }
        // lendo os blocos restantes
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

string Puzzle::to_string()
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

string Puzzle::rowMajor()
{
    stringstream ss;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            if(board[i][j] > 9){
                ss << "*" << board[i][j] << "*";
            } else if(board[i][j] < 0){
                ss << ".";
            } else {
                ss << board[i][j];
            }
        }
    }
    return ss.str();
}

int Puzzle::hash(string str)
{
    int* column = new int[rows];
    int r = 0;
    memset(column, 0, sizeof(int) * rows);
    int i = 0;
    int j = 0;
    int k = 0;
    while(k < str.size()){
        if(str[k] != '.' && str[k] != '*'){
            string num = "";
            num = num + str[k];
            int n = atoi(num.c_str());
            column[i] = column[i] + ((i + 1) * (j + 1) * n);
        } else {
            if(str[k] == '.'){
                column[i] = column[i] + ((i + 1) * (j + 1) * (-1));
            } else {
                string num = "";
                k = k + 1;
                while(str[k] != '*'){
                    num = num + str[k];
                    k++;
                }
                int n = atoi(num.c_str());
                column[i] = column[i] + ((i + 1) * (j + 1) * n);
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
    for(int i = 0; i < rows; i++){
        cout << i << " - " << column[i] << endl;
        r = r + column[i];
    }
    delete[] column;
    return abs(r);
}

int Puzzle::hash()
{
    int* column = new int[rows];
    int r = 0;
    memset(column, 0, sizeof(int) * rows);
    for(int j = 0; j < columns; j++){
        for(int i = 0; i < rows; i++){
            column[i] = column[i] + ((i + 1) * (j + 1) * board[i][j]);
        }
    }
    for(int i = 0; i < rows; i++){
        cout << i << " - " << column[i] << endl;
        r = r + column[i];
    }
    delete[] column;
    return abs(r);
}

// --------------------------------------------------------------------

// --------------------------- snapshot.h ---------------------------
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
    int* column = new int[rows];
    int r = 0;
    memset(column, 0, sizeof(int) * rows);
    int i = 0;
    int j = 0;
    int k = 0;
    while(k < str.size()){
        if(str[k] != '.' && str[k] != '*'){
            string num = "";
            num = num + str[k];
            int n = atoi(num.c_str());
            column[i] = column[i] + ((i + 1) * (j + 1) * n);
        } else {
            if(str[k] == '.'){
                column[i] = column[i] + ((i + 1) * (j + 1) * (-1));
            } else {
                string num = "";
                k = k + 1;
                while(str[k] != '*'){
                    num = num + str[k];
                    k++;
                }
                int n = atoi(num.c_str());
                column[i] = column[i] + ((i + 1) * (j + 1) * n);
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
    for(int i = 0; i < rows; i++){
        r = r + column[i];
    }
    delete[] column;
    return abs(r) % length;
}

bool HashTable::insert(string key, Snapshot* shot)
{
    int index = hash(key);
    Node* pt = table[index];
    Node* ante = NULL;
    while(pt != NULL){
        if(strcmp(key.c_str(), pt->key.c_str()) == 0){
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
        if(strcmp(key.c_str(), pt->key.c_str()) == 0){
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
// -----------------------------------------------------------------

sbpuzzle::sbpuzzle()
{
    //ctor
}

sbpuzzle::~sbpuzzle()
{
    //dtor
}

int main(int argc, char *argv[])
{
    if(argc > 1){
        string file_name = argv[1];
        Puzzle puzzle = Puzzle(file_name);
        cout << "Quebra-Cabeca de Blocos Deslizantes" << endl;
        cout << puzzle.to_string() << endl;
        string rm = puzzle.rowMajor();
        cout << "Row Major:" << rm << endl;
        cout << endl << "Hash RM: " << puzzle.hash(rm) << endl;
        cout << endl << "Hash: " << puzzle.hash() << endl;
        Snapshot* snap = new Snapshot(puzzle.get_rows(), puzzle.get_columns(), puzzle.get_board(), puzzle.get_blocks());
        cout << "Key = " << snap->get_key() << endl;
        cout << snap->to_string() << endl;
        cout << "Solucao: " << snap->is_solution() << endl;
        cout << "--------- Testando a tabela hash ---------" << endl;
        HashTable ht(puzzle.get_rows(), puzzle.get_columns());
        cout << "Tamanho = " << ht.size() << endl;
        for(int i = 1; i < 5; i++){
            cout << "Tentativa " << i << endl;
            string st = ht.insert(snap->get_key(), snap) ? "sim" : "nao";
            cout << "Inseriu: " << st << endl;
            cout << "Tamanho: " << ht.size() << endl;
        }
        cout << endl << "Tamanho = " << ht.size() << endl;
        Snapshot* s = ht.get(snap->get_key());
        if(s != NULL){
            cout << snap->get_key().c_str() << endl;
            cout << s->get_key() << endl;
            if(strcmp(s->get_key().c_str(), snap->get_key().c_str()) == 0){
                cout << "Deu certo!" << endl;
            } else {
                cout << "Deu ERRADO!" << endl;
            }
        }
    } else {
        cerr << "sbpuzzle: nenhum arquivo de entrada foi passado como argumento," << endl;
    }
    return 0;
}
