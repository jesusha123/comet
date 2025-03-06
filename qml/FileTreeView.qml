import QtQuick
import QtQuick.Controls.Fusion

TreeView {
    id: treeView

    signal fileClicked(string fileName)

    model: ListModel {
        ListElement { display: "Apple" }
        ListElement { display: "Orange" }
        ListElement { display: "Banana" }
    }

    delegate: TreeViewDelegate {
        implicitWidth: treeView.width

        TapHandler {
            acceptedButtons: Qt.LeftButton
            onSingleTapped: () => {
                treeView.fileClicked(model.display)
            }
        }
    }
}
