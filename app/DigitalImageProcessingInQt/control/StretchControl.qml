import QtQuick 2.0

BasicControl {

    // Properties to control Stretch
    property double xstretch: 1.0
    property double ystretch: 1.0

    // Function to initialize controls
    function initializeControls() {
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
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "xstretch") {
            // When xstretch is changed
            xstretch = newValue
        }else if(currentProperty === "ystretch") {
            // When ystretch is changed
            ystretch = newValue
        }
    }
}
