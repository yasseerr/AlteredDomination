import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    id: root
    visible: true
    Item {
        id: main
        width: 400
        height: 401
        clip: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        Rectangle {
            id: bgrectangle
            radius: 17
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

        Flickable {
            id: savesflickable
            anchors.bottomMargin: 10
            anchors.topMargin: 10
            anchors.rightMargin: 30
            anchors.leftMargin: 30
            contentHeight: savesflow.height
            contentWidth: this.width
            boundsBehavior: Flickable.StopAtBounds
            flickableDirection: Flickable.VerticalFlick
            clip: false
            anchors.fill: parent

            Flow {
                id: savesflow
                height: childrenRect.height
                spacing: 3
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
            }

        }

    }


    Component.onCompleted: {
        for(var i =0 ;i< savesFile.length;i++){
            var o = savesFile[i]
            var cr = gamesaveComponant.createObject(savesflow);
            cr.gameSave = o
            cr.saveId = i
        }
    }


    Component{
        id: gamesaveComponant
        Item {
            id: root2
            property var gameSave: null
            property int saveId: 0
            height: 100
            width: 340
            Rectangle {
                id: gameSaverectangle
                radius: 8
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "#e6681717"
                    }

                    GradientStop {
                        position: 1
                        color: "#1c1111"
                    }
                }
                anchors.fill: parent
            }

            Rectangle {
                id: line1
                x: 80
                y: 35
                width: 200
                height: 3
                anchors.horizontalCenter: parent.horizontalCenter
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "#ffffff"
                    }

                    GradientStop {
                        position: 1
                        color: "#000000"
                    }
                }
            }

            Image {
                id: flagimage
                width: 65
                height: 37
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: parent.top
                anchors.topMargin: 5
                source: "qrc:/data/flags/"+root2.gameSave.flag+".png"
            }
            Text {
                id: countrytext
                color: "#ffffff"
                text: ""+root2.gameSave.country+(root2.saveId==0?" -autosave- ":"")
                anchors.top: parent.top
                anchors.topMargin: 5
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 20
            }

            Text {
                id: turntext
                color: "#1cc842"
                text: "turn : "+root2.gameSave.turn
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                font.pixelSize: 16
            }

            Text {
                id: datetext
                color: "#e0e76b"
                text: root2.gameSave.date
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 17
            }

            MouseArea {
                id: gameSavemouseArea
                hoverEnabled: true
                anchors.fill: parent
                onEntered: {
                    gameSaverectangle.gradient.stops[0].color = Qt.lighter("#e6681717")

                }
                onExited: {
                    gameSaverectangle.gradient.stops[0].color = "#e6681717"
                }
                onClicked: {
                    bgAmbiant.stop()
                    battleAmbiant.stop()
                    homeClass.loadGame(root2.gameSave.country,root2.gameSave.turn,JSON.stringify(root2.gameSave))
                }
            }

            Item {
                id: deleteitem
                visible: root2.saveId!=0
                width: 40
                height: 40
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.verticalCenter: parent.verticalCenter

                Rectangle {
                    id: deleterectangle
                    radius: 6
                    gradient: Gradient {
                        GradientStop {
                            position: 0
                            color: "#fd2727"
                        }

                        GradientStop {
                            position: 1
                            color: "#300b0b"
                        }
                    }
                    border.width: 2
                    anchors.fill: parent
                }

                Text {
                    id: deleteText
                    color: "#f7f1f1"
                    text: qsTr("X")
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.bold: true
                    font.pixelSize: 20
                }

                MouseArea {
                    id: deletemouseArea
                    anchors.fill: parent
                    onClicked: {

                        if(root2.saveId == 0)return
                        savesFile.splice(root2.gameSave,1)
                        root2.visible = false
                        homeClass.deleteGameSave(JSON.stringify(savesFile))
                    }
                }
            }
        }
    }
}

