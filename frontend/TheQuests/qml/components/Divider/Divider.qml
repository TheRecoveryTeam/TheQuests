import QtQuick 2.0

Rectangle {
    id: divider
    property bool vertical: false
    color: '#E5E5E5'
    Component.onCompleted: {
        if (!vertical) {
            height = 1
            divider.anchors.left = parent.left
            divider.anchors.right = parent.right
        }
        else {
            divider.width = 1
            divider.anchors.top = parent.top
            divider.anchors.bottom = parent.bottom
        }
    }
}
