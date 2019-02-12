import QtQuick 2.11
import 'qrc:/components/CustomButton'
import 'qrc:/components/TexturedRect'
import 'components'
import models 1.0

TexturedRect {
    id: cardContollerView
    property AbstractCardController controller
    property var onBackToQuest
    Item {
        anchors {
            fill: parent
            margins: 20
        }

        Component {
            id: chooseContainer
            ChooseControllerView {
                anchors.fill: parent
                controller: cardContollerView.controller
            }
        }
        Component {
            id: finishContainer
            FinishControllerView {
                anchors.fill: parent
                onBackToQuest: cardContollerView.onBackToQuest
            }
        }

        Loader {
            anchors.fill: parent
            sourceComponent: {
                if (controller !== null && controller.type === 'choose') {
                    return chooseContainer;
                }
                if (controller !== null && controller.type === 'finish') {
                    return finishContainer;
                }

                return Rectangle;
            }
        }
    }
}
