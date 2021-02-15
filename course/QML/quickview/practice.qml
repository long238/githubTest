import QtQuick 2.0

    //用于1，2,3的测试
//Text {
//    function qmlFunction(msg){
//        console.log("message comes:",msg)
//        return "dd"
//    }

//    height: 100
//    width: 100
//    text: applicationData.getCurrentDateTime()
//}

//用于4的测试
Item {
    id:item
    width: 100
    height: 100
    Text {

        text: qsTr("点我")
    }
    signal qmlSignal(string msg)//qml定义信号

    MouseArea{
        anchors.fill:parent
        onClicked: item.qmlSignal("郭伟龙最帅")
    }

}
