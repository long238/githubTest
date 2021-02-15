import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    //1.属性动画
    //格式：PropertyAnimation on 属性
    //easing属性来实现缓和曲线
//    Rectangle {
//        width: 100
//        height: 100
//        color: "red"
//        PropertyAnimation on x {
//            to:50; //移动到50上
//            duration: 1000; //持续时间:1000毫秒   动画持续播放1秒
//            loops: Animation.Infinite//循环:动画.无限    无限循环播放动画
//            easing.type: Easing.OutBounce//设置缓和曲线达到反弹效果
//        }
//        PropertyAnimation on y { to:50;duration: 1000; loops: Animation.Infinite;easing.type: Easing.OutBounce}
//    }

    //2.行为动画 Behavior为一个属性值来指定默认的动画
    //语法：Behavior on 属性
//    Rectangle{
//        id:green_Rectangle
//        width: 640
//        height: 480
//        color: "green"

//        Behavior on x{
//            PropertyAnimation{
//                duration: 500//持续播放的时间
//            }
//        }

//        Behavior on y{
//            PropertyAnimation{
//                duration: 500//持续播放的时间
//            }
//        }
//    }
//    MouseArea{
//        anchors.fill: parent//鼠标活动范围:父类的范围
//        //点击
//        onClicked: {
//            green_Rectangle.x=mouse.x
//            green_Rectangle.y=mouse.y
//        }
//    }

    //3.信号处理器中的动画
//    Rectangle{
//        id:green_Rectangle
//        width: 140
//        height: 180
//        color: "green"

//        MouseArea{
//            anchors.fill: parent//鼠标活动范围:父类的范围
//            onClicked: PropertyAnimation{
//                target: green_Rectangle//要操作的对象
//                properties: "x,y"//操作的属性
//                to:50
//                duration: 2000//持续播放的时间

//            }

//        }
//    }

    //4.独立动画(动画作为普通的QML对象创建）
//    Rectangle{
//        id:green_Rectangle
//        width: 140
//        height: 180
//        color: "green"

//        PropertyAnimation{
//            id:rect_animation
//            target: green_Rectangle
//            properties: "x,y"
//            duration: 1000

//        }

//        MouseArea{
//            anchors.fill: parent
//            onClicked: {
//                rect_animation.to=50
//                rect_animation.running=true//运行动画
//            }
//        }
//    }

    //5.状态切换
//    Rectangle{
//        id:green_Rectangle
//        width: 140
//        height: 180
//        color: "green"

//        MouseArea{
//            anchors.fill: parent
//            //按下
//            onPressed:  {
//                green_Rectangle.state="moved_1"
//            }
//            //释放
//            onReleased: {
//                green_Rectangle.state="moved_2"
//            }
//        }

//        //状态列表
//        states:[
//            State {
//                name: "moved_1"
//                //变更属性
//                PropertyChanges {
//                    target: green_Rectangle
//                    x:100;y:100;color:"red"
//                }
//            },
//            State {
//                name: "moved_2"
//                //变更属性
//                PropertyChanges {
//                    target: green_Rectangle
//                    x:50;y:50;color:"black"
//                }
//            }
//        ]

//        transitions: Transition {
//            PropertyAnimation{
//                properties: "x,y,color";duration: 1000
//            }
//        }
//    }

    //6.动画元素
//    Rectangle{
//        width: 200
//        height: 200
//        //颜色动画效果
//        ColorAnimation on color{
//            from: "yellow"
//            to: "gray"
//            duration: 2000
//        }

//        //旋转动画效果
//        RotationAnimation on rotation {
//            to:90
//            duration: 3000
//            direction: RotationAnimation.Clockwise//顺时针方向
//        }
//    }

    //7.组合动画
    Rectangle{
        width: 300
        height: 300

        Image
        {
            source: "/132148.png"
           // anchors.horizontalCenter: parent.horizontalCenter
            y:0

            SequentialAnimation on y{
                loops: Animation.Infinite//无限循环
                //数字动画
                NumberAnimation{
                    to:250
                    easing.type: Easing.OutBounce
                    duration: 1000
                }

                //暂停动画
                PauseAnimation {
                    duration: 2000
                }

                NumberAnimation{
                    to:0
                    easing.type: Easing.OutBounce
                    duration: 1000
                }
            }
        }
    }
}











