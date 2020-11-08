import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    id: root
    visible: true
    Item {
        id: main
        width: 400
        height: 401
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
            id: uiItem
            width: 160
            height: 200
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            TextField {
                id: textField
    //            x: 229
    //            y: 114
                width: 150
                height: 40
                text: qsTr("")
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 0
                anchors.top : parent.top

    //            anchors.verticalCenter: parent.verticalCenter
                font.pointSize: 9
                placeholderText: "Player Name"
                horizontalAlignment: Text.AlignHCenter
                background: Rectangle{
                    color: "#00000000"
                    radius: 5
                    border.width: 2

                }
            }
            ComboBox {
                id: countrycomboBox
                property var tmp: []
    //            x: 245
                width: 150
                height: 40
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: textField.bottom
    //            anchors.verticalCenter: parent.verticalCenter
                anchors.topMargin: 30
                editable: false
                flat: false
                displayText: "Country :"+currentText
                textRole: ""
                model: tmp
                popup.height: 400
                Component.onCompleted: {
                    for(var i =0 ;i< mapFile.length;i++){
                        countrycomboBox.tmp.push(mapFile[i].name)

                    }
                    model = tmp
                    countrycomboBox.currentIndex = Math.random() * tmp.length
                }
            }

            ComboBox {
                id: modecomboBox
    //            x: 245
    //            y: 9
                width: 150
                height: 40
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 30
                displayText: "Mode : "+currentText
                flat: false
                anchors.top: countrycomboBox.bottom
    //            anchors.verticalCenter: parent.verticalCenter
                textRole: ""
                editable: false
                model: ["GDP","CityCount"]

            }

            Item {
                id: startitem
                x : 30
                width: 104
                height: 45
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: modecomboBox.bottom
                anchors.topMargin: 30
                //            anchors.verticalCenter: parent.verticalCenter

                Rectangle {
                    id: startbgrectangle
                    radius: 8
                    gradient: Gradient {
                        GradientStop {
                            position: 0
                            color: "#ccf30c0c"
                        }

                        GradientStop {
                            position: 1
                            color: "#cc3a0505"
                        }
                    }
                    border.width: 2
                    anchors.fill: parent
                }

                Text {
                    id: text1
                    color: "#e7e2e2"
                    text: qsTr("Start")
                    font.bold: true
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 16
                }

                MouseArea {
                    id: mouseArea
                    hoverEnabled: true
                    anchors.fill: parent
                    onEntered: {
                        startbgrectangle.gradient.stops[0].color = Qt.lighter("#ccf30c0c")


                    }
                    onExited: {
                        startbgrectangle.gradient.stops[0].color = "#ccf30c0c"
                    }
                    onClicked: {
//                        loaderFrame.visible = true
                        bgAmbiant.stop()
                        battleAmbiant.stop()
                        homeClass.startGame(countrycomboBox.currentText,modecomboBox.currentIndex)
                    }
                }
            }

        }
    }

}
