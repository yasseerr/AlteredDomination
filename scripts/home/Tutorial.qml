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
            visible: false
        }
        Rectangle {
            id: bgrectangle
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

            Flickable {
                id: componantflickable
                clip: true
                anchors.fill: parent
                contentHeight: titlesflow.height
                contentWidth: 150
                Flow {
                    id: titlesflow
                    width: 141
                    height: childrenRect.height
                    anchors.top: parent.top
                    anchors.topMargin: 5
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 2


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
                id: rectangle
                x: 20
                y: 224
                height: 213
                color: "#00000000"
                radius: 10
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                border.width: 1
                anchors.rightMargin: 24
                anchors.leftMargin: 19
                anchors.bottomMargin: 23
            }

            Rectangle {
                id: contentrectangle
                color: "#00000000"
                radius: 2
                border.width: 2
                anchors.fill: parent
            }

            Image {
                id: image2
                x: 203
                y: -7
                width: 205
                height: 183
                anchors.top: parent.top
                fillMode: Image.Stretch
                source: "qrc:/data/units/movements/soldier.svg"
                opacity: 0.9
                anchors.right: parent.right
                anchors.rightMargin: 197
                anchors.topMargin: 40
            }

            Image {
                id: image1
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


            Flickable {
                id: flickable
                y: 224
                height: 206
                flickableDirection: Flickable.VerticalFlick
                clip: true
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 30
                anchors.left: parent.left
                anchors.leftMargin: 30
                anchors.right: parent.right
                anchors.rightMargin: 30
                contentHeight: descriptiontext.height
                contentWidth: 545
                Text {
                    id: descriptiontext
                    x: 0
                    y: 6
                    width: 545
                    height: descriptiontext.contentHeight
                    color: "#ffffff"
                    text: qsTr("\t hello and welcome! in <strong> Altered Domination </strong> the game every concept is new  <br/>
                           in this game you will live the beauty of strategy games and bored games <br/>
                           first of all you need to read the tutorial , so that you can understand how the game works and
                           by consulting the modes of the the game : <br/>
                           \t \t - solo mode<br/>
                           \t \t - multiplayer mode <br/>
                           and then understanding the battle board and see how units behaive on it")
                    horizontalAlignment: Text.AlignLeft
                    wrapMode: Text.WordWrap
                    verticalAlignment: Text.AlignTop
                    font.pixelSize: 15
                }
            }

            Item {
                id: scaleitem
                x: 32
                width: 165
                height: 119
                visible: false
                anchors.top: contenttitletext.bottom
                anchors.topMargin: 37

                Rectangle {
                    id: attackrectangle
                    width: 10
                    height: 10
                    color: "#ff0000"
                    radius: 1
                    border.width: 1
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    anchors.top: parent.top
                    anchors.topMargin: 5
                }

                Text {
                    id: atext
                    color: "#ffffff"
                    text: qsTr("Attack")
                    anchors.verticalCenter: attackrectangle.verticalCenter
                    anchors.left: attackrectangle.right
                    anchors.leftMargin: 5
                    font.pixelSize: 11
                }

                Rectangle {
                    id: moverectangle
                    x: -9
                    y: -9
                    width: 10
                    height: 10
                    color: "#23ce49"
                    radius: 1
                    anchors.top: attackrectangle.bottom
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    anchors.topMargin: 5
                    border.width: 1
                }

                Text {
                    id: mtext
                    x: -9
                    y: -9
                    color: "#ffffff"
                    text: qsTr("Move")
                    font.pixelSize: 11
                    anchors.left: moverectangle.right
                    anchors.verticalCenter: moverectangle.verticalCenter
                    anchors.leftMargin: 5
                }

                Rectangle {
                    id: amrectangle
                    x: -7
                    y: -7
                    width: 10
                    height: 10
                    color: "#ffcc00"
                    radius: 1
                    anchors.top: moverectangle.bottom
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    anchors.topMargin: 5
                    border.width: 1
                }

                Text {
                    id: amtext
                    x: -7
                    y: -7
                    color: "#ffffff"
                    text: qsTr("Attack/Move")
                    font.pixelSize: 11
                    anchors.left: amrectangle.right
                    anchors.verticalCenter: amrectangle.verticalCenter
                    anchors.leftMargin: 5
                }
            }


            anchors.bottom: parent.bottom
            anchors.topMargin: 20
            anchors.top: parent.top
            anchors.bottomMargin: 20
        }

    }

    Component{
        id:titleGenerator
        Item {
            property string titletextpar: ""
            property var cnt: null
            id: titleComponant
            height: 40
            width: 140
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
                text: titleComponant.titletextpar
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
                onClicked: {
                    descriptiontext.text = titleComponant.cnt.text
                    contenttitletext.text = titleComponant.cnt.title
                    image1.source = titleComponant.cnt.src1
                    image2.source = titleComponant.cnt.src2
                    scaleitem.visible = titleComponant.cnt.colorindex

                }
            }
        }
    }

    Component.onCompleted: {
        for(var i =0 ;i< tutoFile.length;i++){
            var o = tutoFile[i]
            var cr = titleGenerator.createObject(titlesflow);
            cr.titletextpar = o.name
            cr.cnt = o
        }
    }
}
