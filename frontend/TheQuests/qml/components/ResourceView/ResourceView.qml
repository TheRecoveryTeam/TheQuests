import QtQuick 2.11
import QtQuick.Layouts 1.3
import 'qrc:/components/Title'
import 'qrc:/components/SimpleText'

Item {
    id: root
    property int value
    property string name
    width: 50

    Column {
        anchors.verticalCenter: parent.verticalCenter
        id: col

        Title {
            id: title
            label: root.value + ''
            spacing: 1
            pixelSize: 20
            anchors.horizontalCenter: parent.horizontalCenter
        }

        SimpleText {
            id: text
            text: root.name
            spacing: 1
            size: 12
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Component.onCompleted: {
        console.log(root.height, col.height, title.height, text.height);
    }
}
