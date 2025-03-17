import QtQuick.Controls
import QtQuick.Layouts
import comet 1.0

SplitView {
    id: splitView
    property Request request
    property Response response
    orientation: Qt.Vertical

    ColumnLayout {
        id: requestArea
        SplitView.preferredHeight: splitView.height / 2
        SplitView.minimumHeight: 50

        TabBar {
            id: requestTabBar

            TabButton {
                text: "Params"
                width: implicitWidth
            }
            TabButton {
                text: "Headers"
                width: implicitWidth
            }
            TabButton {
                text: "Body"
                width: implicitWidth
            }
        }

        StackLayout {
            id: requestStack
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: requestTabBar.currentIndex

            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Table {
                    id: paramsTable
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: request.paramsModel
                }
                Button {
                    text: "Add Param"
                    onClicked: request.paramsModel.appendEmptyRow()
                }
            }
            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Table {
                    id: headersTable
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: request.headersModel
                }
                Button {
                    text: "Add Header"
                    onClicked: request.headersModel.appendEmptyRow()
                }
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
        SplitView.preferredHeight: splitView.height / 2
        SplitView.minimumHeight: 50

        TabBar {
            id: responseTabBar
            currentIndex: responseStack.currentIndex
            onCurrentIndexChanged: responseStack.currentIndex = currentIndex

            TabButton {
                text: "Body"
                width: implicitWidth
            }
            TabButton {
                text: "Headers"
                width: implicitWidth
            }
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
                Layout.fillWidth: true
                Layout.fillHeight: true
                readOnly: true
                model: response.headersModel
            }
        }
    }
}
