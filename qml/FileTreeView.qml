import QtQuick
import QtQuick.Controls

TreeView {
    id: treeView

    signal fileClicked(string fileName)

    model: FileSystemModel

    delegate: TreeViewDelegate {
        implicitWidth: treeView.width

        TapHandler {
            acceptedButtons: Qt.LeftButton
            onSingleTapped: {
                if (!model.isDir)
                    treeView.fileClicked(model.filePath)
            }
        }
    }

    function setPath(path) {
        FileSystemModel.path = path
        treeView.rootIndex = FileSystemModel.rootIndex()
    }
}
