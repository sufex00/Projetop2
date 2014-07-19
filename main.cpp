/* * * * * * * * * * * * * * * * *
*
* BIBLIOTECAS
*
* * * * * * * * * * * * * * * * */

#include "File.cpp"
#include<QDebug>
#include<QString>
#include"Cell.h"
#include "TreeHuffman.h"
#include<stdio.h>
#include <iostream>
#include <unistd.h>
#include<BitVector.h>
#include"huffdecoditication.h"
#include"TreatmentHeader.h"

using namespace std;


int main(int argc, char* argv[])
{
    TreeHuffman treeHuffman = TreeHuffman();
    TreatmentHeader treatmentHeader = TreatmentHeader(argc,argv);
    File* fileObjectInput =new File(treatmentHeader.getFileInput());
    std::ofstream fileObjectOutput;
    BitVector bitVector=BitVector();
    huffdecoditication huffDecodification=huffdecoditication(treatmentHeader.getFileInput());
    double oldPercentage=0;
    int sizeTemp=0;
    if(treatmentHeader.isCodification())
    {
        //Crio a arvore de huffman
        for(int i=0; i<256; i++)
        {
            cell new_cell=cell(fileObjectInput->bitToChar(i),fileObjectInput->bitFrequency(i));
            treeHuffman.insertion(new_cell);
        }
        treeHuffman.buildHuffman();
        cell rootTreeHuffman=treeHuffman.treeHuffmanAT(1);
        QString tree=treeHuffman.treeRepresetation(&rootTreeHuffman).remove(0,1);
        tree.remove(tree.size()-1,1);
        treeHuffman.buildCodification(&rootTreeHuffman);

        //Coloco no bit vector os 3 primeiros bytes do cabeçalho
        bitVector.setbit(QString().setNum(treeHuffman.trashCalculation(fileObjectInput->getFrequency()),2),3);
        bitVector.setbit(QString().setNum(tree.size(),2),13);
        bitVector.setbit(QString().setNum(fileObjectInput->getFileName().size(),2),8);

        //abro o arquivo codificado
        fileObjectOutput.open(treatmentHeader.getFileOutput(),std::ios::binary);

        //Escrevo os 3 primeiros bytes do cabeçalho
        for(int i=0; i<bitVector.getQbitarray().size()-1;i++)
        {
            fileObjectOutput<<bitVector.getQbitarray().at(i).toLatin1();
        }
        //Escrevo o nome do arquivo original
        fileObjectOutput<<fileObjectInput->getFileName().toStdString();
        for(int i=0; i<tree.size();i++)
        {

            fileObjectOutput<<tree.at(i).toLatin1();
        }

        //Limpa o bitVector
        bitVector.clearBitVector();

        //Zero o curso do arquivo
        fileObjectInput->clearPosition();

        //Pega uma parte do arquivo
        QString bucked = fileObjectInput->getfile();

        //conta quantos bytes foram codifcados
        sizeTemp+=bucked.size();
        fileObjectInput->setPosition(0);
        //escreve a a codificação no bit vector
        while(!fileObjectInput->isEnd())
        {
            //Pega uma parte do arquivo
            QString bucked = fileObjectInput->getfile();

            //conta quantos bytes foram codifcados
            sizeTemp+=bucked.size();

            //escreve a a codificação no bit vector
            for(int i=0;i<bucked.size();i++)
            {
                bitVector.setbit(treeHuffman.huffmanRepresentation(fileObjectInput->charToBit(bucked.at(i).toLatin1())));

            }

            //coloca a codificação no arquivo codificado
            for(int y=0; y<bitVector.getQbitarray(false).size();y++)
            {
                fileObjectOutput<<bitVector.getQbitarray(false).at(y).toLatin1();
            }
            //rearanja o bit vector
            bitVector.resize();
            if(int(double(sizeTemp)/fileObjectInput->fileSize()*100)>int(oldPercentage))
                qDebug()<<int(oldPercentage)<<"%";
            oldPercentage=double(sizeTemp)/fileObjectInput->fileSize()*100;

        }
    //verifica se o lixo foi colocado
    if(treeHuffman.trashCalculation(fileObjectInput->getFrequency())!=0)
        fileObjectOutput<<bitVector.getQbitarray().at(0).toLatin1();
    qDebug()<<"100 %";
}
//****-------------------------------------------------------------------------------****
/* * * * * * * * * * * * * * * * *
*
* DECODIFICAÇÃO
*
* * * * * * * * * * * * * * * * */
//****-------------------------------------------------------------------------------****

if(!treatmentHeader.isCodification())
{
    //crio o arquivo original
    std::ofstream fileObjectOutputDecotification;


    //verifico o caminho do arquivo
    if(QString(treatmentHeader.getFileOutput()).isEmpty())
       fileObjectOutputDecotification.open(huffDecodification.getFileName(),std::ios::binary);
    else
        fileObjectOutputDecotification.open(QString(treatmentHeader.getFileOutput()).append(huffDecodification.getFileName()).toLocal8Bit().data(),std::ios::binary);

    sizeTemp=0;

    //limpa o bit vector
    bitVector.clearBitVector();
    QString bucked;

    //gera a arvore aparti da representação
    cell rootTreeHuffman=*huffDecodification.generation(huffDecodification.TreeRepresetation());
    cell* node=&rootTreeHuffman;
    while(!huffDecodification.IsEnd())
    {
        //Pega uma parte do arquivo codificado
        bucked= huffDecodification.grabBucked();

        //conta quantos bytes foram decodificados
        sizeTemp+=bucked.size();
        if(int(double(sizeTemp)/huffDecodification.getSize()*100)>int(oldPercentage))
           qDebug()<<int(oldPercentage)<<"%";
        oldPercentage=double(sizeTemp)/huffDecodification.getSize()*100;

        //decodifica a parte que foi pegada do arquivo, e a coloca no bit vector
        for(int y=0; y<bucked.size();y++)
        {
            int chartTobit;
            if(bucked.at(y).toLatin1()<0)
                chartTobit=bucked.at(y).toLatin1()+256;
            else
                chartTobit=bucked.at(y).toLatin1();
            bitVector.setbit(QString().setNum(chartTobit,2),8);
        }

        //percorre a arvore decodificando os bytes
        for(int y=0; y<bitVector.getSize();y++)
        {

            //verfica se o arquivo acabou, e se ja chegamos no lixo
            if(huffDecodification.getTrash()+y==bitVector.getSize() && huffDecodification.IsEnd())
            {
                break;
            }

            if(bitVector.bitVectorAt(y)==0)
            {
                node=node->left;
                if(node->leaf)
                {
                    fileObjectOutputDecotification<<node->getElement();
                    node=&rootTreeHuffman;
                }
            }
            if(bitVector.bitVectorAt(y)==1)
            {
                node=node->right;
                if(node->leaf)
                {
                    fileObjectOutputDecotification<<node->getElement();
                    node=&rootTreeHuffman;
                }
            }
        }
        //limpa o bit vector
        bitVector.clearBitVector();
    }
    qDebug()<<"100%";
}
}
