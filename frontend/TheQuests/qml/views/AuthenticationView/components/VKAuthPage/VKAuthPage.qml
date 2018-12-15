import QtQuick 2.11
import QtQuick.Controls 2.4
import QtWebView 1.1
import 'qrc:/components/SimpleText'
import 'qrc:/components/CustomButton'
import application 1.0
import controllers 1.0

Item {
    id: root
    property StackView curStackView
    property var popFromStackView: function () {
        root.curStackView.pop();
    }
    anchors.left: parent.left
    anchors.right: parent.right
    height: row.height

    Row {
        id: row
        spacing: 10
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10
        height: 40

        SimpleText {
            anchors.verticalCenter: parent.verticalCenter
            text: 'Войти с помощью'
            spacing: 1
        }

        OutlinedIconButton {
            anchors.verticalCenter: parent.verticalCenter
            symbolIcon: 'qrc:/media/vk-logo.svg'
            onClick: function() {
                root.curStackView.push(webViewPage)
            }
        }
    }

    Component{
        id: webViewPage
        Page {
            property StackView curStackView: root.curStackView

            Rectangle {
                id: toolBar
                anchors {
                    left: parent.left
                    right: parent.right
                    top: parent.top
                }
                height: 60
                color: '#4378a4'

                OutlinedIconButton {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    symbolIcon: ''
                    onClick: root.popFromStackView
                }
            }

            WebView {
                id: oauthWebView
                signal loadStarted(url address)
                property bool isRedirect: false

                anchors {
                    left: parent.left
                    right: parent.right
                    top: toolBar.bottom
                    bottom: parent.bottom
                }

                url: oauthPath

                onLoadingChanged: {
                    if (loadRequest.status === 2) {
                        var js = "document.getElementsByTagName('pre')[0].innerHTML";
                        runJavaScript(js, function(result){
                            UserController.processOauth(result);
                        });
                    }
                }
            }
        }
    }
}
