import QtQuick 2.9
import QtGraphicalEffects 1.0

LinearGradient {
    property string startColor: '#303434'
    property string endColor: '#1D1D1D'

    anchors {
        left: parent.left
        right: parent.right
        top: parent.top
        bottom: parent.bottom
    }
    start: Qt.point(0, 0)
    end: Qt.point(0, height)

    gradient: Gradient {
        GradientStop { position: 0.0; color: startColor }
        GradientStop { position: 1.0; color: endColor }
    }
}
