import QtQuick 2.0
import QtGraphicalEffects 1.0
import QtMultimedia 5.0


Item {
    id:root
    width: 200
    height: 600
    visible: true
    property int frame: 0
    //    property var mainloader: null
    Rectangle {
        id: rectangle
        border.color: "#0ab2c7"
        border.width: 1
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#000000"
            }

            GradientStop {
                position: 1
                color: "#80555555"
            }

        }
        opacity: 1
        anchors.fill: parent
    }
    DropShadow {
        height: parent.height
        color: "#77000000"
        radius: 8
        anchors.fill:rectangle
        source: rectangle
        horizontalOffset: 8
        samples: 17
        verticalOffset: 8
    }

    //    Image {
    //        id: earthimage
    //        width: 475
    //        height: 260
    //        anchors.horizontalCenter: parent.horizontalCenter
    //        source: "qrc:/data/animations/EarthRotation/"+frame+".png"

    //    }

    //    NumberAnimation {
    //        target: root
    //        property: "frame"
    //        duration: 2000
    //        from: 0
    //        to:17
    //        easing.type: Easing.Linear
    //        loops: NumberAnimation.Infinite
    //        running: true
    //    }


    Text {
        id: title
        width: 100
        color: "#feb236"
        text: "ALTERED DOMINATION"
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
        anchors.right: parent.right
        anchors.rightMargin: 50
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.top: parent.top
        anchors.topMargin: 99
        visible: true
        font.family: titleFont.name
        font.pixelSize: 30


    }



    FontLoader{
        id:titleFont
        source: "qrc:/data/fonts/DESTROY_.ttf"
    }
    FontLoader{
        id:buttonFont
        source: "qrc:/data/fonts/Coalition_v2..ttf"
    }
    Audio{
        id:hoverAudio
        source: "qrc:/data/sounds/hover.wav"
    }
    Item {
        id: buttonsitem
        width: 200
        height: parent.height/3
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: parent.height/6
        Rectangle {
            id: linkrectangle
            color: "#00000000"
            border.color: "#000000"
            anchors.right: parent.right
            anchors.rightMargin: 30
            anchors.left: parent.left
            anchors.leftMargin: 30
            anchors.bottom: exitItem.bottom
            anchors.bottomMargin: 10
            anchors.top: continueItem.top
            anchors.topMargin: 10
            border.width: 9
        }

        HomeButton{
            id: continueItem
            x: 0
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            btntext: "Continue"
            isTop: true
            btnOnClick:function(){
                bgAmbiant.stop()
                battleAmbiant.stop()
                var o = savesFile[0]
                homeClass.loadGame(o.country,o.turn,JSON.stringify(o))
            }
        }

        HomeButton{
            id: newgameItem
            x: 0
            btntext: "New Game"
            isTop: false
            anchors.top : continueItem.bottom
            anchors.topMargin: 10
            btnOnClick:function(){
                mainloader.source = "qrc:/scripts/home/NewGame.qml"
            }
        }

        HomeButton{
            id: loadgameItem
            x: 0
            y: -137
            btntext: "Load Game"
            isTop: false
            anchors.top : newgameItem.bottom
            anchors.topMargin: 10
            btnOnClick:function(){
                mainloader.source = "qrc:/scripts/home/LoadGame.qml"
            }
        }

        HomeButton{
            id: multiplayerItem
            x: 0
            y: -52
            btntext: "Multiplayer"
            isTop: false
            anchors.top : loadgameItem.bottom
            anchors.topMargin: 10
            btnOnClick:function(){
                mainloader.source = "qrc:/scripts/home/Multiplayer.qml"
            }
        }

        HomeButton{
            id: tutorialItem
            x: 0
            y: 33
            btntext: "Tutorial"
            isTop: false
            anchors.top : multiplayerItem.bottom
            anchors.topMargin: 10
            btnOnClick:function(){
                mainloader.source = "qrc:/scripts/home/Tutorial.qml"
            }
        }

        HomeButton{
            id: settingItem
            x: 0
            y: 118
            btntext: "Setting"
            isTop: false
            anchors.top : tutorialItem.bottom
            anchors.topMargin: 10
            btnOnClick:function(){
                mainloader.source = "qrc:/scripts/home/Setting.qml"
            }
        }

        HomeButton{
            id: exitItem
            x: 0
            y: 203
            btntext: "Exit"
            isTop: false
            anchors.top : settingItem.bottom
            anchors.topMargin: 10
            btnOnClick:function(){
                homeClass.quitApp();
            }
        }
    }

}
