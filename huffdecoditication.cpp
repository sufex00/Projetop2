#include "huffdecoditication.h"
#include"File.h"
#include"Cell.h"
#include<math.h>
#include<QChar>
#include<QList>

#define MAX_SIZE_BUCKED 5;
huffdecoditication::huffdecoditication(char *FileInput)
{
    this->FileObjectInput = FileInput;
    File* FileObjectInput =new File(this->FileObjectInput);
    BitVector bitVector= BitVector();
    bitVector.setbit(QString().setNum(FileObjectInput->readFile(0),2),8);
    bitVector.setbit(QString().setNum(FileObjectInput->readFile(1),2),8);
    bitVector.setbit(QString().setNum(FileObjectInput->readFile(2),2),8);
    this->trash=0;
    this->sizeTree=0;
    this->sizeName=0;
    for(int i=2;i>=0;i--)
    {
        this->trash+=pow(2,2-i)*bitVector.bitVectorAt(i);
    }
    for(int i=15;i>=3;i--)
    {
        this->sizeTree+=pow(2,15-i)*bitVector.bitVectorAt(i);
    }
    for(int i=23;i>=16;i--)
    {
        this->sizeName+=pow(2,23-i)*bitVector.bitVectorAt(i);
    }
    this->fileName=FileObjectInput->readFile(3,this->sizeName);
    for(int i=3+this->sizeName;i<3+this->sizeName+this->sizeTree;i++)
    {
        this->treeRepresetation.append(FileObjectInput->readFile(i));
    }
    this->position=3+this->sizeName+this->sizeTree;
    FileObjectInput->setPosition(this->position);
    this->isEndBool=false;
}
QString huffdecoditication::TreeRepresetation()
{
    return this->treeRepresetation;
}
bool huffdecoditication::IsEnd()
{
    return this->isEndBool;
}
QString huffdecoditication::grabBucked()
{
    int read;
    std::ifstream inputFile;
    inputFile.open(this->FileObjectInput,std::ios::binary);
    if(inputFile.is_open())
    {
        inputFile.seekg(0,inputFile.end);
        sizeFile=inputFile.tellg();
        inputFile.seekg(0, inputFile.beg);
    }
    inputFile.seekg(this->position);
    if(sizeFile-position>5)
    {
        this->position+=MAX_SIZE_BUCKED;
        read=MAX_SIZE_BUCKED;
        this->isEndBool=false;
    }
    else
    {
        read=sizeFile-position;
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
bool huffdecoditication::isElement(cell* node,QString HuffmanCodification)
{
    bool boolReturn;
    if(HuffmanCodification.size()!=0)
    {
        if(node->leaf != true)
        {
            if(HuffmanCodification.at(0).toLatin1()=='0')
            {
                boolReturn=isElement(node->left, HuffmanCodification.remove(0,1));
            }
            if(HuffmanCodification.at(0).toLatin1()=='1')
            {
                boolReturn=isElement(node->right,HuffmanCodification.remove(0,1));
            }
        }
        if(node->leaf)
        {
            return true;
        }
    }
    else
        return false;
}
char huffdecoditication::getElementTree(cell* node,QString HuffmanCodification)
{
    char charReturn;
    if(node->leaf != true)
    {
        if(HuffmanCodification.at(0).toLatin1()=='0')
        {
            charReturn=isElement(node->left, HuffmanCodification.remove(0,1));
        }
        if(HuffmanCodification.at(0).toLatin1()=='1')
        {
            charReturn=isElement(node->right,HuffmanCodification.remove(0,1));
        }
    }
    if(node->leaf)
    {
        return node->getElement();
    }
}
int huffdecoditication::getTrash()
{
    return this->trash;
}
int huffdecoditication::getSize()
{
    return this->sizeFile;
}


cell* huffdecoditication::generation(QString Tree)
{
    cell* Left;
    cell* Right;
    QString TreeLeft=TreeHuffmanDecodificationLeft(Tree);
    QString TreeRight=TreeHuffmanDecodificationRight(Tree);
    if(TreeLeft.size()>1)
    {
        Left = generation(TreeLeft);
    }
    else
    {
        Left=new cell(TreeLeft.at(0).toLatin1(),0);
    }
    if(TreeRight.size()>1)
    {
        Right = generation(TreeRight);
    }
    else
    {
        Right = new cell(TreeRight.at(0).toLatin1(),0);
    }
    return new cell(0,Left,Right);
}
QString huffdecoditication::TreeHuffmanDecodificationLeft(QString huff)
{
    QList<char> test;
    QString TreeHuffmanDecodificationLeft;
    if(huff.at(0).toLatin1()=='(')
    {
        test.push_back('(');
        for(int i=1;i<huff.size();i++)
        {
            if(huff.at(i).toLatin1()=='(' && huff.at(i-1).toLatin1()!='-')
            {
                test.push_back('(');
            }
            if(huff.at(i).toLatin1()==')' && huff.at(i-1).toLatin1()!='-')
            {
                test.pop_back();
            }
            if(test.isEmpty())
            {
                break;
            }
            TreeHuffmanDecodificationLeft.append(huff.at(i));
        }
    }
    else
    {
        TreeHuffmanDecodificationLeft=huff.at(0);
        if(huff.at(0).toLatin1()=='-')
        {
            TreeHuffmanDecodificationLeft=huff.at(1);
        }
    }

    return TreeHuffmanDecodificationLeft;
}
QString huffdecoditication::TreeHuffmanDecodificationRight(QString huff)
{
    QList<char> test;
    QString TreeHuffmanDecodificationLeft;
    if(huff.at(0).toLatin1()=='(')
    {
        test.push_back('(');
        TreeHuffmanDecodificationLeft.append(')');
        for(int i=1;i<huff.size();i++)
        {
            if(huff.at(i).toLatin1()=='(' && huff.at(i-1).toLatin1()!='-')
            {
                test.push_back('(');
            }
            if(huff.at(i).toLatin1()==')' && huff.at(i-1).toLatin1()!='-')
            {
                test.pop_back();
            }
            TreeHuffmanDecodificationLeft.append(huff.at(i));
            if(test.isEmpty())
            {
                break;
            }
        }
    }
    else
    {
        TreeHuffmanDecodificationLeft=huff.at(0);
        if(huff.at(0).toLatin1()=='-')
        {
            TreeHuffmanDecodificationLeft.append(huff.at(1).toLatin1());
        }
    }
    QString TreeHuffmanDecodificationRight;
    huff.remove(0,TreeHuffmanDecodificationLeft.size());
    if(huff.at(0).toLatin1()=='(')
    {
        test.push_back('(');
        for(int i=1;i<huff.size();i++)
        {
            if(huff.at(i).toLatin1()=='(' && huff.at(i-1).toLatin1()!='-')
            {
                test.push_back('(');
            }
            if(huff.at(i).toLatin1()==')' && huff.at(i-1).toLatin1()!='-')
            {
                test.pop_back();
            }
            if(test.isEmpty())
            {
                break;
            }
           TreeHuffmanDecodificationRight.append(huff.at(i));
        }
    }
    else
    {
        TreeHuffmanDecodificationRight=huff.at(0);
        if(huff.at(0).toLatin1()=='-')
        {
            TreeHuffmanDecodificationRight=huff.at(1);
        }
    }

    return TreeHuffmanDecodificationRight;
}

char* huffdecoditication::getFileName()
{
    return this->fileName.toLocal8Bit().data();
}

