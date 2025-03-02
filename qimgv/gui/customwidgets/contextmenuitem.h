// A menu item that executes an action on press

#ifndef CONTEXTMENUITEM_H
#define CONTEXTMENUITEM_H

#include "gui/customwidgets/menuitem.h"
#include "components/actionmanager/actionmanager.h"

class ContextMenuItem : public MenuItem {
    Q_OBJECT
public:
    ContextMenuItem(QWidget *parent = nullptr);
    ~ContextMenuItem();
    void setAction(QString mAction);

protected:
    virtual void onPress() Q_DECL_OVERRIDE;

private:
    QString mAction;
};

#endif // CONTEXTMENUITEM_H
