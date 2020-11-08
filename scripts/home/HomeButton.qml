import QtQuick 2.0

Item {
    id:root
    property string btntext: ""
    property bool isTop: false
    property var btnOnClick: function(){

    }
    x: -6
    y: -9
    width: 120
    height: 51
    anchors.right: parent.right
    anchors.left: parent.left
    anchors.rightMargin: 0
    anchors.leftMargin: 0
    anchors.bottom: root.isTop?parent.bottom:null
    anchors.bottomMargin: root.isTop?450:0
    Rectangle {
        id: btnrectangle
        opacity: 0.8
        gradient: Gradient {
            GradientStop {
                position: 0
                color: btnmouseArea.containsMouse?Qt.lighter("#222222"):"#00000"
            }

            GradientStop {
                position: 1
                color: "#222222"
            }
        }
        visible: true
        anchors.fill: parent
        border.width: 0
        border.color: "#ffffff"
    }

    Image {
        id: btnImage
        antialiasing: true
        source: "qrc:/data/icons/homebutton.svg"
        visible: true
        anchors.fill: parent
    }

    Image {
        id: btnImagerotate
        x: 8
        y: 5
        width: 30
        height: 30
        antialiasing: true
        source: "qrc:/data/icons/homebuttonrotate.svg"
        visible: true
        rotation: 0

        NumberAnimation {
            target: btnImagerotate
            property: "rotation"
            duration: 600
            easing.type: Easing.InOutQuad
            from: 0
            to:-360
            running: btnmouseArea.containsMouse
            loops: NumberAnimation.Infinite
        }


    }

    Text {
        id: btntextDisp
        color: "#ffffff"
        text: qsTr(root.btntext)
        anchors.verticalCenterOffset: -12
        anchors.horizontalCenterOffset: 21
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
        id: btnmouseArea
        anchors.fill: parent
        rotation: 0
        transformOrigin: Item.Top
        hoverEnabled: true
        onEntered: {
            hoverAudio.play()
            btntextDisp.scale = 1.05
        }
        onExited: {
            hoverAudio.stop()
            btntextDisp.scale = 1
        }
        onClicked:{

            root.btnOnClick()
        }

            /*{
            bgAmbiant.stop()
            battleAmbiant.stop()
            var o = savesFile[0]
            homeClass.loadGame(o.country,o.turn,JSON.stringify(o))
        }*/
    }

}


