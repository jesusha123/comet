import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    Layout.fillWidth: true
    spacing: 5

    ComboBox {
        model: ["GET", "POST", "PUT", "DELETE", "PATCH", "OPTIONS", "HEAD"]
    }

    TextField {
        placeholderText: "Enter URL"
        Layout.fillWidth: true
    }

    Button {
        text: "Send"
    }
}
