import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.3
import models 1.0
import 'qrc:/components/Title'

Rectangle {
    id: cardRoot
    property string title
    property string description
    property alias mediaBlock: mediaLoader.sourceComponent
    property alias toolbarBlock: toolbarLoader.sourceComponent

    BackgroundCardGradient {
        anchors.fill: parent
    }

    CardToolbar {
        id: cardToolbar
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }
        Loader {
            id: toolbarLoader
            anchors.fill: parent
        }
    }

    Rectangle {
        id: cardContentContainer
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            top: cardToolbar.bottom
        }

        color: 'transparent'
        Rectangle {
            id: cardContent
            height: mediaFrame.height + heading.height + cardDescription.height
            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                right: parent.right
            }

            CardDescription {
                id: cardDescription
                text: cardRoot.description
                anchors {
                    left: parent.left
                    right: parent.right
                    margins: 20
                }
            }

            Pane {
                id: mediaFrame
                readonly property int marginValue: 20
                readonly property int side: Math.min(
                    parent.width - marginValue * 2,
                    cardRoot.height - cardToolbar.height
                    - cardDescription.height - heading.height
                )
                height: side
                width: side
                padding: 0

                anchors {
                    top: cardDescription.bottom
                    horizontalCenter: parent.horizontalCenter
                    margins: marginValue
                }

                Material.elevation: 3

                Loader {
                    id: mediaLoader
                    anchors.fill: parent
                }
            }

            Rectangle {
                id: heading

                anchors {
                    left: parent.left
                    right: parent.right
                    top: mediaFrame.bottom
                }

                height: 80

                Title {
                    anchors.fill: parent
                    label: cardRoot.title
                }

                color: 'transparent'
            }
            color: 'transparent'
        }
    }
}
