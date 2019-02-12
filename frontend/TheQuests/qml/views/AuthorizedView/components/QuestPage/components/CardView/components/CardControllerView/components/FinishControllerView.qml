import QtQuick 2.11
import QtQuick.Controls 2.4
import 'qrc:/components/CustomButton'

Item {
    property var onBackToQuest

    anchors.fill: parent
    CustomButton {
        anchors.verticalCenter: parent.verticalCenter
        id: button
        text: qsTr('Вернуться к квесту')
        onClick: onBackToQuest
    }
}
