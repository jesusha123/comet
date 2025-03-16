import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

ApplicationWindow {
    visible: true
    width: 1000
    height: 600
    title: "Comet"

    menuBar: MenuBar {
        Menu {
            title: "&File"
            Action {
                text: "&Open Folder"
                onTriggered: folderDialog.open()
            }
        }
    }

    FolderDialog {
        id: folderDialog
        title: "Open Folder"
        currentFolder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: fileTreeView.setPath(FileSystemModel.toPath(selectedFolder))
    }

    SplitView {
        anchors.fill: parent

        FileTreeView {
            id: fileTreeView
            SplitView.preferredWidth: 250
            SplitView.fillHeight: true
            onFileClicked: (filePath) => requestArea.addRequestPage(filePath)
        }

        RequestArea {
            id: requestArea
            SplitView.fillWidth: true
            SplitView.fillHeight: true
        }
    }

    // Shortcut for closing the active tab
    Shortcut {
        sequences: [StandardKey.Close]
        onActivated: requestArea.removeCurrentPage()
    }
    // Shortcut for sending a request on the active tab
    Shortcut {
        sequence: "Ctrl+Return"
        onActivated: requestArea.sendRequestToCurrentPage()
    }
    // Shortcut for moving to the next tab
    Shortcut {
        sequences: ["Ctrl+Tab", "Meta+Tab"]
        onActivated: requestArea.nextTab()
    }
    // Shortcut for moving to the previous tab
    Shortcut {
        sequences: ["Ctrl+Shift+Tab", "Meta+Shift+Tab"]
        onActivated: requestArea.previousTab()
    }
}
