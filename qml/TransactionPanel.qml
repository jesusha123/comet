import comet 1.0
import QtQuick.Controls
import QtQuick.Layouts

SplitView {
    id: mainSplitView
    property Request request
    property Response response
    orientation: Qt.Horizontal
    spacing: 10

    ColumnLayout {
        id: requestArea
        SplitView.preferredWidth: mainSplitView.width/2
        spacing: 5

        TabBar {
            id: requestTabBar
            Layout.fillWidth: true
            currentIndex: requestStack.currentIndex
            onCurrentIndexChanged: requestStack.currentIndex = currentIndex

            TabButton { text: "Params" }
            TabButton { text: "Headers" }
            TabButton { text: "Body" }
        }

        StackLayout {
            id: requestStack
            Layout.fillWidth: true
            Layout.fillHeight: true

            Table {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            Table {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            ScrollView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                TextArea {
                    placeholderText: "Enter request body here..."
                    text: request.body
                    onTextChanged: request.body = text
                }
            }
        }
    }

    ColumnLayout {
        id: responseArea
        SplitView.preferredWidth: mainSplitView.width/2
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

            ScrollView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                TextArea {
                    id: responseBodyText
                    readOnly: true
                    placeholderText: "Response Body"
                    text: response.body
                }
            }
            Table {
                model: response.headersModel
                Layout.fillWidth: true
                Layout.fillHeight: true
                readOnly: true
            }
        }
    }
}
