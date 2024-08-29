#include "TransformProvider.h"

bool TransformProvider::transformMulti(const QStringList& inFullUrls, const QStringList& in, QStringList& out, transformScope scope)
{
    bool successOne=true;
    bool successAll=true;
    QString transformed;
    out.clear();

    int index=0;

    updateGUIvars();
    QString fileNameOnly;
    QString extensionOnly;
    bool splitFound;
    foreach (QString str, in)
    {
        switch (scope)
        {    
            case name_and_extension:
                transformed=transform(inFullUrls[index],str, index, successOne);
            break;
            case name_only:
                splitFound=splitFileName(str,fileNameOnly,extensionOnly);
                transformed=transform(inFullUrls[index],fileNameOnly, index, successOne);
                if (splitFound)
                {
                    transformed=transformed+"."+extensionOnly;
                }
            break;
            case extension_only:
                splitFound=splitFileName(str,fileNameOnly,extensionOnly);
                if (splitFound)
                {
                    transformed=transform(inFullUrls[index],extensionOnly, index, successOne);
                    transformed=fileNameOnly+"."+transformed;
                }
                else
                {
                    transformed=str;
                }
            break;
        }

        if (successOne==false)
        {
            transformed="";
            successAll=false;
        }
        out.push_back(transformed);
        index++;
    }
    return successAll;
}

bool TransformProvider::splitFileName(const QString& fullFileName, QString& filename, QString& extension, bool greedyExtension)
{
    int offset;
    if (greedyExtension)
    {
        offset=fullFileName.indexOf(".");
    }
    else
    {
        offset=fullFileName.lastIndexOf(".");
    }
    if (offset>=0)
    {
        filename = fullFileName.left(offset);
        extension = fullFileName.mid(offset+1);
    }
    else
    {
        filename=fullFileName;
        extension="";
    }
    return offset>=0;
}





