import QtQuick.Controls
import QtQuick.Layouts
import comet 1.0

RowLayout {
    property Request request
    property string filePath
    signal sendRequestTriggered()

    ComboBox {
        model: ["GET", "POST", "PUT", "DELETE", "PATCH", "OPTIONS", "HEAD"]
        currentIndex: model.indexOf(request.method)
        onCurrentTextChanged: request.method = currentText
    }

    TextField {
        placeholderText: "Enter URL"
        text: request.url
        Layout.fillWidth: true
        onTextChanged: request.url = text
    }

    ToolButton {
        id: saveButton
        icon.source: "qrc:/icons/save.svg"
        onClicked: RequestFileManager.saveRequestToFile(filePath, request)
    }

    ToolButton {
        id: sendButton
        icon.source: "qrc:/icons/send.svg"
        onClicked: sendRequestTriggered()
    }
}
