# OMA defined LwM2M objects and resources

The [OMA LwM2M Registry](http://www.openmobilealliance.org/wp/OMNA/LwM2M/LwM2MRegistry.html) contains a wide range of defined objects and resources,
in a machine readable way (XML).
New objects and resources can be proposed via the [LwM2M Editor](http://devtoolkit.openmobilealliance.org/OEditor/).

WakaamaNode provides ready-to-consume C++ objects for all lwM2M objects of the registry. Just be aware that
special implementations exist for object ID 1 (LWM2M Server), 2 (Access Control), 3 (device) and 5 (firmware)
and you should not use the auto generated ones.

## How to use a predefined object

A full example can be found in [Get started](/quickstart/getting-started.md).
For example if you want to use the "Light Control" lwM2M object:

* Search the list below for "Light Control".
* Find it under object id 3311.
* Include `src/lwm2mObjects/3311.h` and use the class `object` in namespace *KnownObjects/id311*.
* Create as many object instances as you need and add them to the object via `object.addInstance(lwm2mContext, objectInstance)`.
* Make the object itself known to WakaamaNode with `object.register(lwm2mContext)`.


```cpp
#include "lwm2mObjects/3311.h"
#include "lwm2m/connect.h"

lwm2m_client_context_t context;

using namespace KnownObjects;

// Define the object and as many instances as you need
id3311::object lights;
id3311::instance led;

void setup() {
    // Overwrite the verifyFunction and "abuse" it as value changed event.
    lights.verifyWrite = [](id3311::instance* inst, uint16_t res_id) {
        // Is it instance 0 and the OnOff resource?
        if (inst->id == 0 && res_id == id3311::RESID::OnOff) {
            // Change the led pin depending on the OnOff value
            digitalWrite(LED_BUILTIN, inst->OnOff);
        }
        // Return true to accept the value and ACK to the server
        return true;
    };
    
    led.id = 0; // set instance id
    lights.addInstance(CTX(context), &led);
    lights.registerObject(CTX(context));
}

void push_button_pressed(bool newState) {
    led.OnOff = newState;
    digitalWrite(LED_BUILTIN, led.OnOff);
    lights.resChanged(CTX(context), led.id, (uint16_t)id3311::RESID::OnOff);
}
```

## List of supported objects

<style>
#lwm2mObjects tr:nth-child(even){background-color: #f2f2f2;}

#lwm2mObjects tr:hover {background-color: #ddd;}

#lwm2mObjects th {
    padding-top: 12px;
    padding-bottom: 12px;
    text-align: left;
    background-color: #ef5350;
    color: white;
}
  </style>
<table id="lwm2mObjects">
   <thead>
      <tr>
         <th style="text-align:center">Object ID</th>
         <th style="text-align:left">Name</th>
         <th style="text-align:left">Description</th>
      </tr>
   </thead>
   <tbody>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/LWM2M_Server-v1_0.xml"
               title="urn:oma:lwm2m:oma:1">1</a>
         </td>
         <td>LWM2M Server</td>
         <td>It provides the data related to a LWM2M Server. A Bootstrap Server has no such an Object Instance associated to it.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/LWM2M_Access_Control-v1_0_1.xml"
               title="urn:oma:lwm2m:oma:2">2</a>
         </td>
         <td>Access Control</td>
         <td>It is used to check whether the LWM2M Server has access right for performing a operation.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/LWM2M_Device-v1_0_1.xml"
               title="urn:oma:lwm2m:oma:3">3</a>
         </td>
         <td>Device</td>
         <td>It provides a range of device related information which can be queried by the LWM2M Server, and a device reboot and factory reset function.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/LWM2M_Connectivity_Monitoring-v1_0_1.xml"
               title="urn:oma:lwm2m:oma:4">4</a>
         </td>
         <td>Connectivity Monitoring</td>
         <td>It enables monitoring of parameters related to network connectivity. In this general connectivity Object, the Resources are limited to the most general cases common to most network bearers. It is recommended to read the description, which refers to relevant standard development organizations (e.g. 3GPP, IEEE). The goal of the Connectivity Monitoring Object is to carry information reflecting the more up to date values of the current connection for monitoring purposes. Resources such as Link Quality, Radio Signal Strenght, Cell ID are retrieved during connected mode at least for cellular networks.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/LWM2M_Firmware_Update-v1_0_1.xml"
               title="urn:oma:lwm2m:oma:5">5</a>
         </td>
         <td>Firmware</td>
         <td>It enables management of firmware which is to be updated. This Object includes installing firmware package, updating firmware, and performing actions after updating firmware</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/LWM2M_Location-v1_0.xml"
               title="urn:oma:lwm2m:oma:6">6</a>
         </td>
         <td>Location</td>
         <td>It provides a range of device related information which can be queried by the LWM2M Server, and a device reboot and factory reset function.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/LWM2M_Connectivity_Statistics-v1_0_1.xml"
               title="urn:oma:lwm2m:oma:7">7</a>
         </td>
         <td>Connectivity Statistics</td>
         <td>This LWM2M Objects enables client to collect statistical information and enables the LWM2M Server to retrieve these information, set the collection duration and reset the statistical parameters.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/LWM2M_LOCKWIPE-v1_0.xml"
               title="urn:oma:lwm2m:oma:8">8</a>
         </td>
         <td>Lock and Wipe</td>
         <td>This LWM2M objects provides the resources needed to perform the lock and wipe operations</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/LWM2M_Software_Management-v1_0.xml"
               title="urn:oma:lwm2m:oma:9">9</a>
         </td>
         <td>Sofware Management</td>
         <td>This LWM2M objects provides the resources needed to perform software management on the device. Each software component is managed via a dedicated Software Management Object instance</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/LWM2M_Cellular_connectivity-v1_0.xml"
               title="urn:oma:lwm2m:oma:10">10</a>
         </td>
         <td>Cellular connectivity</td>
         <td>It specifies resources to enable a device to connect to a 3GPP or 3GPP2 bearer, including GPRS/EDGE, UMTS, LTE, SMS. For cellular connectivity, this object focuses on Packet Switched (PS) connectivity and doesn't aim to provide comprehensive Circuit Switched (CS) connectivity management.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/LWM2M_APN_connection_profile-v1_0.xml"
               title="urn:oma:lwm2m:oma:11">11</a>
         </td>
         <td>APN connection profile</td>
         <td>It specifies resources to enable a device to connect to an APN.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/LWM2M_WLAN_connectivity4-v1_0.xml"
               title="urn:oma:lwm2m:oma:12">12</a>
         </td>
         <td>WLAN connectivity</td>
         <td>It specifies resources to enable a device to connect to a WLAN bearer.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/LWM2M_Bearer_selection-v1_0.xml"
               title="urn:oma:lwm2m:oma:13">13</a>
         </td>
         <td>Bearer selection</td>
         <td>It specifies resources to enable a device to choose a communications bearer on which to connect.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/LWM2M_Software_Component-v1_0.xml"
               title="urn:oma:lwm2m:oma:14">14</a>
         </td>
         <td>Software Component</td>
         <td>The LWM2M software management object enables remote software management in M2M devices</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/LWM2M_DevCapMgmt-v1_0.xml"
               title="urn:oma:lwm2m:oma:15">15</a>
         </td>
         <td>DevCapMgmt</td>
         <td>It manages the device capabilities of a device e.g. sensors, communication, etc.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/LWM2M_Portfolio-v1_0.xml"
               title="urn:oma:lwm2m:oma:16">16</a>
         </td>
         <td>Porfolio</td>
         <td>The Portfolio Object allows to extend the data storage capability of other Object Instances in the LwM2M system, as well as the services which may be used to authenticate and to protect privacy of data contained in those extensions. In addition, a service of data encryption is also defined</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/Communication_Characteristics-V1_0.xml"
               title="urn:oma:lwm2m:oma:17">17</a>
         </td>
         <td>Communications Characteristics</td>
         <td>This object enables configuration of various generic communications parameters.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/Non-Access_Stratum_NAS_configuration-V1_0.xml"
               title="urn:oma:lwm2m:oma:18">18</a>
         </td>
         <td>Non-Access Stratum (NAS) Configuration</td>
         <td>This object provides Non-Access Stratum (NAS) configuration and is derived from 3GPP TS 24.368.</td>
      </tr>
      <tr>
         <td>
            <a href="" title="urn:oma:lwm2m:oma:19">19</a>
         </td>
         <td>LwM2M APPDATA</td>
         <td>This LwM2M object provides the application service data related to a LwM2M Server, eg. Water meter data.</td>
      </tr>
      <tr>
         <td>
            <a href="" title="urn:oma:lwm2m:oma:20">20</a>
         </td>
         <td>EventLog</td>
         <td>The Event Log Object is a single Instance Object defined for logging data in a straightforward         and generic way. The Resources of that Object are based on the OMA LwM2M set of reusable Resources dedicated to logging event activity.</td>
      </tr>
      <tr>
         <td>
            <a href="" title="urn:oma:lwm2m:oma:21">21</a>
         </td>
         <td>Pending</td>
         <td>Pending</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/2048.xml"
               title="urn:oma:lwm2m:ext:2048">2048</a>
         </td>
         <td>CmdhPolicy</td>
         <td>This Object provides links to a set of rules associated with a specific CSE that governs the behavior             of that CSE regarding rejecting, buffering and sending request or response messages via the Mcc reference point.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/2049.xml"
               title="urn:oma:lwm2m:ext:2049">2049</a>
         </td>
         <td>ActiveCmdhPolicy</td>
         <td>This Object provides a link to the currently active set of CMDH policies</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/2050.xml"
               title="urn:oma:lwm2m:ext:2050">2050</a>
         </td>
         <td>CmdhDefaults</td>
         <td>Defines which CMDH related parameters will be used by default.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/2051.xml"
               title="urn:oma:lwm2m:ext:2051">2051</a>
         </td>
         <td>CmdhDefEcValues</td>
         <td>This Object represents default set of values for the Event Category parameter of an incoming request or response message.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/2052.xml"
               title="urn:oma:lwm2m:ext:2052">2052</a>
         </td>
         <td>CmdhEcDefParamValues</td>
         <td>This Object represents a specific set of default values for the CMDH related parameters Request Expiration Timestamp, Result Expiration Timestamp, Operational Execution Time, Result Persistence and Delivery Aggregation that are applicable for a given Event Category if these parameters are not specified in the message.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/2053.xml"
               title="urn:oma:lwm2m:ext:2053">2053</a>
         </td>
         <td>CmdhLimits</td>
         <td>This Object represents limits for CMDH related parameter values.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/2054.xml"
               title="urn:oma:lwm2m:ext:2054">2054</a>
         </td>
         <td>CmdhNetworkAccessRules</td>
         <td>This Object defines the usage of underlying networks for forwarding information to other CSEs during processing of CMDH-related requests in a CSE.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/2055.xml"
               title="urn:oma:lwm2m:ext:2055">2055</a>
         </td>
         <td>CmdhNwAccessRule</td>
         <td>This Object defines limits in usage of specific underlying networks for forwarding information to other CSEs during processing of CMDH-related requests in a CSE.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/2056.xml"
               title="urn:oma:lwm2m:ext:2056">2056</a>
         </td>
         <td>CmdhBuffer</td>
         <td>This Object defines limits in usage of buffers for temporarily storing information that needs to be forwarded to other CSEs during processing of CMDH-related requests in a CSE.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/2057.xml"
               title="urn:oma:lwm2m:ext:2057">2057</a>
         </td>
         <td>CmdhBackOffParametersSet</td>
         <td>This Object defines set of parameters which can be referenced by a specific Instance of the CmdhNwAccessRule Object (ID: 2055)</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3200.xml"
               title="urn:oma:lwm2m:ext:3200">3200</a>
         </td>
         <td>Digital Input</td>
         <td>This IPSO object is a generic object that can be used with any kind of digital input interface. Specific objects for a given range of sensors are described later in the document, enabling to identify the type of sensors directly from its Object ID. This object may be used as a generic object if a dedicated one does not exist.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3201.xml"
               title="urn:oma:lwm2m:ext:3201">3201</a>
         </td>
         <td>Digital Output</td>
         <td>This IPSO object is a generic object that can be used with any kind of digital output interface. Specific object for a given range of sensors is described later in the document, enabling to identify the type of sensors directly from its Object ID. This object may be used as a generic object if a dedicated one does not exist.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3202.xml"
               title="urn:oma:lwm2m:ext:3202">3202</a>
         </td>
         <td>Analogue Input</td>
         <td>This IPSO object is a generic object that can be used with any kind of analogue input interface. Specific object for a given range of sensors is described later in the document, enabling to identify the type of sensors directly from its Object ID. This object may be used as a generic object if a dedicated one does not exist.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3203.xml"
               title="urn:oma:lwm2m:ext:3203">3203</a>
         </td>
         <td>Analogue Output</td>
         <td>This IPSO object is a generic object that can be used with any kind of analogue input interface. Specific object for a given range of sensors is described later in the document, enabling to identify the type of sensors directly from its Object ID. This object may be used as a generic object if a dedicated one does not exist.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3300.xml"
               title="urn:oma:lwm2m:ext:3300">3300</a>
         </td>
         <td>Generic Sensor</td>
         <td>This IPSO object allow the description of a generic sensor. It is based on the description of a value and a unit according to the UCUM specification. Thus, any type of value defined within this specification can be reporting using this object. Specific object for a given range of sensors is described later in the document, enabling to identify the type of sensors directly from its Object ID. This object may be used as a generic object if a dedicated one does not exist.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3301.xml"
               title="urn:oma:lwm2m:ext:3301">3301</a>
         </td>
         <td>Illuminance Sensor</td>
         <td>This IPSO object should be used over a luminosity sensor to report a remote luminosity measurement. It also provides resources for minimum/maximum measured values and the minimum/maximum range that can be measured by the luminosity sensor. The unit used here is Lux (ucum:lx).</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3302.xml"
               title="urn:oma:lwm2m:ext:3302">3302</a>
         </td>
         <td>Presence Sensor</td>
         <td>This IPSO object should be used over a presence sensor to report a remote presence detection. It also provides resources to manage a counter, the type of sensor used (e.g the technology of the probe), and configuration for the delay between busy and clear detection state.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3303.xml"
               title="urn:oma:lwm2m:ext:3303">3303</a>
         </td>
         <td>Temperature Sensor</td>
         <td>This IPSO object should be used over a temperature sensor to report a remote temperature measurement. It also provides resources for minimum/maximum measured values and the minimum/maximum range that can be measured by the temperature sensor. The unit used here is degree Celsius (ucum:Cel).</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3304.xml"
               title="urn:oma:lwm2m:ext:3304">3304</a>
         </td>
         <td>Humidity Sensor</td>
         <td>This IPSO object should be used over a humidity sensor to report a remote humidity measurement. It also provides resources for minimum/maximum measured values and the minimum/maximum range that can be measured by the humidity sensor. The unit used here is relative humidity as a percentage (ucum:%).</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3305.xml"
               title="urn:oma:lwm2m:ext:3305">3305</a>
         </td>
         <td>Power Measurement</td>
         <td>This IPSO object should be used over a power measurement sensor to report a remote power measurement. It also provides resources for minimum/maximum measured values and the minimum/maximum range for both active and reactive power. Il also provides resources for cumulative energy, calibration, and the power factor.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3306.xml"
               title="urn:oma:lwm2m:ext:3306">3306</a>
         </td>
         <td>Actuation</td>
         <td>This IPSO object is dedicated to remote actuation such as ON/OFF action or dimming. A multistate output can also be described as a string. This is useful to send pilot wire orders for instance. It also provides a resource to reflect the time that the device has been switched on.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3308.xml"
               title="urn:oma:lwm2m:ext:3308">3308</a>
         </td>
         <td>Set Point</td>
         <td>This IPSO object should be used to set a desired value to a controller, such as a thermostat. This object enables a setpoint to be expressed units defined in the UCUM specification, to match an associated sensor or measurement value. A special resource is added to set the colour of an object.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3310.xml"
               title="urn:oma:lwm2m:ext:3310">3310</a>
         </td>
         <td>Load Control</td>
         <td>This Object is used for demand-response load control and other load control in automation application (not limited to power).</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3311.xml"
               title="urn:oma:lwm2m:ext:3311">3311</a>
         </td>
         <td>Light Control</td>
         <td>This Object is used to control a light source, such as a LED or other light. It allows a light to be turned on or off and its dimmer setting to be control as a % between 0 and 100.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3312.xml"
               title="urn:oma:lwm2m:ext:3312">3312</a>
         </td>
         <td>Power Control</td>
         <td>This Object is used to control a power source, such as a Smart Plug. It allows a power relay to be turned on or off and its dimmer setting to be control as a % between 0 and 100.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3313.xml"
               title="urn:oma:lwm2m:ext:3313">3313</a>
         </td>
         <td>Accelerometer</td>
         <td>This IPSO object can be used to represent a 1-3 axis accelerometer.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3314.xml"
               title="urn:oma:lwm2m:ext:3314">3314</a>
         </td>
         <td>Magnetometer</td>
         <td>This IPSO object can be used to represent a 1-3 axis magnetometer with optional compass direction.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3315.xml"
               title="urn:oma:lwm2m:ext:3315">3315</a>
         </td>
         <td>Barometer</td>
         <td>This IPSO object should be used with an air pressure sensor to report a remote barometer measurement. It also provides resources for minimum/maximum measured values and the minimum/maximum range that can be measured by the barometer sensor.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3316.xml"
               title="urn:oma:lwm2m:ext:3316">3316</a>
         </td>
         <td>Voltage</td>
         <td>This IPSO object should be used with voltmeter sensor to report measured voltage between two points. It also provides resources for minimum and maximum measured values, as well as the minimum and maximum range that can be measured by the sensor. An example measurement unit is volts (ucum: V).</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3317.xml"
               title="urn:oma:lwm2m:ext:3317">3317</a>
         </td>
         <td>Current</td>
         <td>This IPSO object should be used with an ammeter to report measured electric current in amperes. It also provides resources for minimum and maximum measured values, as well as the minimum and maximum range that can be measured by the sensor. An example measurement unit is volts (ucum: A).</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3318.xml"
               title="urn:oma:lwm2m:ext:3318">3318</a>
         </td>
         <td>Frequency</td>
         <td>This IPSO object should be used to report frequency measurements. It also provides resources for minimum and maximum measured values, as well as the minimum and maximum range that can be measured by the sensor. An example measurement unit is volts (ucum: Hz).</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3319.xml"
               title="urn:oma:lwm2m:ext:3319">3319</a>
         </td>
         <td>Depth</td>
         <td>This IPSO object should be used to report depth measurements. It can, for example, be used to describe a generic rain gauge that measures the accumulated rainfall in millimetres (mm) or in fathoms (fth).</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3320.xml"
               title="urn:oma:lwm2m:ext:3320">3320</a>
         </td>
         <td>Percentage</td>
         <td>This IPSO object should can be used to report measurements relative to a 0-100% scale. For example it could be used to measure the level of a liquid in a vessel or container in units of %.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3321.xml"
               title="urn:oma:lwm2m:ext:3321">3321</a>
         </td>
         <td>Altitude</td>
         <td>This IPSO object should be used with an altitude sensor to report altitude above sea level in meters. Note that Altitude can be calculated from the measured pressure given the local sea level pressure. It also provides resources for minimum and maximum measured values, as well as the minimum and maximum range that can be measured by the sensor. An example measurement unit is meters (ucum: m).</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3322.xml"
               title="urn:oma:lwm2m:ext:3322">3322</a>
         </td>
         <td>Load</td>
         <td>This IPSO object should be used with a load sensor (as in a scale) to report the applied weight or force. It also provides resources for minimum and maximum measured values, as well as the minimum and maximum range that can be measured by the sensor.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3323.xml"
               title="urn:oma:lwm2m:ext:3323">3323</a>
         </td>
         <td>Pressure</td>
         <td>This IPSO object should be used to report pressure measurements. It also provides resources for minimum and maximum measured values, as well as the minimum and maximum range that can be measured by the sensor.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3324.xml"
               title="urn:oma:lwm2m:ext:3324">3324</a>
         </td>
         <td>Loudness</td>
         <td>This IPSO object should be used to report loudness or noise level measurements. It also provides resources for minimum and maximum measured values, as well as the minimum and maximum range that can be measured by the sensor.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3325.xml"
               title="urn:oma:lwm2m:ext:3325">3325</a>
         </td>
         <td>Concentration</td>
         <td>This IPSO object should be used to the particle concentration measurement of a medium. It also provides resources for minimum and maximum measured values, as well as the minimum and maximum range that can be measured by the sensor.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3326.xml"
               title="urn:oma:lwm2m:ext:3326">3326</a>
         </td>
         <td>Acidity</td>
         <td>This IPSO object should be used to report an acidity measurement of a liquid. It also provides resources for minimum and maximum measured values, as well as the minimum and maximum range that can be measured by the sensor.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3327.xml"
               title="urn:oma:lwm2m:ext:3327">3327</a>
         </td>
         <td>Conductivity</td>
         <td>This IPSO object should be used to report a measurement of the electric conductivity of a medium or sample. It also provides resources for minimum and maximum measured values, as well as the minimum and maximum range that can be measured by the sensor.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3328.xml"
               title="urn:oma:lwm2m:ext:3328">3328</a>
         </td>
         <td>Power</td>
         <td>This IPSO object should be used to report power measurements. It also provides resources for minimum and maximum measured values, as well as the minimum and maximum range that can be measured by the sensor.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3329.xml"
               title="urn:oma:lwm2m:ext:3329">3329</a>
         </td>
         <td>Power Factor</td>
         <td>This IPSO object should be used to report a measurement or calculation of the power factor of a reactive electrical load.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3330.xml"
               title="urn:oma:lwm2m:ext:3330">3330</a>
         </td>
         <td>Distance</td>
         <td>This IPSO object should be used to report a distance measurement. It also provides resources for minimum and maximum measured values, as well as the minimum and maximum range that can be measured by the sensor.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3331.xml"
               title="urn:oma:lwm2m:ext:3331">3331</a>
         </td>
         <td>Energy</td>
         <td>This IPSO object should be used to report energy consumption (Cumulative Power) of an electrical load.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3332.xml"
               title="urn:oma:lwm2m:ext:3332">3332</a>
         </td>
         <td>Direction</td>
         <td>This IPSO object is used to report the direction indicated by a compass, wind vane, or other directional indicator. The units of measure is plane angle degrees (ucum:deg).</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3333.xml"
               title="urn:oma:lwm2m:ext:3333">3333</a>
         </td>
         <td>Time</td>
         <td>This IPSO object is used to report the current time in seconds since January 1, 1970 UTC. There is also a fractional time counter that has a range of less than one second.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3334.xml"
               title="urn:oma:lwm2m:ext:3334">3334</a>
         </td>
         <td>Gyrometer</td>
         <td>This IPSO Object is used to report the current reading of a gyrometer sensor in 3 axes. It provides tracking of the minimum and maximum angular rate in all 3 axes.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3335.xml"
               title="urn:oma:lwm2m:ext:3335">3335</a>
         </td>
         <td>Color</td>
         <td>This IPSO object should be used to report the measured value of a colour sensor in some colour space described by the units resource.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3336.xml"
               title="urn:oma:lwm2m:ext:3336">3336</a>
         </td>
         <td>GPS Location</td>
         <td>This IPSO object represents GPS coordinates. This object is compatible with the LWM2M management object for location, but uses reusable resources.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3337.xml"
               title="urn:oma:lwm2m:ext:3337">3337</a>
         </td>
         <td>Positioner</td>
         <td>This IPSO object should be used with a generic position actuator from 0 to 100%.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3338.xml"
               title="urn:oma:lwm2m:ext:3338">3338</a>
         </td>
         <td>Buzzer</td>
         <td>This IPSO object should be used to actuate an audible alarm such as a buzzer, beeper, or vibration alarm.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3339.xml"
               title="urn:oma:lwm2m:ext:3339">3339</a>
         </td>
         <td>Audio Clip</td>
         <td>This IPSO object should be used for a speaker that plays a pre-recorded audio clip or an audio output that is sent elsewhere.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3340.xml"
               title="urn:oma:lwm2m:ext:3340">3340</a>
         </td>
         <td>Timer</td>
         <td>This IPSO object is used to time events and actions, using patterns common to industrial timers. A POST to the trigger resource or On/Off input state change starts the timing operation, and the timer remaining time shows zero when the operation is complete.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3341.xml"
               title="urn:oma:lwm2m:ext:3341">3341</a>
         </td>
         <td>Addressable Text Display</td>
         <td>This IPSO object is used to send text to a text-only or text mode graphics display.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3342.xml"
               title="urn:oma:lwm2m:ext:3342">3342</a>
         </td>
         <td>On/Off Switch</td>
         <td>This IPSO object should be used with an On/Off switch to report the state of the switch.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3343.xml"
               title="urn:oma:lwm2m:ext:3343">3343</a>
         </td>
         <td>Lever Control</td>
         <td>This IPSO object should be used with a dimmer or level control to report the state of the control.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3344.xml"
               title="urn:oma:lwm2m:ext:3344">3344</a>
         </td>
         <td>Up/Down Control</td>
         <td>This IPSO object is used to report the state of an up/down control element like a pair of push buttons or a rotary encoder.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3345.xml"
               title="urn:oma:lwm2m:ext:3345">3345</a>
         </td>
         <td>Multiple Axis Joystick</td>
         <td>This IPSO object can be used to report the position of a shuttle or joystick control. A digital input is provided to report the state of an associated push button.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3346.xml"
               title="urn:oma:lwm2m:ext:3346">3346</a>
         </td>
         <td>Rate</td>
         <td>This object type should be used to report a rate measurement,</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3347.xml"
               title="urn:oma:lwm2m:ext:3347">3347</a>
         </td>
         <td>Push Button</td>
         <td>This IPSO object is used to report the state of a momentary action push button control and to count the number of times the control has been operated since the last observation.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3348.xml"
               title="urn:oma:lwm2m:ext:3348">3348</a>
         </td>
         <td>Multistate Selector</td>
         <td>This IPSO object is used to represent the state of a multistate selector switch with a number of fixed positions.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3349.xml"
               title="urn:oma:lwm2m:ext:3349">3349</a>
         </td>
         <td>Bitmap</td>
         <td>Summarize several digital inputs to one value by mapping each bit to a digital input.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3350.xml"
               title="urn:oma:lwm2m:ext:3350">3350</a>
         </td>
         <td>Stopwatch</td>
         <td>An ascending timer that counts how long time has passed since the timer was started after reset.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3351.xml"
               title="urn:oma:lwm2m:ext:3351">3351</a>
         </td>
         <td>powerupLog</td>
         <td>One time event sent by the device at power up.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3352.xml"
               title="urn:oma:lwm2m:ext:3352">3352</a>
         </td>
         <td>plmnSearchEvent</td>
         <td>List of all PLMNs found during the initial search/scan</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3353.xml"
               title="urn:oma:lwm2m:ext:3353">3353</a>
         </td>
         <td>scellID</td>
         <td>serving cell information that the RRC decides to camp on</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3354.xml"
               title="urn:oma:lwm2m:ext:3354">3354</a>
         </td>
         <td>cellReselectionEvent</td>
         <td>cell reselection event information</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3355.xml"
               title="urn:oma:lwm2m:ext:3355">3355</a>
         </td>
         <td>handoverEvent</td>
         <td>handover event information</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3356.xml"
               title="urn:oma:lwm2m:ext:3356">3356</a>
         </td>
         <td>radioLinkFailureEvent</td>
         <td>Radio Link Failure Event</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3357.xml"
               title="urn:oma:lwm2m:ext:3357">3357</a>
         </td>
         <td>rrcStateChangeEvent</td>
         <td>Current RRC state change information, including the event that triggered the state change</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3358.xml"
               title="urn:oma:lwm2m:ext:3358">3358</a>
         </td>
         <td>rrcTimerExpiryEvent</td>
         <td>RRC timer expiry event information</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3359.xml"
               title="urn:oma:lwm2m:ext:3359">3359</a>
         </td>
         <td>cellBlacklistEvent</td>
         <td>Cell blacklist information</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3360.xml"
               title="urn:oma:lwm2m:ext:3360">3360</a>
         </td>
         <td>esmContextInfo</td>
         <td>ESM context information</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3361.xml"
               title="urn:oma:lwm2m:ext:3361">3361</a>
         </td>
         <td>emmStateValue</td>
         <td>EMM context information</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3362.xml"
               title="urn:oma:lwm2m:ext:3362">3362</a>
         </td>
         <td>nasEmmTimerExpiryEvent</td>
         <td>NAS EMM timer expiry information</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3363.xml"
               title="urn:oma:lwm2m:ext:3363">3363</a>
         </td>
         <td>nasEsmExpiryEvent</td>
         <td>NAS ESM timer expiry information</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3364.xml"
               title="urn:oma:lwm2m:ext:3364">3364</a>
         </td>
         <td>emmFailureCauseEvent</td>
         <td>Triggered at EMM failure - failure cause is logged</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3365.xml"
               title="urn:oma:lwm2m:ext:3365">3365</a>
         </td>
         <td>rachLatency_delay</td>
         <td>RACH Latency and delay information</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3366.xml"
               title="urn:oma:lwm2m:ext:3366">3366</a>
         </td>
         <td>macRachAttemptEvent</td>
         <td>RACH information. Logged at RACH TX</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3367.xml"
               title="urn:oma:lwm2m:ext:3367">3367</a>
         </td>
         <td>macRachAttemptReasonEvent</td>
         <td>RACH Information - reason for initiating RACH</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3368.xml"
               title="urn:oma:lwm2m:ext:3368">3368</a>
         </td>
         <td>macTimerStatusEvent</td>
         <td>MAC timer expiry information</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3369.xml"
               title="urn:oma:lwm2m:ext:3369">3369</a>
         </td>
         <td>macTimingAdvanceEvent</td>
         <td>Timing advance information</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3370.xml"
               title="urn:oma:lwm2m:ext:3370">3370</a>
         </td>
         <td>ServingCellMeasurement</td>
         <td>Serving Cell Measurement</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3371.xml"
               title="urn:oma:lwm2m:ext:3371">3371</a>
         </td>
         <td>NeighborCellMeasurements</td>
         <td>Neighbor Cell Measurements</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3372.xml"
               title="urn:oma:lwm2m:ext:3372">3372</a>
         </td>
         <td>Timing Advance Information</td>
         <td>Neighbor Cell Measurements</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3373.xml"
               title="urn:oma:lwm2m:ext:3373">3373</a>
         </td>
         <td>txPowerHeadroomEvent</td>
         <td>TX power headroom information</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3374.xml"
               title="urn:oma:lwm2m:ext:3374">3374</a>
         </td>
         <td>radioLinkMonitoring</td>
         <td>Radio Link monitoring information maintained by RRC</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3375.xml"
               title="urn:oma:lwm2m:ext:3375">3375</a>
         </td>
         <td>PagingDRX</td>
         <td>Paging DRX information</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3376.xml"
               title="urn:oma:lwm2m:ext:3376">3376</a>
         </td>
         <td>txPowerBackOffEvent</td>
         <td>TX Power backoff information</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3377.xml"
               title="urn:oma:lwm2m:ext:3377">3377</a>
         </td>
         <td>Message3Report</td>
         <td>RACH message 3 report information</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3378.xml"
               title="urn:oma:lwm2m:ext:3378">3378</a>
         </td>
         <td>PbchDecodingResults</td>
         <td>Serving cell PBCH decoding information</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3379.xml"
               title="urn:oma:lwm2m:ext:3379">3379</a>
         </td>
         <td>pucchPowerControl</td>
         <td>PUCCH TX power control information</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3380.xml"
               title="urn:oma:lwm2m:ext:3380">3380</a>
         </td>
         <td>PrachReport</td>
         <td>PRACH report information</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3381.xml"
               title="urn:oma:lwm2m:ext:3381">3381</a>
         </td>
         <td>VolteCallEvent</td>
         <td>VoLTE call status</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3382.xml"
               title="urn:oma:lwm2m:ext:3382">3382</a>
         </td>
         <td>SipRegistrationEvent</td>
         <td>SIP Registration status</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3383.xml"
               title="urn:oma:lwm2m:ext:3383">3383</a>
         </td>
         <td>sipPublishEvent</td>
         <td>SIP Publish status</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3384.xml"
               title="urn:oma:lwm2m:ext:3384">3384</a>
         </td>
         <td>sipSubscriptionEvent</td>
         <td>SIP Subscription status</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3385.xml"
               title="urn:oma:lwm2m:ext:3385">3385</a>
         </td>
         <td>volteCallStateChangeEvent</td>
         <td>VoLTE call status change</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3386.xml"
               title="urn:oma:lwm2m:ext:3386">3386</a>
         </td>
         <td>VoLTErtpPacketLoss</td>
         <td>Log is generated at the receiving end of RTP flow when newReceivedSequenceNumber - lastReceivedSequenceNumber &gt; 1</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10241.xml"
               title="urn:oma:lwm2m:x:10241">10241</a>
         </td>
         <td>HostDeviceInfo</td>
         <td>This LWM2M Object provides a range of host device related information which can be queried by the LWM2M Server. The host device is any integrated device with an embedded cellular radio module.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10242.xml"
               title="urn:oma:lwm2m:x:10242">10242</a>
         </td>
         <td>3-PhasePM</td>
         <td>This Object provides the information to represent a generic 3-Phase Power Meter</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10243.xml"
               title="urn:oma:lwm2m:x:10243">10243</a>
         </td>
         <td>singlePhasePM</td>
         <td>This Object provides the information to represent a generic Single-Phase Power Meter</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10244.xml"
               title="urn:oma:lwm2m:x:10244">10244</a>
         </td>
         <td>vehicle control unit</td>
         <td>This Object provides the information to represent a generic VCU (vehicle control unit)</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10245.xml"
               title="urn:oma:lwm2m:x:10245">10245</a>
         </td>
         <td>Relay Management</td>
         <td>This LWM2M Object provides a range of eNB related measurements and parameters of which several are changeable. Furthermore, it includes Resources to enable/disable the eNB</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10246.xml"
               title="urn:oma:lwm2m:x:10246">10246</a>
         </td>
         <td>CrowdBox Measurements</td>
         <td>This LWM2M Object provides CrowdBox-related measurements such as serving cell parameters, backhaul timing advance, and neighbour cell reports.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10247.xml"
               title="urn:oma:lwm2m:x:10247">10247</a>
         </td>
         <td>Neighbour Cell Report</td>
         <td>This LWM2M Object provides the neighbour cell report. The CrowdBox Measurements Object and the Connected UE Report Object have both Objlnk Resources pointing to this Object</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10248.xml"
               title="urn:oma:lwm2m:x:10248">10248</a>
         </td>
         <td>Connected UE Measurements</td>
         <td>This LWM2M Object provides a range of measurements of connected UEs and provides an Object link to the Connected UE report.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10249.xml"
               title="urn:oma:lwm2m:x:10249">10249</a>
         </td>
         <td>	Connected UE Report</td>
         <td>This LWM2M Object provides a range of information related to the connected UEs.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10250.xml"
               title="urn:oma:lwm2m:x:10250">10250</a>
         </td>
         <td>App Data Container</td>
         <td>This LWM2M Object is used for reporting application data of a device.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10251.xml"
               title="urn:oma:lwm2m:x:10251">10251</a>
         </td>
         <td>AT Command</td>
         <td>Used to execute an AT command on a cellular modem</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10252.xml"
               title="urn:oma:lwm2m:x:10252">10252</a>
         </td>
         <td>Manifest</td>
         <td>This object provides a range of information related to updating packages on a device</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10253.xml"
               title="urn:oma:lwm2m:x:10253">10253</a>
         </td>
         <td>Confidential Data</td>
         <td>This LWM2M Object is used for reporting data, but in a confidential way</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10254.xml"
               title="urn:oma:lwm2m:x:10254">10254</a>
         </td>
         <td>Current Loop Input</td>
         <td>This LwM2M Object provides a representation of a current loop sensor, which indicates the value emitted by a current source.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10255.xml"
               title="urn:oma:lwm2m:x:10255">10255</a>
         </td>
         <td>Device Metadata</td>
         <td>This object provides a range of information related to device metadata</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10256.xml"
               title="urn:oma:lwm2m:x:10256">10256</a>
         </td>
         <td>ECID-Signal Measurement Information</td>
         <td>This LWM2M Object provides ECID signal measurements of a device.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10257.xml"
               title="urn:oma:lwm2m:x:10257">10257</a>
         </td>
         <td>Heat/Cooling meter</td>
         <td>This Object provides the information to represent a generic (district) heat or cooling meter</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10258.xml"
               title="urn:oma:lwm2m:x:10258">10258</a>
         </td>
         <td>Current Loop Output</td>
         <td>This LWM2M Object provides a representation of a current loop source, which may be used to carry control signals.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10259.xml"
               title="urn:oma:lwm2m:x:10259">10259</a>
         </td>
         <td>System Log</td>
         <td>This object provides read access to log buffers as well as limited configuration of logging services.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10260.xml"
               title="urn:oma:lwm2m:x:10260">10260</a>
         </td>
         <td>Runtime Database</td>
         <td>This object allows manipulation of Runtime Database variables.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10260-2_0.xml"
               title="urn:oma:lwm2m:x:10260:2.0">10260</a>
         </td>
         <td>Runtime Database</td>
         <td>This object allows manipulation of Runtime Database variables.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10262.xml"
               title="urn:oma:lwm2m:x:10262">10262</a>
         </td>
         <td>Interval Data Delivery</td>
         <td>The Interval Data Delivery object provides an optimised means for managing the delivery of interval data from multiple Interval Data Object instances. </td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10263.xml"
               title="urn:oma:lwm2m:x:10263">10263</a>
         </td>
         <td>Event Data Delivery</td>
         <td>The Event Data Delivery object provides a simple means for managing the delivery of event data from multiple Event Data Object instances.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10264.xml"
               title="urn:oma:lwm2m:x:10264">10264</a>
         </td>
         <td>Delivery Schedule</td>
         <td>The Delivery Schedule object provides a means for controlling the periodic delivery of interval and event data to the LwM2M server.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10265.xml"
               title="urn:oma:lwm2m:x:10265">10265</a>
         </td>
         <td>Leakage Detection Configuration</td>
         <td>The leakage detection configuration object provides a means for configuring the timing and sampling frequency of a vibration based network leak detector</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10266.xml"
               title="urn:oma:lwm2m:x:10266">10266</a>
         </td>
         <td>Water Flow Readings</td>
         <td>Measures the flow of water in regular intervals</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10267.xml"
               title="urn:oma:lwm2m:x:10267">10267</a>
         </td>
         <td>Daily Maximum Flow Rate Readings</td>
         <td>Measures the maximum flow rate and its time stamp for specified period</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10268.xml"
               title="urn:oma:lwm2m:x:10268">10268</a>
         </td>
         <td>Temperature Readings</td>
         <td>Periodic temperature measurements</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10269.xml"
               title="urn:oma:lwm2m:x:10269">10269</a>
         </td>
         <td>Pressure Readings</td>
         <td>Periodic pressure measurements</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10270.xml"
               title="urn:oma:lwm2m:x:10270">10270</a>
         </td>
         <td>Battery Level Readings</td>
         <td>Periodic battery level measurements</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10271.xml"
               title="urn:oma:lwm2m:x:10271">10271</a>
         </td>
         <td>Communications Activity Time Readings</td>
         <td>Measures the total duration that the meter was activating its radio for packet transmission or receipt for the period. Used to monitor for excess poower usage over time.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10272.xml"
               title="urn:oma:lwm2m:x:10272">10272</a>
         </td>
         <td>Water Meter Customer Leakage Alarm</td>
         <td>A binary flag indicating continual usage (e.g. greater than 5 L/h for 24 hours and the flow never returning to zero at any time).</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10273.xml"
               title="urn:oma:lwm2m:x:10273">10273</a>
         </td>
         <td>Water Meter Reverse Flow Alarm</td>
         <td>An alarm indicating reverse flow through the pipe. Also supports delivery of the approximate volume of water flowing in the reverse direction in the preceding period.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10274.xml"
               title="urn:oma:lwm2m:x:10274">10274</a>
         </td>
         <td>Water Meter Empty Pipe Alarm</td>
         <td>An alarm when meter detects there is no liquid in the pipe</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10275.xml"
               title="urn:oma:lwm2m:x:10275">10275</a>
         </td>
         <td>Water Meter Tamper Alarm</td>
         <td>            Detects interference from strong magnetic field or other electrical sources. If this is not relevant for            ultrasonic meters then the tamper alarm may be used to            indicate someone attempting to open the physical enclosure or other options the manufacturer may present.        </td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10276.xml"
               title="urn:oma:lwm2m:x:10276">10276</a>
         </td>
         <td>Water Meter High Pressure Alarm</td>
         <td>Where supported by the meter this is an alarm that should be raised if the meter detects pressure above a pre-configured threshold.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10277.xml"
               title="urn:oma:lwm2m:x:10277">10277</a>
         </td>
         <td>Water Meter Low Pressure Alarm</td>
         <td>Where supported by the meter this is an alarm that should be raised if the meter detects pressure below a pre-configured threshold.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10278.xml"
               title="urn:oma:lwm2m:x:10278">10278</a>
         </td>
         <td>High Temperature Alarm</td>
         <td>            Where supported by the meter this is an alarm that should be raised if the meter detects temperature above a pre-configured threshold.            When the temperature drops below the clear threshold, the alarm should be cleared.        </td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10279.xml"
               title="urn:oma:lwm2m:x:10279">10279</a>
         </td>
         <td>Low Temperature Alarm</td>
         <td>            Where supported by the meter this is an alarm that should be raised if the meter detects temperature below a pre-configured threshold.            When the temperature rises above the clear threshold, the alarm should be cleared        </td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10280.xml"
               title="urn:oma:lwm2m:x:10280">10280</a>
         </td>
         <td>Water Network Leak Alarm</td>
         <td>All meters must support the following default configuration. This alarm will be based on the frequency output of the vibration sensor/accelerometer on the SEW Daughter board. When a frequency is identified that has the characteristics of an upstream network leak, and its amplitude is above the defined threshold, the meter will report this as a network leak alarm.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10281.xml"
               title="urn:oma:lwm2m:x:10281">10281</a>
         </td>
         <td>Low Battery Alarm </td>
         <td>This Alarm is raised when the battery voltage drops below a defined level</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10282.xml"
               title="urn:oma:lwm2m:x:10282">10282</a>
         </td>
         <td>Daughter Board Failure Alarm</td>
         <td>This binary status should indicate that the meter MCU can no longer communicate with a daughter board</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10283.xml"
               title="urn:oma:lwm2m:x:10283">10283</a>
         </td>
         <td>Device Reboot Event</td>
         <td>This binary status should indicate that the meter MCU can no longer communicate with a daughter board</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10284.xml"
               title="urn:oma:lwm2m:x:10284">10284</a>
         </td>
         <td>Time Synchronisation Event</td>
         <td>This event records the fact that the device has rebooted</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10286.xml"
               title="urn:oma:lwm2m:x:10286">10286</a>
         </td>
         <td>App Fota Container</td>
         <td>This LWM2M Object is used to download the firmware package of a device's application.</td>
      </tr>
      <tr>
         <td>
            <a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/10299.xml"
               title="urn:oma:lwm2m:x:10299">10299</a>
         </td>
         <td>HostDevice</td>
         <td>This LWM2M Object provides a range of host device related information which can be queried by the LWM2M Server. The host device is any integrated device with an embedded cellular radio module.</td>
      </tr>
      <tr>
         <td>
            <a href="" title="urn:oma:lwm2m:x:10300">10300</a>
         </td>
         <td>Pending</td>
         <td>Pending</td>
      </tr>
   </tbody>
</table>

This list is generated by the `generate_cpp_objects_from_registry` tool in [<img src="../../assets/github.png" style="width:20px"> generate_cpp_objects_from_registry/](https://github.com/Openhab-Nodes/wakaamaNode/blob/master/generate_cpp_objects_from_registry).
