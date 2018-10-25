import QtQuick 2.12
import QtQuick.Controls 2.4
import "components"

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("The Quests")

    BackgroundCardGradient {

    }

    CardToolbar {
        id: cardToolbar
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }
    }

    CardHeading {
        id: title
        label: 'MyCustomText'
    }
}
