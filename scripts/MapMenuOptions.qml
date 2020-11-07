import QtQuick 2.0

Item {
    id:root
    width: 400
    height: 480
    visible: true

    Rectangle {
        id: bg
        width: 300
        radius: 20
        clip: true
        border.width: 4
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#cc5050ce"
            }
            GradientStop {
                position: 1
                color: "#cc324348"
            }
        }
        anchors.fill: parent

        Image {
            id: image
            opacity: 0.4
            fillMode: Image.Tile
            anchors.fill: parent
            source: "qrc:/data/mapmtex.jpg"
        }
    }

    Item {
        id: closeitem
        x: 596
        width: 36
        height: 33
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 8

        Rectangle {
            id: closerectangle
            color: "#fa0a0a"
            radius: 12
            opacity: 0.7
            anchors.fill: parent
        }

        Text {
            id: closetext
            color: "#ffffff"
            text: qsTr("X")
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 17
        }

        MouseArea {
            id: closemouseArea
            hoverEnabled: true
            anchors.fill: parent
            onPressed: {
                menuOpt.hide()
            }
        }
    }

    Item {
        id: saveitem
        x: 181
        width: 277
        height: 47
        anchors.top: parent.top
        anchors.topMargin: 140
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            id: saverectangle
            radius: 5
            opacity: 0.8
            border.color: "#0a1d63"
            border.width: 3
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#cc11e9e9"
                }

                GradientStop {
                    position: 1
                    color: "#cc43475c"
                }
            }
            anchors.fill: parent
        }

        Text {
            id: savetext
            color: "#ffffff"
            text: qsTr("Save")
            font.italic: true
            font.bold: true
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 20
        }

        MouseArea {
            id: savemouseArea
            hoverEnabled: true
            anchors.fill: parent
            onEntered: saveitem.scale = 1.04
            onExited: saveitem.scale = 1
        }

    }

    Item {
        id: loaditem
        x: 189
        width: 277
        height: 47
        anchors.top: saveitem.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            id: loadrectangle
            radius: 5
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#cc11e9e9"
                }

                GradientStop {
                    position: 1
                    color: "#cc43475c"
                }
            }
            anchors.fill: parent
            border.width: 3
            border.color: "#0a1d63"
            opacity: 0.8
        }

        Text {
            id: loadtext
            color: "#ffffff"
            text: qsTr("Load")
            font.italic: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            font.pixelSize: 20
        }

        MouseArea {
            id: loadmouseArea
            hoverEnabled: true
            anchors.fill: parent
            onEntered: loaditem.scale = 1.04
            onExited: loaditem.scale = 1
        }
    }

    Item {
        id: homeitem
        x: 184
        y: -9
        width: 277
        height: 47
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: loaditem.bottom
        anchors.topMargin: 10

        Rectangle {
            id: homerectangle
            radius: 5
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#cc11e9e9"
                }

                GradientStop {
                    position: 1
                    color: "#cc43475c"
                }
            }
            anchors.fill: parent
            border.width: 3
            opacity: 0.8
            border.color: "#0a1d63"
        }

        Text {
            id: hometext
            color: "#ffffff"
            text: qsTr("Home Menu")
            font.italic: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            font.pixelSize: 20
        }

        MouseArea {
            id: homemouseArea
            hoverEnabled: true
            anchors.fill: parent
            onEntered: homeitem.scale = 1.04
            onExited: homeitem.scale = 1
        }
    }

    Item {
        id: exititem
        x: 180
        y: -1
        width: 277
        height: 47
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: homeitem.bottom
        anchors.topMargin: 10

        Rectangle {
            id: exitrectangle
            radius: 5
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#cc11e9e9"
                }

                GradientStop {
                    position: 1
                    color: "#cc43475c"
                }
            }
            anchors.fill: parent
            border.width: 3
            border.color: "#0a1d63"
            opacity: 0.8
        }

        Text {
            id: exittext
            color: "#ffffff"
            text: qsTr("Exit")
            font.italic: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            font.pixelSize: 20
        }

        MouseArea {
            id: exitmouseArea
            hoverEnabled: true
            anchors.fill: parent
            onEntered: exititem.scale = 1.04
            onExited: exititem.scale = 1
        }
    }
}
