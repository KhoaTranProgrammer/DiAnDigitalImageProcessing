import QtQuick 2.0

BasicControl {

    // Properties to control Geometry
    property double angle: 45.0
    property double xstretch: 1.0
    property double ystretch: 1.0
    property int xdisplace: 10
    property int ydisplace: 10
    property double xcross: 0.01
    property double ycross: 0.01

    // Function to initialize controls
    function initializeControls() {
        addControl("Angle", // name
                   0,       // minimum value
                   360,     // maximum value
                   1,       // slider step size
                   angle,   // current value
                   "angle") // property name

        addControl("X Stretch", // name
                   0,           // minimum value
                   2,           // maximum value
                   0.01,        // slider step size
                   xstretch,    // current value
                   "xstretch")  // property name

        addControl("Y Stretch", // name
                   0,           // minimum value
                   2,           // maximum value
                   0.01,        // slider step size
                   ystretch,    // current value
                   "ystretch")  // property name

        addControl("X Displace",    // name
                   0,               // minimum value
                   inputWidth,      // maximum value
                   1,               // slider step size
                   xdisplace,       // current value
                   "xdisplace")     // property name

        addControl("Y Displace",    // name
                   0,               // minimum value
                   inputHeight,     // maximum value
                   1,               // slider step size
                   ydisplace,       // current value
                   "ydisplace")     // property name

        addControl("X Cross",   // name
                   0.0,         // minimum value
                   0.10,        // maximum value
                   0.01,        // slider step size
                   xcross,      // current value
                   "xcross")    // property name

        addControl("Y Cross",   // name
                   0.0,         // minimum value
                   0.10,        // maximum value
                   0.01,        // slider step size
                   ycross,      // current value
                   "ycross")    // property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "angle") {
            // When angle is changed
            angle = newValue
        }else if(currentProperty === "xstretch") {
            // When xstretch is changed
            xstretch = newValue
        }else if(currentProperty === "ystretch") {
            // When ystretch is changed
            ystretch = newValue
        }else if(currentProperty === "xdisplace") {
            // When xdisplace is changed
            xdisplace = newValue
        }else if(currentProperty === "ydisplace") {
            // When ydisplace is changed
            ydisplace = newValue
        }else if(currentProperty === "xcross") {
            // When xcross is changed
            xcross = newValue
        }else if(currentProperty === "ycross") {
            // When ycross is changed
            ycross = newValue
        }
    }
}
