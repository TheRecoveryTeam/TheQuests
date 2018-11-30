import QtQuick 2.0
import 'qrc:/components/form/FormContainer'
import 'qrc:/components/form/TextInput'
import 'qrc:/components/CustomButton'
import application 1.0

Column {
    id: loginView
    property var onOpenRegistrationForm: Function
    spacing: 10

    FormContainer {
        id: loginFormContainer
        label: 'Авторизация'

        property LoginForm form: LoginForm {}

        anchors {
            left: parent.left
            right: parent.right
        }

        inputsBlock: Column {
            spacing: 10

            TextInput {
                id: emailInput
                nextInput: passwordInput.inputId
                inputId {
                    onTextChanged: {
                        loginFormContainer.form.email = inputId.text
                    }
                    text: loginFormContainer.form.email
                }
                label: 'Email'
                errorText: loginFormContainer.form.emailError
            }

            TextInput {
                id: passwordInput
                nextInput: emailInput.inputId
                inputId {
                    onTextChanged: {
                        loginFormContainer.form.password = inputId.text
                    }
                    text: loginFormContainer.form.password
                }
                label: 'Пароль'
                password: true
                errorText: loginFormContainer.form.passwordError
            }
        }
    }

    Row {
        anchors {
            left: parent.left
            right: parent.right
        }
        spacing: 20

        WhiteCustomButton {
            id: continueButton
            text: 'Войти'
            primary: true
            disabled: !loginFormContainer.form.isValid

            onClick: disabled ? undefined : function () {
                loginFormContainer.form.send()
            }
        }

        WhiteCustomButton {
            text: 'Регистрация'
            onClick: loginView.onOpenRegistrationForm
        }
    }
}
