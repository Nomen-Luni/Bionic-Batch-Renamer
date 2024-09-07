#include "DragTableView.h"

DragTableView::DragTableView(QWidget *parent):QTableView(parent)
{
}

void DragTableView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        sourceRow = rowAt(event->position().toPoint().y());
    }
    QTableView::mousePressEvent(event);
}

void DragTableView::dropEvent(QDropEvent* event)
{
    if (event->source()!=this)
        return;

    //if (event->source() != this || event->dropAction() != Qt::MoveAction)
    //    return;

    auto destinationRow = rowAt(event->position().toPoint().y());
    model()->moveRows(QModelIndex(), sourceRow, sourceRow, QModelIndex(), destinationRow);
    event->accept();
}
