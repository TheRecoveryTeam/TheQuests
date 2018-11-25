import QtQuick 2.0
import 'qrc:/components/Title'

Rectangle {
    id: logoText
    property string text: 'The Quests'
    height: 60

    color: 'transparent'

    Title {
        label: logoText.text
        pixelSize: 55
        spacing: 2
        color: '#24A1CD'
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
