import QtQuick 2.12
import QtQuick.Controls 2.4

Label {
    FontLoader {
        id: robotoSlabBold
        source: 'qrc:/media/RobotoSlab-Bold.ttf'
        name: 'RobotoSlabBold'
    }
    property string label: 'Card Heading'

    id: title
    text: label
    color: 'white'
    font {
        family: robotoSlabBold.name
    }
}
