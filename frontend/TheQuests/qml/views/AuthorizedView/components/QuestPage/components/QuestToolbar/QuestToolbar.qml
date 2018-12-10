import QtQuick 2.11
import QtQuick.Controls 2.4
import 'qrc:/components/CustomButton'
import 'qrc:/components/ResourceView'
import 'qrc:/components/Title'
import models 1.0

Item {
    anchors.fill: parent
    anchors.leftMargin: 20
    property StackView curStackView

    Row {
        anchors.fill: parent
        spacing: 20

        OutlinedIconButton {
            id: backButton
            symbolIcon: qsTr('')
            onClick: curStackView.pop
            anchors.verticalCenter: parent.verticalCenter
        }

        ListView {
            id: resourceListView
            model: QuestDetailModel.resources
            interactive: false
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            spacing: 20
            orientation: ListView.Horizontal

            delegate: ResourceView {
                id: resource
                value: model.value
                name: model.name
                height: resourceListView.height
            }

            onCountChanged: {
                resourceListView.width = resourceListView.visibleChildren[0].width
            }
        }
    }
}
