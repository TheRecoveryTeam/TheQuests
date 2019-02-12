import QtQuick 2.11
import QtQuick.Controls 2.2
import 'qrc:/components/CustomButton'
import models 1.0
import controllers 1.0

Item {
    property ChooseCardModel controller

    Item {
        id: column
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter

        ListView {
            id: listView
            interactive: false
            anchors.fill: parent

            model: controller ? controller.linksList : 0;
            spacing: 20
            delegate: CustomButton {
                id: button
                text: model.link
                onClick: function () {
                    CardController.doAnswer('123', model.link)
                }
            }
            onCountChanged: {
                column.height = listView.visibleChildren[0].height
            }
        }
    }
}
