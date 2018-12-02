import QtQuick 2.0

Item {
    id: iconButton
    property var onClick
    property string symbolIcon
    property string backgroundColor: '#ffffff'
    property string textColor: 'black'
    property bool disabled: false

    height: 40
    width: height

    Rectangle {
        id: buttonBackground
        anchors.fill: parent
        radius: parent.height / 2
        color: mouseArea.containsPress && !iconButton.disabled
                ? Qt.darker(iconButton.backgroundColor, 1.05)
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

    FontLoader {
        id: iconFont
        source: 'qrc:/media/MaterialIcons-Regular.ttf'
        name: 'MaterialIcons'
    }

    Text {
        id: iconText

        anchors.centerIn: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter


        text: iconButton.symbolIcon
        color: iconButton.textColor
        font {
            family: iconFont.name
            pixelSize: 18
        }
    }
}
