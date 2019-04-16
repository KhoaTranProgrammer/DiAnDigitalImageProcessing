import QtQuick 2.6

Rectangle {
    id: root
    anchors.fill: parent

    // Background
    gradient: Gradient {
        GradientStop { position: 0.00; color: "#78909C" }
        GradientStop { position: 0.33; color: "#607D8B" }
        GradientStop { position: 0.66; color: "#546E7A" }
        GradientStop { position: 1.00; color: "#455A64" }
    }
}
