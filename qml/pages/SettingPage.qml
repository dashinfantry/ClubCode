import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.clubcode.Settings 1.0

Page {
    id: settingsPage

    objectName: "SettingPage"

    SilicaFlickable {
        anchors.fill: parent
        contentWidth: parent.width
        contentHeight: col.height

        MySettings {
            id: myset
        }

        clip: true

        ScrollDecorator {
        }

        Column {
            id: col
            spacing: isPortrait ? Theme.paddingLarge : Theme.paddingMedium
            width: parent.width
            PageHeader {
                title: qsTr("Settings")
            }

            ComboBox {
                id: screenorientation
                width: parent.width
                label: qsTr("Orientation")
                description: qsTr("How the barcode should be displayed")
                currentIndex: myset.value("orientation")
                              === "landscape" ? 1 : myset.value(
                                                    "orientation") === "portrait" ? 2 : 0
                menu: ContextMenu {
                    MenuItem {
                        text: qsTr("Dynamic") // 0
                    }
                    MenuItem {
                        text: qsTr("Landscape") // 1
                    }
                    MenuItem {
                        text: qsTr("Portrait") // 2
                    }
                }
                onCurrentItemChanged: {
                    if (screenorientation.currentIndex === 0) {
                        myset.setValue("orientation", "dynamic")
                    }
                    if (screenorientation.currentIndex === 1) {
                        myset.setValue("orientation", "landscape")
                    }
                    if (screenorientation.currentIndex === 2) {
                        myset.setValue("orientation", "portrait")
                    }
                    myset.sync()
                }
            }
        }
    }
}
