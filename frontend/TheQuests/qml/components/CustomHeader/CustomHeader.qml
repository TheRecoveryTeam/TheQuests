import QtQuick 2.0
import 'qrc:/components/Divider'
import 'qrc:/components/CustomButton'
import 'qrc:/components/Title'


Rectangle {
    id: customHeader
    property string label
    property var onClose
    height: 50
    color: 'white'

    Title {
        label: customHeader.label
        color: 'black'
        spacing: 1
        anchors.fill: parent
    }

    IconButton {
        anchors {
            right: parent.right
            verticalCenter: parent.verticalCenter
            rightMargin: 10
        }
        symbolIcon: qsTr("") // close material icon
        onClick: parent.onClose
    }

    Divider {
        anchors.bottom: parent.bottom
    }
}
