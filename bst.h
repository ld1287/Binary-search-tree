#ifndef BST_H
#define BST_H

#include <QObject>
#include <QDebug>
#include <unordered_map>
#include <QString>

class Node{
public:
    Node(int value):data(value),x(0),y(0),
        leftChild(nullptr),rightChild(nullptr),parent(nullptr){}
    int data;
    int x;
    int y;
    Node* leftChild;
    Node* rightChild;
    Node* parent;
};

class BST : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString preOrder READ preOrder NOTIFY preOrderChanged)
    Q_PROPERTY(QString inOrder READ inOrder NOTIFY inOrderChanged)
    Q_PROPERTY(QString postOrder READ postOrder NOTIFY postOrderChanged)

public:
    enum Role
    {
        preorder=1,
        inorder,
        postorder
    };
    explicit BST(QObject *parent = nullptr);

    Q_INVOKABLE void BSTinsert(int value);
    Q_INVOKABLE void BSTremove(int value);
    Q_INVOKABLE void BSTfind(int value);

    bool insert(int value);//插入数据
    bool remove(int value);//删除数据
    bool find(int value) const;//查找数据
    Node* getRoot() const;//获取根节点
    void updateNodePositions();//更新节点的信息

    Q_INVOKABLE QString preOrder()const;
    Q_INVOKABLE QString inOrder()const;
    Q_INVOKABLE QString postOrder()const;

    void updateTraversals();
    QString traversal(Node* node,Role role)const;//获取
signals:
    void treeUpdateChanged();
    void preOrderChanged();
    void inOrderChanged();
    void postOrderChanged();
private:
    Node* root;
    QString m_preOrder;//前序
    QString m_inOrder;//中序
    QString m_postOrder;//后序

    //std::unordered_map<Node*,int>widths;
    void calculateWidths(Node* node,std::unordered_map<Node*,int>&widths);

    void setPosition(Node* node, int depth, int offset,std::unordered_map<Node*, int>& widths);//设置节点的位置
    Node* findNode(Node* node, int value) const;//查找节点
    Node* getMinimunNode(Node* node) const;//获取最小节点
    void replaceNode(Node* oldNode, Node* newNode);//替换节点
    void deleteNode(Node* node);//删除节点
    void deleteAllNodes(Node* node);//递归删除所有节点

};

#endif // BST_H
