import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    id: root

    // Input properties
    property string textValue: ""
    property double currentValue: 128
    property double minValue: 0
    property double maxValue: 255
    property double stepValue: 1
    property int textSize: height * 0.4

    Rectangle {
        id: id_displayarea
        anchors.fill: parent
        color: "transparent"

        // Slider to change value
        Slider {
            id: id_slider
            anchors.fill: parent
            value: currentValue
            minimumValue: minValue
            maximumValue: maxValue
            stepSize: stepValue

            onValueChanged: {
                currentValue = value
            }
        }

        // Text to display Minimum value
        Text {
            anchors {
                right: id_slider.left
                verticalCenter: id_slider.verticalCenter
            }
            text: minValue
            font.pixelSize: textSize
            font.bold: true
            color: "black"
        }

        // Text to display Maximum value
        Text {
            anchors {
                left: id_slider.right
                verticalCenter: id_slider.verticalCenter
            }
            text: maxValue
            font.pixelSize: textSize
            font.bold: true
            color: "black"
        }

        // Text to display Current value
        Text {
            anchors {
                bottom: id_slider.verticalCenter
                bottomMargin: 5
                horizontalCenter: id_displayarea.horizontalCenter
            }
            text: textValue + ": " + currentValue
            font.pixelSize: textSize
            font.bold: true
            color: "black"
        }
    }
}
