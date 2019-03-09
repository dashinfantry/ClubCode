import QtQuick 2.0
import Sailfish.Silica 1.0

Column
{
    property variant context
    property var valid_ean8: RegExpValidator { regExp: /^[0-9]{7,8}$/ }
    property var valid_ean13: RegExpValidator { regExp: /^[0-9]{12,13}$/ }
    property var valid_code128: RegExpValidator { regExp: /[a-zA-Z0-9]+/ }

    width: parent.width

    function barcode_length() {
        if (barcode_type.currentIndex === 0) {
            return true
        }
        if (barcode_type.currentIndex === 1) {
            if (code.text.trim().length === 7 || code.text.trim().length === 8)
            return true
        }
        if (barcode_type.currentIndex === 2) {
            if (code.text.trim().length === 12 || code.text.trim().length === 13)
            return true
        }
        return false
    }

    ComboBox {
        id: barcode_type
        label: qsTr("Barcode type")
        currentIndex: context.barcodeType
        menu: ContextMenu {
            MenuItem {
                text: qsTr("Code 128")
            } // 0
            MenuItem {
                text: qsTr("EAN 8")
            } // 1
            MenuItem {
                text: qsTr("EAN 13")
            } // 2
        }
        Binding
        {
            target: context
            property: "barcodeType"
            value: barcode_type.currentIndex
        }
    }

    TextField
    {
        focus: true
        placeholderText: qsTr("Name")
        label: placeholderText
        width: parent.width
        id: name
        text: context.name

        Binding
        {
            target: context
            property: "name"
            value: name.text
        }

    }

    TextField
    {
        placeholderText: qsTr("Description")
        label: placeholderText
        width: parent.width
        id: description
        text: context.description

        Binding
        {
            target: context
            property: "description"
            value: description.text
        }
    }

    TextField
    {
        id: code
        placeholderText: qsTr("Code")
        inputMethodHints: barcode_type.currentIndex === 0 ? Qt.ImhNoPredictiveText : Qt.ImhDigitsOnly
        EnterKey.enabled: barcode_length()
        validator: if (barcode_type.currentIndex === 0) { valid_code128 } else if (barcode_type.currentIndex === 1) { valid_ean8 } else { valid_ean13 }
        label: placeholderText
        width: parent.width
        text: context.code

        Binding
        {
            target: context
            property: "code"
            value: code.text
        }
    }
}
