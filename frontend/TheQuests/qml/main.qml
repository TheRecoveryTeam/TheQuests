import QtQuick 2.12
import QtQuick.Controls 2.4
import 'views/CardView'
import 'components/CustomButton'
import models 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 360
    height: 640
    title: qsTr('The Quests')

    CardView {
        anchors.fill: parent
    }
}
