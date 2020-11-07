import QtQuick 2.0

Item {
    id : root
    height: 60
    width: 900
    visible: true
    Rectangle {
        id: bg
        height: 50
        radius: 0
        border.width: 3
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#231d59"
            }

            GradientStop {
                position: 0.962
                color: "#c9c5ec"
            }
        }
        opacity: 1
        anchors.fill: parent

        Image {
            id: image
            width: 900
            opacity: 0.5
            fillMode: Image.Tile
            anchors.fill: parent
            source: "qrc:/data/mapmtex.jpg"
        }
    }

    Item {
        id: displayCitiesitem
        width: 50
        height: 50
        anchors.left: parent.left
        anchors.leftMargin: 7
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5

        Rectangle {
            id: dsrectangle
            color: "#121f52"
            radius: 6
            opacity: 0.7
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            border.width: 1
            anchors.fill: parent
        }

        Image {
            id: dsimage
            transformOrigin: Item.Center
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.bottomMargin: 5
            anchors.topMargin: 5
            anchors.fill: parent
            source: "qrc:/data/icons/citiesicon.png"
        }

        MouseArea {
            id: dsmouseArea
            hoverEnabled: true
            anchors.fill: parent
            onEntered:{ dsrectangle.color = "#35bbe2"; infotext.text="Show cities" }
            onExited: {dsrectangle.color = "#121f52";infotext.text=""  }
            onPressed: {
                if(citiesDisplayUI.visible){
                    citiesDisplayUI.hide();
                    dsimage.rotation = 0
                }else{
                    citiesDisplayUI.show();
                    dsimage.rotation = 90
                }
            }
        }
    }

    Text {
        id: infotext
        x: 307
        y: 18
        color: "#f5f3f3"
        text: qsTr("")
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 14
    }

    Image {
        id: flagimage
        x: 594
        width: 90
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        anchors.top: parent.top
        anchors.topMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 5
        source: "qrc:/data/flags/"+activePlayer.country.intID+".png"
    }

    Text {
        id: activePtext
        x: 559
        color: "#57f906"
        text: activePlayer.country.name
        anchors.right: flagimage.left
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 16
        font.underline: false
        font.italic: true
        font.bold: true
        anchors.verticalCenterOffset: 1
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 18
    }

    Item {
        id: mainMenuItem
        x: -1
        y: -9
        width: 50
        anchors.topMargin: 5
        anchors.leftMargin: 5
        Rectangle {
            id: mmrectangle
            color: "#121f52"
            radius: 6
            border.width: 1
            anchors.topMargin: 0
            anchors.leftMargin: 0
            opacity: 0.7
            anchors.bottomMargin: 0
            anchors.fill: parent
            anchors.rightMargin: 0
        }

        Image {
            id: mmimage
            source: "qrc:/data/icons/menu.png"
            anchors.topMargin: 5
            anchors.leftMargin: 5
            transformOrigin: Item.Center
            anchors.bottomMargin: 5
            anchors.fill: parent
            anchors.rightMargin: 5
        }

        MouseArea {
            id: mmmouseArea1
            hoverEnabled: true
            anchors.fill: parent
            onEntered:{ mmrectangle.color = "#35bbe2"; infotext.text="Main Menu" }
            onExited: {mmrectangle.color = "#121f52";infotext.text=""  }
            onPressed: {
                menuOpt.show()
            }
        }
        anchors.bottomMargin: 5
        anchors.top: parent.top
        anchors.left: displayCitiesitem.right
        anchors.bottom: parent.bottom
    }

    Item {
        id: endturnItem
        x: 2
        y: -7
        width: 50
        anchors.topMargin: 5
        anchors.leftMargin: 5
        Rectangle {
            id: etrectangle
            color: "#121f52"
            radius: 6
            border.width: 1
            anchors.topMargin: 0
            anchors.leftMargin: 0
            opacity: 0.7
            anchors.bottomMargin: 0
            anchors.fill: parent
            anchors.rightMargin: 0
        }

        Image {
            id: etimage
            source: "qrc:/data/icons/endturn.png"
            anchors.topMargin: 5
            anchors.leftMargin: 5
            transformOrigin: Item.Center
            anchors.bottomMargin: 5
            anchors.fill: parent
            anchors.rightMargin: 5
        }

        MouseArea {
            id: etmouseArea
            hoverEnabled: true
            anchors.fill: parent
            onEntered:{ etrectangle.color = "#35bbe2"; infotext.text="End Turn" }
            onExited: {etrectangle.color = "#121f52";infotext.text=""  }
            onPressed: mainmenu.runNextTurn()
        }
        anchors.bottomMargin: 5
        anchors.top: parent.top
        anchors.left: mainMenuItem.right
        anchors.bottom: parent.bottom
    }

    Item {
        id: incomeItem
        x: -3
        y: -3
        width: 157
        anchors.leftMargin: 7
        anchors.topMargin: 7
        Rectangle {
            id: inrectangle
            color: "#121f52"
            radius: 6
            border.width: 1
            anchors.leftMargin: 0
            anchors.topMargin: 0
            opacity: 0.7
            anchors.bottomMargin: 0
            anchors.fill: parent
            anchors.rightMargin: 0
        }

        MouseArea {
            id: inmouseArea
            hoverEnabled: true
            anchors.fill: parent
        }

        Rectangle {
            id: rectangle
            width: 55
            color: "#121f52"
            radius: 3
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            Text {
                id: incomeText
                x: 16
                y: 13
                color: "#09f623"
                text: "+" +activePlayer.country.income
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 13
            }
        }

        Text {
            id: fundstext
            color: "#f2ea5b"
            text: activePlayer.country.funds+" $ "
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            anchors.verticalCenterOffset: 0
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 19
        }
        anchors.bottomMargin: 7
        anchors.top: parent.top
        anchors.left: endturnItem.right
        anchors.bottom: parent.bottom
    }

    Text {
        id: actualPimage
        x: 438
        width: 54
        color: "#86f0e9"
        text: actuelPlayer.name
        font.bold: true
        font.pointSize: 12
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: activePtext.left
        anchors.rightMargin: 30
    }
    Connections{
        target:mainmenu.mapView
        onActuelPlayerChanged: {
            actualPimage.text =  mainmenu.mapView.actuelPlayer.name
        }
    }

}
