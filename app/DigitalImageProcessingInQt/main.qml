import QtQuick 2.6
import QtQuick.Dialogs 1.0
import DIPShowImage 1.0
import "Common.js" as Common

Rectangle {
    id: root
    anchors.fill: parent

    // Current feature is selected by user
    property string current_feature: ""

    // This property is changed when Feature is updated
    property bool refreshfeature: false

    // Decide input or output is selected
    property bool isChooseInput: false

    // Hold status of detail information is displayed or not
    property bool isClickedDetail: false

    // Hold status of histogram is displayed or not
    property bool isClickedHistogram: false

    // Default input image
    property string inputimage: defaultinput + "/image/obama.bmp"

    // Default output image
    property string outputimage: defaultinput + "/image/output.bmp"

    QtObject {
        id: id_data

        // Used to indicate the group status is clicked or not
        property var groupstatus: []
        property int numberofgroup: 0
    }

    Component.onCompleted: {
        // Load the Features into the screen
        for (var i = 0 ; i < Common.group_list.length; i++ ) {
            for (var j = 0 ; j < Common.group_list[i].length; j+=3 ) {
                /*
                  Add features to model as template:
                   feature: feature name
                   control: control GUI
                   groupstatusindex: status of parent group
                */
                id_listFeatures.append({"feature": Common.group_list[i][j], "control": Common.group_list[i][j + 1], "groupstatusindex": id_data.numberofgroup, "description": Common.group_list[i][j + 2]})
            }

            // Group status is closed as default
            id_data.groupstatus[id_data.numberofgroup] = false
            id_data.numberofgroup++
        }

        // Display default input image
        dipFeatures.dipSetImageSource(inputimage)
        dipFeatures.dipLoadImage()
        id_inputimage.image = dipFeatures.dipConvertInput2QImage()
    }

    // Background
    gradient: Gradient {
        GradientStop { position: 0.00; color: "#78909C" }
        GradientStop { position: 0.33; color: "#607D8B" }
        GradientStop { position: 0.66; color: "#546E7A" }
        GradientStop { position: 1.00; color: "#455A64" }
    }

    // Area for application name
    Rectangle {
        id: id_appnamearea
        anchors {
            top: root.top
            left: root.left
        }
        width: root.width * 0.2
        height: root.height * 0.1
        color: "transparent"

        Text {
            anchors.fill: parent
            text: "Digital Image Processing In Qt"
            font.pixelSize: parent.height / 3
            font.bold: true
            color: "black"
            wrapMode: Text.WordWrap
        }
    }

    // Area for input/output selection
    Rectangle {
        id: id_inoutarea
        anchors {
            top: root.top
            horizontalCenter: root.horizontalCenter
        }
        width: root.width * 0.5
        height: root.height * 0.1
        color: "transparent"

        // Button to select Input Image
        Rectangle {
            anchors {
                left: parent.left
                top: parent.top
                margins: parent.height * 0.03
            }
            width: parent.width * 0.25
            height: parent.height * 0.45
            radius: parent.height

            // Static text to display "Choose Input"
            Text {
                anchors.centerIn: parent
                text: "Choose Input"
                font.pixelSize: parent.height * 0.5
                font.bold: true
                color: "black"
            }

            // When user clicks, display FileDialog and announce Input is selected
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    id_fileDialog.visible = true
                    isChooseInput = true
                }
            }
        }

        // Display Input File Name
        Rectangle {
            anchors {
                right: parent.right
                top: parent.top
                margins: parent.height * 0.03
            }
            width: parent.width * 0.74
            height: parent.height * 0.45
            radius: parent.height

            // Text to display full input image location
            Text {
                anchors {
                    left: parent.left
                    leftMargin: parent.height * 0.2
                    verticalCenter: parent.verticalCenter
                }
                text: inputimage
                font.pixelSize: parent.height * 0.3
                color: "black"
                wrapMode: Text.WordWrap
            }
        }

        // Button to select Output Image
        Rectangle {
            anchors {
                left: parent.left
                bottom: parent.bottom
                margins: parent.height * 0.03
            }
            width: parent.width * 0.25
            height: parent.height * 0.45
            radius: parent.height

            // Static text to display "Choose Output"
            Text {
                anchors.centerIn: parent
                text: "Choose Output"
                font.pixelSize: parent.height * 0.5
                font.bold: true
                color: "black"
            }

            // When user clicks, display FileDialog and announce Output is selected
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    id_fileDialog.visible = true
                    isChooseInput = false
                }
            }
        }

        // Display Output File Name
        Rectangle {
            anchors {
                right: parent.right
                bottom: parent.bottom
                margins: parent.height * 0.03
            }
            width: parent.width * 0.74
            height: parent.height * 0.45
            radius: parent.height

            // Text to display full output image location
            Text {
                anchors {
                    left: parent.left
                    leftMargin: parent.height * 0.2
                    verticalCenter: parent.verticalCenter
                }
                text: outputimage
                font.pixelSize: parent.height * 0.3
                color: "black"
                wrapMode: Text.WordWrap
            }
        }
    }

    // FileDialog to select file
    FileDialog {
        id: id_fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            if(isChooseInput){ // Processing in case of input
                var path = id_fileDialog.fileUrl.toString()
                path = path.replace(/^(file:\/{3})/, "")
                // Update Input image location
                inputimage = decodeURIComponent(path)

                // Reset data
                id_inputimage.freeImage()
                id_outputimage.freeImage()
                id_executingTime.text = ""
                dipFeatures.dipResetData()
                dipFeatures.dipSetImageSource(inputimage)
                dipFeatures.dipLoadImage()
                id_inputimage.image = dipFeatures.dipConvertInput2QImage()
                current_feature = ""
                root.refreshfeature = !root.refreshfeature

                // When new file is loaded, also update histogram
                if(root.isClickedHistogram){
                    dipFeatures.dipCalculateHistogramInput()
                    id_histogramInputArea.show()
                    id_histogramOutputArea.stop()
                }
            }else{ // Processing in case of output
                var path = id_fileDialog.fileUrl.toString()
                path = path.replace(/^(file:\/{3})/, "")
                // Update Output image location
                outputimage = decodeURIComponent(path)
            }
        }
    }

    // Area for exit processing
    Rectangle {
        id: id_exitarea
        anchors {
            top: root.top
            right: root.right
        }
        width: root.width * 0.23
        height: root.height * 0.1
        color: "transparent"

        // Exit button
        Rectangle {
            anchors {
                top: parent.top
                right: parent.right
                margins: parent.width * 0.01
            }
            width: parent.width * 0.2
            height: parent.width * 0.2
            color: "transparent"

            Image {
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                source: 'image//close.png'
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    Qt.quit()
                }
            }
        }

        // Text to display execution time
        Text {
            id: id_executingTime
            anchors.fill: parent
            text: ""
            font.pixelSize: parent.height / 3
            font.bold: true
            color: "black"
            wrapMode: Text.WordWrap
        }
    }

    // Area to list up features
    Rectangle {
        id: id_featurearea
        anchors {
            top: id_appnamearea.bottom
            left: root.left
            bottom: root.bottom
        }
        width: root.width * 0.12
        color: "transparent"
    }

    // Area to display input image
    Rectangle {
        id: id_inputimagearea
        anchors {
            top: id_appnamearea.bottom
            left: id_featurearea.right
        }
        width: root.width * 0.44
        height: root.height * 0.7
        color: "transparent"

        DIPShowImage {
            id: id_inputimage
            anchors.centerIn: parent
            anchors.fill: parent
        }

        // Text to display detail information of input image
        Text {
            id: id_inputimagearea_detail
            anchors.fill: parent
            text: "WIDTH: " + dipFeatures.getInputWidth() + "\n" +
                  "HEIGHT: " + dipFeatures.getInputHeight() + "\n" +
                  "DEPTH: " + dipFeatures.getInputDepth()
            font.pixelSize: parent.height * 0.05
            color: "black"
            visible: false
        }
    }

    // Area to display output image
    Rectangle {
        id: id_outputimagearea
        anchors {
            top: id_appnamearea.bottom
            right: root.right
        }
        width: root.width * 0.44
        height: root.height * 0.7
        color: "transparent"

        DIPShowImage {
            id: id_outputimage
            anchors.centerIn: parent
            anchors.fill: parent
        }

        // Text to display detail information of output image
        Text {
            id: id_outputimagearea_detail
            anchors.fill: parent
            text: "WIDTH: " + dipFeatures.getOutputWidth() + "\n" +
                  "HEIGHT: " + dipFeatures.getOutputHeight() + "\n" +
                  "DEPTH: " + dipFeatures.getOutputDepth()
            font.pixelSize: parent.height * 0.05
            color: "black"
            visible: false
        }
    }

    // Area to display information of each feature
    Rectangle {
        id: id_informationarea
        anchors {
            bottom: root.bottom
            left: id_featurearea.right
            top: id_inputimagearea.bottom
        }
        width: root.width * 0.50
        color: "transparent"

        Rectangle {
            anchors{
                fill: parent
                margins: parent.height * 0.05
            }
            color: "white"
            opacity: 0.4
        }

        // Static text displays string "Description"
        Text {
            id: id_textstatic
            anchors {
                top: parent.top
                topMargin: parent.height * 0.05
                horizontalCenter: parent.horizontalCenter
            }
            text: "Description"
            font.pixelSize: parent.height * 0.2
            font.bold: true
            color: "black"
        }

        Rectangle {
            anchors {
                top: id_textstatic.bottom
                left: parent.left
                right: parent.right
                bottom: parent.bottom
                margins: parent.height * 0.06
            }
            color: "transparent"

            // Text to display information of feature
            Text {
                id: id_textdescription
                anchors.fill: parent
                text: ""
                font.pixelSize: id_informationarea.height * 0.1
                color: "black"
                wrapMode: Text.WordWrap
            }
        }
    }

    // Area to control of each feature
    Rectangle {
        id: id_controlarea
        anchors {
            bottom: root.bottom
            left: id_informationarea.right
            top: id_inputimagearea.bottom
            right: root.right
            margins: id_informationarea.height * 0.05
        }
        color: "white"
        opacity: 0.4
        radius: height * 0.2
    }

    // Area to support option functions
    Rectangle {
        id: id_optionarea
        anchors {
            right: root.right
            verticalCenter: id_outputimagearea.verticalCenter
        }
        width: root.width * 0.03
        height: width * 3.2
        color: "transparent"

        // Button to save output image to file
        Rectangle {
            id: id_save
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
                margins: 2
            }
            height: parent.width
            radius: height * 0.2

            // Image for button
            Image {
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                source: 'image//save.png'
            }

            // When user clicks, write output to BMP file
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    dipFeatures.dipWriteBmp(outputimage)
                }
            }
        }

        // Button to show up detail information of input/output image
        Rectangle {
            id: id_detail
            anchors {
                top: id_save.bottom
                left: parent.left
                right: parent.right
                margins: 2
            }
            height: parent.width
            radius: height * 0.2

            // Image for button
            Image {
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                source: 'image//detail.png'
            }

            // When user clicks, processing to show information
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.isClickedDetail = !root.isClickedDetail
                    if(root.isClickedDetail){ // In case of enable detail information
                        id_detail.color = "#FFDE03"

                        // Display input information
                        id_inputimagearea_detail.visible = true
                        id_inputimagearea_detail.text =
                                "WIDTH: " + dipFeatures.getInputWidth() + "\n" +
                                "HEIGHT: " + dipFeatures.getInputHeight() + "\n" +
                                "DEPTH: " + dipFeatures.getInputDepth()

                        // Display output information
                        id_outputimagearea_detail.visible = true
                        id_outputimagearea_detail.text =
                                "WIDTH: " + dipFeatures.getOutputWidth() + "\n" +
                                "HEIGHT: " + dipFeatures.getOutputHeight() + "\n" +
                                "DEPTH: " + dipFeatures.getOutputDepth()
                    }else{ // In case of disable detail information
                        id_detail.color = "white"
                        id_inputimagearea_detail.visible = false
                        id_outputimagearea_detail.visible = false
                    }
                }
            }
        }

        // Button to show up histogram of input/output image
        Rectangle {
            id: id_histogram
            anchors {
                top: id_detail.bottom
                left: parent.left
                right: parent.right
                margins: 2
            }
            height: parent.width
            radius: height * 0.2

            // Image for button
            Image {
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                source: 'image//histogram.png'
            }

            // When user clicks, processing to show histogram
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.isClickedHistogram = !root.isClickedHistogram
                    if(root.isClickedHistogram){ // In case of enable histogram
                        id_histogram.color = "#FFDE03"

                        // Calculate and display Histogram for Input
                        dipFeatures.dipCalculateHistogramInput()
                        id_histogramInputArea.show()

                        // Calculate and display Histogram for Output
                        if(current_feature) {
                            dipFeatures.dipCalculateHistogramOutput()
                            id_histogramOutputArea.show()
                        }
                    }else{ // In case of disable histogram
                        id_histogram.color = "white"

                        // Stop display for both of Input/Output
                        id_histogramInputArea.stop()
                        id_histogramOutputArea.stop()
                    }
                }
            }
        }
    }

    // Area for Input image histogram
    HistogramArea {
        id: id_histogramInputArea
        anchors.fill: id_inputimagearea
        isInput: true
    }

    // Area for Output image histogram
    HistogramArea {
        id: id_histogramOutputArea
        anchors.fill: id_outputimagearea
        isInput: false
    }

    // Store the list of Features
    ListModel {
        id: id_listFeatures
    }

    // Display the list of Features
    Component {
        id: id_displayFeatures

        Item {
            // By default, only display GroupItem(parent).
            // The feature(children) will be displayed when user select
            height: (control == Common.GroupItem) ? id_featurearea.height / 20 : 0
            width: id_featurearea.width

            // Button to display Group Icon
            Rectangle {
                id: id_groupicon

                // Internal property to receive Feature list refresh signal
                property bool isRefresh: refreshfeature

                anchors {
                    left: parent.left
                    top: parent.top
                    bottom: parent.bottom
                    leftMargin: 2
                    topMargin: 2
                    bottomMargin: 2
                }
                width: parent.width * 0.1
                // Only visible for GroupItem
                visible: (control == Common.GroupItem) ? true : false

                // Status Image
                Image {
                    id: id_groupiconstatus
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    source: 'image//groupclose.png'
                }

                // Processing when user clicks
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        // Update group status
                        id_data.groupstatus[groupstatusindex] = !id_data.groupstatus[groupstatusindex]

                        // Announce feature list is refreshed
                        root.refreshfeature = !root.refreshfeature
                    }
                }

                // Catch up feature list is refreshed
                onIsRefreshChanged: {
                    if(id_data.groupstatus[groupstatusindex]) {
                        // When group is opened
                        id_groupiconstatus.source = 'image//groupopen.png'
                    }else{
                        // When group is closed
                        id_groupiconstatus.source = 'image//groupclose.png'
                    }
                }
            }

            // Button to display Group Item or Feature Item
            Rectangle {
                // Internal property to receive Feature list refresh signal
                property bool isRefresh: refreshfeature

                anchors {
                    left: id_groupicon.right
                    top: parent.top
                    bottom: parent.bottom
                    right: parent.right
                    rightMargin: 2
                    topMargin: 2
                    bottomMargin: 2
                }
                color: (current_feature == feature) ? "black" : "white"
                // By defaut, only group items are displayed
                visible: (control == Common.GroupItem) ? true : false
                radius: (control == Common.GroupItem) ? 0 : parent.height * 0.5

                // Catch up feature list is refreshed
                onIsRefreshChanged: {
                    if(control == Common.GroupItem){
                        // visible when GroupItem is selected
                        visible = true
                    }else if(id_data.groupstatus[groupstatusindex]){
                        // visible when GroupItem status is opened
                        visible = true
                        parent.height = id_featurearea.height / 20
                    }else{
                        // invisible when GroupItem status is closed
                        visible = false
                        parent.height = 0
                    }
                }

                // Text to display feature name
                Text {
                    anchors.centerIn: parent
                    text: feature
                    font.pixelSize: 20
                    font.bold: (control == Common.GroupItem) ? true : false
                    color: (current_feature == feature) ? "white" : "black"
                }

                // Processing when user clicks
                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        if(control == Common.GroupItem){
                            // Click on GroupItem
                            id_data.groupstatus[groupstatusindex] = !id_data.groupstatus[groupstatusindex]
                        }

                        // Update and refresh feature
                        root.refreshfeature = !root.refreshfeature
                        current_feature = feature

                        // Load feature
                        if(control != Common.GroupItem){ // Click on none group item
                            // Clear old control
                            id_loaderControl.source = ""
                            id_textdescription.text = description
                            if(control != ""){
                                // Setting new control
                                id_loaderControl.source = "control/" + control

                                // Initialize data for new control
                                var scene = null
                                scene = id_loaderControl.item
                                scene.parent = root
                                scene.anchors.fill = id_controlarea
                                scene.inputWidth = dipFeatures.getInputWidth()
                                scene.inputHeight = dipFeatures.getInputHeight()
                                // Connect signal controlInfor with slot controlInformationUpdate
                                scene.controlInfor.connect(controlInformationUpdate)
                                // Call initializeControls function
                                scene.initializeControls()
                            }
                            executeDIPFeatures()
                        }
                    }
                }
            }
        }
    }

    // Apply Scroll View for Features List
    Flickable {
        id: id_scrollview
        anchors.fill: id_featurearea
        contentHeight: id_listFeatures.count * (id_featurearea.height / 20)
        clip: true

        Column {
            anchors.fill: parent
            Repeater {
                model: id_listFeatures // ListModel
                delegate: id_displayFeatures // Component delegate
            }
        }
    }

    // Using to open control
    Loader {
        id: id_loaderControl
    }

    // Function to call Digital Image Processing features
    function executeDIPFeatures() {
        // Variable to get input arguments for DIP features
        var scene = null
        scene = id_loaderControl.item

        // Start counting timer
        dipFeatures.dipStartTimer()

        // The feature is decided by global property current_feature
        if(current_feature === Common.RGB2Gray){
            dipFeatures.dipConvertRGBToGrayScale()
        }else if(current_feature === Common.FlipVer){
            dipFeatures.dipFlipVertical()
        }else if(current_feature === Common.FlipHor){
            dipFeatures.dipFlipHorizontal()
        }else if(current_feature === Common.Rot90){
            dipFeatures.dipRotation90()
        }else if(current_feature === Common.Rot180){
            dipFeatures.dipRotation180()
        }else if(current_feature === Common.Rot270){
            dipFeatures.dipRotation270()
        }else if(current_feature === Common.Rot){
            dipFeatures.dipRotation(scene.xorigin, scene.yorigin, scene.angle)
        }else if(current_feature === Common.HistogramEqualization){
            dipFeatures.dipHistogramEqualization(256, scene.newGrays)
        }else if(current_feature == Common.MathAdd){
            dipFeatures.dipMathAdd(scene.pValue)
        }else if(current_feature == Common.MathSubtract){
            dipFeatures.dipMathSubtract(scene.pValue)
        }else if(current_feature == Common.MathAnd){
            dipFeatures.dipMathAnd(scene.pValue)
        }else if(current_feature == Common.MathOr){
            dipFeatures.dipMathOr(scene.pValue)
        }else if(current_feature == Common.MathXor){
            dipFeatures.dipMathXor(scene.pValue)
        }else if(current_feature == Common.MathNot){
            dipFeatures.dipMathNot()
        }else if(current_feature == Common.MathNand){
            dipFeatures.dipMathNand(scene.pValue)
        }else if(current_feature == Common.MathNor){
            dipFeatures.dipMathNor(scene.pValue)
        }else if(current_feature == Common.OverlayNonZero){
            dipFeatures.dipOverlayNonZero(scene.startrowofimg1, scene.startrowofimg2, scene.newheight,
                                 scene.startcolofimg1, scene.startcolofimg2, scene.newwidth)
        }else if(current_feature == Common.OverlayZero){
            dipFeatures.dipOverlayZero(scene.startrowofimg1, scene.startrowofimg2, scene.newheight,
                                 scene.startcolofimg1, scene.startcolofimg2, scene.newwidth)
        }else if(current_feature == Common.OverlayGreater){
            dipFeatures.dipOverlayGreater(scene.startrowofimg1, scene.startrowofimg2, scene.newheight,
                                 scene.startcolofimg1, scene.startcolofimg2, scene.newwidth)
        }else if(current_feature == Common.OverlayLess){
            dipFeatures.dipOverlayLess(scene.startrowofimg1, scene.startrowofimg2, scene.newheight,
                                 scene.startcolofimg1, scene.startcolofimg2, scene.newwidth)
        }else if(current_feature == Common.OverlayAverage){
            dipFeatures.dipOverlayAverage(scene.startrowofimg1, scene.startrowofimg2, scene.newheight,
                                 scene.startcolofimg1, scene.startcolofimg2, scene.newwidth)
        }else if(current_feature == Common.Invert){
            dipFeatures.dipInvert()
        }else if(current_feature == Common.Geometry){
            dipFeatures.dipGeometry(scene.angle, scene.xstretch, scene.ystretch, scene.xdisplace, scene.ydisplace, scene.xcross, scene.ycross)
        }else if(current_feature == Common.Stretch){
            dipFeatures.dipStretch(scene.xstretch, scene.ystretch)
        }else if(current_feature == Common.Crop){
            dipFeatures.dipCrop(scene.startrow, scene.startcol, scene.newheight, scene.newwidth)
        }else if(current_feature == Common.Paste){
            dipFeatures.dipPaste(scene.startrowofimg1, scene.startrowofimg2, scene.newheight,
                                 scene.startcolofimg1, scene.startcolofimg2, scene.newwidth)
        }else if(current_feature == Common.Warp){
            dipFeatures.dipWarp(scene.xcontrol, scene.ycontrol)
        }else if(current_feature == Common.ObjectWarp){
            dipFeatures.dipObjectWarp(scene.x1, scene.y1, scene.x2, scene.y2, scene.x3, scene.y3, scene.x4, scene.y4)
        }else if(current_feature == Common.FilterImage){
            dipFeatures.dipFilterImage(scene.masktype, scene.lowhigh)
        }else if(current_feature == Common.MedianFilter){
            dipFeatures.dipMedianFilter(scene.size)
        }

        // Stop counting timer and display result
        id_executingTime.text = "Executing time:\n" + dipFeatures.dipStopTimer() + " ms"

        // Convert output image to QImage for display
        id_outputimage.image = dipFeatures.dipConvertOutput2QImage()

        // Update output image information to display in detail area
        if(root.isClickedDetail){
            id_outputimagearea_detail.text =
                    "WIDTH: " + dipFeatures.getOutputWidth() + "\n" +
                    "HEIGHT: " + dipFeatures.getOutputHeight() + "\n" +
                    "DEPTH: " + dipFeatures.getOutputDepth()
        }

        // Update histogram information of output image
        if(root.isClickedHistogram){
            dipFeatures.dipCalculateHistogramOutput()
            id_histogramOutputArea.show()
        }
    }

    // This is processing slot for signal controlInfor
    function controlInformationUpdate() {
        executeDIPFeatures()
    }
}
