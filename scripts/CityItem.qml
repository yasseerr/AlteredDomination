import QtQuick 2.0

Item {
    id:rootCity
    property string name: ""
    property var city: null
    property var mm: null
    width: 170
    height: 40
    visible: true
    Rectangle {
        id: bg
        color: "#0d7489"
        radius: 4
        border.width: 1
        opacity: 0.8
        anchors.fill: parent
    }

    MouseArea {
        id: ctyArea
        hoverEnabled: true
        anchors.fill: parent
        onEntered: bg.color = Qt.lighter("#0d7489")
        onExited: bg.color = "#0d7489"
        onPressed: mm.focusOnCity(city)
    }

    Text {
        id: citytext
        x: 95
        y: 10
        color: "#f9f8f8"
        text: city.name
        font.bold: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 16
    }

}
