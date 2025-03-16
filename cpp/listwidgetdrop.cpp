#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>
#include <QDrag>
#include "listwidgetdrop.h"

listWidgetDrop::listWidgetDrop(QWidget * parent, SecondWindow *qMain) : QListWidget(parent),
    m_secWindow(qMain)

{

    setAcceptDrops(true);
    setDragEnabled(true);

}

void listWidgetDrop::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void listWidgetDrop::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void listWidgetDrop::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        auto test = event->mimeData()->urls();
        qDebug()<<"url"<< test;
        addItem(event->mimeData()->text());
        event->acceptProposedAction();
    }
}


