import QtQuick 2.0
import QtMultimedia 5.0
import QtQuick.Particles 2.0
import QtGraphicalEffects 1.0
Item {
    id: root
    width: 640
    height: 480
    visible: true
    anchors.fill: parent
    property int frame: 0
    property var mapFile: JSON.parse(homeClass.mapData)
    property var savesFile: JSON.parse(homeClass.savesData)
    property var tutoFile: JSON.parse(homeClass.tutoData)
    Image {
        id: bgimage
        visible: true
        fillMode: Image.Tile
        anchors.fill: parent
        source: "qrc:/data/mapmtex.jpg"
    }

    Rectangle {
        id: bgrectangle
        opacity: 1
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#e690cafd"
            }

            GradientStop {
                position: 1
                color: "#e6010130"
            }

        }
        anchors.fill: parent
    }

    Image {
        id: earthimage
        width: 475
        height: 260
        anchors.centerIn: parent
        source: "qrc:/data/animations/EarthRotation/"+frame+".png"

    }

    Image {
        id: afkaarimage
        width: 300
        height: 70
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        source: "qrc:/data/logo/afkaarlogo.svg"
    }

    NumberAnimation {
        target: root
        property: "frame"
        duration: 2000
        from: 0
        to:17
        easing.type: Easing.Linear
        loops: NumberAnimation.Infinite
        running: false
    }

    Item {
        id: rotationItem
        width: 500
        height: 500
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        rotation: 0
        Image {
            id: circle
            opacity: 0.5
            anchors.rightMargin: -100
            anchors.leftMargin: -100
            anchors.bottomMargin: -100
            anchors.topMargin: -100
            anchors.fill: parent
            source: "qrc:/data/icons/circle.png"
        }
        Image {
            id: playerAImage
            width: 100
            height: 100
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            source: "qrc:/data/icons/homeA.png"

        }
        Image {
            id: playerBImage
            x: 270
            y: 333
            width: 100
            height: 100
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            transformOrigin: root.Center
            source: "qrc:/data/icons/homeB.png"
        }
        ParticleSystem{
            id:systemA
            anchors.fill: parent
            Emitter{
                anchors.left: parent.left
                anchors.leftMargin: 70
                anchors.top: parent.top
                anchors.topMargin: 70
                sizeVariation: 10
                size: 30
                lifeSpanVariation: 500
                emitRate: 3
                velocity: TargetDirection{
                    targetItem: playerBImage
                    magnitudeVariation: 300
                    magnitude: 500

                }
            }
            ImageParticle{
                alphaVariation: 0.2
                source: "qrc:/data/fire.png"
            }
        }
        ParticleSystem{
            id:systemB
            anchors.fill: parent
            Emitter{
                anchors.right: parent.right
                anchors.rightMargin: 70
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 70
                sizeVariation: 10
                size: 30
                lifeSpanVariation: 500
                emitRate: 3
                velocity: TargetDirection{
                    targetItem: playerAImage
                    magnitudeVariation: 300
                    magnitude: 500

                }
            }
            ImageParticle{

                alphaVariation: 0.2
                source: "qrc:/data/fire.png"
            }
        }

        ParallelAnimation{
            id: rotationAnimation
            running: false
            NumberAnimation {
                target: rotationItem
                property: "rotation"
                from :0
                to : -360
                loops: NumberAnimation.Infinite
                duration: 6000
                easing.type: Easing.Linear
            }
            NumberAnimation {
                target: playerAImage
                property: "rotation"
                from :0
                to : 360
                loops: NumberAnimation.Infinite
                duration: 6000
                easing.type: Easing.Linear
            }
            NumberAnimation {
                target: playerBImage
                property: "rotation"
                from :0
                to : 360
                loops: NumberAnimation.Infinite
                duration: 6000
                easing.type: Easing.Linear
            }

        }


    }



    Loader{
        id:menuLoader
        width: 200
        source: "qrc:/scripts/home/HomeMenuComponant.qml"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 30


    }

    Loader{
        id:mainloader
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        anchors.top: parent.top
        anchors.topMargin: 100
        anchors.right: menuLoader.left
        anchors.rightMargin: 20
        source: ""
        anchors.left: parent.left
        anchors.leftMargin: 100

    }


    Audio{
        id:au
        source: "qrc:/data/sounds/hover.wav"
    }
    Audio{
        id:battleAmbiant
        autoPlay: false
        source: "qrc:/data/sounds/battleambiant.MP3"
        loops: Audio.Infinite
        volume: 0.3
    }
    Audio{
        id:bgAmbiant
        autoPlay: false
        source: "qrc:/data/sounds/ambiant1.MP3"
        loops: Audio.Infinite
        volume: 0.4
    }
    Timer{
        id :audiooffset
        running: true
        interval: 8000
        onTriggered: {
            bgAmbiant.play()
            battleAmbiant.play()
        }

    }



}
