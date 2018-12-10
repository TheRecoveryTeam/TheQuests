import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Window 2.11
import QtQuick.LocalStorage 2.0
import "../js/db.js" as JS
import 'views/CardView'
import 'views/AuthenticationView'
import 'views/AuthorizedView'
import 'components/CustomButton'
import models 1.0
import controllers 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 360
    height: 640
    title: qsTr('The Quests')

    // If android android
    // visibility: Window.FullScreen

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

    property var handleSelectUser: function(result) {
        if (result !== null) {
            console.log('result: ', result.nickname);
            UserController.checkAuth(result.user_id,
                                     result.nickname,
                                     result.email,
                                     result.vk_id,
                                     result.token,
                                     result.avatar_path);
        }
    }

    Component.onCompleted: {
        console.log('on completed');
        JS.dbInit();
        JS.dbRead(window.handleSelectUser);
    }
    Connections {
        target: UserController
        onAuthorized: function(userId, nickname, email, vkId, token, expires, avatarPath) {
            console.log("kek: ", userId, nickname, email, vkId, token, expires, avatarPath);
            JS.dbInsert(userId, nickname, email, vkId, token, avatarPath);
            console.log("completed");
        }
        onLoggedOut: function() {
            JS.dbDeleteRows();
            console.log("kek: logged out");
        }
    }
}
