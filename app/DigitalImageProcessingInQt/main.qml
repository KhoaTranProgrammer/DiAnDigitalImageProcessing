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

    // Area for application name
    Rectangle {
        id: id_appnamearea
        anchors {
            top: root.top
            left: root.left
        }
        width: root.width * 0.2
        height: root.height * 0.1
        color: "transparent"

        Text {
            anchors.fill: parent
            text: "Digital Image Processing In Qt"
            font.pixelSize: parent.height / 3
            font.bold: true
            color: "black"
            wrapMode: Text.WordWrap
        }
    }

    // Area for input/output selection
    Rectangle {
        id: id_inoutarea
        anchors {
            top: root.top
            horizontalCenter: root.horizontalCenter
        }
        width: root.width * 0.5
        height: root.height * 0.1
        color: "transparent"

    }

    // Area for exit processing
    Rectangle {
        id: id_exitarea
        anchors {
            top: root.top
            right: root.right
        }
        width: root.width * 0.23
        height: root.height * 0.1
        color: "transparent"
    }

    // Area to list up features
    Rectangle {
        id: id_featurearea
        anchors {
            top: id_appnamearea.bottom
            left: root.left
            bottom: root.bottom
        }
        width: root.width * 0.12
        color: "transparent"
    }

    // Area to display input image
    Rectangle {
        id: id_inputimagearea
        anchors {
            top: id_appnamearea.bottom
            left: id_featurearea.right
        }
        width: root.width * 0.44
        height: root.height * 0.7
        color: "transparent"
    }

    // Area to display output image
    Rectangle {
        id: id_outputimagearea
        anchors {
            top: id_appnamearea.bottom
            right: root.right
        }
        width: root.width * 0.44
        height: root.height * 0.7
        color: "transparent"
    }

    // Area to display information of each feature
    Rectangle {
        id: id_informationarea
        anchors {
            bottom: root.bottom
            left: id_featurearea.right
            top: id_inputimagearea.bottom
        }
        width: root.width * 0.50
        color: "transparent"
    }

    // Area to control of each feature
    Rectangle {
        id: id_controlarea
        anchors {
            bottom: root.bottom
            left: id_informationarea.right
            top: id_inputimagearea.bottom
            right: root.right
            margins: id_informationarea.height * 0.05
        }
        color: "white"
        opacity: 0.4
        radius: height * 0.2
    }

    // Area to support option functions
    Rectangle {
        id: id_optionarea
        anchors {
            right: root.right
            verticalCenter: id_outputimagearea.verticalCenter
        }
        width: root.width * 0.03
        height: width * 3.2
        color: "transparent"
    }
}
