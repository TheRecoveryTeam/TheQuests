import QtQuick 2.11
import 'qrc:/components/SimpleText'

Item {
    id: customButton
    property bool wide: true
    property string text
    property var onClick
    property string backgroundColor: '#ffffff'
    property string borderColor: backgroundColor
    property string textColor: '#333333'
    property bool contained: true
    property double backgrounOpacity: 0.6
    property int spacing: 3
    property bool disabled: false

    anchors {
        left: wide ? parent.left : undefined
        right: wide ? parent.right : undefined
//        margins: 20
    }
    height: 50
    width: wide ? undefined : buttonText.implicitWidth + 40

    Rectangle {
        anchors.fill: parent
        radius: 10
        color: 'transparent'
        border {
            width: 1
            color: customButton.borderColor
        }
        Rectangle {
            radius: parent.radius
            opacity: mouseArea.containsPress && !disabled
                     ? customButton.backgrounOpacity + 0.2
                     : customButton.backgrounOpacity
            color: customButton.backgroundColor
            anchors.fill: parent
            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: {
                    if (!customButton.disabled) {
                        onClick()
                    }
                }

            }
        }
    }

    SimpleText {
        id: buttonText
        text: parent.text
        anchors.fill: parent
        wrapMode: Text.NoWrap
        color: customButton.textColor
        spacing: parent.spacing
    }
}
