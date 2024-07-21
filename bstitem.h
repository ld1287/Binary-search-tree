#ifndef BSTITEM_H
#define BSTITEM_H

#include <QQuickPaintedItem>
#include <QPainter>
#include "bst.h"

class BSTItem:public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(BST* getBST READ getBST WRITE setBST NOTIFY bstChanged)
public:
    BSTItem(QQuickItem* parent=nullptr);

    BST* getBST()const;
    void setBST(BST* bst);
    void drawNode(QPainter* painter,Node* node);
    void paint(QPainter* painter)override;
signals:
    void bstChanged();
public slots:
    void onTreeUpdate();
private:
    BST* m_bst;
};

#endif // BSTITEM_H
