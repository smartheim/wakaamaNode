#pragma once
// Automatically generated header file

#include "lwm2m_objects.hpp"
namespace KnownObjects {
namespace id3378 {
/* \brief Class for object 3378 - PbchDecodingResults
 *  Serving cell PBCH decoding information
 */
class instance : public Lwm2mObjectInstance {
public:

    // 0 - Serving Cell ID
    int servingCellID;
    
    // 1 - fail=0pass=1
    bool crcResult;
    
    // 6037 - system frame number when pbch was decoded
    int sysFrameNumber;
    
    enum class RESID {
        servingCellID = 0,
        crcResult = 1,
        sysFrameNumber = 6037,
        
    };
};

/* \brief Class for object 3378 - PbchDecodingResults
 *  Serving cell PBCH decoding information
 */
class object : public Lwm2mObject<3378, object, instance> {
public:

    // 0 - Serving Cell ID
    Resource(0, &instance::servingCellID, O_RES_R) servingCellID;
    
    // 1 - fail=0pass=1
    Resource(1, &instance::crcResult, O_RES_R) crcResult;
    
    // 6037 - system frame number when pbch was decoded
    Resource(6037, &instance::sysFrameNumber, O_RES_R) sysFrameNumber;
    
};

} // end of id namespace
inline bool operator== (id3378::instance::RESID c1, uint16_t c2) { return (uint16_t) c1 == c2; }
inline bool operator== (uint16_t c2, id3378::instance::RESID c1) { return (uint16_t) c1 == c2; }

} // end of KnownObjects namespace
	