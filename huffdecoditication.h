#ifndef HUFFDECODITICATION_H
#define HUFFDECODITICATION_H

/* * * * * * * * * * * * * * * * *
*
* BIBLIOTECAS
*
* * * * * * * * * * * * * * * * */

#include"BitVector.h"
#include"Cell.h"
#include<QDebug>
#include<QString>

class huffdecoditication
{

    /* * * * * * * * * * * * * * * * *
    *
    * MEMBROS DA CLASSE
    *
    * * * * * * * * * * * * * * * * */

    int sizeName;              //Tamanho do nome original do arquivo
    int sizeTree;              //Tamanho da representação da arvore
    int trash;                 //Tamanho do lixo
    int sizeFile;              //Tamanho
    QString fileName;          //Nome original do arquivo
    QString treeRepresetation; //Representação da arvore
    int position;              //Posição atual do curso
    char *FileObjectInput;     //Nome do arquivo
    bool isEndBool;            //Verificador se o arquivo acabou

public:

    /* * * * * * * * * * * * * * * * *
    *
    * CONSTRUTOR
    *
    * * * * * * * * * * * * * * * * */

    huffdecoditication(char* FileInput);

    /* * * * * * * * * * * * * * * * *
    *
    * MÉTODOS DO HUFFDECODIFICATION
    *
    * * * * * * * * * * * * * * * * */

    //Retorna a representação da arvore
    QString TreeRepresetation();

    //Retorna se houve fim de arquivo
    bool IsEnd();

    //Retorna um pedaço do arquivo original
    QString grabBucked();

    //Retorna o tamanho do arquivo
    int getSize();

    //Retorna se a arvore possue o elemento node com a codificação 'Huffman Codification'
    bool isElement(cell* node,QString HuffmanCodification);

    //Retorna o elemento da arvore que possue a codificação Huffman Codification
    char getElementTree(cell* node,QString HuffmanCodification);

    //Retorna o valor do lixo
    int getTrash();

    //Gera a arvore, recebendo a representação 'Tree'
    cell* generation(QString Tree);

    //Retorna o filho da direita da arvore 'TreeHuffman'
    QString TreeHuffmanDecodificationRight(QString TreeHuffman);

    //Retorna o filho da esquerda da arvore 'TreeHuffman'
    QString TreeHuffmanDecodificationLeft(QString TreeHuffman);

    //Retorna o nome original do arquivo
    char* getFileName();
};

#endif // HUFFDECODITICATION_H
