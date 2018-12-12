import QtQuick 2.11
import QtQuick.Controls 2.4
import 'components/LogoText'
import 'components/LoginFormView'
import 'components/SignUpFormView'
import 'components/SignUpFinishFormView'
import 'components/VKAuthPage'
import 'qrc:/components/SimpleText'
import 'qrc:/components/CustomButton'
import 'qrc:/components/BackgroundGradient'
import controllers 1.0
import models 1.0

StackView {
    id: curStackView
    anchors.fill: parent

    initialItem: Page {
        id: authenticationView
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

        BackgroundGradient {
            startColor: '#00B796'
            endColor: '#2D9CDB'
            anchors.fill: parent
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

                LogoText { }

                SwipeView {
                    id: authenticationSwipeView
                    currentIndex: 0

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
                    height: Math.max(loginFormContainer.implicitHeight,
                                     signUpFormContainer.implicitHeight);

                    Column {
                        id: loginFormContainer
                        spacing: 10

                        LoginFormView {
                            onOpenRegistrationForm: function() {
                                authenticationSwipeView.currentIndex = 1;
                            }
                        }

                        VKAuthPage {
                            curStackView: curStackView
                        }
                    }

                    Column {
                        id: signUpFormContainer
                        SignUpFormView {
                            form: authenticationView.signupForm
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

                    SignUpFinishFormView {
                        form: authenticationView.signupFinishForm
                        onOpenSignUpForm: function () {
                            authenticationSwipeView.currentIndex = 1;
                        }
                    }
                }
            }
        }
    }
}
