import QtQuick 2.11
import QtQuick.Controls 2.2
import 'qrc:/components/CustomButton'
import application 1.0
import controllers 1.0

Item {
    property ChooseCardModel controller

    ListView {
        interactive: false
        anchors.fill: parent
        model: controller ? controller.linksList : 0;
        spacing: 20
        delegate: CustomButton {
            text: model.link.answer
            onClick: function () {
                CardController.doAnswer('123', model.link.answer)
            }
        }
    }
}
