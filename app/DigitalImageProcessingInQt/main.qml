import QtQuick 2.6
import DIPShowImage 1.0
import "Common.js" as Common

Rectangle {
    id: root
    anchors.fill: parent

    // Current feature is selected by user
    property string current_feature: ""

    // This property is changed when Feature is updated
    property bool refreshfeature: false

    // Default input image
    property string inputimage: defaultinput + "/image/obama.bmp"

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
                            id_textdescription.text = description
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
        contentHeight: id_listFeatures.rowCount() * (id_featurearea.height / 20)
        clip: true

        Column {
            anchors.fill: parent
            Repeater {
                model: id_listFeatures // ListModel
                delegate: id_displayFeatures // Component delegate
            }
        }
    }

    // Function to call Digital Image Processing features
    function executeDIPFeatures() {
        // Start counting timer
        dipFeatures.dipStartTimer()

        // The feature is decided by global property current_feature
        if(current_feature == Common.RGB2Gray){
            dipFeatures.dipConvertRGBToGrayScale()
        }

        // Stop counting timer and display result
        id_executingTime.text = "Executing time:\n" + dipFeatures.dipStopTimer() + " ms"

        // Convert output image to QImage for display
        id_outputimage.image = dipFeatures.dipConvertOutput2QImage()
    }
}
