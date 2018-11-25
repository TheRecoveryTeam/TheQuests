import QtQuick 2.11
import QtQuick.Controls 2.4
import QtGraphicalEffects 1.0
import 'components/LogoText'
import 'qrc:/components/form/FormContainer'
import 'qrc:/components/form/TextInput'

Page {
    anchors.fill: parent

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
            margins: 10
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

            FormContainer {
                id: loginFormContainer
                label: 'Авторизация'
                anchors {
                    left: parent.left
                    right: parent.right
                }

                inputsBlock: Column {
                    spacing: 10

                    TextInput {
                        id: emailInput
                        nextInput: passwordInput.inputId
                        inputId.onTextChanged: {
                            console.log(inputId.text)
                        }
                        label: 'Email'
                        errorText: 'Пароль слишком короткий'
                    }

                    TextInput {
                        id: passwordInput
                        nextInput: emailInput.inputId
                        label: 'Пароль'
                        password: true
                    }
                }
            }
        }
    }
}
