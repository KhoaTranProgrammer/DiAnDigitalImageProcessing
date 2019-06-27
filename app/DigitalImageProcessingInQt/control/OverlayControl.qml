import QtQuick 2.0

BasicControl {

    // Properties to control Overlay
    property int startrowofimg1: 0
    property int startcolofimg1: 0
    property int startrowofimg2: 0
    property int startcolofimg2: 0
    property int newheight: inputHeight / 2
    property int newwidth: inputWidth / 2

    // Function to initialize controls
    function initializeControls() {
        addControl("Start Row Of Image 1",  // name
                   0,                       // minimum value
                   inputHeight,             // maximum value
                   1,                       // slider step size
                   startrowofimg1,          // current value
                   "startrowofimg1")        // property name

        addControl("Start Column Of Image 1",   // name
                   0,                           // minimum value
                   inputWidth,                  // maximum value
                   1,                           // slider step size
                   startcolofimg1,              // current value
                   "startcolofimg1")            // property name

        addControl("Start Row Of Image 2",  // name
                   0,                       // minimum value
                   inputHeight,             // maximum value
                   1,                       // slider step size
                   startrowofimg2,          // current value
                   "startrowofimg2")        // property name

        addControl("Start Column Of Image 2",   // name
                   0,                           // minimum value
                   inputWidth,                  // maximum value
                   1,                           // slider step size
                   startcolofimg2,              // current value
                   "startcolofimg2")            // property name

        addControl("New Height",        // name
                   0,                   // minimum value
                   inputHeight,         // maximum value
                   1,                   // slider step size
                   inputHeight * 0.95, // current value
                   "newheight")         // property name

        addControl("New Width",         // name
                   0,                   // minimum value
                   inputWidth,          // maximum value
                   1,                   // slider step size
                   inputWidth * 0.95,  // current value
                   "newwidth")          // property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "startrowofimg1") {
            // When startrowofimg1 is changed
            startrowofimg1 = newValue
        }else if(currentProperty === "startcolofimg1") {
            // When startcolofimg1 is changed
            startcolofimg1 = newValue
        }else if(currentProperty === "startrowofimg2") {
            // When startrowofimg2 is changed
            startrowofimg2 = newValue
        }else if(currentProperty === "startcolofimg2") {
            // When startcolofimg2 is changed
            startcolofimg2 = newValue
        }else if(currentProperty === "newheight") {
            // When newheight is changed
            newheight = newValue
        }else if(currentProperty === "newwidth") {
            // When newwidth is changed
            newwidth = newValue
        }
    }
}
