import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    ListModel {
        id: requestModel
    }

    TabBar {
        id: requestTabBar
        Layout.fillWidth: true
        clip: true

        Repeater {
            model: requestModel
            TabButton {
                id: tabButton
                width: implicitWidth
                text: fileNameWithoutExtension(model.filePath)

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.MiddleButton
                    onClicked: (mouse) => {
                        if (mouse.button === Qt.MiddleButton) {
                            removeRequestPage(index)
                        }
                    }
                }

                contentItem: RowLayout {
                    Text {
                        text: tabButton.text
                    }
                    Button {
                        text: "X"
                        onClicked: removeRequestPage(index)
                    }
                }
            }
        }
    }

    StackLayout {
        id: requestStackLayout
        Layout.fillWidth: true
        Layout.fillHeight: true
        currentIndex: requestTabBar.currentIndex

        Repeater {
            model: requestModel
            RequestPage {
                filePath: model.filePath
            }
        }
    }

    function addRequestPage(filePath) {
        // Check if an element with the same file path already exists
        for (let i = 0; i < requestModel.count; i++) {
            if (requestModel.get(i).filePath === filePath) {
                requestTabBar.currentIndex = i;
                return;
            }
        }

        requestModel.append({ filePath });
        requestTabBar.currentIndex = requestTabBar.count - 1;
    }

    function removeRequestPage(index) {
        if (index >= 0)
            requestModel.remove(index);
    }

    function removeCurrentPage() {
        removeRequestPage(requestTabBar.currentIndex)
    }


    function fileNameWithoutExtension(filePath) {
        var fileName = filePath.split("/").pop();
        var dotIndex = fileName.lastIndexOf(".");
        if (dotIndex === -1)
            return fileName;
        return fileName.substring(0, dotIndex);
    }

    function sendRequestToCurrentPage() {
        var currentItem = requestStackLayout.itemAt(requestStackLayout.currentIndex)
        if (currentItem)
            currentItem.sendRequest();
    }

    function nextTab() {
        if (requestTabBar.count > 0) {
            if (requestTabBar.currentIndex < requestTabBar.count - 1)
                requestTabBar.currentIndex++
            else
                requestTabBar.currentIndex = 0
        }
    }

    function previousTab() {
        if (requestTabBar.count > 0) {
            if (requestTabBar.currentIndex > 0)
                requestTabBar.currentIndex--
            else
                requestTabBar.currentIndex = requestTabBar.count - 1
        }
    }
}
