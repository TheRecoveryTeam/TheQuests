import QtQuick 2.11
import 'qrc:/components/SimpleText'

Item {
    property bool wide: true
    property string text

    anchors {
        left: wide ? parent.left : undefined
        right: wide ? parent.right : undefined
    }
    height: 50

    Rectangle {
        radius: 5
        opacity: mouseArea.containsPress ? 0.8 : 0.6
        color: '#ffffff'
        anchors.fill: parent
        MouseArea {
            id: mouseArea
            anchors.fill: parent
        }
    }

    SimpleText {
        text: parent.text
        anchors.fill: parent
        color: '#333333'
    }
}
