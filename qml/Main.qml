import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 1000
    height: 600
    title: "Comet"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        RequestControlPanel {
            Layout.fillWidth: true
        }

        TransactionPanel {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
