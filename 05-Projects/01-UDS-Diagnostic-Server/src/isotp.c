#include "isotp.h"
#include  "can_if.h"
#include <stddef.h>

Std_ReturnType IsoTp_Transmit(uint16 can_id , const uint8 *data , uint16 length ){
    if (data == NULL){
        return E_NOT_OK;
    }
    if (length==0 || length>7){
        return E_NOT_OK;
    }
    Can_FrameType frame ={0};
    frame.id = can_id;
    frame.dlc =length+1;
    frame.data[0]=length & 0x0F;
    for (uint16 i=0;i<length;i++){
        frame.data[i+1]=data[i];
    }

    return CanIf_Transmit(&frame);
}