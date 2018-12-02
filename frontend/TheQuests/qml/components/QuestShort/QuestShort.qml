import QtQuick 2.11
import QtQuick.Controls 2.4
import QtGraphicalEffects 1.0
import 'qrc:/components/Title'
import 'qrc:/components/SimpleText'

Rectangle {
    id: questShort
    property string id
    property string title
    property string description
    property string authorNickname
    property int playerCount
    property string imagePath: 'qrc:/media/king.jpg'

    height: width

    radius: 20

    Image {
        id: backgoundImage
        anchors.fill: parent
        anchors.margins: 1
        source: imagePath
        clip: true
        fillMode: Image.PreserveAspectCrop
        layer {
            enabled: true
            effect: OpacityMask { maskSource: imageMask }
        }
    }

    Rectangle {
        id: imageMask
        visible: false
        anchors.fill: parent
        anchors.margins: parent.border.width
        radius: questShort.radius
    }

    LinearGradient {
        id: grad

        anchors.fill: parent
        start: Qt.point(0, 0)
        end: Qt.point(0, height)

        gradient: Gradient {
            GradientStop { position: 0.0; color: "#ffffff" }
            GradientStop { position: (
                                         descriptionContainer.height
                                         + titleContainer.height
                                         + contentContainer.spacing
                ) / height; color: "#e2ffffff" }
            GradientStop { position: 1.0; color: "transparent" }
        }

        layer {
            enabled: true
            effect: OpacityMask { maskSource: imageMask }
        }
    }

    Column {
        id: contentContainer
        anchors {
            fill: parent
            margins: 20
        }
        spacing: 20

        Title {
            id: titleContainer
            label: questShort.title
            color: 'black'
            spacing: 1
            pixelSize: 18
            horizontalAlignment: Text.AlignLeft
            anchors.left: parent.left
            anchors.right: parent.right
        }
        SimpleText {
            id: descriptionContainer
            text: questShort.description
            color: '#565656'
            spacing: 1
            size: 16
            horizontalAlignment: Text.AlignLeft
            anchors.left: parent.left
            anchors.right: parent.right
        }
    }

    Rectangle {
        anchors.fill: parent
        color: 'transparent'
        radius: parent.radius
        border {
            width: 1
            color: '#E5E5E5'
        }
    }
}
