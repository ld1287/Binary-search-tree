#include "bstitem.h"


BSTItem::BSTItem(QQuickItem *parent):
    QQuickPaintedItem(parent),m_bst(nullptr)
{

}

BST *BSTItem::getBST() const
{
    return m_bst;
}

void BSTItem::setBST(BST *bst)
{
    if(m_bst != bst){
        if(m_bst){
            disconnect(m_bst,&BST::treeUpdateChanged,this,&BSTItem::onTreeUpdate);
        }
        m_bst=bst;
        if(m_bst){
            connect(m_bst,&BST::treeUpdateChanged,this,&BSTItem::onTreeUpdate);
        }
        emit bstChanged();
    }
}

void BSTItem::drawNode(QPainter *painter, Node *node)
{
    if(node == nullptr) return;  // 如果节点为空，直接返回

    QPen pen(Qt::black); // 设置线条颜色为紫色
    painter->setPen(pen);

    QBrush brush(Qt::darkCyan); // 设置填充颜色为黄色
    painter->setBrush(brush);

    // 绘制节点的圆形
    painter->drawEllipse(node->x, node->y, 30, 30);

    // 在节点圆形的中心绘制节点数据
    painter->drawText(node->x + 10, node->y + 20, QString::number(node->data));

    // 如果左子节点存在，绘制连接线并递归绘制左子节点
    if (node->leftChild) {
        // 绘制当前节点到左子节点的连接线
        painter->drawLine(node->x + 15, node->y + 15,
                          node->leftChild->x + 15, node->leftChild->y + 15);
        // 递归绘制左子节点
        drawNode(painter, node->leftChild);
    }

    // 如果右子节点存在，绘制连接线并递归绘制右子节点
    if (node->rightChild) {
        // 绘制当前节点到右子节点的连接线
        painter->drawLine(node->x + 15, node->y + 15,
                          node->rightChild->x + 15, node->rightChild->y + 15);
        // 递归绘制右子节点
        drawNode(painter, node->rightChild);
    }
}

void BSTItem::paint(QPainter *painter)
{
//    painter->setBrush(Qt::blue);
//    painter->drawEllipse(100, 100, 50, 50);
    if(m_bst==nullptr)return;
    if(m_bst->getRoot()){
        drawNode(painter,m_bst->getRoot());
    }
}

void BSTItem::onTreeUpdate()
{
    update();
}
