#ifndef BLOCK_H
#define BLOCK_H

/**
*
* A classe Block representa um bloco em um tabuleiro.
*
* @author João
* @author Ingrid
*/
class Block
{
    public:
        /**
        *
        * Construtor que configura um objeto do tipo Block.
        *
        * @param n Número (0 a 127) que será inserido no bloco.
        * @param r Linha em que o bloco está posicionado.
        * @param c Coluna em que o bloco está posicionado.
        * @param w Largura do bloco.
        * @param h Altura do bloco.
        * @param d Direção do bloco.
        */
        Block(int n, int r, int c, int w, int h, char d);

        /**
        *
        * Destrutor que libera a memória alocada pela classe Block.
        *
        */
        virtual ~Block();

        /**
        *
        * Função que recupera o número de um bloco.
        *
        * @return o número contido no bloco.
        */
        int get_number();

        /**
        *
        * Função que grava um número no bloco.
        *
        * @param n É o número a ser gravado no bloco.
        */
        void set_number(int n);

        /**
        *
        * Função que recupera a linha de um bloco
        *
        * @return a linha.
        */
        int get_row();

        /**
        *
        * Função que grava uma linha.
        *
        * @param r É a linha a ser gravada.
        */
        void set_row(int r);

        /**
        *
        * Função que recupera a coluna de um bloco.
        *
        * @return a coluna
        */
        int get_column();

        /**
        *
        * Função que grava uma coluna.
        *
        * @param c É a coluna a ser gravada.
        */
        void set_column(int c);

        /**
        *
        * Função que recupera a largura de um bloco.
        *
        * @return a largura do bloco.
        */
        int get_width();

        /**
        *
        * Função que grava a largura de um bloco.
        *
        * @param w É a largura a ser gravada.
        */
        void set_width(int w);

        /**
        *
        * Função que recupera a altura de um bloco.
        *
        * @return a altura do bloco.
        */
        int get_height();

        /**
        *
        * Função que grava a altura de um bloco.
        *
        * @param h É a altura a ser gravada.
        */
        void set_height(int h);

        /**
        *
        * Função que recupera a direção de um bloco.
        *
        * @return a direção do bloco.
        */
        char get_direction();

        /**
        *
        * Função que grava a direção de um bloco.
        *
        * @param d É a direção a ser gravada.
        */
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
