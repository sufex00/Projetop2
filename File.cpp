#include"File.h"
#include<string>
#include<QDebug>

#define MAX_SIZE_BUCKED 5;
File::File()
{

}

File::File(char FileName[])
{
    for(int i=0; i<255; i++)
    {
        frequency[i]=0;
    }
    this->fileName=QString(FileName);
    inputFile.open(FileName,std::ios::binary);
    if(inputFile.is_open())
    {
        inputFile.seekg(0,inputFile.end);
        size=inputFile.tellg();
        inputFile.seekg(0, inputFile.beg);
    }
    this->position=0;
    while(!this->isEnd())
    {
        this->grabBucked();
    }
}
void File::grabBucked()
{
    int read;
    inputFile.seekg(this->position);
    if(size-position>5)
    {
        this->position+=MAX_SIZE_BUCKED;
        read=MAX_SIZE_BUCKED;
        this->isEndBool=false;
    }
    else
    {
        read=size-position;
        this->isEndBool=true;
    }
    fileCount(read);
}

int File::readFile(int initPosition)
{
    QString file;
    char buff;
    inputFile.seekg(initPosition);
    inputFile.get(buff);
    if(buff<0)file.append(QString().setNum(buff+256));
    else
        file=(QString(QString().setNum((int)buff)));
    return file.toInt();
}
QString File::readFile(int initPosition, int sizeRead)
{
    QString file;
    for(int i=initPosition;i<initPosition+sizeRead;i++)
    {
        file.append(readFile(i));
    }
    return file;
}
int File::fileSize()
{
    return this->size;
}
void File::fileCount(int size)
{
    char file[size];
    inputFile.read(file,size);
    for(int i=0; i<size; i++)
    {
        frequency[int(file[i])+128]++;
    }
}
int File::bitFrequency(int Bit)
{
    return frequency[Bit];
}
char File::bitToChar(int Bit)
{
    return char(Bit-128);
}
int File::charToBit(char Char)
{
    return int(Char+128);
}

void File::setFileName(QString fileName)
{
    this->fileName=fileName;
}

QString File::getFileName()
{
    return this->fileName.toLocal8Bit().data();
}
void File::clearPosition()
{
    this->position=0;
    this->isEndBool=false;
}

QString File::getfile()
{
        int read;
        inputFile.seekg(this->position);
        if(size-position>5)
        {
            this->position+=MAX_SIZE_BUCKED;
            read=MAX_SIZE_BUCKED;
            this->isEndBool=false;
        }
        else
        {
            read=size-position;
            this->isEndBool=true;
        }
        QString file;
        char buff;
        for(int i=0;i<read;i++)
        {
            inputFile.get(buff);
            if(buff<0)
                file.append(buff+256);
            else
                file.append(buff);
        }
        return file;
}
int File::getBucked()
{
    return MAX_SIZE_BUCKED;
}

bool File::isEnd()
{
return this->isEndBool;
}
int* File::getFrequency()
{
    return this->frequency;
}
void File::setPosition(int position)
{
    this->position=position;
    if(this->position==this->size)
    {
        this->isEndBool=true;
    }
    else
        this->isEndBool=false;
}
