import QtQuick 2.11
import 'qrc:/components/CustomButton'
import 'qrc:/components/TexturedRect'
import 'components'
import application 1.0

TexturedRect {
    id: cardContollerView
    property AbstractCardController controller
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

        Loader {
            anchors.fill: parent
            sourceComponent: {
                if (controller !== null && controller.type === 'choose') {
                    return chooseContainer;
                }
                return Rectangle;
            }
        }
    }
}
