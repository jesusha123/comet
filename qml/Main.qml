import QtQuick.Controls

ApplicationWindow {
    visible: true
    width: 1000
    height: 600
    title: "Comet"

    SplitView {
        anchors.fill: parent

        FileTreeView {
            SplitView.preferredWidth: 250
            SplitView.fillHeight: true
            onFileClicked: (fileName) => requestArea.addTab(fileName)
        }

        RequestArea {
            id: requestArea
            SplitView.fillWidth: true
            SplitView.fillHeight: true
        }
    }
}
