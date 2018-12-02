import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Window 2.11
import 'views/CardView'
import 'views/AuthenticationView'
import 'views/AuthorizedView'
import 'components/CustomButton'
import models 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 360
    height: 640
    title: qsTr('The Quests')

    // If android android
//    visibility: Window.FullScreen

    Component {
        id: cardContainer
        AuthorizedView {
            anchors.fill: parent
        }
    }

    Component {
        id: authenticationContainer
        AuthenticationView {
            anchors.fill: parent
        }
    }

    Loader {
        anchors.fill: parent
        sourceComponent: UserModel.isAuthenticated
                         ? cardContainer
                         : authenticationContainer
    }

}
