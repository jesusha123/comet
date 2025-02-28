import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.qmlmodels

ColumnLayout {
    id: table
    property var model
    property bool readOnly: false

    HorizontalHeaderView {
        id: horizontalHeader
        Layout.fillWidth: true
        syncView: tableView
        clip: true
        model: ["Key", "Value"]

        delegate: Rectangle {
            implicitWidth: tableView.width / 2
            implicitHeight: 30

            color: "transparent"

            TextField {
                anchors.fill: parent
                text: modelData
                background: null // Disable TextField border

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }
        }
    }

    TableView {
        id: tableView

        Layout.fillWidth: true
        Layout.fillHeight: true

        columnSpacing: 1
        rowSpacing: 1
        clip: true

        model: table.model

        delegate: Rectangle {
            implicitWidth: tableView.width / 2
            implicitHeight: 30

            // color: "transparent"

            TextField {
                anchors.fill: parent
                text: display
                background: null // Disable TextField border
                readOnly: table.readOnly

                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}
