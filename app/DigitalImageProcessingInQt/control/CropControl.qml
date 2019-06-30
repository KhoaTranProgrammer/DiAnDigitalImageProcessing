import QtQuick 2.0

BasicControl {

    // Properties to control Crop
    property int startrow: 0
    property int startcol: 0
    property int newheight: inputHeight / 2
    property int newwidth: inputWidth / 2

    // Function to initialize controls
    function initializeControls() {
        addControl("Start Row", // name
                   0,           // minimum value
                   inputHeight, // maximum value
                   1,           // slider step size
                   startrow,    // current value
                   "startrow")  // property name

        addControl("Start Column",  // name
                   0,               // minimum value
                   inputWidth,      // maximum value
                   1,               // slider step size
                   startcol,        // current value
                   "startcol")      // property name

        addControl("New Height",    // name
                   0,               // minimum value
                   inputHeight,     // maximum value
                   1,               // slider step size
                   inputHeight / 2, // current value
                   "newheight")     // property name

        addControl("New Width",     // name
                   0,               // minimum value
                   inputWidth,      // maximum value
                   1,               // slider step size
                   inputWidth / 2,  // current value
                   "newwidth")      // property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "startrow") {
            // When startrow is changed
            startrow = newValue
        }else if(currentProperty === "startcol") {
            // When startcol is changed
            startcol = newValue
        }else if(currentProperty === "newheight") {
            // When newheight is changed
            newheight = newValue
        }else if(currentProperty === "newwidth") {
            // When newwidth is changed
            newwidth = newValue
        }
    }
}
