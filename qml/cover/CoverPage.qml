import QtQuick 2.0
import Sailfish.Silica 1.0

CoverBackground
{
    Image
    {
        anchors.centerIn: parent
        source: Qt.resolvedUrl("../../cover.png")
        scale: mainApp.sizeRatio
    }

//    CoverActionList {
//        id: coverAction

//        CoverAction {
//            iconSource: "image://theme/icon-cover-next"
//        }

//        CoverAction {
//            iconSource: "image://theme/icon-cover-pause"
//        }
//    }
}
