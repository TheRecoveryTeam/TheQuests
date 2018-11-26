import QtQuick 2.11
import QtQuick.Controls 2.4
import 'qrc:/components/SimpleText'

Column {
    id: inputRoot
    property alias inputId: textInput
    property var nextInput
    property string label
    property bool password: false
    property string errorText

    anchors {
        left: parent.left
        right: parent.right
    }
    spacing: 5

    Item {
        id: labelContainer
        height: labelText.implicitHeight
        anchors {
            left: parent.left
            right: parent.right
        }

        SimpleText {
            id: labelText
            text: label
            horizontalAlignment: Text.AlignLeft
            size: 16
            spacing: 1
        }
    }

    Rectangle {
        anchors {
            left: parent.left
            right: parent.right
        }
        color: 'transparent'
        border {
            width: 1
            color: '#ffffff'
        }
        radius: 10

        height: 50
        Rectangle {
            id: textInputContainer
            radius: parent.radius
            opacity: textInput.cursorVisible ? 0.5 : 0.3
            color: '#ffffff'
            height: 50
            anchors.fill: parent
        }

        TextInput {
            id: textInput
            anchors {
                fill: parent
                leftMargin: 13
            }
            verticalAlignment: TextInput.AlignVCenter
            font {
                pixelSize: 16
            }
            color: '#ffffff'
            echoMode: inputRoot.password ? TextInput.Password : TextInput.Normal
            KeyNavigation.tab: inputRoot.nextInput
            maximumLength: 36
        }
    }


    Item {
        height: labelText.implicitHeight
        anchors {
            left: parent.left
            right: parent.right
        }

        SimpleText {
            id: errorText
            text: inputRoot.errorText
            horizontalAlignment: Text.AlignLeft
            color: '#EF9A9A'
            size: 16
            spacing: 1
        }
    }

}
