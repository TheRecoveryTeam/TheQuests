import QtQuick 2.12
import QtQuick.Controls 2.4

Label {
    FontLoader {
        id: robotoSlabBold
        source: 'qrc:/media/RobotoSlab-Bold.ttf'
        name: 'RobotoSlabBold'
    }
    property string label: 'Card Heading'
    property int spacing: 3
    property int pixelSize: 16

    id: title
    text: label
    color: 'white'
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    font {
        letterSpacing: spacing
        family: robotoSlabBold.name
        pixelSize: pixelSize
    }
}
