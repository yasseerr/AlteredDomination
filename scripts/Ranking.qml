import QtQuick 2.0
import QtQuick.Controls 1.6

Item {
    id: item1
    width: 100
    height: 479
    visible: true

    Connections{
        target: mainmenu
        onSendCountryToRanking: {
            var obj = countryComponent.createObject(countriesItem)
            obj.country = c
            obj.rank = r

        }
    }
    Connections{
        target: mainmenu
        onClearCountriesInRanking: {
            countriesItem.children = []
        }
    }

    Rectangle {
        id: bg
        border.width: 4
        gradient: Gradient {
            GradientStop {
                position: 0.846
                color: "#329157"
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
        id : countriesScroll
        contentHeight: countriesItem.height
        contentWidth: 170
        anchors.leftMargin: 5
        anchors.fill: parent
        Flow {
            id: countriesItem
            width: 170
            height: childrenRect.height
            spacing: 2
        }

    }
    Component{
        id: countryComponent
        Item{
            property var country: null
            property int rank: 0
            id:root
            height: 60
            width: 150
            visible: true

            Rectangle{
                id:bg
                color: root.country.income!=0?"#185795":"#ff0000"
                radius: 4
                border.width: 3
                anchors.fill: parent
                opacity: 0.7

            }
            Rectangle{
                id:lineUnderName
                height: 3
                radius: 2
                anchors.right: countryName.right
                anchors.rightMargin: 0
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "#caf533"
                    }

                    GradientStop {
                        position: 1
                        color: "#000000"
                    }
                }
                anchors.left: countryName.left
                anchors.top: countryName.bottom
                anchors.topMargin: 3
            }
            Text {
                id: countryName
                color: "#eff4f4"
                text: root.rank+" - "+root.country.name
                clip: true
                font.bold: true
                font.pointSize: 7
                anchors.left: parent.left
                anchors.leftMargin: 7
                anchors.top: parent.top
                anchors.topMargin: 6

            }
            Text {
                id: countryIncome
                color: "#38f711"
                text: root.country.income
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                horizontalAlignment: Text.AlignRight
                anchors.right: parent.right
                anchors.rightMargin: 15
                font.bold: true
                font.pointSize: 12

            }

        }
    }
}
