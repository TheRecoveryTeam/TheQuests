import QtQuick 2.0
import 'qrc:/components/form/FormContainer'
import 'qrc:/components/form/TextInput'


FormContainer {
    id: loginFormContainer
    label: 'Регистрация'
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
            nextInput: passwordRepeatInput.inputId
            label: 'Пароль'
            password: true
        }

        TextInput {
            id: passwordRepeatInput
            nextInput: emailInput.inputId
            label: 'Повторите пароль'
            password: true
        }
    }
}
