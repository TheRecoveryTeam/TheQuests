import QtQuick 2.11

Rectangle {
    Image {
        anchors.fill: parent
        fillMode: Image.Tile
        source: 'qrc:/media/pointStars.svg'
        verticalAlignment: Image.verticalCenter
        horizontalAlignment: Image.horizontalCenter
    }
    color: '#403933'
}
