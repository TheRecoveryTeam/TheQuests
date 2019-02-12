import QtQuick 2.11
import QtGraphicalEffects 1.0
import 'qrc:/components/IconText'

Item {

    id: iconButton
    property var onClick
    property string symbolIcon
    property string color: '#ffffff'
    property bool disabled: false

    height: 40
    width: height


    Rectangle {
        anchors.fill: parent
        color: 'transparent'
        opacity: disabled ? 0.2 : 1

        Rectangle {
            id: buttonBackground
            anchors.fill: parent
            radius: parent.height / 2
            color: iconButton.color
            opacity: mouseArea.containsPress && !iconButton.disabled
                    ? 0.2 : 0

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: {
                    if (!iconButton.disabled) {
                        onClick()
                    }
                }
            }
        }

        Rectangle {
            anchors.fill: parent
            radius: parent.height / 2
            color: 'transparent'
            border {
                width: 1
                color: iconButton.color
            }
        }


        Component {
            id: iconTextContainer

            IconText {
                id: iconText

                anchors.centerIn: parent

                text: iconButton.symbolIcon
                color: iconButton.color
            }
        }

        Component {
            id: iconSvgContainer

            Item {
                id: iconSvg
                anchors.fill: parent
                anchors.margins: 10
                Image {
                    id: iconSvgMask
                    anchors.fill: parent
                    source: iconButton.symbolIcon
                    antialiasing: true
                    visible: false
                    fillMode: Image.PreserveAspectFit
                }
                ColorOverlay{
                    anchors.fill: iconSvgMask
                    source: iconSvgMask
                    color: iconButton.color
                    antialiasing: true
                }
            }
        }

        Loader {
            anchors.fill: parent

            sourceComponent: {
                if (symbolIcon.length === 1) {
                    return iconTextContainer;
                }
                return iconSvgContainer;
            }
        }
    }

}
