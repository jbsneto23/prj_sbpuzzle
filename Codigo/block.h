#ifndef BLOCK_H
#define BLOCK_H

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

#endif // BLOCK_H
