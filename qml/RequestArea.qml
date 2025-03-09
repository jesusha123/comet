import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    ListModel {
        id: requestModel
    }

    TabBar {
        id: requestTabBar
        Layout.fillWidth: true
        clip: true

        Repeater {
            model: requestModel
            TabButton {
                id: tabButton
                width: implicitWidth
                text: model.title

                contentItem: RowLayout {
                    Text {
                        text: tabButton.text
                    }
                    Button {
                        text: "X"
                        onClicked: requestTabBar.removeItem(tabButton)
                    }
                }
            }
        }
    }

    StackLayout {
        id: requestStackLayout
        Layout.fillWidth: true
        Layout.fillHeight: true
        currentIndex: requestTabBar.currentIndex

        Repeater {
            model: requestModel
            RequestPage {}
        }
    }

    function addTab(tabText) {
        requestModel.append({ title: tabText });
        requestTabBar.currentIndex = requestTabBar.count - 1;
    }
}
