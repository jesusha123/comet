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
            id: requestControlPanel
            Layout.fillWidth: true
            onSendRequestTriggered: {
                let xhr = new XMLHttpRequest();
                xhr.onreadystatechange = function() {
                    if (xhr.readyState === XMLHttpRequest.DONE) {
                        if (xhr.status === 200) {
                            transactionPanel.processResponse(xhr.responseText);
                        } else {
                            transactionPanel.processResponse("Error: " + xhr.status);
                        }
                    }
                }
                xhr.open(requestControlPanel.httpVerb, requestControlPanel.url);
                xhr.send();
            }
        }

        TransactionPanel {
            id: transactionPanel

            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
