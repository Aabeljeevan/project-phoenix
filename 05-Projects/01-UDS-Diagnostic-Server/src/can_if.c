#include "can_if.h"
#include <stddef.h>
/*--------------------------------------------------------------
 * CAN Interface Transmission
 *-------------------------------------------------------------*/

Std_ReturnType CanIf_Transmit(const Can_FrameType *frame)
{
    if (frame == NULL)
    {
        return E_NOT_OK;
    }

    return Can_SendFrame(frame);
}

/*--------------------------------------------------------------
 * CAN Interface Reception
 *-------------------------------------------------------------*/

Std_ReturnType CanIf_Receive(Can_FrameType *frame)
{
    if (frame == NULL)
    {
        return E_NOT_OK;
    }

    return Can_ReceiveFrame(frame);
}