import QtQuick 2.0
import QtQuick.Controls 1.6
import "../scripts" as MItems
Item {
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
    Rectangle {
        id: bg
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
    ScrollView{
        id : citiesScroll
        anchors.fill: parent
        Flow {
            id: citiesItem
            width: 100
            height: childrenRect.height
            spacing: 2
        }

    }

}
