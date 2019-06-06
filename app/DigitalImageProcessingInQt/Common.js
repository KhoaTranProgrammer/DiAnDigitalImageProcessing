// Name of features are used by QML
// current_feature will be updated each time user selects feature
var GroupItem = "GroupItem"
var RGB2Gray = "ConvertRGB2Gray"
var HistogramEqualization = "HistogramEqualization"

/*
 Group format
  + GroupItem: this is parent of group, just display group name
  + FeatureItem(s): they are detail Features in group
*/

/*
 GroupItem format
  + GroupName: this is the name of Feature
  + Control: group do not need control GUI
  + Description: group do not need description
*/

/*
 FeatureItem format
  + FeatureName: this is the name of Feature
  + Control: this is GUI to contron Feature arguments
  + Description: this is the introduction about Feature
*/

// Group of Convert Features
var group_convert = [
    /* GroupItem */ "Convert", GroupItem, "",
    /* FeatureItem */ RGB2Gray, "", "Function: DaDip_Convert_RGB_To_GrayScale. API to convert from RGB to GrayScale image."
]

// Group of Histogram Features
var group_histogram = [
    /* GroupItem */ "Histogram", GroupItem, "",
    /* FeatureItem */ HistogramEqualization, "HistogramEqualizationControl.qml", "Function: DaDip_Histogram_Equalization. API to perform histogram equalization of input image"
]

// List of all groups. It is directly used by application to add feature list
var group_list = [
    /* Group of Convert Features */ group_convert,
    /* Group of Histogram Features */ group_histogram
]
