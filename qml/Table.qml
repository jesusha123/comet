import QtQuick
import QtQuick.Layouts
import Qt.labs.qmlmodels

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.qmlmodels

TableView {
    id: tableView
    columnSpacing: 1
    rowSpacing: 1
    clip: true

    model: TableModel {
        TableModelColumn { display: "name" }
        TableModelColumn { display: "color" }

        rows: [
            { "name": "cat", "color": "black" },
            { "name": "dog", "color": "brown" },
            { "name": "cat", "color": "black" },
            { "name": "dog", "color": "brown" },
            { "name": "cat", "color": "black" },
            { "name": "dog", "color": "brown" },
            { "name": "cat", "color": "black" },
            { "name": "dog", "color": "brown" },
            { "name": "cat", "color": "black" },
            { "name": "dog", "color": "brown" },
            { "name": "cat", "color": "black" },
            { "name": "dog", "color": "brown" },
            { "name": "cat", "color": "black" },
            { "name": "dog", "color": "brown" },
            { "name": "cat", "color": "black" },
            { "name": "dog", "color": "brown" },
            { "name": "cat", "color": "black" },
            { "name": "dog", "color": "brown" },
            { "name": "cat", "color": "black" },
            { "name": "dog", "color": "brown" },
            { "name": "cat", "color": "black" },
            { "name": "dog", "color": "brown" },
            { "name": "cat", "color": "black" },
            { "name": "dog", "color": "brown" },
            { "name": "cat", "color": "black" },
            { "name": "dog", "color": "brown" },
            { "name": "cat", "color": "black" },
            { "name": "dog", "color": "brown" },
            { "name": "cat", "color": "black" },
            { "name": "dog", "color": "brown" },
            { "name": "cat", "color": "black" },
            { "name": "dog", "color": "brown" },
            { "name": "cat", "color": "black" },
            { "name": "dog", "color": "brown" },
            { "name": "cat", "color": "black" },
            { "name": "dog", "color": "brown" },
            { "name": "bird", "color": "white" }
        ]
    }

    delegate: Rectangle {
        implicitWidth: tableView.width / 2
        implicitHeight: 30

        TextField {
            anchors.fill: parent
            text: display
            background: null // Disable TextField border

            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }
    }
}
