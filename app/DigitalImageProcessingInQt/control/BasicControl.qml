import QtQuick 2.0

Item {
    id: root
    anchors.fill: parent

    // Image information
    property int inputWidth: 0
    property int inputHeight: 0

    // Signal to announce when control information are updated
    signal controlInfor
}
