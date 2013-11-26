#ifndef FILETREE_H
#define FILETREE_H

#include <QWidget>
#include <QTreeWidget>

class FileTree: public QTreeWidget
{
public:
    FileTree(QWidget *parent = 0);
    ~FileTree();
protected:
    /*
    void startDrag(Qt::DropActions supportedActions);
    void dragMoveEvent(QDragMoveEvent * event);
    void dragEnterEvent(QDragEnterEvent * event);
    void dropEvent(QDropEvent * event );
    void mousePressEvent(QMouseEvent *event);
    */
};

#endif // FILETREE_H
