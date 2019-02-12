import QtQuick 2.0
import 'qrc:/components/form/FormContainer'
import 'qrc:/components/form/TextInput'
import 'qrc:/components/CustomButton'
import 'qrc:/components/SimpleText'
import controllers 1.0

Column {
    id: signUpFinishView
    property var onOpenSignUpForm: Function
    property SignUpFinishFrom form
    anchors.fill: parent
    anchors.leftMargin: 10
    anchors.rightMargin: 10
    spacing: 10

    FormContainer {
        id: signUpFinishFormContainer
        label: 'Придумайте никнейм'

        anchors {
            left: parent.left
            right: parent.right
        }

        inputsBlock: Column {
            spacing: 10

            TextInput {
                id: nicknameInput
                inputId {
                    onTextChanged: {
                        signUpFinishView.form.nickname = inputId.text
                    }
                    text: signUpFinishView.form.nickname
                }
                label: 'Никнейм'
                errorText: signUpFinishView.form.nicknameError
                nextInput: nicknameInput.inputId
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
            text: 'Назад'
            onClick: signUpFinishView.onOpenSignUpForm
        }

        WhiteCustomButton {
            text: 'Продолжить'
            primary: true
            disabled: !signUpFinishView.form.isValid
            onClick: signUpFinishView.form.send
        }
    }
}
