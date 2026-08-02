#ifndef CAN_H
#define CAN_H

#include "types.h"

/*--------------------------------------------------------------
 * CAN Frame Structure
 *-------------------------------------------------------------*/

typedef struct
{
    uint16 id;
    uint8  dlc;
    uint8  data[8];

} Can_FrameType;

/*--------------------------------------------------------------
 * CAN Driver APIs
 *-------------------------------------------------------------*/

Std_ReturnType Can_Init(void);

Std_ReturnType Can_SendFrame(const Can_FrameType *frame);

Std_ReturnType Can_ReceiveFrame(Can_FrameType *frame);

#endif /* CAN_H */