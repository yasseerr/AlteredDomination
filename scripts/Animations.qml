import QtQuick 2.0

Item {
    id:root
    width: 64
    height: 64
    visible: true
    AnimatedSprite{
        id: explodeAnim
        anchors.fill: parent
        frameDuration: 70
        currentFrame: 0
        source: "qrc:/data/animations/explosion2.png"
        frameWidth: 64
        frameHeight: 64
        frameCount: 16

    }

}
