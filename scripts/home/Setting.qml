import QtQuick 2.0
import QtQuick.Controls 2.0
Item {
    Item {
        id: main
        width: 600
        height: 500
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        Image {
            id: bgImage
            opacity: 0.6
            fillMode: Image.Tile
            source: "qrc:/data/mapmtex.jpg"
            anchors.fill: parent
            visible: false
        }
        Rectangle {
            id: bgrectangle
            width: 600
            radius: 2
            border.width: 3
            gradient: Gradient {
                GradientStop {
                    position: 1
                    color: "#cc222222"
                }

                GradientStop {
                    position: 0
                    color: "#cc555555"
                }
            }
            anchors.fill: parent
        }

        Item {
            id: graphicsitem
            height: 200
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 20

            Rectangle {
                id: graphicstitlerectangle
                x: -20
                y: -20
                color: "#0f0c0c"
                radius: 2
                border.width: 0
                border.color: "#ffffff"
                anchors.fill: graphicstext
            }

            Text {
                id: graphicstext
                x: 0
                y: 0
                width: 100
                height: 40
                color: "#ffffff"
                text: qsTr("Graphics")
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 15
            }

            Item {
                id: graphicscontentitem
                height: 200
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.top: graphicstitlerectangle.bottom
                anchors.topMargin: 1

                Rectangle {
                    id: gcrectangle
                    color: "#00000000"
                    border.width: 2
                    anchors.fill: parent
                }

                CheckBox {
                    id: checkBox
                    x: 155
                    width: 173
                    height: 40
                    text: qsTr("Antialiasing")
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 10
                    font.bold: true
                    font.pointSize: 11
                    checkState: Qt.Checked
                }
            }



        }
    }
}
