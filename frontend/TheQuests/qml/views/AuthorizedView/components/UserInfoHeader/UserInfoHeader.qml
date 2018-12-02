import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import 'qrc:/components/ImageCircled'
import 'qrc:/components/Title'
import 'qrc:/components/Divider'
import 'qrc:/components/SimpleText'
import 'qrc:/components/CustomButton'

import models 1.0

Rectangle {
    id: headerPanel
    height: userUnfoColumn.implicitHeight + userUnfoColumn.anchors.margins
    property StackView curStackView
    property var settingsPage

    Column {
        id: userUnfoColumn
        spacing: 20
        anchors {
            fill: parent
            margins: spacing
        }

        Row {
            id: userShortRow
            spacing: userUnfoColumn.spacing
            anchors {
                left: parent.left
                right: parent.right
            }
            Item {
                width: 100
                height: width
                ImageCircled {
                    anchors.fill: parent
                    sideLen: parent.width
                    image.placeholderColor: '#24A1CD'
                }
                IconButton {
                    anchors {
                        right: parent.right
                        bottom: parent.bottom
                    }

                    symbolIcon: qsTr("") // settings icon material
                    onClick: function() {
                        headerPanel.curStackView.push(settingsPage)
                    }

                    borderColor: '#E5E5E5'
                }
            }
            Column {
                anchors.verticalCenter: parent.verticalCenter
                id: userInfoDetails
                spacing: 5
                Title {
                    label: UserModel.nickname || 'Imechko Familiya'
                    spacing: 1
                    pixelSize: 18
                    color: 'black'
                }
                SimpleText {
                    text: UserModel.email || 'example@gmail.com'
                    spacing: 1
                    size: 16
                    color: '#565656'
                }
            }
        }

        Divider {
            anchors.leftMargin: -1 * parent.spacing
            anchors.rightMargin: anchors.leftMargin
        }
    }
}
