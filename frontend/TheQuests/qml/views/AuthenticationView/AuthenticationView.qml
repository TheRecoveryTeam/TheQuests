import QtQuick 2.11
import QtQuick.Controls 2.4
import QtGraphicalEffects 1.0
import 'components/LogoText'
import 'components/LoginFormView'
import 'components/SignUpFormView'
import 'components/SignUpFinishFormView'
import 'qrc:/components/SimpleText'
import 'qrc:/components/CustomButton'
import application 1.0

Page {
    id: authenticationView
    anchors.fill: parent
    property SignUpForm signupForm: SignUpForm { onIsValidChanged: function (isValid) {
        if (isValid) {
            authenticationSwipeView.addPage(signUpFinishView)
            authenticationView.signupFinishForm.initialize(signupForm.email, signupForm.password)
        }
        else {
            authenticationSwipeView.removePage(signUpFinishView)
        }
    } }
    property SignUpFinishFrom signupFinishForm: SignUpFinishFrom {}

    LinearGradient {
        id: grad
        property string startColor: '#303434'
        property string endColor: '#1D1D1D'

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

                function addPage(page) {
                    addItem(page);
                    page.visible = true;
                }

                function removePage(page) {
                    for (var n = 0; n < count; n++) { if (page === itemAt(n)) { removeItem(n) } }
                    page.visible = false
                }

                anchors {
                    left: parent.left
                    right: parent.right
                    margins: -10
                }
                height: Math.max(loginFormContainer.implicitHeight, signUpFormContainer.implicitHeight);

                Column {
                    id: loginFormContainer
                    spacing: 10

                    LoginFormView {
                        anchors {
                            left: parent.left
                            right: parent.right
                            margins: 10
                        }
                        onOpenRegistrationForm: function() {
                            authenticationSwipeView.currentIndex = 1;
                        }
                    }

                    Row {
                        spacing: 10
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.margins: 10
                        height: 60

                        SimpleText {
                            anchors.verticalCenter: parent.verticalCenter
                            text: 'Войти с помощью'
                            spacing: 1
                        }

                        OutlinedIconButton {
                            anchors.verticalCenter: parent.verticalCenter
                            symbolIcon: 'qrc:/media/vk-logo.svg'
                        }
                    }
                }

                Column {
                    id: signUpFormContainer
                    SignUpFormView {
                        form: signupForm
                        anchors {
                            left: parent.left
                            right: parent.right
                            margins: 10
                        }
                        onOpenLoginForm: function() {
                            authenticationSwipeView.currentIndex = 0;
                        }
                        onContinueSignUp: function() {
                            authenticationSwipeView.currentIndex = 2;
                        }
                    }
                }
            }

            Page {
                id: signUpFinishView
                visible: false
                background: Rectangle { color: 'transparent' }
                Item {
                    anchors {
                        leftMargin: 10
                        rightMargin: 10
                        fill: parent
                    }

                    SignUpFinishFormView {
                        anchors.fill: parent
                        form: signupFinishForm
                        onOpenSignUpForm: function () {
                            authenticationSwipeView.currentIndex = 1;
                        }
                    }
                }
            }
        }
    }
}
