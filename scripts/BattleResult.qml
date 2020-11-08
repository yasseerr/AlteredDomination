import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: root
    width: 500
    height: 300
    visible: true
    clip: true
    
    Image {
        id: bgimage
        opacity: 0.6
        anchors.fill: parent
        source: "qrc:/data/cities/attackUIBG.jpg"
    }

    Rectangle {
        id: bgrectangle
        radius: 1
        border.color: "#05ac35"
        border.width: 3
        gradient: Gradient {
            GradientStop {
                position: 0.205
                color: "#33000000"
            }
            
            GradientStop {
                position: 0
                color: "#e6000000"
            }
            
            GradientStop {
                position: 0.811
                color: "#b3000000"
            }
        }
        anchors.fill: parent
    }

    Image {
        id: attackerimage
        x: 47
        y: 50
        width: 80
        height: 40
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.top: parent.top
        anchors.topMargin: 20
        source: "qrc:/data/flags/"+attacker.country.intID+".png"
        layer.enabled: true
        layer.effect: OpacityMask{
            maskSource:Item {
                width: attackerimage.width
                height: attackerimage.height
                Rectangle{
                    anchors.centerIn: parent
                    width: attackerimage.width
                    height: attackerimage.height
                    radius:10
                }
            }
        }
    }

    Image {
        id: deffenderimage
        x: 355
        y: 45
        width: 80
        height: 40
        anchors.verticalCenter: attackerimage.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 50
        source: attacker != deffender?"qrc:/data/flags/"+deffender.country.intID+".png":deffenderimage.source
        anchors.topMargin: 20
        anchors.top: parent.top
        layer.enabled: true
        layer.effect: OpacityMask{
            maskSource:Item {
                width: deffenderimage.width
                height: deffenderimage.height
                Rectangle{
                    anchors.centerIn: parent
                    width: deffenderimage.width
                    height: deffenderimage.height
                    radius:10
                }
            }
        }

    }

    Text {
        id: vs
        x: 225
        y: 78
        color: "#ede9e9"
        text: qsTr(" -   VS   -")
        font.family: "Arial"
        font.italic: true
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: attackerimage.verticalCenter
        font.pixelSize: 33
    }

    Item {
        id: okItem
        x: 159
        y: 239
        width: 80
        height: 41
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            id: okbgrectangle
            radius: 9
            border.width: 2
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#1b4825"
                }

                GradientStop {
                    position: 1
                    color: "#1ca83b"
                }
            }
            anchors.fill: parent
        }

        Text {
            id: oktext
            color: "#f4f4f4"
            text: qsTr("OK")
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 16
        }

        MouseArea {
            id: okmouseArea
            hoverEnabled: true
            anchors.fill: parent
            onEntered: okbgrectangle.gradient.stops[0].color = Qt.lighter("#dddddd")
            onExited: okbgrectangle.gradient.stops[0].color = "#1b4825"
            onClicked: {
                battleResultUI.hide();
                bform.closeYet = true;                
                battleResultUI.deleteLater()
            }
        }
    }

    Flow {
        id: flow1
        width: 462
        height: 110
        anchors.verticalCenterOffset: 9
        anchors.horizontalCenterOffset: 0
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            id: resulttext
            color: "#79f8f8"
            text: bform.resultText
            anchors.fill: parent
            font.italic: true
            wrapMode: Text.Wrap
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 20
        }
    }

    
}
