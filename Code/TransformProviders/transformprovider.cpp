#include "transformprovider.h"

bool TransformProvider::transformMulti(const QStringList& inFullUrls, const QStringList& in, QStringList& out, transformScope scope)
{
    bool successOne=true;
    bool successAll=true;
    QString transformed;
    out.clear();

    int index=0;

    UpdateGUIvars();
    QString fileNameOnly;
    QString extensionOnly;
    foreach (QString str, in)
    {
        switch (scope)
        {    
            case name_and_extension:
                SplitFileName(str,fileNameOnly,extensionOnly);
                //transformed=fileNameOnly+":"+extensionOnly;
                transformed=transform(inFullUrls[index],str, index, successOne);
            break;
            case name_only:
                SplitFileName(str,fileNameOnly,extensionOnly);
                transformed=transform(inFullUrls[index],fileNameOnly, index, successOne);
                transformed=transformed+"."+extensionOnly;
            break;
            case extension_only:
                SplitFileName(str,fileNameOnly,extensionOnly);
                transformed=transform(inFullUrls[index],extensionOnly, index, successOne);
                transformed=fileNameOnly+"."+transformed;
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

int TransformProvider::SplitFileName(const QString& fullFileName, QString& filename, QString& extension, bool greedyExtension)
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
    return 0;
}





