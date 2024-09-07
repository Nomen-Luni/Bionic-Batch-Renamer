#include "FileNameTableModel.h"
#include "../TransformEngine/TransformEngine.h"

FileNameTableModel::FileNameTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int FileNameTableModel::rowCount(const QModelIndex & /*parent*/) const
{
    return sourceFileNames.length();
}

int FileNameTableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 2;
}

QVariant FileNameTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (index.column() == 0)
            return sourceFileNames[index.row()];
        else
            return targetFileNames[index.row()];
    }

    return QVariant();
}

QVariant FileNameTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Name");
        case 1:
            return QString("New Name");
        }
    }
    return QVariant();
}

Qt::ItemFlags FileNameTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flag = QAbstractItemModel::flags(index);

    if (index.isValid()) {
        return flag | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
    } else {
        return flag | Qt::ItemIsDropEnabled;
    }
}

void FileNameTableModel::setFileNames(QStringList sourceFileNames, QStringList targetFileNames)
{
    beginResetModel();
    this->sourceFileNames = sourceFileNames;
    this->targetFileNames = targetFileNames;
    endResetModel();
}

Qt::DropActions FileNameTableModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

bool FileNameTableModel::moveRows(const QModelIndex& parent1, int source_first, int source_last, const QModelIndex& parent2, int dest)
{
    if (source_first==dest) return false;

    //beginMoveRows(parent1, source_first, source_last, parent2, dest);

    beginResetModel();

    /*
    this->sourceFileNames.clear();
    this->sourceFileNames.append({"00","01","02","03","04","05"});
    qDebug("moveRows: %i -> %i", source_first, dest);
    qDebug("%s:%s:%s:%s:%s:%s->",
           qPrintable(this->sourceFileNames[0]),
           qPrintable(this->sourceFileNames[1]),
           qPrintable(this->sourceFileNames[2]),
           qPrintable(this->sourceFileNames[3]),
           qPrintable(this->sourceFileNames[4]),
           qPrintable(this->sourceFileNames[5])
           );
    */

    // Re-order source file names list
    auto sourceVal=this->sourceFileNames[source_first];
    this->sourceFileNames.removeAt(source_first);
    this->sourceFileNames.insert(dest,sourceVal);

    if (TransformEngine::transformIsOrderDependent())
    {
        TransformEngine::doTransform();
        this->targetFileNames=TransformEngine::getTargetFileNamesList();
    }
    else
    {
        // Re-order target file names list
        sourceVal=this->targetFileNames[source_first];
        this->targetFileNames.removeAt(source_first);
        this->targetFileNames.insert(dest,sourceVal);
    }

    /*
    qDebug("%s:%s:%s:%s:%s:%s",
           qPrintable(this->sourceFileNames[0]),
           qPrintable(this->sourceFileNames[1]),
           qPrintable(this->sourceFileNames[2]),
           qPrintable(this->sourceFileNames[3]),
           qPrintable(this->sourceFileNames[4]),
           qPrintable(this->sourceFileNames[5])
           );
    */

    endResetModel();

    return true;
}

/*
void dragMoveEvent(QDragMoveEvent* event)
{
    event->setDropAction(Qt::MoveAction);
    event->accept();
}
*/

/*
QModelIndex index(int row, int column, const QModelIndex &parent)
{
    return new QModelIndex(row, column);
}
*/
