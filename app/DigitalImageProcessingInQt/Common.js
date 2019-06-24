// Name of features are used by QML
// current_feature will be updated each time user selects feature
var GroupItem = "GroupItem"
var RGB2Gray = "ConvertRGB2Gray"
var FlipVer = "FlipVertical"
var FlipHor = "FlipHorizontal"
var Rot90 = "Rotate90"
var Rot180 = "Rotate180"
var Rot270 = "Rotate270"
var Rot = "RotateAny"
var HistogramEqualization = "HistogramEqualization"
var MathAdd = "Add"
var MathSubtract = "Subtract"
var MathAnd = "And"
var MathOr = "Or"
var MathXor = "Xor"
var MathNot = "Not"
var MathNand = "Nand"
var MathNor = "Nor"

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

// Group of Rotation Features
var group_rotate = [
    /* GroupItem */ "Rotate", GroupItem, "",
    /* FeatureItem */ FlipVer, "", "Function: DaDip_Flip_Vertical. API to perform Flip image as vertical",
    /* FeatureItem */ FlipHor, "", "Function: DaDip_Flip_Horizontal. API to perform Flip image as horizontal",
    /* FeatureItem */ Rot90, "", "Function: DaDip_Rotation_90_Degree. API to perform 90 degree rotation",
    /* FeatureItem */ Rot180, "", "Function: DaDip_Rotation_180_Degree. API to perform 180 degree rotation",
    /* FeatureItem */ Rot270, "", "Function: DaDip_Rotation_270_Degree. API to perform 270 degree rotation",
    /* FeatureItem */ Rot, "RotationControl.qml", "Function: DaDip_Rotation. API to perform rotation in any point of origin"
]

// Group of Histogram Features
var group_histogram = [
    /* GroupItem */ "Histogram", GroupItem, "",
    /* FeatureItem */ HistogramEqualization, "HistogramEqualizationControl.qml", "Function: DaDip_Histogram_Equalization. API to perform histogram equalization of input image"
]

// Group of Mathematic Features
var group_math = [
    /* GroupItem */ "Mathematic", GroupItem, "",
    /* FeatureItem */ MathAdd, "MathControl.qml", "Function: DaDip_Math_Add. API to implement the basic algebra function Add",
    /* FeatureItem */ MathSubtract, "MathControl.qml", "Function: DaDip_Math_Subtract. API to implement the basic algebra function Subtract",
    /* FeatureItem */ MathAnd, "MathControl.qml", "Function: DaDip_Math_And. API to implement the basic algebra function And",
    /* FeatureItem */ MathOr, "MathControl.qml", "Function: DaDip_Math_Or. API to implement the basic algebra function Or",
    /* FeatureItem */ MathXor, "MathControl.qml", "Function: DaDip_Math_Xor. API to implement the basic algebra function Xor",
    /* FeatureItem */ MathNot, "", "Function: DaDip_Math_Not. API to implement the basic algebra function Not",
    /* FeatureItem */ MathNand, "MathControl.qml", "Function: DaDip_Math_Nand. API to implement the basic algebra function Nand",
    /* FeatureItem */ MathNor, "MathControl.qml", "Function: DaDip_Math_Nor. API to implement the basic algebra function Nor"
]

// List of all groups. It is directly used by application to add feature list
var group_list = [
    /* Group of Convert Features */ group_convert,
    /* Group of Histogram Features */ group_histogram,
    /* Group of Rotation Features */ group_rotate,
    /* Group of Mathematic Features */ group_math
]
