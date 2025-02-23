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

        RequestControlPanel {
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
                    TextArea {
                        placeholderText: "Enter request body here..."
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
                    Table {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                }
            }
        }
    }
}
