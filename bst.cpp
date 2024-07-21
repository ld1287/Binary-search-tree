#include "bst.h"

BST::BST(QObject *parent)
    : QObject{parent},
    root(nullptr),
    m_preOrder(""),
    m_inOrder(""),
    m_postOrder("")
{

}

void BST::BSTinsert(int value)
{
    qDebug()<<"value"<<value;
    insert(value);
    updateNodePositions();
    emit treeUpdateChanged();
}

void BST::BSTremove(int value)
{
    remove(value);
    updateNodePositions();
    emit treeUpdateChanged();
}

void BST::BSTfind(int value)
{
    find(value);
    emit treeUpdateChanged();
}

bool BST::insert(int value)
{
    Node* newNode = new Node(value);
    if(root==nullptr){
        root = newNode;
        return true;
    }
    Node* current = root;      //获取root节点的临时节点
    Node* parent = nullptr;

    while(current){
        parent = current;                      //存储上一个节点
        if(value < current->data){             //如果当前值小于节点值
            current = current->leftChild;
        }
        else if(value > current->data){        //大于
            current = current->rightChild;
        }
        else{                                  //重复值
            delete newNode;
            return false;
        }
    }
    newNode->parent = parent;                 //获取当前节点的父节点
    if(value < parent->data){
        parent->leftChild = newNode;
    }
    else{
        parent->rightChild = newNode;
    }

    return true;
}

bool BST::remove(int value)
{
    Node* node = findNode(root, value);
    if(node==nullptr){
        return false;
    }//未找到
    deleteNode(node);
    return true;
}

bool BST::find(int value) const
{
    Node* node = findNode(root, value);
    return node != nullptr;
}

Node *BST::getRoot() const
{
    return root;
}

void BST::updateNodePositions()
{
    if (!root) return;
    std::unordered_map<Node*, int> widths;
    calculateWidths(root, widths);
    setPosition(root, 20, 300, widths); // 初始位置可以根据需要调整
}

QString BST::preOrder() const
{
    return m_preOrder;
}

QString BST::inOrder() const
{
    return m_inOrder;
}

QString BST::postOrder() const
{
    return m_postOrder;
}

void BST::updateTraversals()
{
    m_preOrder=traversal(root,preorder);
    m_inOrder=traversal(root,inorder);
    m_postOrder=traversal(root,postorder);
    emit preOrderChanged();
    emit inOrderChanged();
    emit postOrderChanged();
}

QString BST::traversal(Node *node, Role role) const
{
    if (!node) return "";
    QString result;
    if (role == preorder) {
        result += QString::number(node->data) + " ";
        result += traversal(node->leftChild, role);
        result += traversal(node->rightChild, role);
    } else if (role == inorder) {
        result += traversal(node->leftChild, role);
        result += QString::number(node->data) + " ";
        result += traversal(node->rightChild, role);
    } else if (role == postorder) {
        result += traversal(node->leftChild, role);
        result += traversal(node->rightChild, role);
        result += QString::number(node->data) + " ";
    }
    return result.trimmed();

}

void BST::calculateWidths(Node *node, std::unordered_map<Node *, int> &widths)
{
    if(node==nullptr)return;
    calculateWidths(node->leftChild,widths);
    calculateWidths(node->rightChild,widths);
    int leftWidth=(node->leftChild) ? widths[node->leftChild] :0;
    int rightWidth=(node->rightChild) ? widths[node->rightChild]:0;
    widths[node]=1+std::max(leftWidth,rightWidth);
}

void BST::setPosition(Node *node, int depth, int offset,std::unordered_map<Node*, int>& widths)
{
    if (node == nullptr) return;

    int leftWidth = (node->leftChild) ? widths[node->leftChild] : 0;
    int rightWidth = (node->rightChild) ? widths[node->rightChild] : 0;

    int leftOffset = offset - rightWidth * 15;
    int rightOffset = offset + leftWidth * 15;

    node->x = offset;
    node->y = depth;

    setPosition(node->leftChild, depth + 50, leftOffset, widths);
    setPosition(node->rightChild, depth + 50, rightOffset, widths);
}

Node *BST::findNode(Node *node, int value) const
{
    while(node!=nullptr){
        if(value < node->data){
            node = node->leftChild;
        }
        else if(value > node->data){
            node = node->rightChild;
        }
        else {
            return node;    //返回节点
        }
    }
    return nullptr;
}

Node *BST::getMinimunNode(Node *node) const
{
    while(node->leftChild != nullptr){
        node = node->leftChild;
    }
    return node;
}

void BST::replaceNode(Node *oldNode, Node *newNode)
{
    if(oldNode->parent == nullptr ){//如果当前节点的父节点为空，则设为root节点
        root = newNode;
    }
    else if(oldNode == oldNode->parent->leftChild){//如果当前节点是父节点的左子节点
        oldNode->parent->leftChild = newNode;
    }
    else{////如果当前节点是父节点的右子节点
        oldNode->parent->rightChild = newNode;
    }

    if(newNode != nullptr){//把旧父节点赋值给新父节点
        newNode->parent = oldNode->parent;
    }
}

void BST::deleteNode(Node *node)
{
    if((node->leftChild ==nullptr) && (node->rightChild==nullptr)){//尾节点
        replaceNode(node, nullptr);
        delete node;
    }
    else if(node->leftChild == nullptr){//没有左子节点
        replaceNode(node, node->rightChild);
        delete node;
    }
    else if(node->rightChild == nullptr){//没有右子节点
        replaceNode(node, node->leftChild);
        delete node;
    }
    else{
        Node* successor = getMinimunNode(node->rightChild);//获取右子树的最小节点
        node->data = successor->data;//当前节点设置为最小节点的值
        deleteNode(successor);//递归删除尾节点
    }
}

void BST::deleteAllNodes(Node *node)
{
    if (node!=nullptr) {
        deleteAllNodes(node->leftChild);
        deleteAllNodes(node->rightChild);
        delete node;
    }
}
