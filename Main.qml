import QtQuick
import QtQuick.Window
import QtQuick.Controls

import com.BSTItem 1.0
import com.BST 1.0

Window {
    id:root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    Column{
        anchors.fill: parent

        ScrollView{
            id:scrollView
            width: parent.width
            height:parent.height-100
            Flickable{
                id:flickable
                width: scrollView.width
                height: scrollView.height
                contentWidth: flickable.width
                contentHeight: bstItem.height
            }
            BSTItem {
                id:bstItem
                width: parent.width
                height: 1000
                getBST:bst
            }
        }

        Row {
            id:insertROW
            spacing: 10
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            height: 50
            Rectangle{
                id:insertRect
                radius: 5
                width:100
                height:insertBtn.height
                border{
                    color:insertInput.activeFocus ? "red" : color
                    width:3
                }
                color:"lightsteelblue"
                TextInput{
                    id:insertInput
                    anchors.centerIn: parent
                    width: parent.width-20
                    clip:true
                }
            }
            Button{
                id:insertBtn
                text:"插入节点"
                onClicked: {
                    bst.BSTinsert(parseInt(insertInput.text))
                    insertInput.text=""
                    bstItem.update()
                }
            }

            Rectangle{
                id:removeRect
                radius: 5
                width:100
                height:removeBtn.height
                border{
                    color:removeInput.activeFocus ? "red" : color
                    width:3
                }
                color:"lightsteelblue"
                TextInput{
                    id:removeInput
                    anchors.centerIn: parent
                    width: parent.width-20
                    clip:true
                }
            }
            Button{
                id:removeBtn
                text:"删除节点"
                onClicked: {
                    bst.BSTremove(parseInt(removeInput.text))
                    insertInput.text=""
                    bstItem.update()
                }
            }
//            Rectangle{
//                id:findRect
//                radius: 5
//                width:100
//                height:findBtn.height
//                border{
//                    color:findInput.activeFocus ? "red" : color
//                    width:3
//                }
//                color:"lightsteelblue"
//                TextInput{
//                    id:findInput
//                    anchors.centerIn: parent
//                    width: parent.width-20
//                    clip:true
//                }
//            }
//            Button{
//                id:findBtn
//                text:"查找节点"
//                onClicked: {
//                    bst.BSTfind(parseInt(findInput.text))
//                    bstItem.update()
//                }
//            }
        }
    }
    BST{
        id:bst
    }
}
