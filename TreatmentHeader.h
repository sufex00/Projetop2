#ifndef TREATMENTHEADER_H
#define TREATMENTHEADER_H
#include<QString>
class TreatmentHeader
{
    /* * * * * * * * * * * * * * * * *
    *
    * MEMBROS DA CLASSE
    *
    * * * * * * * * * * * * * * * * */
    bool isCodificationBool; //Verifica se o programa deve codificar ou não
    bool isSuccessBool;      //Verifica se o programa codificou corretamente
    int argc;                //quantidade de argumentos
    char** argv;             //argumentos


public:

    /* * * * * * * * * * * * * * * * *
    *
    * CONSTRUTOR
    *
    * * * * * * * * * * * * * * * * */
    TreatmentHeader(int argc, char* argv[]);

    /* * * * * * * * * * * * * * * * *
    *
    * MÉTODOS DA TREATMENTHEADER
    *
    * * * * * * * * * * * * * * * * */

    //Verifica se e codificação.
    bool isCodification();

    //Retorna o nome do arquivo de entrada passado no argumentos da função main.
    char* getFileInput();

    //Retorna o nome do arquivo de saída passado no argumentos da função main.
    char *getFileOutput();

    //Retorna se a codificação ou descodificação teve sucesso ou não.
    bool isSuccess();
};

#endif // TREATMENTHEADER_H
