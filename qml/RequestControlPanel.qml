import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    ComboBox {
        model: ["GET", "POST", "PUT", "DELETE", "PATCH", "OPTIONS", "HEAD"]
    }

    TextField {
        placeholderText: "Enter URL"
        text: "https://example.com"
        Layout.fillWidth: true
    }

    Button {
        text: "Send"
    }
}
