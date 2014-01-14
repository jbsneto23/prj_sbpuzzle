#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <queue>

#include "snapshot.h"

#ifndef SOLVER_H
#define SOLVER_H

/**
*
* Classe principal do programa, respons�vel por ler o arquivo de entrada e retornar a solu��o do quebra-cabe�a.
*
* @author Jo�o
* @author Ingrid
*/
class Solver
{
    public:

        /**
        *
        * Fun��o que recebe o Snapshot do estado inicial de um quebra-cabe�a e retorna o Snapshot da solu��o deste quebra-cabe�a ou NULL caso n�o tenha solu��o.
        *
        * @param shot Snapshot do estado inicial do quebra-cabe�a.
        * @param html_mode Flag que indica se o resultado das mens�gens deve ser em ASCII ou em HTML.
        * @return Snapshot da solu��o ou NULL caso o quebra-cabe�a n�o tenha solu��o.
        */
        static Snapshot* solve(Snapshot* shot, bool html_mode);

        /**
        *
        * Fun��o que recebe o arquivo de entrada de um quebra-cabe�a, soluciona-o e imprime na tela os resultados.
        *
        * @param puzzle_file Nome do arquivo que cont�m as informa��es do quebra-cabe�a.
        */
        static void solve_puzzle(string puzzle_file);

        /**
        *
        * Fun��o que recebe o arquivo de entrada de um quebra-cabe�a, soluciona-o e gera um documento HTML com os resultados.
        *
        * @param puzzle_file Nome do arquivo que cont�m as informa��es do quebra-cabe�a.
        */
        static void solve_puzzle_html(string puzzle_file);
    protected:
    private:
};

#endif // SOLVER_H
