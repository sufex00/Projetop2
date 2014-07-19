#ifndef ARVOREHUFFMAN_H
#define ARVOREHUFFMAN_H

/* * * * * * * * * * * * * * * * *
*
* BIBLIOTECAS
*
* * * * * * * * * * * * * * * * */

#include <vector>
#include "Cell.h"
#include<QDebug>
#include<stdio.h>
#include <iostream>
using namespace std;

class TreeHuffman
{
    /* * * * * * * * * * * * * * * * *
    *
    * MEMBROS DA CLASSE
    *
    * * * * * * * * * * * * * * * * */

    vector<cell> treeHuffman;
    cell ref;
    int size;
    QString huffmanRepresentationArray[256];

public:

    /* * * * * * * * * * * * * * * * *
    *
    * CONSTRUTOR
    *
    * * * * * * * * * * * * * * * * */

    TreeHuffman();

    /* * * * * * * * * * * * * * * * *
    *
    * MÉTODOS DO BIT VECTOR
    *
    * * * * * * * * * * * * * * * * */

    //Retorna o elemento da posição 'pos'
    cell treeHuffmanAT(int pos);

    //Muda coloca a ceula 'nill' na posição 'pos'
    void setTreeHuffman(int pos, cell nil);

    //Retorna o tamanho arvore
    int getSize();

    //Insere uma celula na arvore
    void insertion(cell newCell);

    //Ordena a arvore
    void bubbleHuffman();

    //Troca a posição entre os elementos 'prev' e 'next'
    void swap(cell &prev, cell &next);

    //Constroi a arvore de huffman
    void buildHuffman();

    //Retorna representação da arvore
    QString treeRepresetation(cell* node,QString R = "(", bool left=true);

    //Imprime a arvore na tela
    void printTree(cell* node , int level = 1);

    //Retorna a representação do 'Char'
    QString huffmanRepresentation(int Char);

    //Constroi a codificação de huffman
    void buildCodification(cell *node, long int level=1);

    //Calcula o lixo
    int trashCalculation(int* frequency);


};

#endif // ARVOREHUFFMAN_H
