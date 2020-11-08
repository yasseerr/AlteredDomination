import QtQuick 2.0
import QtGraphicalEffects 1.0


Item {
    id: rootIntro
    width: 640
    height: 480
    anchors.fill: parent
    Rectangle {
        id: rectangle
        color: "#ffffff"
        anchors.fill: parent
    }

    Image {
        id: afkaarimage
        width:parent.width/3
        height: width/4
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        opacity: 0
        source: "qrc:/data/logo/afkaarlogo.svg"
    }
    DropShadow{
        color: "#000000"
        radius: 15
        horizontalOffset: 20*afkaarimage.opacity
        opacity: afkaarimage.opacity
        verticalOffset: 20
        samples: 17
        anchors.fill: afkaarimage
        source: afkaarimage
    }

    Image {
        id: adimage
        width: parent.width/3
        height: 2*width/3
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        opacity: 0
        source: "qrc:/data/logo/adlogo.svg"
    }
    DropShadow{
        color: "#000000"
        radius: 15
        horizontalOffset: 5
        opacity: adimage.opacity
        scale: adimage.scale
        verticalOffset: 10
        samples: 30
        anchors.fill: adimage
        source: adimage
    }
    SequentialAnimation{
        running: true
        PropertyAnimation{
            target: afkaarimage
            duration: 20
            property: "opacity"
            from : 0
            to : 1
        }
        PauseAnimation{ duration: 1000}
        PropertyAnimation{
            target: afkaarimage
            duration: 10
            property: "opacity"
            from : 1
            to : 0
        }
        PauseAnimation{ duration: 2}
        ParallelAnimation{
            PropertyAnimation{
                target: adimage
                duration: 10
                property: "opacity"
                from : 0
                to : 1
            }
            PropertyAnimation{
                target: adimage
                duration: 10
                property: "scale"
                from : 0
                to : 1
            }
        }
        PauseAnimation{ duration: 20}
        PropertyAnimation{
            target: adimage
            duration: 10
            property: "opacity"
            from : 1
            to : 0
        }
        ScriptAction{
             script: {
                rectangle.visible =false
                homeloader.visible = true

             }
        }
    }
    Loader{
        id:homeloader
        anchors.fill: parent
        visible: false
        source: "qrc:/scripts/home/HomeMenu.qml"
    }

}
