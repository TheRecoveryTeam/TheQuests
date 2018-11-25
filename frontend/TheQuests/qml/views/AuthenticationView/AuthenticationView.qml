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
    property bool isLoginView: true

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

            Component {
                id: loginContainer
                LoginFormView {}
            }

            Component {
                id: signUpContainer
                SignUpFormView {}
            }

            Loader {
                anchors {
                    left: parent.left
                    right: parent.right
                }
                sourceComponent: authenticationView.isLoginView
                                 ? loginContainer
                                 : signUpContainer
            }

            Row {
                anchors {
                    left: parent.left
                    right: parent.right
                }

                spacing: 10
                CustomButton {
                    textColor: '#ffffff'
                    text: 'Вход'
                    wide: false
                    backgrounOpacity: authenticationView.isLoginView ? 0.4 : 0

                    onClick: function () {
                        if (authenticationView.isLoginView) {
                            // TODO: process login
                        }
                        else {
                            authenticationView.isLoginView = true;
                        }
                    }
                }

                CustomButton {
                    textColor: '#ffffff'
                    text: 'Регистрация'
                    wide: false
                    backgrounOpacity: authenticationView.isLoginView ? 0 : 0.4

                    onClick: function () {
                        if (authenticationView.isLoginView) {
                            authenticationView.isLoginView = false;
                        }
                        else {
                            // TODO: process signup
                        }
                    }
                }
            }
        }
    }
}
