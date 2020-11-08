import QtQuick 2.0

Item {
    Item {
        id: main
        width: 800
        height: 500
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        Image {
            id: bgImage
            opacity: 0.6
            fillMode: Image.Tile
            source: "qrc:/data/mapmtex.jpg"
            anchors.fill: parent
        }
        Rectangle {
            id: bgrectangle
            radius: 2
            border.width: 3
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#ccff7b25"
                }

                GradientStop {
                    position: 1
                    color: "#cc6b5b95"
                }
            }
            anchors.fill: parent
        }

        Item {
            id: titlesitem
            width: 150
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20

            Rectangle {
                id: titlesrectangle
                color: "#00000000"
                radius: 2
                border.width: 2
                anchors.fill: parent
            }

            Item {
                id: titleComponant
                height: 40
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: parent.top
                anchors.topMargin: 6

                Rectangle {
                    id: titlebgrectangle
                    radius: 7
                    gradient: Gradient {
                        GradientStop {
                            position: 0
                            color: "#622626"
                        }

                        GradientStop {
                            position: 1
                            color: "#361212"
                        }
                    }
                    border.width: 1
                    anchors.fill: parent
                }

                Text {
                    id: titletext
                    color: "#ffffff"
                    text: qsTr("Introduction")
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 12
                }

                MouseArea {
                    id: titlemouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        titlebgrectangle.gradient.stops[0].color = Qt.lighter("#622626")
                    }
                    onExited: {
                        titlebgrectangle.gradient.stops[0].color = "#622626"
                    }
                }
            }
        }

        Item {
            id: contentitem
            y: 3
            anchors.left: titlesitem.right
            anchors.leftMargin: 5
            anchors.right: parent.right
            anchors.rightMargin: 20
            Rectangle {
                id: contentrectangle
                color: "#00000000"
                radius: 2
                border.width: 2
                anchors.fill: parent
            }

            Image {
                id: image
                x: -175
                width: 200
                height: 200
                fillMode: Image.PreserveAspectCrop
                opacity: 0.9
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 10
                source: "qrc:/data/units/fighter.png"
            }

            Text {
                id: contenttitletext
                x: 40
                y: 40
                width: 167
                height: 24
                color: "#ffffff"
                text: qsTr("Fighter Unit")
                font.bold: true
                font.wordSpacing: 0.7
                lineHeight: 1.3
                font.underline: false
                anchors.top: parent.top
                anchors.topMargin: 40
                anchors.left: parent.left
                anchors.leftMargin: 40
                font.italic: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 29
            }

            Text {
                id: descriptiontext
                x: 30
                y: 230
                height: 200
                color: "#ffffff"
                text: qsTr("This unit is by far the most efficient unit in the map <br>
                            however when the enemy possese anti aircraft vheicles it may
                            be difficlet to use this unit whithout beig shot!
                            ")
                horizontalAlignment: Text.AlignLeft
                wrapMode: Text.WordWrap
                verticalAlignment: Text.AlignTop
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 30
                anchors.right: parent.right
                anchors.rightMargin: 30
                anchors.left: parent.left
                anchors.leftMargin: 30
                font.pixelSize: 15

                Rectangle {
                    id: rectangle
                    color: "#00000000"
                    radius: 10
                    border.width: 1
                    anchors.rightMargin: -10
                    anchors.leftMargin: -10
                    anchors.bottomMargin: -10
                    anchors.topMargin: -10
                    anchors.fill: parent
                }
            }
            anchors.bottom: parent.bottom
            anchors.topMargin: 20
            anchors.top: parent.top
            anchors.bottomMargin: 20
        }

    }
}
