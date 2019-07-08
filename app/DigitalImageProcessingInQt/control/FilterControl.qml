import QtQuick 2.0

BasicControl {

    // Property to control Filter
    property int masktype: 4
    property int lowhigh: 0

    // Function to initialize controls
    function initializeControls() {
        addControl("Mask Type", // name to display angle
                   1,           // minimum type
                   8,           // maximum type
                   1,           // type step size
                   masktype,    // current type
                   "masktype")  // type property name

        addControl("Low High",  // name to display angle
                   0,           // minimum value
                   1,           // maximum value
                   1,           // step size
                   lowhigh,     // current value
                   "lowhigh")   // value property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "masktype") {
            // When masktype is changed
            masktype = newValue
        }else if(currentProperty === "lowhigh") {
            // When lowhigh is changed
            lowhigh = newValue
        }
    }
}
