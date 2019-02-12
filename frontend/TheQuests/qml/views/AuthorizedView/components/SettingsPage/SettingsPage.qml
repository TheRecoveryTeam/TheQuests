import QtQuick 2.11
import QtQuick.Controls 2.4
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import 'qrc:/components/CustomHeader'
import 'qrc:/components/CustomButton'
import controllers 1.0

Page {
    id: settingsPage
    property var onClose

    Flickable {
        anchors {
            left: parent.left
            right: parent.right
            top: header.bottom
            bottom: parent.bottom
            margins: 0
        }
        contentHeight: content.implicitHeight + content.anchors.margins

        Column {
            id: content
            padding: 0
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
                margins: 10
            }
            spacing: 10

            CustomButton {
                spacing: 1
                borderColor: '#E5E5E5'
                text: qsTr('Выйти')
                onClick: function () {
                    UserController.logout()
                }
            }
        }

        ScrollBar.vertical: ScrollBar {
            visible: false
        }
    }

    CustomHeader {
        id: header
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        label: 'Настройки'
        onClose: settingsPage.onClose
    }

}
