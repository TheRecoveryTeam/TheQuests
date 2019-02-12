import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import 'qrc:/components/ImageContainer'

Item {
    id: circledImageContainer
    property string source: ''
    property alias  image: image
    property int sideLen
    width: sideLen
    height: sideLen

    ImageContainer {
        id: image
        source: circledImageContainer.source
        anchors.fill: parent
        rawImage.layer {
            enabled: true
            effect: OpacityMask {
                maskSource: itemLogoMask
            }
        }
        placeholder.radius: sideLen / 2
    }

    Rectangle {
        id: itemLogoMask
        visible: false
        width: sideLen
        height: sideLen
        radius: sideLen / 2
    }
}
