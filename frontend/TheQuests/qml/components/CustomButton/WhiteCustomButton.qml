import QtQuick 2.0

CustomButton {
    property bool primary: false
    textColor: '#ffffff'
    opacity: disabled ? 0.2 : 1
    wide: false
    backgrounOpacity: primary ? 0.4 : 0;
    spacing: 1
}
