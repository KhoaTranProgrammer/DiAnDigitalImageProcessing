import QtQuick 2.0

BasicControl {

    // Property for control gray level
    property int newGrays: 128

    // Function to initialize controls
    function initializeControls() {
        addControl("New Gray Level",// name
                   0,               // minimum value
                   255,             // maximum value
                   1,               // slider step size
                   newGrays,        // current value
                   "newGrays")      // property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "newGrays") {
            // When newGrays is changed
            newGrays = newValue
        }
    }
}
