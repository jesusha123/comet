import QtQuick.Layouts
import comet 1.0

ColumnLayout {
    Request {
        id: request
        url: "http://httpbin.org/anything"
    }
    Response {
        id: response
    }

    RequestControlPanel {
        id: requestControlPanel
        request: request
        Layout.fillWidth: true
        onSendRequestTriggered: NetworkManager.sendRequest(request, response)
    }

    TransactionPanel {
        id: transactionPanel
        request: request
        response: response

        Layout.fillWidth: true
        Layout.fillHeight: true
    }
}
