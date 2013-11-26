#include "filetree.h"

FileTree::FileTree(QWidget* parent) : QTreeWidget(parent)
{
    this->setDragDropMode(QAbstractItemView::InternalMove);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setDragEnabled(true);
    this->setAcceptDrops(true);
}

FileTree::~FileTree() {

}

/*
#include <QDragMoveEvent>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>

QTreeWidgetItem* draggingItem;
QTreeWidgetItem* dropingOn;

void FileTree::startDrag(Qt::DropActions supportedActions) {
    QTreeWidget::startDrag(supportedActions);
    return;

    QDrag *drag = new QDrag(this);
    QMimeData *data = new QMimeData;
    data->setText(currentItem()->text(0));
    drag->setMimeData(data);
    drag->exec(supportedActions, Qt::MoveAction);
}

void FileTree::dragMoveEvent(QDragMoveEvent * event) {
    event->acceptProposedAction();
}

void FileTree::dragEnterEvent(QDragEnterEvent * event ) {
    event->acceptProposedAction();
}

void FileTree::dropEvent(QDropEvent * event ) {
    dropingOn = this->itemAt(event->pos());
    int dropingIndex = this->indexOfTopLevelItem(dropingOn);
    this->takeTopLevelItem(this->indexOfTopLevelItem(draggingItem));
    int index = this->indexOfTopLevelItem(dropingOn);
    if(index < dropingIndex) index++;
    this->insertTopLevelItem(index, draggingItem);
}

void FileTree::mousePressEvent(QMouseEvent *event) {
    if(event->button()==Qt::LeftButton) {
        draggingItem = this->itemAt(event->pos());
        QDrag *drag = new QDrag(this);
        drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction);
        event->accept();
    }
}
*/
