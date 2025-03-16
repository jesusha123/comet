import QtQuick
import QtQuick.Layouts
import comet 1.0

ColumnLayout {
    property string filePath

    Request {
        id: request
        url: "http://httpbin.org/anything"
    }
    Response {
        id: response
    }

    Component.onCompleted: RequestLoader.loadRequestFromFile(filePath, request)

    RequestControlPanel {
        id: requestControlPanel
        request: request
        Layout.fillWidth: true
        onSendRequestTriggered: sendRequest()
    }

    TransactionPanel {
        id: transactionPanel
        request: request
        response: response

        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    function sendRequest() {
        NetworkManager.sendRequest(request, response)
    }
}
