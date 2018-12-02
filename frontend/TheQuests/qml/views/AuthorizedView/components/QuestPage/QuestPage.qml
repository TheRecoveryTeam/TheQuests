import QtQuick 2.11
import QtQuick.Controls 2.4
import 'qrc:/components/Card'
import 'qrc:/components/ImageContainer'
import 'qrc:/components/CustomButton'

Item {
    id: questRoot
    property StackView currStackView

    property string questId: 'some quest'
    property string title: 'Quest title'
    property string description: 'Quest description'
    property string imagePath: ''
    property string currCardId: ''
    property string authorNickname: 'Author'
    property int playerCount
    property string stage

    Card {
        title: questRoot.title
        description: questRoot.description
        mediaBlock: SwipeView {
            id: cardSwipeView
            currentIndex: 0
            anchors.fill: parent

            Item {
                id: firstPage
                ImageContainer {
                    anchors.fill: parent
                    source: CardModel.imagePath
                    placeholderColor: '#1D1D1D'
                }
            }


        }

        toolbarBlock: Row {
            anchors.fill: parent
            anchors.margins: 20

            IconButton {
                symbolIcon: qsTr('')
                onClick: currStackView.pop()
            }
        }
    }
}
