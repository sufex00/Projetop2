#ifndef BITVECTOR_H
#define BITVECTOR_H

/* * * * * * * * * * * * * * * * *
*
* BIBLIOTECAS
*
* * * * * * * * * * * * * * * * */

#include <QBitArray>
#include<QString>

class BitVector
{

    /* * * * * * * * * * * * * * * * *
    *
    * MEMBROS DA CLASSE
    *
    * * * * * * * * * * * * * * * * */

    QBitArray biTvector; //BitVector
    int size; //Tamanho do BitVector
public:

    /* * * * * * * * * * * * * * * * *
    *
    * CONSTRUTOR
    *
    * * * * * * * * * * * * * * * * */

    BitVector();

    /* * * * * * * * * * * * * * * * *
    *
    * MÉTODOS DO BIT VECTOR
    *
    * * * * * * * * * * * * * * * * */

    //Muda o para o valor 'value' na posição 'pos' do BitVector.
    void setbit(int pos, int value);

    //Muda os valores para a sequencias de valores 'value' partindo da posição 'pos' do BitVector.
    void setbit(QString value, int sizemax=0, int pos=-1);

    //Retorna o elemento da posição 'pos'.
    int bitVectorAt(int pos);

    //Retorna uma QString contendo bytes com o valor do BitVector,
    //onde o bool de entrada define se o retorno possui lixo.
    QString getQbitarray(bool WithTrash=true);

    //Limpa o BitVetor
    void clearBitVector();

    //Retorna o tamanho do BitVector
    int getSize();

    //Modifica o tamanho do bit vector
    void setSize(int size);

    //Retimenciona o BitVector, ou seja, apaga os valores em grupos de 8 em 8.
    void resize();

};

#endif // BITVECTOR_H
