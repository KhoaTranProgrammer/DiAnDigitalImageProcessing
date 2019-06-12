import QtQuick 2.0

BasicControl {

    // Property to control Rotation
    property double angle: 45.0
    property int xorigin: 0
    property int yorigin: 0

    // Function to initialize controls
    function initializeControls() {
        // Add control for Angle
        addControl("Angle", // name to display angle
                   0,       // minimum angle
                   360,     // maximum angle
                   1,       // angle step size
                   angle,   // current angle
                   "angle") // angle property name

        // Add control for XOrigin
        addControl("X Origin",  // name to display xorigin
                   0,           // minimum xorigin
                   inputWidth,  // maximum xorigin
                   1,           // xorigin step size
                   xorigin,     // current xorigin
                   "xorigin")   // xorigin property name

        // Add control for YOrigin
        addControl("Y Origin",  // name to display yorigin
                   0,           // minimum yorigin
                   inputHeight, // maximum yorigin
                   1,           // yorigin step size
                   yorigin,     // current yorigin
                   "yorigin")   // yorigin property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "angle") {
            // When angle is changed
            angle = newValue
        }else if(currentProperty === "xorigin") {
            // When xorigin is changed
            xorigin = newValue
        }else if(currentProperty === "yorigin") {
            // When yorigin is changed
            yorigin = newValue
        }
    }
}
