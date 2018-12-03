import QtQuick 2.11
import 'qrc:/components/IconText'

Item {

    id: iconButton
    property var onClick
    property string symbolIcon
    property string color: '#ffffff'
    property bool disabled: false

    height: 40
    width: height


Rectangle {
    anchors.fill: parent
    color: 'transparent'
    opacity: disabled ? 0.2 : 1

    Rectangle {
        id: buttonBackground
        anchors.fill: parent
        radius: parent.height / 2
        color: iconButton.color
        opacity: mouseArea.containsPress && !iconButton.disabled
                ? 0.2 : 0

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: {
                if (!iconButton.disabled) {
                    onClick()
                }
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        radius: parent.height / 2
        color: 'transparent'
        border {
            width: 1
            color: iconButton.color
        }
    }

    IconText {
        id: iconText

        anchors.centerIn: parent

        text: iconButton.symbolIcon
        color: iconButton.color
    }
}

}
