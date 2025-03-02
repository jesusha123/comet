import comet 1.0
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    property Request request
    signal sendRequestTriggered()

    ComboBox {
        model: ["GET", "POST", "PUT", "DELETE", "PATCH", "OPTIONS", "HEAD"]
        onCurrentTextChanged: request.method = currentText
    }

    TextField {
        placeholderText: "Enter URL"
        text: request.url
        Layout.fillWidth: true
        onTextChanged: request.url = text
    }

    Button {
        text: "Send"
        onClicked: sendRequestTriggered()
    }
}
