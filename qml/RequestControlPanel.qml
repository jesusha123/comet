import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    property alias url: urlTextField.text
    property alias httpVerb: httpVerbComboBox.currentText
    signal sendRequestTriggered()

    ComboBox {
        id: httpVerbComboBox
        model: ["GET", "POST", "PUT", "DELETE", "PATCH", "OPTIONS", "HEAD"]
    }

    TextField {
        id: urlTextField
        placeholderText: "Enter URL"
        text: "http://httpbin.org/anything"
        Layout.fillWidth: true
    }

    Button {
        text: "Send"

        onClicked: {
            sendRequestTriggered()
        }
    }
}
