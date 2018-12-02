import QtQuick 2.0
import 'qrc:/components/SimpleText'

Column {
    id: formContainer
    property string label: 'Form label'
    property alias inputsBlock: inputsLoader.sourceComponent

    spacing: 10

    Item {
        height: formLabel.implicitHeight
        anchors {
            left: parent.left
            right: parent.right
        }

        SimpleText {
            id: formLabel
            anchors {
                left: parent.left
                right: parent.right
            }

            text: formContainer.label
            spacing: 2
            size: 24
        }
    }

    Loader {
        id: inputsLoader
        anchors {
            left: formContainer.left
            right: formContainer.right
        }
    }
}
