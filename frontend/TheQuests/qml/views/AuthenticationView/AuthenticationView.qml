import QtQuick 2.11
import QtQuick.Controls 2.4
import QtGraphicalEffects 1.0
import 'components/LogoText'
import 'components/LoginFormView'
import 'components/SignUpFormView'
import 'qrc:/components/CustomButton'

Page {
    id: authenticationView
    anchors.fill: parent
    // if signUpView -> false

    LinearGradient {
        id: grad
        property string startColor: '#00B796'
        property string endColor: '#2D9CDB'

        anchors.fill: parent
        start: Qt.point(0, 0)
        end: Qt.point(0, height)

        gradient: Gradient {
            GradientStop { position: 0.0; color: grad.startColor }
            GradientStop { position: 1.0; color: grad.endColor }
        }
    }

    Rectangle {
        anchors {
            left: parent.left
            right: parent.right
            verticalCenter: parent.verticalCenter
            margins: 20
        }
        color: 'transparent'
        height: pageContent.implicitHeight


        Column {
            id: pageContent
            spacing: 10
            anchors.fill: parent

            LogoText {
                id: logo

                anchors {
                    left: parent.left
                    right: parent.right
                }
            }

            SwipeView {
                id: authenticationSwipeView
                currentIndex: !authenticationView.isLoginView

                anchors {
                    left: parent.left
                    right: parent.right
                    margins: -10
                }
                height: Math.max(loginFormContainer.implicitHeight, signUpFormContainer.implicitHeight);

                Column {
                    id: loginFormContainer
                    LoginFormView {
                        anchors {
                            left: parent.left
                            right: parent.right
                            margins: 10
                        }
                    }
                }

                Column {
                    id: signUpFormContainer
                    SignUpFormView {
                        anchors {
                            left: parent.left
                            right: parent.right
                            margins: 10
                        }
                    }
                }
            }

            Row {
                anchors {
                    left: parent.left
                    right: parent.right
                }

                spacing: 20
                CustomButton {
                    property int curIndex: 0
                    property int nextIndex: 1
                    textColor: '#ffffff'
                    text: 'Вход'
                    wide: false
                    backgrounOpacity: authenticationSwipeView.currentIndex === curIndex ? 0.4 : 0;

                    onClick: function () {
                        if (authenticationSwipeView.currentIndex === curIndex) {
                        }
                        else {
                            authenticationSwipeView.currentIndex = curIndex;
                        }
                    }
                }

                CustomButton {
                    property int curIndex: 1
                    property int nextIndex: 0
                    textColor: '#ffffff'
                    text: 'Регистрация'
                    wide: false
                    backgrounOpacity: authenticationSwipeView.currentIndex == curIndex ? 0.4 : 0

                    onClick: function () {
                        if (authenticationSwipeView.currentIndex === curIndex) {
                        }
                        else {
                            authenticationSwipeView.currentIndex = curIndex;
                        }
                    }
                }
            }
        }
    }
}
