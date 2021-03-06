import QtQuick 2.0
import QtQuick.Controls 1.6
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0
import QtMultimedia 5.0
import City 1.0

Item{
    id:win1
    width: 650
    height: 500
    clip: true
    visible: true
    opacity: 1
    property var unitsList: []
    //    CityUI.onVisibleChanged: infoText.text = "hello"
    //    onVisibleChanged: mapUI.enabled = !visible


    Image {
        id: bgImage
        visible: false
        anchors.fill: parent
        opacity: 0.5
        //            anchors.bottomMargin: -100
        source: "qrc:/data/cities/bg2.jpg"
    }

    Rectangle{
        id:mainRect
        color: "#803e3c3c"
        radius: 3
        border.width: 4
        clip: true
        anchors.fill: parent
        layer.enabled: true
        layer.effect: OpacityMask{
            maskSource:Item {
                width: mainRect.width
                height: mainRect.height
                Rectangle{
                    anchors.centerIn: parent
                    width: mainRect.width
                    height: mainRect.height
                    radius: 5
                }
            }
        }


    }


    Text {
        id: text1
        x: 13
        y: 124
        text: qsTr("Units :")
        font.bold: true
        elide: Text.ElideRight
        font.pixelSize: 16
    }

    Item{
        id:header
        width: 400
        height: 41
        clip: true

        Rectangle{
            id:headerBG
            anchors.fill: parent
            opacity: 0.5
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#e6000000"
                }

                GradientStop {
                    position: 1
                    color: "#ccffffff"
                }
            }
        }
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        Rectangle {
            id: flagRectangle
            width: 80
            height: 40
            color: "#ffffff"
            radius: 8
            anchors.left: parent.left
            anchors.leftMargin: 0
            border.width: 3
            clip: true
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.verticalCenter: parent.verticalCenter

            Image {
                id: flagImg
                anchors.fill: parent
                clip: true
                opacity: 1
                source: "qrc:/data/flags/dz.png"
                layer.enabled: true
                layer.effect: OpacityMask{
                    maskSource:Item {
                        width: flagImg.width
                        height: flagImg.height
                        Rectangle{
                            anchors.centerIn: parent
                            width: flagImg.width
                            height: flagImg.height
                            radius:10
                        }
                    }
                }


            }
        }

        Text {
            id: cityName
            x: 133
            color: "#ffffffff"
            text: city.name
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            opacity: 1
            wrapMode: Text.WrapAnywhere
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 25
            onTextChanged: flagImg.source = "qrc:/data/flags/"+city.country.intID+".png"
        }

        Rectangle {
            id: quitRectangle
            x: 367
            y: 7
            width: 27
            height: 26
            color: "#99f20d0d"
            radius: 9
            anchors.right: parent.right
            anchors.rightMargin: 10

            Text {
                id: closeT
                color: "#f5f4f4"
                text: qsTr("X")
                fontSizeMode: Text.VerticalFit
                font.bold: true
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 12
            }

            MouseArea {
                id: closemouseArea
                hoverEnabled: true
                anchors.fill: parent
                onClicked: {
                    viewUI.hide();
                    unitsList = []
                    unitsFlow.children =[]
                    mapUI.enabled = true;
                }
                onEntered: quitRectangle.scale = 1.5
                onExited: quitRectangle.scale = 1
                function closeOp(){
                    unitsList = []
                    unitsFlow.children =[]
                    viewUI.hide();
                }

            }

        }


    }

    Rectangle {
        id: buttonsContainer
        x: 0
        y: 47
        height: 71
        color: "#80777777"
        border.width: 2
        anchors.top: parent.top
        anchors.topMargin: 47
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

        Rectangle {
            id: attackRect
            width: 50
            height: 50
            color: "#e0bb72"
            radius: 19
            border.width: 2
            clip: true
            anchors.top: parent.top
            anchors.topMargin: 13
            anchors.left: parent.left
            anchors.leftMargin: 18

            MouseArea {
                id: attackMouseArea
                hoverEnabled: true
                anchors.fill: parent
                enabled : cityGraphics.mapView.turnNumber !=0;
                onEntered: {
                    attackRect.color = Qt.lighter(investRect.color);
                    hoverAudio.play()
                    infoText.text="Attack"+(unitsFlow.childrenRect.width>0?"":"(no units)") ;

                }
                onExited: {attackRect.color = "#e0bb72"; infoText.text="";}
                onPressed: {
                    attackRect.color = "#00ff00"
                    unitsFlow.children = []
                    unitsList = []
                    viewUI.hide()
                    cityGraphics.attack()
                    mapUI.enabled = true
                }
                onReleased: attackRect.color = "#e0bb72"

            }

            Image {
                id: attackImage
                antialiasing: true
                clip: true
                anchors.fill: parent
                source: "qrc:/data/icons/attack.png"
            }

        }

        Rectangle {
            id: moveRect
            x: 4
            y: -9
            width: 50
            height: 50
            color: "#e0bb72"
            radius: 19
            border.width: 2
            anchors.leftMargin: 74
            anchors.topMargin: 13
            anchors.left: parent.left
            anchors.top: parent.top
            clip: true
            MouseArea {
                id: moveMouseArea
                hoverEnabled: true
                anchors.fill: parent
                onEntered: {moveRect.color = Qt.lighter(investRect.color); infoText.text="move units" ; }
                onExited: {moveRect.color = "#e0bb72"; infoText.text="";}
                onPressed: {
                    moveRect.color = "#00ff00";
                    closemouseArea.closeOp();
                    cityGraphics.moveUnits();
                    mapUI.enabled = true
                }
                onReleased :  moveRect.color="#e0bb72"

            }

            Image {
                id: moveImage
                anchors.fill: parent
                clip: true
                source: "qrc:/data/icons/move.png"
            }
        }

        Rectangle {
            id: addRect
            x: -2
            y: 8
            width: 50
            height: 50
            color: "#e0bb72"
            radius: 19
            border.width: 2
            anchors.leftMargin: 130
            anchors.topMargin: 13
            anchors.left: parent.left
            anchors.top: parent.top
            clip: true
            MouseArea {
                id: addMouseArea
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {addRect.color = Qt.lighter(investRect.color); infoText.text="add Units" ; }
                onExited: {addRect.color = "#e0bb72"; infoText.text="";}
                onPressed: {addRect.color = "#00ff00"; cityUI.hide(); addUI.show(); }
                onReleased: addRect.color = "#e0bb72"

            }

            Image {
                id: addImage
                anchors.fill: parent
                clip: true
                source: "qrc:/data/icons/add.png"
            }
        }

        Rectangle {
            id: investRect
            x: -7
            y: 0
            width: 50
            height: 50
            color: "#e0bb72"
            radius: 19
            border.width: 2
            anchors.leftMargin: 186
            anchors.topMargin: 13
            anchors.left: parent.left
            anchors.top: parent.top
            clip: true
            MouseArea {
                id: investMouseArea
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {investRect.color = Qt.lighter(investRect.color); infoText.text="invest" ;bomb.play() }
                onExited: {investRect.color = "#e0bb72"; infoText.text="";bomb.stop()}
                onPressed: investRect.color = "#00ff00"
                onReleased: investRect.color = "#e0bb72"
            }

            Image {
                id: investImage4
                anchors.fill: parent
                clip: true
                source: "qrc:/data/icons/invest.png"
            }
        }

        Text {
            id: infoText
            x: 332
            color: "#d6d6fb"
            text: qsTr("")
            anchors.top: parent.top
            anchors.topMargin: 26
            anchors.right: parent.right
            anchors.rightMargin: 14
            anchors.verticalCenterOffset: 0
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            font.family: "Verdana"
            font.pixelSize: 17
        }

        Text {
            id: text2
            x: 275
            y: 13
            color: "#ffffff"
            text: cityGraphics.mapView.turnNumber ==0?"turn 0 no attack ":cityGraphics.city.used?"city is already used":""
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 14
        }


    }

//    Item {
//        id: scrollitem
//        x: 5
//        anchors.top: text1.bottom
//        anchors.topMargin: 10
//        anchors.bottom: parent.bottom
//        anchors.bottomMargin: 5
//        anchors.right: parent.right
//        anchors.rightMargin: 5
//        anchors.left: parent.left
//        anchors.leftMargin: 5

//        Rectangle {
//            id: bgrectangleunits
//            x: 0
//            y: -2
//            color: "#99777777"
//            visible: true
//            anchors.fill: parent
//            border.width: 2
//        }

//        ScrollView {
//            id: scrollView
//            anchors.fill: parent

//            clip: true

//            Item {
//                id: unitsrectangle1
//                x: 0
//                y: 0
//                width: 500
//                height: 218
//                anchors.right: parent.right
//                anchors.rightMargin: 0
//                anchors.top: parent.top
//                anchors.topMargin: -1
//                anchors.left: parent.left
//                anchors.leftMargin: 0
//            }
//        }

//    }
    Item{
        id:unitsItem
        anchors.top: text1.bottom
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5
        Rectangle {
            id: bgunits
            x: 0
            y: -2
            color: "#80787878"
            visible: true
            anchors.fill: parent
            border.width: 2
        }
        Flickable{
            id:flickView
            anchors.fill: parent
            clip: true
            contentWidth: width
            contentHeight: unitsFlow.childrenRect.height
            Flow{
                id:unitsFlow
                spacing:5
                width: parent.width
            }
        }

    }

    Component{
        id : typegenerator
        Item{
            id:mainRect
            property string name: ""
            property string src: ""
            property int cost: 0
            width: 80
            height: 80
            visible: true
            opacity: 1
            clip: true
            Rectangle{
                id:fillr
                anchors.fill: parent
                color: "#ccffffff"
                opacity: 0.6
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
                    fillr.color="#00ffff";
                }
                onExited: {mainRect.scale = 1; fillr.color="#ffffff"}


            }

        }
    }


    Connections{
        target:city
        onAddedUnitSig:{
            var i = unitsList.length
            var obj = typegenerator.createObject(unitsFlow);
            obj.src = "qrc:/data/units/"+typeS+".png";
            unitsList.push(typeS)
//            unitsrectangle.height = unitsrectangle.childrenRect.height
        }
    }
    Audio{
        id:bomb
        source: "qrc:/data/sounds/explosion.wav"
    }






}

















/*##^## Designer {
    D{i:35;anchors_height:222;anchors_y:154}
}
 ##^##*/
