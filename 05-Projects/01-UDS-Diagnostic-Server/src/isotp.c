#include "isotp.h"
#include  "can_if.h"
#include <stddef.h>

Std_ReturnType IsoTp_Transmit(uint16 can_id , const uint8 *data , uint16 length ){
    if (data == NULL){
        return E_NOT_OK;
    }
    if (length==0){
        return E_NOT_OK;
    }
    if (length>0x0FFF){
        return E_NOT_OK;
    }
    if (length<=7){
        Can_FrameType frame ={0};
        frame.id = can_id;
        frame.dlc =length+1;
        frame.data[0]=length & 0x0F;
        for (uint16 i=0;i<length;i++){
            frame.data[i+1]=data[i];
        }
        return CanIf_Transmit(&frame);
                                        //single frame
    }
    else{
        Can_FrameType frame={0};
        frame.id=can_id;
        frame.dlc=8;
        frame.data[0]=0x10 |((length>>8)&0x0F);
        frame.data[1]=length& 0xFF;
        for(uint16 i=0;i<6;i++){
            frame.data[i+2]=data[i];
        }
        // return CanIf_Transmit(&frame);
        Std_ReturnType status;
        status =CanIf_Transmit(&frame);
        if (status != E_OK){
            return E_NOT_OK;
        }
        Can_FrameType fcframe={0};
        status=CanIf_Receive(&fcframe);
        if (status !=E_OK){
            return E_NOT_OK;
        }
        uint8 frame_type;
        frame_type=(fcframe.data[0]>>4)&0x0F;
        if (frame_type !=3){
            return E_NOT_OK;
        }
        uint8 flowstatus;
        flowstatus=(fcframe.data[0]&0xF);
        if (flowstatus==0){
            uint16 offset=6;
            uint8 sequence_number=1;
            while(offset<length){
                Can_FrameType cfframe={0};
                cfframe.id=can_id;
                cfframe.dlc=8;
                cfframe.data[0]=0x20|(sequence_number&0x0F);
                uint16 remaining=length-offset;
                uint8 bytes_to_copy;
                if (remaining>7){
                    bytes_to_copy=7;
                }
                else{
                    bytes_to_copy=remaining;
                }
                for(uint8 i=0;i<bytes_to_copy;i++){
                    cfframe.data[i+1]=data[offset+i];
                }
                status=CanIf_Transmit(&cfframe);
                if (status != E_OK){
                    return E_NOT_OK;
                }
                offset=offset+bytes_to_copy;
                sequence_number++;
            }
            //continue to send
        }
        else if(flowstatus==1 ){
            //wait
        }
        else if (flowstatus ==2){
            //overflow
        }
        else{
            return E_NOT_OK;
        }


    return E_OK;
        //multiple frane
    }
   

}