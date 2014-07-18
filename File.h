#include<fstream>
#include"Cell.h"
#include<QString>
class File
{
    /* * * * * * * * * * * * * * * * *
    *
    * MEMBROS DA CLASSE
    *
    * * * * * * * * * * * * * * * * */
    std::ifstream inputFile;
    int size;
    int frequency[256];
    char* file;
    QString fileName;
    int position;
    bool isEndBool;

public:

    /* * * * * * * * * * * * * * * * *
    *
    * CONSTRUTOR
    *
    * * * * * * * * * * * * * * * * */
    File(char file[]);
    File();

    /* * * * * * * * * * * * * * * * *
    *
    * MÉTODOS DA FILE
    *
    * * * * * * * * * * * * * * * * */

    //Retorna tamanho do arquivo
    int fileSize();

    //Conta a frenquência de elemento
    void fileCount(int size);

    //Retorna a frequência do Bit
    int bitFrequency(int Bit);

    //Retorna a transformação de Bit para o caractere representado
    char bitToChar(int Bit);

    //Retorna a transformação do Caractere para o Bit representado
    int charToBit(char Char);

    //Modifica o fileName
    void setFileName(QString fileName);

    //Retorna o fileName em char
    QString getFileName();

    //Retorna o file
    QString getfile();

    //Retorna o valor da posição 'initPosition' do arquivo
    int readFile(int initPosition);

    ///Retorna o valor das 'sizeRead' primeiras posições do arquivo  aparti de 'initPosition'
    QString readFile(int initPosition,int sizeRead);

    //Seleciona uma parte do arquivo
    void grabBucked();

    //Verifica se é o fim do arquivo
    bool isEnd();

    //Reseta da posição do ponteiro do arquivo
    void clearPosition();

    //Retorna o tamanho do pedaço a ser pego no arquivo
    int getBucked();

    //Retorna um array com as frequencias dos caracteres
    int* getFrequency();

    //Muda a posição do curso
    void setPosition(int position);
};
