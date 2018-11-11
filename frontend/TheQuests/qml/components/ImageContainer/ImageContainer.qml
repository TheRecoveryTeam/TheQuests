import QtQuick 2.11
import QtQuick.Controls 2.4


Item {
    id: imageContainer
    property string source: 'qrc:/media/king.jpg'

    Rectangle {
        anchors.fill: parent
        BusyIndicator {
            anchors {
                verticalCenter: parent.verticalCenter
                horizontalCenter: parent.horizontalCenter
            }

            running: image.status === Image.Loading
        }
        color: '#4b413a'
    }

    Image {
        id: image
        anchors.fill: parent
        source: imageContainer.source
        fillMode: Image.PreserveAspectCrop
        clip: true
    }
}
