import QtQuick 2.0

import QtQuick 2.0
import QtQuick.Controls 1.6
//import City 1.0
Item {
    id : root
    width: 650
    height: 500
    visible: true
//    anchors.fill: parent
    property var unitsTypes: JSON.parse(multiplayerGame.unitsText());
    property var toAddUnits: []
    property var toAddUnitsCost: []
    property int totalCost: 0
    property int funds: multiplayerGame.myCity.country.funds
    Rectangle {
        id: rectangle
        color: "#99867070"
        radius: 5
        border.width: 6
        anchors.fill: parent
    }

    Component{
        id : typegenerator
        Item{
            id:mainRect
            property string name: ""
            property string src: ""
            property bool isSctd: false
            property int cost: 0
            property int indice: 0
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
                        root.totalCost -= mainRect.cost
                        root.toAddUnits.splice(mainRect.indice,1)
                        root.toAddUnitsCost.splice(mainRect.indice,1)
                        mainRect.destroy()
                        return;
                    }

                    for(var c =0; c<parseInt(unitPerClickGroup.current.text);c++){

                        /// > funds
                        if((root.totalCost+mainRect.cost)>root.funds){
                            return
                        }

                        root.toAddUnits.push(mainRect.name)
                        root.toAddUnitsCost.push(mainRect.cost)
                        var i = root.toAddUnits.length-1;
                        var obj = typegenerator.createObject(addedFlow);
                        obj.src = "qrc:/data/units/"+mainRect.name+".png";                        
                        obj.isSctd = true
                        obj.cost = mainRect.cost
                        obj.indice = i;
                        root.totalCost += mainRect.cost
                    }
                }

            }

        }
    }

    Rectangle {
        id: incomeRectangle
        x: 324
        y: 6
        width: 168
        height: 53
        color: "#cc494826"
        radius: 4
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 6

        Text {
            id: incomeText
            color: "#f7e768"
            text: "Funds : "+root.funds+" $"
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

    Item{
        id: addedItem
        x: 0
        y: 247
        height: 176
        //            ScrollBar.vertical.interactive:true
        //            ScrollBar.vertical.policy : ScrollBar.AlwaysOn
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 247
        clip: true
        Rectangle {
            id: addedRectanglebg
            color: "#99777777"
            anchors.fill: parent
        }
        Flickable{
            id:addedFlickable
            width: parent.width
            height: parent.height
            contentHeight: addedFlow.height
            contentWidth: parent.width
            Flow{
                id:addedFlow
                width: parent.width
                height: childrenRect.height
            }
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
            radius: 4
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#992c8214"
                }

                GradientStop {
                    position: 1
                    color: "#000000"
                }
            }
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0

            MouseArea {
                id: submitmouseArea
                anchors.fill: parent
                onClicked: {
                    for(var i =0;i< root.toAddUnits.length;i++){
                        multiplayerGame.addUnitFromQml(root.toAddUnits[i],root.toAddUnitsCost[i])
                    }
                    multiplayerGame.submitUnits()
                    root.toAddUnits= [];
                    root.toAddUnitsCost= [];
//                    addedRectangle1.children =[]
                    root.totalCost = 0;
//                    cityUI.show()
//                    addUI.hide()
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
        x: 46
        y: 447
        text: qsTr("")
        anchors.left: parent.left
        anchors.leftMargin: 46
        anchors.verticalCenter: costRectangle.verticalCenter
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 16
    }

    Item {
        id: typesItem
        x: 0
        y: 65
        height: 176
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 65
        Rectangle {
            id: typesbg
            y: 0
            height: 176
            color: "#99777777"
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0

        }
        Flickable{
            id:typesFlickable
            width: parent.width
            height: parent.height
            Flow{
                id:typesFlow
                height: childrenRect.height
                width: parent.width
            }
        }
        anchors.right: parent.right
        clip: true
        anchors.top: parent.top
        anchors.left: parent.left
        Component.onCompleted: {
            var i = 0;
            for(var tp in root.unitsTypes){
                var obj = typegenerator.createObject(typesFlow);
                obj.src = "qrc:/data/units/"+root.unitsTypes[i].name+".png";
                obj.cost = root.unitsTypes[i].cost;
                obj.name = root.unitsTypes[i].name;
                i++;
            }
        }
    }

    Image {
        id: countryimage
        x: 323
        width: 74
        height: 34
        anchors.right: incomeRectangle.left
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 5
        source: "qrc:/data/flags/"+multiplayerGame.myCity.country.intID+".png"
    }

    Text{
        id: countrytext
        x: 387
        width: 80
        height: 20
        color: "#2eeccd"
        text: multiplayerGame.myCity.country.name
        font.italic: true
        anchors.top: countryimage.bottom
        anchors.topMargin: 0
        anchors.horizontalCenter: countryimage.horizontalCenter
        font.pixelSize: 12
    }

    Text {
        id: citytext
        color: "#ffffff"
        text: multiplayerGame.myCity.name
        horizontalAlignment: Text.AlignHCenter
        anchors.verticalCenter: incomeRectangle.verticalCenter
        verticalAlignment: Text.AlignVCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 20
    }

    GroupBox {
        id: groupBox
        x: 8
        y: 73
        width: 183
        height: 49
        checkable: false
        flat: false
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 8
        title: qsTr("Unit Per click")

        Row {
            id: row
            anchors.topMargin: 0
            spacing: 16
            anchors.fill: parent
            ExclusiveGroup{ id: unitPerClickGroup }
            RadioButton {
                id: radioButton1
                text: qsTr("1")
                checked: true
                exclusiveGroup: unitPerClickGroup
            }

            RadioButton {
                id: radioButton3
                text: qsTr("3")
                checked: false
                exclusiveGroup: unitPerClickGroup
            }

            RadioButton {
                id: radioButton5
                text: qsTr("5")
                checked: false
                exclusiveGroup: unitPerClickGroup
            }
        }


    }




}
