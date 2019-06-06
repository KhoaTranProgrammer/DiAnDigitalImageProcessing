import QtQuick 2.0

Item {
    id: root
    anchors.fill: parent

    // Image information
    property int inputWidth: 0
    property int inputHeight: 0

    // The height of each control
    property int sliderHeight: height / 4

    // Properties to update new value for property
    property double newValue: 0
    property string currentProperty: ""

    // Signal to announce when control information are updated
    signal controlInfor

    // Store the list of Controls
    ListModel {
        id: id_listOfControls
    }

    // Display the list of Controls
    Component {
        id: id_displayControls

        Item {
            anchors {
                horizontalCenter: parent.horizontalCenter
            }

            height: sliderHeight
            width: parent.width * 3 / 4

            // The CustomSlider is used for user to control feature
            CustomSlider {
                anchors.fill: parent

                // Setting input for CustomSlider
                textValue: name
                currentValue: currentV
                minValue: minV
                maxValue: maxV
                stepValue: stepV

                // When user changes value of Slider
                onCurrentValueChanged: {
                    // Update the name of property that is changed
                    currentProperty = propertyName

                    // New value of changed property
                    newValue = currentValue

                    // Call updateProperties function
                    updateProperties()

                    // Emit controlInfor signal
                    controlInfor()
                }
            }
        }
    }

    // Apply Scroll View for Control List
    Flickable {
        anchors.fill: parent
        contentHeight: id_listOfControls.count * sliderHeight
        clip: true

        Column {
            anchors.fill: parent
            Repeater {
                model: id_listOfControls
                delegate: id_displayControls
            }
        }
    }

    // Function to add control into the list of Controls
    function addControl(name, minV, maxV, stepV, currentV, propertyName) {
        id_listOfControls.append({"name": name,
                                  "minV": minV,
                                  "maxV": maxV,
                                  "stepV": stepV,
                                  "currentV": currentV,
                                  "propertyName": propertyName
                                 })
    }
}
