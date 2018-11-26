import QtQuick 2.0
import 'qrc:/components/form/FormContainer'
import 'qrc:/components/form/TextInput'
import application 1.0

FormContainer {
    id: loginFormContainer
    label: 'Регистрация'

    property SignUpForm form: SignUpForm {}
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
                    form.email = inputId.text
                }
                text: form.email
            }
            label: 'Email'
            errorText: form.emailError
        }

        TextInput {
            id: passwordInput
            nextInput: passwordRepeatInput.inputId
            inputId {
                onTextChanged: {
                    form.password = inputId.text
                }
                text: form.password
            }
            label: 'Пароль'
            password: true
            errorText: form.passwordError
        }

        TextInput {
            id: passwordRepeatInput
            nextInput: emailInput.inputId
            inputId {
                onTextChanged: {
                    form.passwordRepeat = inputId.text
                }
                text: form.passwordRepeat
            }
            label: 'Повторите пароль'
            password: true
            errorText: form.passwordRepeatError
        }
    }
}
