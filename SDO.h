#ifndef SDO_H
#define SDO_H

#include <stdint.h>	//  for uint16_t

typedef enum  {SENDINTR,SPARE1} sdo_type;

typedef struct SDOStruct {
        sdo_type SelSDO;   	//SENDINTR
        uint16_t TargetID;  // TILT_ID
        char pCmd[3] ;    	// KP
        uint16_t Index;   	// 1
        int32_t Value;    	// 1000
} SDO;

typedef const SDO	*SDOptr_t ;

#endif // SDO_H
