import QtQuick 2.12
import QtQuick.Controls 2.4
import "components/Card"

ApplicationWindow {
    id: window
    visible: true
    width: 360
    height: 640
    title: qsTr("The Quests")

    Card {
        anchors.fill: parent
    }
}
