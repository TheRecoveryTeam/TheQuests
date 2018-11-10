import QtQuick 2.12
import QtQuick.Controls 2.4
import './components/Card'
import './components/CustomButton'
import models 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 360
    height: 640
    title: qsTr('The Quests')

    Card {
        anchors.fill: parent
        title: CardModel.title
        description: CardModel.description
        mediaBlock: Rectangle {
            color: '#362c23'
            CustomButton {
                text: 'click me'
            }
        }
    }
}
