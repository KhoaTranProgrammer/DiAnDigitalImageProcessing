import QtQuick 2.0

BasicControl {

    // Properties to control Warp
    property int xcontrol: inputWidth / 2
    property int ycontrol: inputHeight / 2

    // Function to initialize controls
    function initializeControls() {
        // Add control for XControl
        addControl("X Control",     // name to display xcontrol
                   0,               // minimum xcontrol
                   inputWidth,      // maximum xcontrol
                   1,               // xcontrol step size
                   inputWidth / 2,  // current xcontrol
                   "xcontrol")      // xcontrol property name

        // Add control for YControl
        addControl("Y Control",     // name to display ycontrol
                   0,               // minimum ycontrol
                   inputHeight,     // maximum ycontrol
                   1,               // ycontrol step size
                   inputHeight / 2, // current ycontrol
                   "ycontrol")      // ycontrol property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "xcontrol") {
            // When xcontrol is changed
            xcontrol = newValue
        }else if(currentProperty === "ycontrol") {
            // When ycontrol is changed
            ycontrol = newValue
        }
    }
}
