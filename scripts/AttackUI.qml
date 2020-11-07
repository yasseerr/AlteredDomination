import QtQuick 2.0
import QtQuick.Controls 1.6


Item {
    id: attackUIitem
    width: 800
    height: 480
    visible: true
    clip: true
    opacity: 1

    Component{
        id : typegenerator
        Item{
            id:mainRect
            property string name: ""
            property string src: ""
            property bool isSctd: false
            property int idU: 0
            width: 80
            height: 80
            visible: true
            clip: true
            Rectangle{
                id:fillr
                anchors.fill: parent
                color: "#ffffff"
                opacity: 0.4
                radius: 10
                border.width: 5
            }
            Image {
                id: typeImg
                width: 80
                height: 80
                source: mainRect.src
                anchors.fill: parent
                anchors.margins: 10
            }
            MouseArea{
                id:ma
                hoverEnabled: true
                anchors.fill: parent
                onEntered: {
                    mainRect.scale = 1.1;
                    fillr.color=mainRect.isSctd?"#ff0000":"#00ffff";
                }
                onExited: {mainRect.scale = 1; fillr.color="#ffffff"}
                onPressed: {

                }

            }

        }
    }
    Rectangle {
        id: rectangle1
        color: "#00000000"
        radius: 6
        border.width: 7
        opacity: 1
        anchors.fill: parent
    }

    Connections{
        target: sourceCity
        onUnitToAttackQml: {
            var obj1 = typegenerator.createObject(attackerflow)
            obj1.src = "qrc:/data/units/"+typeU+".png"
        }
    }
    Connections{
        target: destinationCity
        onUnitToAttackQml: {
            var obj2 = typegenerator.createObject(attackedflow)
            obj2.src = "qrc:/data/units/"+typeU+".png"
        }
    }
    Image {
        id: bg
        opacity: 0.7
        anchors.fill: parent
        source: "qrc:/data/cities/attackUIBG.jpg"
    }

    Item {
        id: attackedItem
        width: 400
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

        Rectangle {
            id: attackedRectangle
            color: "#f4faee"
            opacity: 0.3
            visible: true
            anchors.fill: parent
        }

        Item {
            id: attackedHead
            height: 127
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            Rectangle {
                id: attackedheadBG
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "#4b1515"
                    }

                    GradientStop {
                        position: 1
                        color: "#8b7d7d"
                    }
                }
                opacity: 0.6
                anchors.fill: parent
            }

            Text {
                id: attackedtext
                y: 72
                color: "#f9f9f9"
                text: destinationCity.city.name
                anchors.left: attackedCountryImage.right
                anchors.leftMargin: 34
                anchors.verticalCenterOffset: 0
                anchors.verticalCenter: attackedCountryImage.verticalCenter
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 22
            }

            Image {
                id: attackedCountryImage
                width: 81
                height: 47
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.top: parent.top
                anchors.topMargin: 5
                source: "qrc:/data/flags/"+destinationCity.city.country.intID+".png"
            }


        }

        Item {
            id: attackedunitsitem
            x: 8
            y: 138
            anchors.right: parent.right
            anchors.rightMargin: 13
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
            anchors.top: parent.top
            anchors.topMargin: 138

            Rectangle {
                id: attackedunitsrectangle
                color: "#d0bdbd"
                radius: 11
                opacity: 0.4
                border.width: 3
                anchors.fill: parent
            }
            ScrollView{
                id: attackedScroll
                anchors.fill: parent

                Flow {
                    id: attackedflow
                    width: 356
                    height: childrenRect.height
                    spacing: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0
                }
            }
        }





    }

    Item {
        id: attackerItem
        x: 0
        y: 2
        width: 400
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.topMargin: 0
        Rectangle {
            id: attackerRectangle
            color: "#f4faee"
            anchors.fill: parent
            visible: true
            opacity: 0.3
        }

        Item {
            id: attackerdHead
            height: 127
            anchors.leftMargin: 0
            anchors.left: parent.left
            anchors.topMargin: 0
            Rectangle {
                id: attackerheadBG
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "#4b1515"
                    }

                    GradientStop {
                        position: 1
                        color: "#8b7d7d"
                    }
                }
                opacity: 0.6
                anchors.fill: parent
            }

            Text {
                id: attackertext
                x: 120
                y: 72
                color: "#f9f9f9"
                text: sourceCity.city.name
                anchors.right: attackerCountryImage.left
                anchors.rightMargin: 34
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 22
                anchors.verticalCenterOffset: 0
                anchors.verticalCenter: attackerCountryImage.verticalCenter
            }

            Image {
                id: attackerCountryImage
                x: 19
                width: 81
                height: 47
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.topMargin: 5
                anchors.top: parent.top
                source: "qrc:/data/flags/"+sourceCity.city.country.intID+".png"
            }
            anchors.rightMargin: 0
            anchors.right: parent.right
            anchors.top: parent.top
        }

        Item {
            id: attackerunitsitem
            x: 8
            y: 138
            anchors.leftMargin: 6
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.topMargin: 138
            Rectangle {
                id: attackerunitsrectangle
                color: "#d0bdbd"
                radius: 11
                border.width: 3
                opacity: 0.4
                anchors.fill: parent
            }
            ScrollView{
                id: attackerScroll
                width: 380
                height: 333
                anchors.rightMargin: 0
                anchors.bottomMargin: 0
                anchors.leftMargin: 0
                anchors.topMargin: 0
                anchors.fill: parent

                Flow {
                    id: attackerflow
                    width: 360
                    height: childrenRect.height
                    spacing: 0
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0
                }
            }
            anchors.rightMargin: 13
            anchors.right: parent.right
            anchors.bottomMargin: 8
            anchors.top: parent.top
        }
        anchors.bottomMargin: 0
        anchors.top: parent.top
    }

    Rectangle {
        id: statusBar
        x: 236
        width: 400
        height: 14
        color: "#ff0000"
        radius: 6
        opacity: 1
        clip: true
        anchors.horizontalCenter: parent.horizontalCenter

        anchors.top: parent.top
        anchors.topMargin: 102

        Rectangle {
            id: rectangle
            x: 192
            width: (sourceCity.power*400)/(destinationCity.power+sourceCity.power)
            color: "#00ff00"
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
        }

        Image {
            id: image
            opacity: 0.3
            anchors.fill: parent
            source: "qrc:/data/icons/statustexture.jpg"
        }

    }

    Rectangle {
        id: battlerectangle
        width: 86
        height: 41
        color: "#db2d2d"
        radius: 17
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 8

        MouseArea {
            id: battlemouseArea
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            hoverEnabled: true
            anchors.fill: parent
            onEntered: battlerectangle.scale = 1.2
            onExited: battlerectangle.scale = 1
        }

        Text {
            id: starttext
            color: "#efebeb"
            text: qsTr("Start")
            font.bold: true
            font.family: "Tahoma"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 26
        }
    }

    Rectangle {
        id: cancelrectangle
        x: -9
        y: -2
        width: 66
        height: 37
        color: "#10663d"
        radius: 28
        anchors.horizontalCenter: parent.horizontalCenter

        MouseArea {
            id: cancelmouseArea
            width: 100
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            anchors.topMargin: 0
            onEntered: cancelrectangle.scale = 1.2
            onExited: cancelrectangle.scale = 1
            onPressed: {
                sourceCity.cancelAttack()
                attackerflow.children = []
                attackedflow.children = []
                attackUI.hide()
            }
            hoverEnabled: true
        }

        Text {
            id: canceltext
            x: 0
            y: -43
            color: "#efebeb"
            text: qsTr("Cancel")
            anchors.verticalCenterOffset: 0
            anchors.horizontalCenterOffset: 0
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 17
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Tahoma"
            font.bold: true
        }
        anchors.topMargin: 56
        anchors.top: parent.top
    }





}
