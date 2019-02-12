import QtQuick 2.11
import 'qrc:/components/IconText'

Item {
    id: iconButton
    property var onClick
    property string symbolIcon
    property string backgroundColor: '#ffffff'
    property string textColor: 'black'
    property bool disabled: false
    property string borderColor: 'transparent'

    height: 40
    width: height

    Rectangle {
        id: buttonBackground
        anchors.fill: parent
        radius: parent.height / 2
        color: mouseArea.containsPress && !iconButton.disabled
                ? Qt.darker(iconButton.backgroundColor, 1.1)
                : iconButton.backgroundColor
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
            color: parent.borderColor
        }
    }

    IconText {
        id: iconText

        anchors.centerIn: parent

        text: iconButton.symbolIcon
        color: iconButton.textColor
    }
}
