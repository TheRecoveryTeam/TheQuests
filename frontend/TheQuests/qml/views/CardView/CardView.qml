import QtQuick 2.11
import QtQuick.Controls 2.4
import 'qrc:/components/Card'
import 'qrc:/components/CustomButton'
import 'qrc:/components/ImageContainer'
import 'components/CardControllerView'
import models 1.0


Card {
    title: CardModel.title
    description: CardModel.description
    mediaBlock: SwipeView {
        id: cardSwipeView
        currentIndex: 0
        anchors.fill: parent

        Item {
            id: firstPage
            ImageContainer {
                anchors.fill: parent
                source: CardModel.imagePath
                placeholderColor: '#4b413a'
            }
        }
        CardControllerView {
            controller: CardModel.controller
        }
    }
}
