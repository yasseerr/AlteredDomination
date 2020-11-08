import QtQuick 2.0
import QtQuick.Controls 2.3

Item {
    id: item1
    Image {
        id: image
        anchors.fill: parent
        source: "qrc:/data/icons/loading.svg"
    }

    BusyIndicator {
        id: busyIndicator
        x: 1047
        y: 813
        width: 66
        height: 69
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
    }

    Text {
        id: text1
        x: 499
        y: 421
        text: qsTr("Loading ...")
        font.family: "Courier"
        anchors.right: busyIndicator.left
        anchors.rightMargin: 10
        font.pixelSize: 17
    }

}
