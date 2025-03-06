import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    TabBar {
        id: requestTabBar
    }

    StackLayout {
        id: requestStackLayout
        currentIndex: requestTabBar.currentIndex
    }

    Component {
        id: requestTabButton
        TabButton {}
    }

    Component {
        id: requestPage
        RequestPage {}
    }

    function addTab(tabText) {
        requestTabBar.addItem(requestTabButton.createObject(requestTabBar, {"text": tabText}))
        requestPage.createObject(requestStackLayout)
    }
}
