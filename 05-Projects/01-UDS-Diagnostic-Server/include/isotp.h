#ifndef ISOTP_H
#define ISOTP_H

#include "types.h"

Std_ReturnType IsoTp_Transmit(uint16 can_id,const uint8 *data,uint16 length);

#endif