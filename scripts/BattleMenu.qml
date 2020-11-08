import QtQuick 2.0
import QtQuick.Particles 2.0
Item {
    id: item1
    width: 1200
    height: 100

    visible: true

    Rectangle {
        id: rectangle
        height: 100
        opacity: 0.9
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#ef351d"
            }

            GradientStop {
                position: 1
                color: "#270d0a"
            }
        }
        anchors.fill: parent
    }

    Image {
        id: image
        opacity: 0.6
        fillMode: Image.Tile
        anchors.fill: parent
        source: "qrc:/data/mapmtex.jpg"
    }
//    ParticleSystem{
//        anchors.fill: parent
//        Emitter{
//            sizeVariation: 4
//            size: 20
//            anchors.fill: parent
//            lifeSpan: 1000
//            emitRate: 5
//            lifeSpanVariation: 200

//        }
//        ImageParticle{
//            source:"qrc:/data/fire.png"
//        }
//    }
    Item {
        id: surrenderitem
        x: 1100
        y: 25
        width: 90
        height: 50
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 25
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 25

        Rectangle {
            id: surrenderrectangle
            color: "#f50e0e"
            radius: 10
            border.width: 2
            anchors.fill: parent
        }

        MouseArea {
            id: surrendermouseArea
            anchors.fill: parent
            hoverEnabled: true
            onEntered: surrenderrectangle.color = Qt.lighter("#f50e0e")
            onExited: surrenderrectangle.color = "#f50e0e"
            onClicked:{
                battleForm.surrender()
                battleForm.battleEnded()
            }
        }

        Text {
            id: surrendertext
            x: 6
            y: 16
            color: "#f6f3f3"
            text: qsTr("Surrender")
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 15
        }
    }

    Item {
        id: drawitem
        x: 1090
        y: 23
        width: 90
        height: 50
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.topMargin: 25
        anchors.bottomMargin: 25
        anchors.right: surrenderitem.left
        anchors.rightMargin: 10
        Rectangle {
            id: drawrectangle
            color: "#757b12"
            radius: 10
            border.width: 2
            anchors.fill: parent
        }

        MouseArea {
            id: drawmouseArea
            enabled: false
            anchors.fill: parent
            hoverEnabled: false
            onEntered: drawrectangle.color = Qt.lighter("#757b12")
            onExited: drawrectangle.color = "#757b12"
        }

        Text {
            id: drawtext
            x: 6
            y: 16
            color: "#f6f3f3"
            text: qsTr("Draw")
            horizontalAlignment: Text.AlignHCenter
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 15
            verticalAlignment: Text.AlignVCenter
        }
    }

    Item {
        id: readyitem
        x: 904
        y: 30
        width: 90
        height: 50
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.topMargin: 25
        anchors.bottomMargin: 25
        anchors.right: drawitem.left
        anchors.rightMargin: 10
        Rectangle {
            id: readyrectangle1
            color: "#11a018"
            radius: 10
            border.width: 2
            anchors.fill: parent
        }

        MouseArea {
            id: readymouseArea
            enabled: ((bscene.generalsToChooseA == 0)&&(bscene.generalsToChooseD == 0))?true:false
            hoverEnabled: enabled
            anchors.fill: parent
            onEntered: readyrectangle1.color = Qt.lighter("#11a018")
            onExited: readyrectangle1.color = "#11a018"
            onClicked: {
                promoteitem.scale = 1
                promotemouseArea.enabled =  false
                promotemouseArea.hoverEnabled = false
                promoterectangle.color = "#888888"

                readyitem.scale = 1.2
                readymouseArea.enabled = false
                readymouseArea.hoverEnabled = false
                stattext.text = "turn 1 : "+bscene.generalsToChooseA
                readytext.text = "playing .."

                drawmouseArea.enabled = true
                drawmouseArea.hoverEnabled = true              

                battleForm.play()
            }
            Connections{
                target: bscene
                onCurrentCityPlayingChanged:{
                    stattext.text = bscene.currentCityPlaying.country.name+" : "+Math.max(bscene.generalsToChooseA,bscene.generalsToChooseD)
                                    +" moves "
                }
            }
        }

        Text {
            id: readytext
            x: 6
            y: 16
            color: "#f6f3f3"
            text: qsTr("Ready")
            horizontalAlignment: Text.AlignHCenter
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 15
            verticalAlignment: Text.AlignVCenter
        }
    }

    Item {
        id: promoteitem
        x: 804
        y: 28
        width: 90
        height: 50
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.topMargin: 25
        anchors.bottomMargin: 25
        anchors.right: readyitem.left
        anchors.rightMargin: 10
        Rectangle {
            id: promoterectangle
            color: "#1131a2"
            radius: 10
            border.width: 2
            anchors.fill: parent
        }

        MouseArea {
            id: promotemouseArea
            enabled: false
            anchors.fill: parent
            hoverEnabled: false
            onEntered: promoterectangle.color = Qt.lighter("#1131a2")
            onExited: promoterectangle.color = "#1131a2"
            onClicked: {

                placeitem.scale = 1
                placemouseArea.enabled =  false
                placemouseArea.hoverEnabled = false
                placerectangle.color = "#888888"

                promoteitem.scale = 1.2
                promotemouseArea.enabled = false
                promotemouseArea.hoverEnabled = false
                stattext.text = "choose all your generals : "+bscene.generalsToChooseA
                promotetext.text = "prmoting .."

//                readymouseArea.enabled = true
//                readymouseArea.hoverEnabled = true                
                battleForm.setPromote()
            }
        }

        Text {
            id: promotetext
            x: 6
            y: 16
            color: "#f6f3f3"
            text: qsTr("Promote")
            horizontalAlignment: Text.AlignHCenter
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 15
            verticalAlignment: Text.AlignVCenter
        }
    }

    Item {
        id: placeitem
        x: 797
        y: 35
        width: 90
        height: 50
        scale: 1
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.rightMargin: 10
        anchors.bottomMargin: 25
        anchors.topMargin: 25
        anchors.right: promoteitem.left
        Rectangle {
            id: placerectangle
            color: "#a21171"
            radius: 10
            anchors.fill: parent
            border.width: 2
        }

        MouseArea {
            id: placemouseArea
            scale: 1.3
            hoverEnabled: true
            anchors.fill: parent
            onEntered: placerectangle.color = Qt.lighter("#a21171")
            onExited: placerectangle.color = "#a21171"
            onClicked: {

                placeitem.scale = 1.2
                placemouseArea.enabled =  false
                placemouseArea.hoverEnabled = false
                placerectangle.color = "#888888"
                stattext.text = "enemy is placing units... "
                placetext.text = "placing ..."

                promotemouseArea.enabled =  true
                promotemouseArea.hoverEnabled = true

                battleForm.battleAI.placeUnits()
            }
        }

       Text {
            id: placetext
            x: 6
            y: 16
            color: "#f6f3f3"
            text: "Placed"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.bold: true
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 15
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Text {
        id: stattext
        x: 580
        y: 38
        color: "#ffffff"
        text: qsTr("build your formation")
        anchors.verticalCenterOffset: -30
        anchors.horizontalCenterOffset: -12
        font.bold: true
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 18
    }

    Image {
        id: attackerimage
        width: 87
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50
        anchors.top: parent.top
        anchors.topMargin: 7
        source: "qrc:/data/flags/"+attacker.country.intID+".png"
    }

    Image {
        id: deffenderimage
        x: -6
        y: -7
        width: 87
        height: 42
        anchors.verticalCenter: attackerimage.verticalCenter
        anchors.leftMargin: 231
        anchors.left: attackerimage.right
        source: "qrc:/data/flags/"+deffender.country.intID+".png"
    }

    Text {
        id: attackertext
        x: 115
        y: 18
        width: 32
        height: 22
        color: "#ffffff"
        text: attacker.country.name
        font.bold: true
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        anchors.top : attackerimage.top
        anchors.left: attackerimage.right
        anchors.leftMargin: 6
        font.pixelSize: 17
    }

    Text {
        id: deffendertext
        x: 115
        y: 18
        width: 32
        height: 22
        color: "#fdfdfd"
        text: deffender.country.name
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
        anchors.top :deffenderimage.top
        anchors.right: deffenderimage.left
        anchors.rightMargin: 6
        font.pixelSize: 17
    }
    Rectangle {
        id: statusBar
        width: 400
        height: 14
        color: "#ff0000"
        radius: 6
        anchors.left: parent.left
        anchors.leftMargin: 13
        opacity: 1
        clip: true

        anchors.top: parent.top
        anchors.topMargin: 70

        Rectangle {
            id: statusbarrectangle
            x: 192
            width: (deffender.power/(deffender.power+attacker.power))*400
            color: "#00ff00"
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            Connections{
                target: deffender
                onPowerChanged:{
                    statusbarrectangle.width = (deffender.power/(deffender.power+attacker.power))*400
                }
            }
            Connections{
                target: attacker
                onPowerChanged:{
                    statusbarrectangle.width = (deffender.power/(deffender.power+attacker.power))*400
                }
            }
        }

        Image {
            id: sbimage
            opacity: 0.3
            anchors.fill: parent
            source: "qrc:/data/icons/statustexture.jpg"
        }
        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: {
                console.log(deffender.power+" "+attacker.power+" "+(deffender.power*400)/(deffender.power+attacker.power))
            }
        }

    }

    Text {
        id: attackerCity
        x: 115
        width: 32
        height: 22
        color: "#ffffff"
        text: attacker.name
        font.italic: true
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        anchors.top: attackertext.bottom
        anchors.topMargin: 1
        anchors.left: attackertext.left
        anchors.leftMargin: 0
        font.pixelSize: 12
    }

    Text {
        id: deffenderCity
        width: 32
        height: 22
        color: "#ffffff"
        text: deffender.name
        font.italic: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
        anchors.top: deffendertext.bottom
        anchors.topMargin: 1
        anchors.right: deffendertext.right
        anchors.rightMargin: 0
        font.pixelSize: 12
    }

    Item {
        id: endTurnitem
        width: 144
        visible: false
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 38

        Rectangle {
            id: rectangle1
            color: "#075854"
            radius: 24
            border.width: 2
            anchors.fill: parent
        }

        Text {
            id: text1
            color: "#f2f1f1"
            text: qsTr("End Turn")
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 19
        }

        MouseArea {
            id: endturnmouseArea
            visible: false
            enabled: false
            anchors.fill: parent
        }
    }



}
