import QtQuick 2.0
import 'qrc:/components/Title'

Rectangle {
    id: logoText
    property string text: 'The Quests'
    height: 60
    anchors {
        left: parent.left
        right: parent.right
    }

    color: 'transparent'

    Title {
        label: logoText.text
        pixelSize: 55
        spacing: 2
        color: '#2D9CDB'
        anchors.centerIn: parent
        anchors.verticalCenterOffset: 3
        anchors.horizontalCenterOffset: 3
    }
    Title {
        anchors.fill: parent
        label: logoText.text
        pixelSize: 55
        spacing: 2
    }
}
