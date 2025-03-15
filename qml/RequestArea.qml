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
                text: fileNameWithoutExtension(model.title)

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.RightButton
                    onClicked: (mouse) => {
                        if (mouse.button === Qt.RightButton) {
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
            RequestPage {}
        }
    }

    function addRequestPage(fileName) {
        // Check if an element with the same fileName already exists
        for (let i = 0; i < requestModel.count; i++) {
            if (requestModel.get(i).title === fileName) {
                requestTabBar.currentIndex = i;
                return;
            }
        }

        requestModel.append({ title: fileName });
        requestTabBar.currentIndex = requestTabBar.count - 1;
    }

    function removeRequestPage(index) {
        requestModel.remove(index);
    }

    function fileNameWithoutExtension(fullPath) {
        var fileName = fullPath.split("/").pop();
        var dotIndex = fileName.lastIndexOf(".");
        if (dotIndex === -1)
            return fileName;
        return fileName.substring(0, dotIndex);
    }
}
