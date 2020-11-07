import QtQuick 2.0
import QtQuick.Controls 1.6

Item {
    id : adUnitUI
    width: 500
    height: 500
    visible: true
    property var unitsTypes: JSON.parse(mapUI.unitsText());
    property var toAddUnits: []
    property int totalCost: 0
    Component{
        id : typegenerator
        Item{
            id:mainRect
            property string name: ""
            property string src: ""
            property bool isSctd: false
            property int cost: 0
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
                    infoText.text = mainRect.name+" : "+mainRect.cost+"$";
                }
                onExited: {mainRect.scale = 1; fillr.color="#ffffff"}
                onPressed: {
                    if(mainRect.isSctd){
                        adUnitUI.totalCost -= addedRectangle1.children[adUnitUI.toAddUnits.length-1].cost
                        addedRectangle1.children[adUnitUI.toAddUnits.length-1].destroy()
                        adUnitUI.toAddUnits.pop()
                        return;
                    }
                    adUnitUI.toAddUnits.push(mainRect.name)
                    var i = adUnitUI.toAddUnits.length-1;
                    var obj = typegenerator.createObject(addedRectangle1,{"x":85*(i%5),"y":5+Math.floor(i/5)*85});
                    obj.src = "qrc:/data/units/"+mainRect.name+".png";
                    addedRectangle1.height =addedRectangle1.childrenRect.height
                    obj.isSctd = true
                    obj.cost = mainRect.cost
                    adUnitUI.totalCost += mainRect.cost
                }

            }

        }
    }

    Rectangle {
        id: rectangle
        color: "#99867070"
        radius: 11
        border.width: 6
        anchors.fill: parent

        Rectangle {
            id: incomeRectangle
            x: 324
            width: 168
            height: 53
            color: "#cc494826"
            radius: 15
            anchors.right: parent.right
            anchors.rightMargin: 8
            anchors.top: parent.top
            anchors.topMargin: 6

            Text {
                id: incomeText
                color: "#f7e768"
                text: qsTr("Sold : 1500 $")
                anchors.rightMargin: 0
                anchors.bottomMargin: 0
                anchors.leftMargin: 0
                anchors.topMargin: 0
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
                font.pixelSize: 21
            }
        }

        Rectangle {
            id: typesRectangle
            y: 65
            height: 176
            color: "#99777777"
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            Component.onCompleted: {
                var i = 0;
                for(var tp in adUnitUI.unitsTypes){
                    var obj = typegenerator.createObject(typesRectangle,{"x":85*(i%5),"y":5+Math.floor(i/5)*85});
                    obj.src = "qrc:/data/units/"+adUnitUI.unitsTypes[i].name+".png";
                    obj.cost = adUnitUI.unitsTypes[i].cost;
                    obj.name = adUnitUI.unitsTypes[i].name;
                    i++;
                }
            }

        }

        ScrollView{
            id: addedScroll
            x: 0
            y: 247
            height: 176
            verticalScrollBarPolicy: 0
            highlightOnFocus: true
            horizontalScrollBarPolicy: 1
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.topMargin: 247
            clip: true
            Rectangle {
                id: addedRectangle1
                color: "#99777777"
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                height: 176
                width: 500

            }
        }

        Rectangle {
            id: costRectangle
            x: 221
            y: 429
            width: 262
            height: 55
            color: "#b3ba932e"
            radius: 6

            Rectangle {
                id: submitRectangle
                x: 239
                y: 0
                width: 94
                height: 55
                color: "#992c8214"
                radius: 28
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 5

                MouseArea {
                    id: submitmouseArea
                    anchors.fill: parent
                    onClicked: {
                        adUnitUI.toAddUnits.forEach(function(element){ cityGraphics.addUnitFromQml(element)})
                        adUnitUI.toAddUnits= [];
                        addedRectangle1.children =[]
                        adUnitUI.totalCost = 0;
                        addUI.hide()
                    }

                    Text {
                        id: text2
                        color: "#ffffff"
                        text: qsTr("Submit")
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        anchors.fill: parent
                        font.pixelSize: 17
                    }
                }
            }

            Text {
                id: costtext
                text: "Cost :"+totalCost
                anchors.leftMargin: 0
                anchors.rightMargin: 97
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
                font.pixelSize: 15
            }

        }

        Text {
            id: infoText
            y: 450
            text: qsTr("")
            anchors.left: parent.left
            anchors.leftMargin: 46
            anchors.verticalCenter: costRectangle.verticalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 16
        }

    }
    

}
