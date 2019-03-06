import QtQuick 2.0
import Sailfish.Silica 1.0

Page
{
    property variant current

    id: page

    Rectangle
    {
        color: "white"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        id: background

        Column
        {
            anchors.centerIn: parent
            rotation: isPortrait ? 90 : 0

            Label
            {
                anchors.horizontalCenter: parent.horizontalCenter
                text: current.name
                color: "black"
                font.bold: true
            }
            Label
            {
                color: "black"
                font.family: "Code 128"
                fontSizeMode: Text.Fit
                font.pixelSize: 300 * mainApp.sizeRatio
                width: isPortrait ? background.height - 20 : background.width - 20
                height: isPortrait ? background.width - 150 : background.height -150
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                text: current.generateCode(current.code)
                font.letterSpacing: 0
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Label
            {
                anchors.horizontalCenter: parent.horizontalCenter
                text: current.code
                color: "black"
            }
        }
    }
}
