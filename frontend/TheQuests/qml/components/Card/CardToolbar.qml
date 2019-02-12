import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.3

Pane {
    property string backgroundColor: '#1D1D1D'
    height: 60
    padding: 0
    Material.elevation: 6
    Rectangle {
        anchors.fill: parent
        color: backgroundColor
    }
}
