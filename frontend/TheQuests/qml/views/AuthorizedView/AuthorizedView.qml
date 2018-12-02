import QtQuick 2.11
import QtQuick.Controls 2.4
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.3
import 'components/UserInfoHeader'
import 'components/SettingsPage'
import 'qrc:/components/CustomHeader'
import 'qrc:/components/QuestShort'

StackView {
    id: autorizedStackView
    anchors.fill: parent

    initialItem: Page {
        header: UserInfoHeader {
            id: pageHeader
            curStackView: autorizedStackView
            scrollPosition: flickableContainer.contentY
            contentHeight: flickableContainer.contentHeight / 2
            settingsPage: SettingsPage {
                onClose: function () {
                    autorizedStackView.pop();
                }
            }
        }


        contentChildren: [ Flickable {
            id: flickableContainer;
            anchors.fill: parent
            contentHeight: questColumnLayout.implicitHeight
                           + questColumnLayout.anchors.margins * 2

            Column {
                id: questColumnLayout
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 10
                spacing: 10

                QuestShort {
                    title: 'Заголовок квеста'
                    description: 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam auctor facilisis leo et feugiat. Maecenas molestie pellentesque libero, ut egestas diam lacinia in. In ac neque rhoncus, interdum mi vitae.'
                    questId: 'questId'
                    authorNickname: 'Imechko Familiya'
                    playerCount: 761
                    anchors.left: parent.left
                    anchors.right: parent.right
                    onClick: function(questId) {
                        console.log(questId);
                    }
                }

                QuestShort {
                    title: 'Заголовок квеста'
                    description: 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam auctor facilisis leo et feugiat. Maecenas molestie pellentesque libero, ut egestas diam lacinia in. In ac neque rhoncus, interdum mi vitae.'
                    questId: 'questId1'
                    authorNickname: 'Imechko Familiya'
                    playerCount: 761
                    anchors.left: parent.left
                    anchors.right: parent.right
                }

                QuestShort {
                    title: 'Заголовок квеста'
                    description: 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam auctor facilisis leo et feugiat. Maecenas molestie pellentesque libero, ut egestas diam lacinia in. In ac neque rhoncus, interdum mi vitae.'
                    questId: 'questId2'
                    authorNickname: 'Imechko Familiya'
                    playerCount: 761
                    anchors.left: parent.left
                    anchors.right: parent.right
                }

                QuestShort {
                    title: 'Заголовок квеста'
                    description: 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam auctor facilisis leo et feugiat. Maecenas molestie pellentesque libero, ut egestas diam lacinia in. In ac neque rhoncus, interdum mi vitae.'
                    questId: 'questId3'
                    authorNickname: 'Imechko Familiya'
                    playerCount: 761
                    anchors.left: parent.left
                    anchors.right: parent.right
                }
            }

            ScrollBar.vertical: ScrollBar {
                visible: false
            }
        } ]
    }
}
