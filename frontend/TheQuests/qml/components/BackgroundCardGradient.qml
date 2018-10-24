import QtQuick 2.0
import QtGraphicalEffects 1.0

LinearGradient {
    anchors {
        left: parent.left
        right: parent.right
        top: parent.top
        bottom: parent.bottom
    }
    start: Qt.point(0, 0)
    end: Qt.point(0, height)
    gradient: Gradient {
        GradientStop { position: 0.0; color: "#303434" }
        GradientStop { position: 1.0; color: "#0B4A60" }
    }
}
