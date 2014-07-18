#include "TreatmentHeader.h"
TreatmentHeader::TreatmentHeader(int argc, char* argv[])
{
    this->argc=argc;
    this->argv=argv;
    this->isCodificationBool=false;
    this->isSuccessBool=false;
    if(QString(argv[1]).contains("-c") && QString(argv[1]).size()==2)
    {
        this->isCodificationBool=true;
    }

}
bool TreatmentHeader::isCodification()
{
    return this->isCodificationBool;
}
bool TreatmentHeader::isSuccess()
{
    return this->isSuccessBool;
}

char* TreatmentHeader::getFileInput()
{
    char* FileInputReturn;
    if(this->isCodification())
    {
        if(argc==3)
        {
            FileInputReturn=argv[2];
        }
        if(argc==5)
        {
            if(QString(argv[3]).contains("-o") && QString(argv[3]).size()==2)
            {
                FileInputReturn=argv[2];
            }
        }
    }
    else
    {
        if(argc==2)
        {
            FileInputReturn=this->argv[1];
        }
        if(argc==4)
        {
            if(QString(argv[2]).contains("-d") && QString(argv[2]).size()==2)
            {
                FileInputReturn=this->argv[1];
            }
        }
    }
    return FileInputReturn;
}

char* TreatmentHeader::getFileOutput()
{
    QString ReturnString;
    if(this->isCodificationBool)
    {
        if(argc==3)
        {
            ReturnString=QString(argv[2]);
            int position=ReturnString.indexOf(QString('.'));
            if(position!=-1)
            {
                ReturnString.remove(position,ReturnString.size()-position);
            }
            ReturnString.append(".huff");
            this->isSuccessBool=true;

        }
        if(argc==5)
        {
            if(QString(argv[3]).contains("-o") && QString(argv[3]).size()==2)
            {
                ReturnString=QString(argv[4]);
                this->isSuccessBool=true;
            }
        }
    }
    else
    {
        if(argc==4 && QString(argv[2]).contains("-d") && QString(argv[2]).size()==2)
        {
            ReturnString = QString(argv[3]).append("/");
            this->isSuccessBool=true;
        }
        if(argc==2)
        {
        }

    }
    return ReturnString.toLocal8Bit().data();
}
