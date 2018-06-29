#pragma once
// Automatically generated header file

#include "lwm2m/objects.h"
namespace KnownObjects {
namespace id15 {
// Custom, overrideable types for Opaque and String resources

    #ifndef Property15
    class PropertyType : public PreallocString<30> {};
    #endif
    
    #ifndef Description15
    class DescriptionType : public PreallocString<30> {};
    #endif
    

/* \brief Class for object 15 - DevCapMgmt
 *  This LWM2M Object is dedicated to manage the device capabilities of a device e.g. sensors,
 *  communication, etc.
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - List of Device Capabilities inside a given Group.The format is a free list ASCII-represented integers separated by a semi colon. (e.g. 0;1;10)The list of capabilities per Group is given in Appendix B: Device Capabilities Vocabularyexecutable Resource can work with.
    PropertyType Property;
    
    // 1 - Group name of Device Capabilities0: SENSOR: luminosity, presence,temp,humidity1: CONTROL: Light, Power, Sound2: CONNECTIVITY: Bluetooth, wifi, …3: NAVIGATION: gps, galieo4: STORAGE: external memory,5: VISION: cam, video-cam, night_cam.6: SOUND: speaker, buzzer7: ANALOG_INPUT: generic input8: ANALOG_OUTPUT: generic output9-15: reserved
    int Group;
    
    // Optional resource
    // 2 - Device Capability Description(manufacturer specified string)
    DescriptionType Description;
    
    // Optional resource
    // 3 - When the resource doesn’t exist, it means the associated Device Capability is not removable.When this resource is “False”, it means the associated Device Capability is removable and is currently not attached to the device.When this resource is “True”, it means the associated Device Capability – if removable – is currently attached to the Device.When a Device Capability is not removable, and the “Attached” Resource is present, the “Attached” value but be set to “True”.
    bool Attached;
    
    // 4 - This resource indicates whether the Device Capability is enabled regardless whether the Device Capability is attached or not. If the value of this resource is “True” the Device Capability is in Enabled State. If the value is “False” the Device Capability is in Disabled State;The ‘Attached’ and ‘Enabled’ resources are independent. A Device Capability MAY have ‘True’ as value for ‘Enabled’ Resource while having ‘False’ as value for the ‘Attached’ Resource. That means the Device Capability is still not available and can’t be used until it is attached to the Device, but will be useable once the Device Capability is attached.
    bool Enabled;
    
    // 5 - This command is used to enable the Device Capability to transfer the Device Capability from Disabled State to Enabled state.In Enabled State, the Device Capability is allowed to work when it is attached to the Device.
    Executable opEnable;

    // 6 - This command is used to disable the Device Capability to transfer the Device Capability from Enabled State to Disabled State.In Disabled state the Device Capability is not allowed to work.
    Executable opDisable;

    // Optional resource
    // 7 - When the Resources “Enabled” or “Attached” are under “Observation”, this resource specifies whether the LWM2M Server MUST be notified when the value of the Resource on “Observation” changed. If the Resource “NotifyEn” is not present or the value is ‘False’, the LWM2M Server will be not notified about this change. If the “NotifyEn” Resource is present and the value is ‘True’, the LWM2M Server will be notified.
    bool NotifyEn;
    
};

enum class RESID {
    Property = 0,
    Group = 1,
    Description = 2,
    Attached = 3,
    Enabled = 4,
    opEnable = 5,
    opDisable = 6,
    NotifyEn = 7,
    
};

/* \brief Class for object 15 - DevCapMgmt
 *  This LWM2M Object is dedicated to manage the device capabilities of a device e.g. sensors,
 *  communication, etc.
 */
class object : public Lwm2mObject<15, object, instance> {
public:

    // 0 - List of Device Capabilities inside a given Group.The format is a free list ASCII-represented integers separated by a semi colon. (e.g. 0;1;10)The list of capabilities per Group is given in Appendix B: Device Capabilities Vocabularyexecutable Resource can work with.
    Resource(0, &instance::Property, O_RES_R) Property;
    
    // 1 - Group name of Device Capabilities0: SENSOR: luminosity, presence,temp,humidity1: CONTROL: Light, Power, Sound2: CONNECTIVITY: Bluetooth, wifi, …3: NAVIGATION: gps, galieo4: STORAGE: external memory,5: VISION: cam, video-cam, night_cam.6: SOUND: speaker, buzzer7: ANALOG_INPUT: generic input8: ANALOG_OUTPUT: generic output9-15: reserved
    Resource(1, &instance::Group, O_RES_R) Group;
    
    // Optional resource
    // 2 - Device Capability Description(manufacturer specified string)
    Resource(2, &instance::Description, O_RES_R) Description;
    
    // Optional resource
    // 3 - When the resource doesn’t exist, it means the associated Device Capability is not removable.When this resource is “False”, it means the associated Device Capability is removable and is currently not attached to the device.When this resource is “True”, it means the associated Device Capability – if removable – is currently attached to the Device.When a Device Capability is not removable, and the “Attached” Resource is present, the “Attached” value but be set to “True”.
    Resource(3, &instance::Attached, O_RES_R) Attached;
    
    // 4 - This resource indicates whether the Device Capability is enabled regardless whether the Device Capability is attached or not. If the value of this resource is “True” the Device Capability is in Enabled State. If the value is “False” the Device Capability is in Disabled State;The ‘Attached’ and ‘Enabled’ resources are independent. A Device Capability MAY have ‘True’ as value for ‘Enabled’ Resource while having ‘False’ as value for the ‘Attached’ Resource. That means the Device Capability is still not available and can’t be used until it is attached to the Device, but will be useable once the Device Capability is attached.
    Resource(4, &instance::Enabled, O_RES_R) Enabled;
    
    // 5 - This command is used to enable the Device Capability to transfer the Device Capability from Disabled State to Enabled state.In Enabled State, the Device Capability is allowed to work when it is attached to the Device.
    Resource(5, &instance::opEnable) opEnable;
    
    // 6 - This command is used to disable the Device Capability to transfer the Device Capability from Enabled State to Disabled State.In Disabled state the Device Capability is not allowed to work.
    Resource(6, &instance::opDisable) opDisable;
    
    // Optional resource
    // 7 - When the Resources “Enabled” or “Attached” are under “Observation”, this resource specifies whether the LWM2M Server MUST be notified when the value of the Resource on “Observation” changed. If the Resource “NotifyEn” is not present or the value is ‘False’, the LWM2M Server will be not notified about this change. If the “NotifyEn” Resource is present and the value is ‘True’, the LWM2M Server will be notified.
    Resource(7, &instance::NotifyEn, O_RES_RW) NotifyEn;
    
};

} // end of id namespace
} // end of KnownObjects namespace
inline bool operator== (KnownObjects::id15::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, KnownObjects::id15::RESID c1) { return (uint16_t) c1 == c2; }
	