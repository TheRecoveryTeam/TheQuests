import QtQuick 2.0
import 'qrc:/components/form/FormContainer'
import 'qrc:/components/form/TextInput'
import 'qrc:/components/CustomButton'
import application 1.0

Column {
    id: signUpView
    property var onOpenLoginForm: Function
    property var onContinueSignUp: Function
    property SignUpForm form: SignUpForm {}
    spacing: 10

    FormContainer {
        id: signUpFormContainer
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
                inputId {
                    onTextChanged: {
                        signUpView.form.email = inputId.text
                    }
                    text: signUpView.form.email
                }
                label: 'Email'
                errorText: signUpView.form.emailError
            }

            TextInput {
                id: passwordInput
                nextInput: passwordRepeatInput.inputId
                inputId {
                    onTextChanged: {
                        signUpView.form.password = inputId.text
                    }
                    text: signUpView.form.password
                }
                label: 'Пароль'
                password: true
                errorText: signUpView.form.passwordError
            }

            TextInput {
                id: passwordRepeatInput
                nextInput: emailInput.inputId
                inputId {
                    onTextChanged: {
                        signUpView.form.passwordRepeat = inputId.text
                    }
                    text: signUpView.form.passwordRepeat
                }
                label: 'Повторите пароль'
                password: true
                errorText: signUpView.form.passwordRepeatError
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
            text: 'Вход'
            onClick: signUpView.onOpenLoginForm
        }

        WhiteCustomButton {
            text: 'Далее'
            primary: true
            disabled: !signUpView.form.isValid
            onClick: signUpView.onContinueSignUp
        }
    }
}
