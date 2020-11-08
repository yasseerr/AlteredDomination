import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    id: root
    visible: true
    FontLoader{
        id:buttonFont
        source: "qrc:/data/fonts/Coalition_v2..ttf"
    }
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
            radius: 5
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

            Text {
                id: statusText
                x: 289
                y: 304
                color: "#e7e8ea"
                text: qsTr("")
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 17
            }
        }

        Image {
            id: versusimage
            x:270
            width: 60
            height: 60
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 30
            source: "qrc:/data/icons/versus.png"
        }

        Item {
            id: thisplayerItem
            width: 250
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.left: parent.left
            anchors.leftMargin: 20

            Rectangle {
                id: thisrectangle
                width: 150
                color: "#00000000"
                radius: 1
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottomMargin: 60
                border.width: 2
            }

            Text {
                id: thisplayertext
                x: -8
                y: 30
                color: "#ffffff"
                text: qsTr("ThisPlayerText")
                font.underline: true
                horizontalAlignment: Text.AlignHCenter
                anchors.top: parent.top
                anchors.topMargin: 30
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 18
                font.family: buttonFont.name
            }

            ComboBox {
                property var tmp: []
                id: countrycomboBox
                x: 25
                y: 83
                width: 150
                height: 40
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: thisplayertext.bottom
                anchors.topMargin: 50
                editable: false
                flat: false
                displayText: "Country : "+currentText
                textRole: ""
//                model: ["Algeria","Tunisia","Lybia"]
                Component.onCompleted: {
                    for(var i =0 ;i<mapFile.length ;i++){
                        countrycomboBox.tmp.push(mapFile[i].name)
                    }
                    model = tmp
                }
                popup.height: 400
            }

            ComboBox {
                id: fundscomboBox
                x: 19
                y: 85
                width: 150
                height: 40
                currentIndex: 2
                displayText: "funds : "+currentText
                anchors.topMargin: 30
                textRole: ""
                editable: false
                anchors.top: countrycomboBox.bottom
                model: [100,300,500,1000,2000]
                anchors.horizontalCenter: parent.horizontalCenter
                flat: false
            }


        }
        Item {
            id: otherplayerItem
            width: 250
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.right : parent.right
            anchors.rightMargin: 20

            Rectangle {
                id: otherrectangle
                width: 150
                color: "#00000000"
                radius: 1
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottomMargin: 60
                border.width: 2
            }

            Text {
                id: otherplayertext
                x: -8
                y: 30
                color: "#ffffff"
                text: qsTr("otherPlayerText")
                font.underline: true
                horizontalAlignment: Text.AlignHCenter
                anchors.top: parent.top
                anchors.topMargin: 30
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 18
                font.family: buttonFont.name
            }

            ComboBox {
                id: othercountrycomboBox
                x: 25
                y: 83
                width: 150
                height: 40
                currentIndex: -1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: otherplayertext.bottom
                anchors.topMargin: 50
                editable: false
                flat: false
                displayText: "Country : "+currentText
                textRole: ""
                model: ["Algeria","Tunisia","Lybia"]
            }

            ComboBox {
                id: otherfundscomboBox
                x: 19
                y: 85
                width: 150
                height: 40
                currentIndex: -1
                displayText: "funds : "+currentText
                anchors.topMargin: 30
                textRole: ""
                editable: false
                anchors.top: othercountrycomboBox.bottom
                model: [100,300,500,1000,2000]
                anchors.horizontalCenter: parent.horizontalCenter
                flat: false
            }

        }

        Item {
            id: findOpponantItem
            width: 120
            height: 40
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.bottomMargin: 10
            anchors.rightMargin: 20
            Rectangle {
                id: findrectangle
                width: 70
                anchors.fill: parent
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "#405d27"
                    }

                    GradientStop {
                        position: 1
                        color: "#82b74b"
                    }
                }
                radius: 4
                border.width: 2
            }

            Text {
                id: findtext
                text: qsTr("Find Opponant")
                font.bold: true
                font.pixelSize: 13
                anchors.centerIn: parent
                color: "#ffffff"
            }

            MouseArea {
                id: findmouseArea
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    findrectangle.gradient.stops[0].color = Qt.lighter("#405d27")

                }
                onExited: {
                    findrectangle.gradient.stops[0].color = "#405d27"
                }
                onClicked: {
                    busyIndicator.running = true
                    homeClass.entermatchmaking(createiptext.text,joiniptext.text,countrycomboBox.currentText)
                }
            }

        }

        Item {
            id: createItem
            x: 326
            y: 350
            width: 70
            height: 40
            anchors.rightMargin: 10
            anchors.bottom: parent.bottom
            anchors.right: findOpponantItem.left
            Rectangle {
                id: createrectangle
                width: 90
                radius: 5
                anchors.fill: parent
                border.width: 2
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "#f64f20"
                    }

                    GradientStop {
                        position: 1
                        color: "#deb397"
                    }
                }
            }

            Text {
                id: createtext
                color: "#ffffff"
                text: qsTr("create")
                anchors.centerIn: parent
                font.pixelSize: 13
                font.bold: true
            }

            MouseArea {
                id: createmouseArea
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    createrectangle.gradient.stops[0].color = Qt.lighter("#f64f20")

                }
                onExited: {
                    createrectangle.gradient.stops[0].color = "#f64f20"
                }

            }
            anchors.bottomMargin: 10
        }

        Item {
            id: createipItem
            x: 300
            y: 350
            width: 120
            height: 40
            anchors.rightMargin: 10
            anchors.bottom: parent.bottom
            anchors.right: createItem.left
//            Rectangle {
//                id: createiprectangle
//                width: 120
//                color: "#00000000"
//                radius: 1
//                anchors.fill: parent
//                border.width: 2
//            }

            TextField {
                id: createiptext
                color: "#ffffff"
                text: qsTr("192.168.1.1")
                anchors.centerIn: parent
                anchors.fill: parent
                font.pixelSize: 13
                font.bold: false
                placeholderText: "ip"
                background: Rectangle {
                    color: "#00000000"
                    radius: 1
                    anchors.fill: parent
                    border.width: 2
                }
            }
            anchors.bottomMargin: 10
        }

        Item {
            id: joinItem
            x: 174
            y: 350
            width: 70
            height: 40
            anchors.rightMargin: 10
            anchors.bottom: parent.bottom
            anchors.right: createipItem.left
            Rectangle {
                id: joinrectangle
                width: 90
                radius: 5
                anchors.fill: parent
                border.width: 2
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "#0928bf"
                    }

                    GradientStop {
                        position: 1
                        color: "#7a81bc"
                    }
                }
            }

            Text {
                id: jointext
                color: "#ffffff"
                text: qsTr("join")
                anchors.centerIn: parent
                font.pixelSize: 13
                font.bold: true
            }

            MouseArea {
                id: joinmouseArea
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    joinrectangle.gradient.stops[0].color = Qt.lighter("#0928bf")

                }
                onExited: {
                    joinrectangle.gradient.stops[0].color = "#0928bf"
                }
            }
            anchors.bottomMargin: 10
        }

        TextField {
            id: joiniptext
            x: 48
            y: 350
            width: 120
            height: 40
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.right: joinItem.left
            anchors.rightMargin: 10
            text: qsTr("213.154.12.5")
            color: "#ffffff"
            placeholderText: "ip of the opponant"
            background: Rectangle {
                color: "#00000000"
                radius: 1
                anchors.fill: parent
                border.width: 2
            }
        }
        BusyIndicator {
            id: busyIndicator
            running: false
            anchors.centerIn: parent
        }
    }


}
