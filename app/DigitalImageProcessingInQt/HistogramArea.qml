import QtQuick 2.0
import "control"

Item {
    // Hold status is Input or Output
    property bool isInput: true

    // Hold status visible or invisible
    visible: false

    // Channel 1, default to display Red data for RGB
    // For gray scale, display gray data
    Item {
        id: id_channel1Area
        anchors {
            left: parent.left
            bottom: parent.bottom
            margins: parent.height * 0.01
        }
        width: parent.width * 0.4
        height: width * 0.4

        Rectangle {
            anchors.fill: parent
            opacity: 0.5
        }

        HistogramControl {
            id: id_histogramchannel1
            thetitle: "R"
            titlecolor: "red"
        }
    }

    // Channel 2, default to display Green data
    Item {
        id: id_channel2Area
        anchors {
            left: parent.left
            bottom: id_channel1Area.top
            margins: parent.height * 0.01
        }
        width: parent.width * 0.4
        height: width * 0.4

        Rectangle {
            anchors.fill: parent
            opacity: 0.5
        }

        HistogramControl {
            id: id_histogramchannel2
            thetitle: "G"
            titlecolor: "green"
        }
    }

    // Channel 3, default to display Blue data
    Item {
        id: id_channel3Area
        anchors {
            left: parent.left
            bottom: id_channel2Area.top
            margins: parent.height * 0.01
        }
        width: parent.width * 0.4
        height: width * 0.4

        Rectangle {
            anchors.fill: parent
            opacity: 0.5
        }

        HistogramControl {
            id: id_histogramchannel3
            thetitle: "B"
            titlecolor: "blue"
        }
    }

    // Function to calculate and show histogram
    function show() {
        var i
        if(isInput) { // In case of Input image
            if(dipFeatures.getInputDepth() === 24) { // In case of RGB image
                // Update Channel1 title, it may change for grayscale image before
                id_histogramchannel1.thetitle = "R"
                id_histogramchannel1.titlecolor = "red"

                // Display Channel2/3
                id_channel2Area.visible = true
                id_channel3Area.visible = true

                // Reset data of all Channels
                id_histogramchannel1.clearData()
                id_histogramchannel2.clearData()
                id_histogramchannel3.clearData()

                // Reload data for all Channels
                for(i = 0; i < 256; i++){
                    id_histogramchannel1.addData(dipFeatures.dipGetHistogramInputAt(0, i))
                    id_histogramchannel2.addData(dipFeatures.dipGetHistogramInputAt(1, i))
                    id_histogramchannel3.addData(dipFeatures.dipGetHistogramInputAt(2, i))
                }

                // Draw data for all Channels
                id_histogramchannel1.drawData()
                id_histogramchannel2.drawData()
                id_histogramchannel3.drawData()
            }else{ // In case of Grayscale image
                // Update Channel1 title
                id_histogramchannel1.thetitle = "Gray"
                id_histogramchannel1.titlecolor = "black"

                // Stop display Channel2/3
                id_channel2Area.visible = false
                id_channel3Area.visible = false

                // Reload data for Channel1
                id_histogramchannel1.clearData()
                for(i = 0; i < 256; i++){
                    id_histogramchannel1.addData(dipFeatures.dipGetHistogramInputAt(0, i))
                }

                // Draw data for Channel1
                id_histogramchannel1.drawData()
            }
        }else{ // In case of Output image
            if(dipFeatures.getOutputDepth() === 24) { // In case of RGB image
                // Update Channel1 title, it may change for grayscale image before
                id_histogramchannel1.thetitle = "R"
                id_histogramchannel1.titlecolor = "red"

                // Dispplay Channel2/3
                id_channel2Area.visible = true
                id_channel3Area.visible = true

                // Reset data of all Channels
                id_histogramchannel1.clearData()
                id_histogramchannel2.clearData()
                id_histogramchannel3.clearData()

                // Reload data for all Channels
                for(i = 0; i < 256; i++){
                    id_histogramchannel1.addData(dipFeatures.dipGetHistogramOutputAt(0, i))
                    id_histogramchannel2.addData(dipFeatures.dipGetHistogramOutputAt(1, i))
                    id_histogramchannel3.addData(dipFeatures.dipGetHistogramOutputAt(2, i))
                }

                // Draw data for all Channels
                id_histogramchannel1.drawData()
                id_histogramchannel2.drawData()
                id_histogramchannel3.drawData()
            }else{ // In case of Grayscale image
                // Update Channel1 title
                id_histogramchannel1.thetitle = "Gray"
                id_histogramchannel1.titlecolor = "black"

                // Stop display Channel2/3
                id_channel2Area.visible = false
                id_channel3Area.visible = false

                // Reload data for Channel1
                id_histogramchannel1.clearData()
                for(i = 0; i < 256; i++){
                    id_histogramchannel1.addData(dipFeatures.dipGetHistogramOutputAt(0, i))
                }

                // Draw data for Channel1
                id_histogramchannel1.drawData()
            }
        }
        // Change status to visible
        visible = true
    }

    // Function to invisible histogram display
    function stop() {
        visible = false
    }
}
