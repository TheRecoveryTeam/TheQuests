import QtQuick 2.11
import QtQuick.Controls 2.4
import 'qrc:/components/Card'
import 'qrc:/components/ImageContainer'
import 'qrc:/components/CustomButton'
import 'qrc:/components/Title'
import 'qrc:/components/SimpleText'
import 'qrc:/components/TexturedRect'
import 'qrc:/components/CustomButton'
import 'qrc:/views/CardView'
import models 1.0
import controllers 1.0

Item {
    id: questRoot
    property StackView curStackView
    property string questId

    property var getButtonLabel: function (){
        if (QuestDetailModel.stage === '') {
            return 'Начать квест!';
        }
        if (QuestDetailModel.stage === 'end') {
            return 'Пройти квест снова!';
        }
        return 'Продолжить квест!';
    }

    Component {
        id: cardView
        CardView {}
    }

    property var handleOpenCard: function (){
        CardController.get(QuestDetailModel.currCardId);
        curStackView.push(cardView);
    }

    Component.onCompleted: function() {
        console.log(questId);
        QuestController.getQuestDetail(questId);
    }

    Card {
        anchors.fill: parent
        title: QuestDetailModel.title
        description: QuestDetailModel.description
        mediaBlock: SwipeView {
            id: cardSwipeView
            currentIndex: 0
            anchors.fill: parent

            Item {
                id: firstPage
                ImageContainer {
                    anchors.fill: parent
                    source: QuestDetailModel.imagePath
                    placeholderColor: '#1D1D1D'
                }
            }

            TexturedRect {
                id: infoPage
                Column {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.margins: 20
                    spacing: 20

                    SimpleText {
                        text: 'Сейчас играют: ' + QuestDetailModel.playerCount
                    }

                    SimpleText {
                        text: 'Автор: ' + QuestDetailModel.authorNickName
                    }

                    CustomButton {
                        text: getButtonLabel()
                        onClick: handleOpenCard
                    }
                }
            }
        }

        toolbarBlock: Item {
            anchors.fill: parent
            anchors.margins: 20

            OutlinedIconButton {
                symbolIcon: qsTr('')
                onClick: curStackView.pop
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
            }

            Title {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                label: "by " + QuestDetailModel.authorNickName
            }
        }
    }
}
