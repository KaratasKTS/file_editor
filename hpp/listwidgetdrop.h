#ifndef LISTWIDGETDROP_H
#define LISTWIDGETDROP_H

#include <QListWidget>
#include <QObject>
#include <QWidget>

class SecondWindow;

class listWidgetDrop : public QListWidget
{
    Q_OBJECT
private:
    SecondWindow* m_secWindow;
public:
    explicit listWidgetDrop(QWidget * parent= nullptr,SecondWindow* window = nullptr);


protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
};

#endif // LISTWIDGETDROP_H
