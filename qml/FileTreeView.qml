import QtQuick
import QtQuick.Controls.Fusion

TreeView {
    id: treeView

    signal fileClicked(string fileName)

    model: FileSystemModel

    delegate: TreeViewDelegate {
        implicitWidth: treeView.width

        TapHandler {
            acceptedButtons: Qt.LeftButton
            onSingleTapped: treeView.fileClicked(model.display)
        }
    }

    function setPath(path) {
        FileSystemModel.path = path
        treeView.rootIndex = FileSystemModel.rootIndex()
    }
}
