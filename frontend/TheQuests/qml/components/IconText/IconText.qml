import QtQuick 2.11

Text {
    id: iconText
    color: '#000000'

    FontLoader {
        id: iconFont
        source: 'qrc:/media/MaterialIcons-Regular.ttf'
        name: 'MaterialIcons'
    }

    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter

    font {
        family: iconFont.name
        pixelSize: 18
    }
}
