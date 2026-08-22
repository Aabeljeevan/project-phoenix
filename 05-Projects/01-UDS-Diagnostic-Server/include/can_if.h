#ifndef CAN_IF_H
#define CAN_IF_H

#include "can.h"

/*--------------------------------------------------------------
 * CAN Interface APIs
 *-------------------------------------------------------------*/

Std_ReturnType CanIf_Transmit(const Can_FrameType *frame);

Std_ReturnType CanIf_Receive(Can_FrameType *frame);

#endif /* CAN_IF_H */