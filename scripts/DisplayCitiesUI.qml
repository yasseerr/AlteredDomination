import QtQuick 2.0
import QtQuick.Controls 1.6
import "../scripts" as MItems
Item {
    id: item1
    width: 100
    height: 479
    visible: true

    Component{
        id:cityGen
        MItems.CityItem{
        }

    }

    Connections{
        target: mainmenu
        onSendCityToDisplay: {
            var obj = cityGen.createObject(citiesItem)
            obj.city = c
            obj.mm = mainmenu
        }
    }
    Connections{
        target: mainmenu
        onClearCitiesInDisplay: {
            citiesItem.children=[]
        }
    }
    Rectangle {
        id: bg
        border.width: 4
        gradient: Gradient {
            GradientStop {
                position: 0.846
                color: "#323d91"
            }
            GradientStop {
                position: 0
                color: "#12152d"
            }
        }
        anchors.fill: parent

        Image {
            id: image
            opacity: 0.4
            fillMode: Image.Tile
            anchors.fill: parent
            source: "qrc:/data/mapmtex.jpg"
        }
    }
    Flickable{
        id : citiesScroll
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        contentHeight: citiesItem.height
        contentWidth: 100
        Flow {
            id: citiesItem
            width: 100
            height: childrenRect.height
            spacing: 2
        }

    }

}
