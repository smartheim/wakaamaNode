#pragma once
// Automatically generated header file

#include "lwm2m_objects.hpp"
namespace KnownObjects {
namespace id3349 {
/* \brief Class for object 3349 - Bitmap
 *  Summarize several digital inputs to one value by mapping each bit to a digital input.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 5910 - Integer in which each of the bits are associated with specific digital input value. Represented as a binary signed integer in network byte order, and in two's complement representation. Using values in range 0-127 is recommended to avoid ambiguities with byte order and negative values.
    int BitmapInput;
    
    // Optional resource
    // 5911 - Reset the Bitmap Input value.
    Executable BitmapInputReset;

    // Optional resource
    // 5912 - The semantics / description of each bit as a string. First instance describes the least significant bit, second instance the second least significant bit, etc.
    PreallocString<30> ElementDescription;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    PreallocString<30> ApplicationType;
    
    enum class RESID {
        BitmapInput = 5910,
        BitmapInputReset = 5911,
        ElementDescription = 5912,
        ApplicationType = 5750,
        
    };
};

/* \brief Class for object 3349 - Bitmap
 *  Summarize several digital inputs to one value by mapping each bit to a digital input.
 */
class object : public Lwm2mObject<3349, object, instance> {
public:

    // 5910 - Integer in which each of the bits are associated with specific digital input value. Represented as a binary signed integer in network byte order, and in two's complement representation. Using values in range 0-127 is recommended to avoid ambiguities with byte order and negative values.
    Resource(5910, &instance::BitmapInput, O_RES_R) BitmapInput;
    
    // Optional resource
    // 5911 - Reset the Bitmap Input value.
    Resource(5911, &instance::BitmapInputReset) BitmapInputReset;
    
    // Optional resource
    // 5912 - The semantics / description of each bit as a string. First instance describes the least significant bit, second instance the second least significant bit, etc.
    Resource(5912, &instance::ElementDescription, O_RES_RW) ElementDescription;
    
    // Optional resource
    // 5750 - The application type of the sensor or actuator as a string depending on the use case.
    Resource(5750, &instance::ApplicationType, O_RES_RW) ApplicationType;
    
};

} // end of id namespace
inline bool operator== (id3349::instance::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, id3349::instance::RESID c1) { return (uint16_t) c1 == c2; }

} // end of KnownObjects namespace
	