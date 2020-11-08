import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    id : moveUnitUI
    width: 650
    height: 500
    visible: true
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
                    mainRect.scale = 1; fillr.color="#ffffff"
                    if(mainRect.parent==sourceflow){

                        mainRect.parent = destinationflow
                        destinationCity.receiveUnitFromNeighbour(mainRect.idU)

                    }
                    //                    else if(mainRect.parent==destinationflow){
                    //                        mainRect.parent = sourceflow
                    //                        destinationCity.sendUnitToNeighbour(mainRect.idU)
                    //                    }
                }

            }

        }
    }
    Connections{
        target: sourceCity
        onUnitToQml: {
            var obj1 = typegenerator.createObject(sourceflow)
            obj1.src = "qrc:/data/units/"+typeU+".png"
            obj1.idU = idU
        }
    }
    Connections{
        target: destinationCity
        onUnitToQml: {
            var obj2 = typegenerator.createObject(destinationflow)
            obj2.src = "qrc:/data/units/"+typeU+".png"
            obj2.idU
        }
    }

    Rectangle {
        id: rectangle
        color: "#803f3c3c"
        radius: 11
        border.width: 6
        anchors.fill: parent


//        ScrollView{
//            id: sourceScroll
//            x: 0
//            y: 247
//            height: 176
//            verticalScrollBarPolicy: 0
//            highlightOnFocus: true
//            horizontalScrollBarPolicy: 1
//            anchors.right: parent.right
//            anchors.left: parent.left
//            anchors.top: parent.top
//            anchors.topMargin: 53
//            clip: true
//            Rectangle {
//                id: sourceRectangle
//                color: "#99777777"
//                anchors.left: parent.left
//                anchors.leftMargin: 0
//                anchors.top: parent.top
//                anchors.topMargin: 0
//                height: sourceflow.height
//                width: 500

//                Flow {
//                    id: sourceflow1
//                    height: childrenRect.height
//                    anchors.right: parent.right
//                    anchors.left: parent.left
//                    anchors.top: parent.top
//                }

//            }
//        }

        Item {
            id: sourceItem
            height: 200
            anchors.right: parent.right
            anchors.rightMargin: 2
            anchors.left: parent.left
            anchors.leftMargin: 2
            anchors.top: sourceText.bottom
            anchors.topMargin: 10
            Rectangle{
                anchors.fill: parent
                color: "#99777777"

            }
            Flickable{
                clip: true
                anchors.fill: parent
                contentWidth: width
                contentHeight: sourceflow.height
                Flow{
                    id:sourceflow
                    width: parent.width
                    height: childrenRect.height
                }
            }

        }
        Item {
            id: destinationItem
            height: 200
            anchors.right: parent.right
            anchors.rightMargin: 2
            anchors.left: parent.left
            anchors.leftMargin: 2
            anchors.top: destinationText.bottom
            anchors.topMargin: 5
            Rectangle{
                anchors.fill: parent
                color: "#99777777"

            }
            Flickable{
                clip: true
                anchors.fill: parent
                contentWidth: width
                contentHeight: sourceflow.height
                Flow{
                    id:destinationflow
                    width: parent.width
                    height: childrenRect.height
                }
            }

        }


//        ScrollView{
//            id: destinationScroll
//            x: 0
//            y: 247
//            height: 176
//            verticalScrollBarPolicy: 0
//            highlightOnFocus: true
//            horizontalScrollBarPolicy: 1
//            anchors.right: parent.right
//            anchors.left: parent.left
//            anchors.top: parent.top
//            anchors.topMargin: 257
//            clip: true
//            Rectangle {
//                id: destinationRectangle
//                color: "#99777777"
//                anchors.left: parent.left
//                anchors.leftMargin: 0
//                anchors.top: parent.top
//                anchors.topMargin: 0
//                height: destinationflow.height
//                width: 500

//                Flow {
//                    id: destinationflow
//                    height: childrenRect.height
//                    anchors.right: parent.right
//                    anchors.left: parent.left
//                    anchors.top: parent.top
//                }

//            }
//        }

        Text {
            id: sourceText
            color: "#eceaea"
            text: sourceCity.city.name
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.left: parent.left
            anchors.leftMargin: 16
            anchors.top: parent.top
            anchors.topMargin: 5
            font.pixelSize: 21
        }

        Text {
            id: destinationText
            x: 1
            y: 3
            color: "#fdfdfd"
            text: destinationCity.city.name
            anchors.leftMargin: 16
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.left: parent.left
            anchors.topMargin: 5
            font.pixelSize: 21
            anchors.top: sourceItem.bottom
        }

        Rectangle {
            id: submitRectangle
            x: 399
            y: 436
            width: 94
            height: 55
            radius: 8
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#247c0c"
                }

                GradientStop {
                    position: 1
                    color: "#2f5723"
                }
            }
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 9
            anchors.right: parent.right
            anchors.rightMargin: 7

            MouseArea {
                id: submitmouseArea
                anchors.fill: parent
                onClicked: {
                    //                    adUnitUI.toAddUnits.forEach(function(element){ cityGraphics.addUnitFromQml(element)})
                    moveUI.hide()
                    sourceflow.children = []
                    destinationflow.children = []
                    sourceCity.deSelect()
                    mapUI.enabled = true
                }
            }

            Text {
                id: text2
                x: 0
                y: 0
                color: "#ffffff"
                text: "Submit"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
                font.pixelSize: 17
            }
        }

    }

}
