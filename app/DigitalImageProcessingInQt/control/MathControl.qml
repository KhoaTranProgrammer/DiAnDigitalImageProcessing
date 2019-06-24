import QtQuick 2.0

BasicControl {

    // Value to be processed
    property int pValue: 128

    // Function to initialize controls
    function initializeControls() {
        addControl("Value",     // name
                   0,           // minimum value
                   255,         // maximum value
                   1,           // slider step size
                   pValue,      // current value
                   "pValue")    // property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "pValue") {
            // When pValue is changed
            pValue = newValue
        }
    }
}
