#ifndef BLOCK_H
#define BLOCK_H

/**
*
* A classe Block representa um bloco em um tabuleiro.
*
* @author Jo�o
* @author Ingrid
*/
class Block
{
    public:
        /**
        *
        * Construtor que configura um objeto do tipo Block.
        *
        * @param n N�mero (0 a 127) que ser� inserido no bloco.
        * @param r Linha em que o bloco est� posicionado.
        * @param c Coluna em que o bloco est� posicionado.
        * @param w Largura do bloco.
        * @param h Altura do bloco.
        * @param d Dire��o do bloco.
        */
        Block(int n, int r, int c, int w, int h, char d);

        /**
        *
        * Destrutor que libera a mem�ria alocada pela classe Block.
        *
        */
        virtual ~Block();

        /**
        *
        * Fun��o que recupera o n�mero de um bloco.
        *
        * @return o n�mero contido no bloco.
        */
        int get_number();

        /**
        *
        * Fun��o que grava um n�mero no bloco.
        *
        * @param n � o n�mero a ser gravado no bloco.
        */
        void set_number(int n);

        /**
        *
        * Fun��o que recupera a linha de um bloco
        *
        * @return a linha.
        */
        int get_row();

        /**
        *
        * Fun��o que grava uma linha.
        *
        * @param r � a linha a ser gravada.
        */
        void set_row(int r);

        /**
        *
        * Fun��o que recupera a coluna de um bloco.
        *
        * @return a coluna
        */
        int get_column();

        /**
        *
        * Fun��o que grava uma coluna.
        *
        * @param c � a coluna a ser gravada.
        */
        void set_column(int c);

        /**
        *
        * Fun��o que recupera a largura de um bloco.
        *
        * @return a largura do bloco.
        */
        int get_width();

        /**
        *
        * Fun��o que grava a largura de um bloco.
        *
        * @param w � a largura a ser gravada.
        */
        void set_width(int w);

        /**
        *
        * Fun��o que recupera a altura de um bloco.
        *
        * @return a altura do bloco.
        */
        int get_height();

        /**
        *
        * Fun��o que grava a altura de um bloco.
        *
        * @param h � a altura a ser gravada.
        */
        void set_height(int h);

        /**
        *
        * Fun��o que recupera a dire��o de um bloco.
        *
        * @return a dire��o do bloco.
        */
        char get_direction();

        /**
        *
        * Fun��o que grava a dire��o de um bloco.
        *
        * @param d � a dire��o a ser gravada.
        */
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
#endif // BLOCK_H
