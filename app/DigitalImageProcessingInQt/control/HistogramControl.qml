import QtQuick 2.0

BasicControl {

    // General Properties
    property string thetitle
    property string titlecolor

    // Global object stores histogram data
    QtObject {
        id: id_hist
        property var histarray: []
        property int length: 0
        property int max: 0
    }

    // Text to display title
    Text {
        anchors {
            fill: parent
            margins: parent.height * 0.05
        }
        text: thetitle
        font.pixelSize: parent.height * 0.2
        font.bold: true
        color: titlecolor
    }

    // Histogram be displayed by using Canvas
    Canvas {
        id: id_canvas
        anchors {
            fill: parent
            margins: parent.height * 0.01
        }

        contextType: "2d"
        antialiasing: true

        onPaint: {
            // Initialize drawing
            var context = id_canvas.getContext('2d');
            context.clearRect(0, 0, width, height)

            // Setting properties
            context.beginPath();
            context.strokeStyle = titlecolor;
            context.lineWidth = 3;

            // Loop all of data in histogram array
            for(var i = 0; i < id_hist.length; i++) {
                // Move to beginning of line
                context.moveTo((i * id_canvas.width) / (id_hist.length - 1),
                               id_canvas.height);
                // Draw line from beginning to ending
                context.lineTo((i * id_canvas.width) / (id_hist.length - 1),
                               id_canvas.height - (id_hist.histarray[i] * id_canvas.height) / id_hist.max);
            }
            // Make the drawing effect
            context.stroke()
        }
    }

    // Function to add data to histogram list
    function addData(newData) {
        id_hist.histarray[id_hist.length++] = newData
        if(newData > id_hist.max) id_hist.max = newData
    }

    // Function to refresh histogram drawing
    function drawData() {
        id_canvas.requestPaint();
    }

    // Function to clear histogram data
    function clearData() {
        for(var i = 0; i < id_hist.length; i++) {
            id_hist.histarray[i] = 0
        }
        id_hist.length = 0
        id_hist.max = 0
    }
}
