import QtQuick 2.11

Text {
    id: cardDescriptionText
    property int spacing: 4
    property int size: 18

    FontLoader {
        id: robotoSlabBold
        source: 'qrc:/media/Exo2-Regular.ttf'
        name: 'Exo2-Regular'
    }

    wrapMode: Text.Wrap
    color: 'white'
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    font {
        family: robotoSlabBold.name
        letterSpacing: cardDescriptionText.spacing
        pixelSize: cardDescriptionText.size
    }
    lineHeight: 1.3
}
