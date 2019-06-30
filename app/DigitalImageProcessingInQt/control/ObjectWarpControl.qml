import QtQuick 2.0

BasicControl {

    // Properties to control Object Warp
    property int x1
    property int y1
    property int x2
    property int y2
    property int x3
    property int y3
    property int x4
    property int y4

    // Function to initialize controls
    function initializeControls() {
        // Add control for X1
        addControl("X1",        // name to display X1
                   0,           // minimum X1
                   inputWidth,  // maximum X1
                   1,           // X1 step size
                   0,           // current X1
                   "x1")        // X1 property name

        // Add control for Y1
        addControl("Y1",        // name to display Y1
                   0,           // minimum Y1
                   inputHeight, // maximum Y1
                   1,           // Y1 step size
                   0,           // current Y1
                   "y1")        // Y1 property name

        // Add control for X2
        addControl("X2",        // name to display X2
                   0,           // minimum X2
                   inputWidth,  // maximum X2
                   1,           // X2 step size
                   0,           // current X2
                   "x2")        // X2 property name

        // Add control for Y2
        addControl("Y2",        // name to display Y2
                   0,           // minimum Y2
                   inputHeight, // maximum Y2
                   1,           // Y2 step size
                   0,           // current Y2
                   "y2")        // Y2 property name

        // Add control for X3
        addControl("X3",        // name to display X3
                   0,           // minimum X3
                   inputWidth,  // maximum X3
                   1,           // X3 step size
                   0,           // current X3
                   "x3")        // X3 property name

        // Add control for Y3
        addControl("Y3",        // name to display Y3
                   0,           // minimum Y3
                   inputHeight, // maximum Y3
                   1,           // Y3 step size
                   0,           // current Y3
                   "y3")        // Y3 property name

        // Add control for X4
        addControl("X4",        // name to display X4
                   0,           // minimum X4
                   inputWidth,  // maximum X4
                   1,           // X4 step size
                   0,           // current X4
                   "x4")        // X4 property name

        // Add control for Y4
        addControl("Y4",        // name to display Y4
                   0,           // minimum Y4
                   inputHeight, // maximum Y4
                   1,           // Y4 step size
                   0,           // current Y4
                   "y4")        // Y4 property name

    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "x1") {
            // When x1 is changed
            x1 = newValue
        }else if(currentProperty === "y1") {
            // When y1 is changed
            y1 = newValue
        }else if(currentProperty === "x2") {
            // When x2 is changed
            x2 = newValue
        }else if(currentProperty === "y2") {
            // When y2 is changed
            y2 = newValue
        }else if(currentProperty === "x3") {
            // When x3 is changed
            x3 = newValue
        }else if(currentProperty === "y3") {
            // When y3 is changed
            y3 = newValue
        }else if(currentProperty === "x4") {
            // When x4 is changed
            x4 = newValue
        }else if(currentProperty === "y4") {
            // When y4 is changed
            y4 = newValue
        }
    }
}
