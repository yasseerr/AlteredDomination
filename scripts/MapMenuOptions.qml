import QtQuick 2.0

Item {
    id:root
    width: 400
    height: 480
    visible: true

    Image {
        id: image
        opacity: 0.7
        fillMode: Image.Tile
        anchors.fill: parent
        source: "qrc:/data/mapmtex.jpg"
    }

    Rectangle {
        id: bg
        width: 300
        radius: 20
        opacity: 1
        clip: true
        border.width: 4
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
            border.color: "#ffffff"
            border.width: 3
            gradient: Gradient {
                GradientStop {
                    position: 1
                    color: savemouseArea.containsMouse?"#cc80c4c8":"#cc222222";
                }

                GradientStop {
                    position: 0
                    color: "#cc555555"
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
            onClicked: {
                mapView.saveGame()
                menuOpt.hide()
            }
        }

    }

    Item {
        id: settingitem
        x: 189
        width: 277
        height: 47
        anchors.top: saveitem.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            id: settingrectangle
            radius: 5
            gradient: Gradient {
                GradientStop {
                    position: 1
                    color: settingmouseArea.containsMouse?"#cc80c4c8":"#cc222222";
                }

                GradientStop {
                    position: 0
                    color: "#cc555555"
                }
            }
            anchors.fill: parent
            border.width: 3
            border.color: "#ffffff"
            opacity: 0.8
        }

        Text {
            id: settingtext
            color: "#ffffff"
            text: qsTr("Setting")
            font.italic: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.bold: true
            font.pixelSize: 20
        }

        MouseArea {
            id: settingmouseArea
            hoverEnabled: true
            anchors.fill: parent
            onEntered: settingitem.scale = 1.04
            onExited: settingitem.scale = 1
        }
    }

    Item {
        id: homeitem
        x: 184
        y: -9
        width: 277
        height: 47
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: settingitem.bottom
        anchors.topMargin: 10

        Rectangle {
            id: homerectangle
            radius: 5
            gradient: Gradient {
                GradientStop {
                    position: 1
                    color: homemouseArea.containsMouse?"#cc80c4c8":"#cc222222";
                }

                GradientStop {
                    position: 0
                    color: "#cc555555"
                }
            }
            anchors.fill: parent
            border.width: 3
            opacity: 0.8
            border.color: "#ffffff"
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
            onClicked: {
                menuOpt.hide()
                mapView.returnHome()
            }
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
                    position: 1
                    color: exitmouseArea.containsMouse?"#cc80c4c8":"#cc222222";
                }

                GradientStop {
                    position: 0
                    color: "#cc555555"
                }
            }
            anchors.fill: parent
            border.width: 3
            border.color: "#ffffff"
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
            onClicked: mapView.quitGame()
        }
    }

}
