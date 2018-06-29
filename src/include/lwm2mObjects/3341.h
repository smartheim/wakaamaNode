#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id3341 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Text3341
    class TextType : public PreallocString<30> {};
    #endif
    
    #ifndef ApplicationType3341
    class ApplicationTypeType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 3341 - Addressable Text Display
 *  This IPSO object is used to send text to a text-only or text mode graphics display. POSTing
 *  a string of text to the text resource causes it to be displayed at the selected X and Y locations
 *  on the display. If X or Y are set to a value greater than the size of the display, the position
 *  “wraps around” to the modulus of the setting and the display size. Likewise, if the text
 *  string overflows the display size, the text “wraps around” and displays on the next
 *  line down or, if the last line has been written, wraps around to the top of the display.
 *  Brightness and Contrast controls are provided to allow control of various display
 *  types including STN and DSTN type LCD character displays. POSTing an empty payload
 *  to the Clear Display resource causes the display to be erased.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5527 - A string of text.
    TextType Text;
    
    // Optional resource
    // 5528 - X Coordinate.
    int XCoordinate;
    
    // Optional resource
    // 5529 - Y Coordinate.
    int YCoordinate;
    
    // Optional resource
    // 5545 - The highest X coordinate the display supports before wrapping to the next line.
    int MaxXCoordinate;
    
    // Optional resource
    // 5546 - The highest Y coordinate the display supports before wrapping to the next line.
    int MaxYCoordinate;
    
    // Optional resource
    // 5530 - Command to clear the display.
    Executable ClearDisplay;

    // Optional resource
    // 5851 - Proportional control, integer value between 0 and 100 as a percentage.
    float Dimmer;
    
    // Optional resource
    // 5531 - Proportional control, integer value between 0 and 100 as a percentage.
    float Contrast;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    ApplicationTypeType ApplicationType;
    
};

enum class RESID {
    Text = 5527,
    XCoordinate = 5528,
    YCoordinate = 5529,
    MaxXCoordinate = 5545,
    MaxYCoordinate = 5546,
    ClearDisplay = 5530,
    Dimmer = 5851,
    Contrast = 5531,
    ApplicationType = 5750,
    
};

/* \brief Class for object 3341 - Addressable Text Display
 *  This IPSO object is used to send text to a text-only or text mode graphics display. POSTing
 *  a string of text to the text resource causes it to be displayed at the selected X and Y locations
 *  on the display. If X or Y are set to a value greater than the size of the display, the position
 *  “wraps around” to the modulus of the setting and the display size. Likewise, if the text
 *  string overflows the display size, the text “wraps around” and displays on the next
 *  line down or, if the last line has been written, wraps around to the top of the display.
 *  Brightness and Contrast controls are provided to allow control of various display
 *  types including STN and DSTN type LCD character displays. POSTing an empty payload
 *  to the Clear Display resource causes the display to be erased.
 */
class object : public Lwm2mObject<3341, object, instance> {
public:

    // 5527 - A string of text.
    Resource(5527, &instance::Text, O_RES_RW) Text;
    
    // Optional resource
    // 5528 - X Coordinate.
    Resource(5528, &instance::XCoordinate, O_RES_RW) XCoordinate;
    
    // Optional resource
    // 5529 - Y Coordinate.
    Resource(5529, &instance::YCoordinate, O_RES_RW) YCoordinate;
    
    // Optional resource
    // 5545 - The highest X coordinate the display supports before wrapping to the next line.
    Resource(5545, &instance::MaxXCoordinate, O_RES_R) MaxXCoordinate;
    
    // Optional resource
    // 5546 - The highest Y coordinate the display supports before wrapping to the next line.
    Resource(5546, &instance::MaxYCoordinate, O_RES_R) MaxYCoordinate;
    
    // Optional resource
    // 5530 - Command to clear the display.
    Resource(5530, &instance::ClearDisplay) ClearDisplay;
    
    // Optional resource
    // 5851 - Proportional control, integer value between 0 and 100 as a percentage.
    Resource(5851, &instance::Dimmer, O_RES_RW) Dimmer;
    
    // Optional resource
    // 5531 - Proportional control, integer value between 0 and 100 as a percentage.
    Resource(5531, &instance::Contrast, O_RES_RW) Contrast;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id3341::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id3341::RESID c1) { return (uint16_t) c1 == c2; }
	