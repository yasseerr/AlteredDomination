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
        opacity: 1
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#6b5b95"
            }

            GradientStop {
                position: 1
                color: "#b3d64161"
            }
        }
        anchors.fill: parent
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
        anchors.topMargin: 100
        visible: true
        font.family: titleFont.name
        font.pixelSize: 30


    }

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
        id: newGameItem
        width: 120
        height: 51
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: continueItem.bottom
        anchors.topMargin: 10

        Rectangle {
            id: newGamerectangle
            visible: false
            color: "#00000000"
            border.width: 3
            border.color: "#43024f"
            anchors.fill: parent
        }

        Image {
            id: newGameImage
            visible: true
            anchors.fill: parent
            source: "qrc:/data/icons/metalsign.png"
        }

        DropShadow{
            height: 50
            color: "#000000"
            anchors.fill: newGameImage
            radius: 8
            horizontalOffset: 8
            samples: 17
            verticalOffset: 8
            source: newGameImage
        }

        Text {
            id: newgametext
            color: "#000000"
            text: qsTr("New Game")
            font.italic: true
            font.bold: false
            font.pixelSize: 15
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.family: buttonFont.name
        }

        MouseArea {
            id: mouseArea
            hoverEnabled: true
            anchors.fill: parent
            onEntered: {
                hoverAudio.play()
                parent.scale = 1.05
            }
            onExited: {
                hoverAudio.stop()
                parent.scale = 1
            }
            onClicked: {
                mainloader.source = "qrc:/scripts/home/NewGame.qml"
            }
        }

    }

    Item {
        id: loadGameItem
        x: -5
        y: -9
        width: 120
        height: 51
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.left: parent.left
        Rectangle {
            id: loadrectangle
            color: "#00000000"
            anchors.fill: parent
            border.width: 3
            border.color: "#43024f"
            visible: false
        }

        Image {
            id: loadGameImage
            anchors.fill: parent
            source: "qrc:/data/icons/metalsign.png"
            visible: true
        }

        DropShadow {
            height: 50
            color: "#000000"
            radius: 8
            anchors.fill:loadGameImage
            source: loadGameImage
            horizontalOffset: 8
            samples: 17
            verticalOffset: 8
        }

        Text {
            id: loadgametext
            color: "#000000"
            text: qsTr("Load Game")
            font.family: buttonFont.name
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.italic: true
            font.pixelSize: 15
            anchors.verticalCenter: parent.verticalCenter
            font.bold: false
            verticalAlignment: Text.AlignVCenter
        }

        MouseArea {
            id: loadmouseArea
            hoverEnabled: true
            anchors.fill: parent
            onEntered: {
                hoverAudio.play()
                parent.scale = 1.05
            }
            onExited: {
                hoverAudio.stop()
                parent.scale = 1
            }
            onClicked: {
                mainloader.source = "qrc:/scripts/home/LoadGame.qml"
            }
        }
        anchors.top: newGameItem.bottom
        anchors.leftMargin: 10
        anchors.rightMargin: 10
    }

    Item {
        id: multiplayerItem
        x: 0
        y: -2
        width: 120
        height: 51
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.left: parent.left
        Rectangle {
            id: multiplayerrectangle
            color: "#00000000"
            anchors.fill: parent
            border.width: 3
            border.color: "#43024f"
            visible: false
        }

        Image {
            id: multiplayerImage
            anchors.fill: parent
            source: "qrc:/data/icons/metalsign.png"
            visible: true
        }

        DropShadow {
            height: 50
            color: "#000000"
            radius: 8
            anchors.fill: multiplayerImage
            source: multiplayerImage
            horizontalOffset: 8
            samples: 17
            verticalOffset: 8
        }

        Text {
            id: multiplayertext
            color: "#000000"
            text: qsTr("Multiplayer")
            font.family: buttonFont.name
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.italic: true
            font.pixelSize: 15
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            font.bold: false
        }

        MouseArea {
            id: multiplayermouseArea
            hoverEnabled: true
            anchors.fill: parent
            onEntered: {
                hoverAudio.play()
                parent.scale = 1.05
            }
            onExited: {
                hoverAudio.stop()
                parent.scale = 1
            }
            onClicked: {
                mainloader.source = "qrc:/scripts/home/Multiplayer.qml"
            }

        }
        anchors.top: loadGameItem.bottom
        anchors.leftMargin: 10
        anchors.rightMargin: 10
    }

    Item {
        id: tutorialItem
        x: 3
        y: -3
        width: 120
        height: 51
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.left: parent.left
        Rectangle {
            id: tutorialrectangle
            color: "#00000000"
            anchors.fill: parent
            border.width: 3
            border.color: "#43024f"
            visible: false
        }

        Image {
            id: tutorialImage
            anchors.fill: parent
            source: "qrc:/data/icons/metalsign.png"
            visible: true
        }

        DropShadow {
            height: 50
            color: "#000000"
            radius: 8
            anchors.fill: tutorialImage
            source: tutorialImage
            horizontalOffset: 8
            samples: 17
            verticalOffset: 8
        }

        Text {
            id: tutorialtext
            color: "#000000"
            text: qsTr("Tutorial")
            font.family: buttonFont.name
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.italic: true
            font.pixelSize: 15
            anchors.verticalCenter: parent.verticalCenter
            font.bold: false
            verticalAlignment: Text.AlignVCenter
        }

        MouseArea {
            id: tutorialmouseArea
            hoverEnabled: true
            anchors.fill: parent
            onEntered: {
                hoverAudio.play()
                parent.scale = 1.05
            }
            onExited: {
                hoverAudio.stop()
                parent.scale = 1
            }
            onClicked: {
                mainloader.source = "qrc:/scripts/home/Tutorial.qml"
            }
        }
        anchors.top: multiplayerItem.bottom
        anchors.leftMargin: 10
        anchors.rightMargin: 10
    }


    Item {
        id: settingItem
        x: 11
        y: -4
        width: 120
        height: 51
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.left: parent.left
        Rectangle {
            id: settingrectangle
            color: "#00000000"
            anchors.fill: parent
            border.width: 3
            border.color: "#43024f"
            visible: false
        }

        Image {
            id: settingImage
            anchors.fill: parent
            source: "qrc:/data/icons/metalsign.png"
            visible: true
        }

        DropShadow {
            height: 50
            color: "#000000"
            radius: 8
            anchors.fill: settingImage
            source: settingImage
            horizontalOffset: 8
            samples: 17
            verticalOffset: 8
        }

        Text {
            id: settingtext
            color: "#000000"
            text: qsTr("Setting")
            font.family: buttonFont.name
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.italic: true
            font.pixelSize: 15
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            font.bold: false
        }

        MouseArea {
            id: settingmouseArea
            hoverEnabled: true
            anchors.fill: parent
            onEntered: {
                hoverAudio.play()
                parent.scale = 1.05
            }
            onExited: {
                hoverAudio.stop()
                parent.scale = 1
            }
            onClicked: {
                mainloader.source = "qrc:/scripts/home/Setting.qml"
            }
        }
        anchors.top: tutorialItem.bottom
        anchors.leftMargin: 10
        anchors.rightMargin: 10
    }

    Item {
        id: exitItem
        x: 4
        y: -7
        width: 120
        height: 51
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.left: parent.left
        Rectangle {
            id: exitrectangle
            color: "#00000000"
            anchors.fill: parent
            border.width: 3
            border.color: "#43024f"
            visible: false
        }

        Image {
            id: exitImage
            anchors.fill: parent
            source: "qrc:/data/icons/metalsign.png"
            visible: true
        }
        DropShadow {
            height: 50
            color: "#000000"
            radius: 8
            anchors.fill: exitImage
            source: exitImage
            horizontalOffset: 8
            samples: 17
            verticalOffset: 8
        }

        Text {
            id: exittext
            color: "#000000"
            text: qsTr("Exit")
            font.family: buttonFont.name
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.italic: true
            font.pixelSize: 15
            anchors.verticalCenter: parent.verticalCenter
            font.bold: false
            verticalAlignment: Text.AlignVCenter
        }

        MouseArea {
            id: exitmouseArea
            hoverEnabled: true
            anchors.fill: parent
            onEntered: {
                hoverAudio.play()
                parent.scale = 1.05
            }
            onExited: {
                hoverAudio.stop()
                parent.scale = 1
            }
            onClicked: {
                homeClass.quitApp();
            }
        }
        anchors.top: settingItem.bottom
        anchors.leftMargin: 10
        anchors.rightMargin: 10
    }

    Item {
        id: continueItem
        x: -6
        y: -9
        width: 120
        height: 51
        anchors.top: title.bottom
        anchors.topMargin: 220
        Rectangle {
            id: continuerectangle
            color: "#00000000"
            visible: false
            anchors.fill: parent
            border.width: 3
            border.color: "#43024f"
        }

        Image {
            id: continueImage
            source: "qrc:/data/icons/metalsign.png"
            visible: true
            anchors.fill: parent
        }

        DropShadow {
            height: 50
            color: "#000000"
            radius: 8
            source: continueImage
            anchors.fill: continueImage
            horizontalOffset: 8
            samples: 17
            verticalOffset: 8
        }

        Text {
            id: continuetext
            color: "#000000"
            text: qsTr("Continue")
            font.family: buttonFont.name
            font.bold: false
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            font.italic: true
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 15
            anchors.horizontalCenter: parent.horizontalCenter
        }

        MouseArea {
            id: continuemouseArea
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                hoverAudio.play()
                parent.scale = 1.05
            }
            onExited: {
                hoverAudio.stop()
                parent.scale = 1
            }
            onClicked: {
                var o = savesFile[0]
                homeClass.loadGame(o.country,o.turn,JSON.stringify(o))
            }
        }
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.rightMargin: 10
        anchors.leftMargin: 10
    }


}
