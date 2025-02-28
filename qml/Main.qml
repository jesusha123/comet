import comet 1.0
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 1000
    height: 600
    title: "Comet"

    Request {
        id: request
        url: "https://example.com"
    }
    Response {
        id: response
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        RequestControlPanel {
            id: requestControlPanel
            request: request
            Layout.fillWidth: true
            onSendRequestTriggered: NetworkManager.sendRequest(request, response)
        }

        TransactionPanel {
            id: transactionPanel
            response: response

            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
