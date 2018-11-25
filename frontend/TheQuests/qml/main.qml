import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import 'views/CardView'
import 'views/AuthenticationView'
import 'components/CustomButton'
import models 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 360
    height: 640
    title: qsTr('The Quests')

//    CardView {
//        anchors.fill: parent
//    }

    AuthenticationView {
        anchors.fill: parent
    }
}
