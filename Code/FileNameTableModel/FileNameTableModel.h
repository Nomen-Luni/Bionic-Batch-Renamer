#ifndef FILENAMETABLEMODEL_H
#define FILENAMETABLEMODEL_H

#include <QAbstractTableModel>
#include <QDropEvent>
#include <QModelIndex>

class FileNameTableModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit FileNameTableModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void setFileNames(QStringList sourceFileNames, QStringList targetFileNames);
    Qt::DropActions supportedDropActions() const override;
    bool moveRows(const QModelIndex& parent1, int source_first, int source_last, const QModelIndex& parent2, int dest) override;
private:
    QStringList sourceFileNames;
    QStringList targetFileNames;
};

#endif // FILENAMETABLEMODEL_H
