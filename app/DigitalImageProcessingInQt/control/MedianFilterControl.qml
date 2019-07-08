import QtQuick 2.0

BasicControl {

    // Property to control Median Filter
    property int size: 3

    // Function to initialize controls
    function initializeControls() {
        addControl("Size",  // name to display angle
                   3,           // minimum size
                   7,           // maximum size
                   2,           // step size
                   size,     // current size
                   "size")   // size property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "size") {
            // When size is changed
            size = newValue
        }
    }
}
