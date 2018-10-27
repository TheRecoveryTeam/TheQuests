import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.3

Rectangle {
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

        Rectangle {
            id: cardDescription
            property string text: currentCard.description
            Text {
                FontLoader {
                    id: robotoSlabBold
                    source: 'qrc:/media/Exo2-Regular.ttf'
                    name: 'Exo2-Regular'
                }

                id: cardDescriptionText
                anchors.fill: parent
                text: qsTr(cardDescription.text)
                wrapMode: Text.Wrap
                color: 'white'
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font {
                    family: robotoSlabBold.name
                    letterSpacing: 4
                }
                lineHeight: 1.3
            }
            anchors {
                left: parent.left
                right: parent.right
                margins: 20
            }
            height: cardDescriptionText.implicitHeight
            color: 'transparent'
        }

        Pane {
            id: mediaFrame
            property int marginValue: 20
            property int side: parent.width - marginValue * 2
            height: side
            width: side

            anchors {
                top: cardDescription.bottom
                left: parent.left
                right: parent.right
                margins: marginValue
            }

            Material.elevation: 3
        }

        Rectangle {
            id: heading

            anchors {
                left: parent.left
                right: parent.right
                top: mediaFrame.bottom
            }

            height: 80

            CardHeading {
                anchors.fill: parent
                label: currentCard.title
            }
            color: 'transparent'
        }
        color: 'transparent'
    }
    }
}
