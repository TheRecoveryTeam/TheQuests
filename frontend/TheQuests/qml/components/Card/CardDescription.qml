import QtQuick 2.11
import 'qrc:/components/SimpleText'

Rectangle {
    property string text

    SimpleText {
        anchors {
            left: parent.left
            right: parent.right
        }

        id: cardDescriptionText
        text: parent.text
    }

    height: cardDescriptionText.implicitHeight
    color: 'transparent'
}
