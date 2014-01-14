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
* Classe principal do programa, responsável por ler o arquivo de entrada e retornar a solução do quebra-cabeça.
*
* @author João
* @author Ingrid
*/
class Solver
{
    public:

        /**
        *
        * Função que recebe o Snapshot do estado inicial de um quebra-cabeça e retorna o Snapshot da solução deste quebra-cabeça ou NULL caso não tenha solução.
        *
        * @param shot Snapshot do estado inicial do quebra-cabeça.
        * @param html_mode Flag que indica se o resultado das menságens deve ser em ASCII ou em HTML.
        * @return Snapshot da solução ou NULL caso o quebra-cabeça não tenha solução.
        */
        static Snapshot* solve(Snapshot* shot, bool html_mode);

        /**
        *
        * Função que recebe o arquivo de entrada de um quebra-cabeça, soluciona-o e imprime na tela os resultados.
        *
        * @param puzzle_file Nome do arquivo que contém as informações do quebra-cabeça.
        */
        static void solve_puzzle(string puzzle_file);

        /**
        *
        * Função que recebe o arquivo de entrada de um quebra-cabeça, soluciona-o e gera um documento HTML com os resultados.
        *
        * @param puzzle_file Nome do arquivo que contém as informações do quebra-cabeça.
        */
        static void solve_puzzle_html(string puzzle_file);
    protected:
    private:
};

#endif // SOLVER_H
