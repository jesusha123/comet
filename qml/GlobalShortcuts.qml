import QtQuick

Item {
    // Shortcut for opening folder
    Shortcut {
        sequences: [StandardKey.Open]
        onActivated: folderDialog.open()
    }
    // Shortcut for closing the active tab
    Shortcut {
        sequences: [StandardKey.Close]
        onActivated: requestArea.removeCurrentPage()
    }
    // Shortcut for saving the active request
    Shortcut {
        sequences: [StandardKey.Save]
        onActivated: requestArea.saveCurrentPage()
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
