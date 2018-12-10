import QtQuick 2.11
import QtQuick.Controls 2.4
import 'qrc:/components/Card'
import 'qrc:/components/ImageContainer'
import 'qrc:/components/CustomButton'
import 'qrc:/components/Title'
import 'qrc:/components/SimpleText'
import 'qrc:/components/TexturedRect'
import 'qrc:/components/CustomButton'
import 'qrc:/components/IconText'
import 'components/CardView'
import 'components/QuestToolbar'
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
        CardView {
            toolbarBlock: QuestToolbar {
                curStackView: questRoot.curStackView
            }
            onBackToQuest: function() {
                questRoot.curStackView.pop()
            }
        }
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

                    Item {
                        anchors {
                            left: parent.left
                            right: parent.right
                            margins: 10
                        }
                        height: 40

                        Rectangle {
                            radius: 20
                            anchors.fill: parent
                            opacity: 0.9
                            border {
                                width: 1
                                color: '#E5E5E5'
                            }
                        }

                        IconText {
                            id: playerCountIcon
                            anchors {
                                left: parent.left
                                top: parent.top
                                bottom: parent.bottom
                                leftMargin: 20
                            }

                            color: '#565656'
                            text: qsTr('')
                        }

                        SimpleText {
                            text: "" + QuestDetailModel.playerCount
                            color: '#565656'
                            anchors.left: playerCountIcon.right
                            anchors.top: parent.top
                            anchors.bottom: parent.bottom
                            anchors.leftMargin: 10
                            size: 14
                            spacing: 1
                        }

                        SimpleText {
                            text: QuestDetailModel.authorNickName
                            color: '#565656'
                            anchors.right: parent.right
                            anchors.top: parent.top
                            anchors.bottom: parent.bottom
                            anchors.rightMargin: 20
                            size: 14
                            spacing: 1
                        }
                    }

                    CustomButton {
                        text: getButtonLabel()
                        onClick: handleOpenCard
                    }
                }
            }
        }

        toolbarBlock: QuestToolbar {
            curStackView: questRoot.curStackView
        }
    }
}
