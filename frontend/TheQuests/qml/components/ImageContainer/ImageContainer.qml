import QtQuick 2.11
import QtQuick.Controls 2.4


Item {
    id: imageContainer
    property string source: 'qrc:/media/king.jpg'
    property string placeholderColor: 'transparent'
    property alias rawImage: image
    property alias placeholder: placeholder

    Rectangle {
        id: placeholder
        anchors.fill: parent
        BusyIndicator {
            anchors {
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
            }

            running: image.status === Image.Loading
        }
        color: imageContainer.placeholderColor
    }

    Image {
        id: image
        anchors.fill: parent
        source: imageContainer.source
        fillMode: Image.PreserveAspectCrop
        clip: true
    }
}
