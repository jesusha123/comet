import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 1000
    height: 600
    title: "Comet"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        RowLayout {
            Layout.fillWidth: true
            spacing: 5

            TextField {
                id: urlField
                placeholderText: "Enter URL"
                Layout.fillWidth: true
            }

            Button {
                text: "Send"
                onClicked: {
                    responseBodyText.text = "Loading...";
                    var xhr = new XMLHttpRequest();
                    xhr.onreadystatechange = function() {
                        if (xhr.readyState === XMLHttpRequest.DONE) {
                            if (xhr.status === 200) {
                                responseBodyText.text = xhr.responseText;
                            } else {
                                responseBodyText.text = "Error: " + xhr.status;
                            }
                        }
                    }
                    xhr.open("GET", urlField.text);
                    xhr.send();
                }
            }
        }

        SplitView {
            id: mainSplitView
            Layout.fillWidth: true
            Layout.fillHeight: true
            orientation: Qt.Horizontal
            spacing: 10

            ColumnLayout {
                id: requestArea
                Layout.fillHeight: true
                implicitWidth: mainSplitView.width / 2
                spacing: 5

                TabBar {
                    id: requestTabBar
                    Layout.fillWidth: true
                    currentIndex: requestStack.currentIndex
                    onCurrentIndexChanged: requestStack.currentIndex = currentIndex

                    TabButton { text: "Query" }
                    TabButton { text: "Body" }
                    TabButton { text: "Headers" }
                }

                StackLayout {
                    id: requestStack
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    TextArea {
                        placeholderText: "Enter query parameters here..."
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                    TextArea {
                        placeholderText: "Enter request body here..."
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                    TextArea {
                        placeholderText: "Enter request headers here..."
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                }
            }

            ColumnLayout {
                id: responseArea
                Layout.fillHeight: true
                implicitWidth: mainSplitView.width / 2
                spacing: 5

                TabBar {
                    id: responseTabBar
                    Layout.fillWidth: true
                    currentIndex: responseStack.currentIndex
                    onCurrentIndexChanged: responseStack.currentIndex = currentIndex

                    TabButton { text: "Body" }
                    TabButton { text: "Headers" }
                }

                StackLayout {
                    id: responseStack
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    TextArea {
                        id: responseBodyText
                        readOnly: true
                        placeholderText: "Response Body"
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                    TextArea {
                        id: responseHeadersText
                        readOnly: true
                        placeholderText: "Response Headers"
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                }
            }
        }
    }
}
