#include "TreeHuffman.h"
#include "File.h"

TreeHuffman::TreeHuffman()
{
    treeHuffman.reserve(258);
    size = 0;
}


cell TreeHuffman::treeHuffmanAT(int pos)
{
    return treeHuffman[pos];
}
void TreeHuffman::setTreeHuffman(int pos, cell nil)
{
    treeHuffman[pos] = nil;
}
int TreeHuffman::getSize()
{
  return size;
}
void TreeHuffman::insertion(cell newCell)
{
    if(newCell.getSize()!=0)
    {
        size++;
        treeHuffman[size] = newCell;
    }
}
void TreeHuffman::swap(cell &prev, cell &next)
{
    cell aux= prev;
    prev=next;
    next=aux;
}
void TreeHuffman::bubbleHuffman()
{
    for(int i = 1;i<=size;i++)
    {
        for(int j = i+1; j<=size;j++)
        {
            if(treeHuffman[i].getSize()<treeHuffman[j].getSize())
            {
                swap(treeHuffman[i],treeHuffman[j]);
            }
            else
            {
                if(treeHuffman[i].getSize()==treeHuffman[j].getSize())
                {
                    if(!treeHuffman[i].leaf && treeHuffman[j].leaf)
                    {
                        swap(treeHuffman[i],treeHuffman[j]);
                    }
                    else
                    {
                        if(treeHuffman[i].leaf && treeHuffman[j].leaf)
                        {
                            if(treeHuffman[i].getElement()<treeHuffman[j].getElement())
                            {
                                swap(treeHuffman[i],treeHuffman[j]);
                            }
                        }
                    }

                }
            }

        }
    }
    cell* left =new cell();
    *left=treeHuffman[size];
    cell* right= new cell();
    *right=treeHuffman[size-1];
    size = size-2;
    ref= cell(left->getSize()+right->getSize(),left,right);
    this->insertion(ref);
}
void TreeHuffman::buildHuffman()
{
    while(size>1)
    {
        this->bubbleHuffman();
    }
}

QString TreeHuffman::treeRepresetation(cell* node,QString R , bool left)
{
    QString returnRepresetation;
    if(node->leaf != true)
    {
        returnRepresetation.append(QString("("));
        //returnRepresetation.append(QString().setNum(node->getSize()));
        //returnRepresetation.append(QString(","));
        returnRepresetation.append(treeRepresetation(node->left,returnRepresetation));
        //returnRepresetation.append(QString(","));
        returnRepresetation.append(treeRepresetation(node->right,returnRepresetation,false));
        if(left==false)
            returnRepresetation.append(QString(")"));
    }

    else
    {
        if(node->getElement()=='(' || node->getElement()== '-' || node->getElement() == ')')
            returnRepresetation.append(QString("-"));
        if(node->getElement()<0)
            returnRepresetation.append(node->getElement()+256);
        else
            returnRepresetation.append(node->getElement());
        if(left==false)
            returnRepresetation.append(QString(")"));
    }
    return returnRepresetation;
}

void TreeHuffman::printTree(cell* node , int level )
{
    if(node->leaf != true)
    {
        printTree(node->left, level +1);
        cout << qPrintable(QString("\t").repeated(level)) << node->getSize() <<endl;
        printTree(node->right,level +1);
    }
    if(node->leaf)
    {
        cout << qPrintable(QString("\t").repeated(level)) <<"element="<< node->getElement()<<"e="<<(int) node->getElement() + 128 <<endl;
    }

}
QString TreeHuffman::huffmanRepresentation(int Char)
{
    QString huffmanRepresentationArrayReturn=this->huffmanRepresentationArray[Char];
    return huffmanRepresentationArrayReturn;
}
void TreeHuffman::buildCodification(cell* node,long int level)
{
        if(node->leaf != true)
        {
            buildCodification(node->left, level*10);
            buildCodification(node->right,level*10+1);
        }
        if(node->leaf)
        {
            node->setHuffmanRepresentation(level);
            this->huffmanRepresentationArray[File().charToBit(node->getElement())]=node->getHuffmanRepresentation();
        }
}
int TreeHuffman::trashCalculation(int *frequency)
{
    int trash;
    int numberBits=0;
    for(int i=0;i<256;i++)
    {
        numberBits += this->huffmanRepresentationArray[i].size() * frequency[i];
    }
    trash=8-(numberBits%8);
    if(trash==8)
        trash=0;
    return trash;
}
