#include "FileNameTableModel.h"

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
    /*
    if (sourceFileNames.length()>0)
    {
        QModelIndex topLeft = createIndex(0,0);
        QModelIndex bottomRight = createIndex(1,sourceFileNames.length()-1);
        // emit a signal to make the view reread identified data
        emit dataChanged(topLeft, bottomRight, {Qt::DisplayRole});
    }
    */
}

/*
void FileNameTableModel::dropEvent(QDropEvent *event)
{
    never called
}
*/

Qt::DropActions FileNameTableModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

/*
bool FileNameTableModel::canDropMimeData(const QMimeData* data, Qt::DropAction action, int row, int col, const QModelIndex& parent) const
{
    return true; // just for simplicity
}
*/

bool FileNameTableModel::moveRows(const QModelIndex& parent1, int source_first, int source_last, const QModelIndex& parent2, int dest)
{
    if (source_first==dest) return false;

    //beginMoveRows(parent1, source_first, source_last, parent2, dest);

    beginResetModel();

    //auto before=this->sourceFileNames.sliced(0, source_first - 1);
    //auto toMove=this->sourceFileNames.sliced(source_first, source_last - source_first+ 1);
    //auto after=

    //this->sourceFileNames[0]=this->sourceFileNames[1];
    //this->sourceFileNames[1]=rem;

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

    auto sourceVal=this->sourceFileNames[source_first];
    this->sourceFileNames.removeAt(source_first);
    this->sourceFileNames.insert(dest,sourceVal);

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

    //rem=this->targetFileNames[0];
    //this->targetFileNames[0]=this->targetFileNames[1];
    //this->targetFileNames[1]=rem;

    //endMoveRows();

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
