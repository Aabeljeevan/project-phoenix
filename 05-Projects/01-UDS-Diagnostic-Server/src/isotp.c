#include "isotp.h"
#include  "can_if.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>


static Std_ReturnType IsoTp_ReceiveFlowControl(uint8 *block_size,uint8 *flow_status,uint8 *STmin){
    Can_FrameType fcframe={0};
    Std_ReturnType status =CanIf_Receive(&fcframe);
    if (status !=E_OK){
        return E_NOT_OK;
    }
    if (fcframe.dlc <3){
        return E_NOT_OK;
    }
    if (((fcframe.data[0]>>4)&0x0F) !=3){
        return E_NOT_OK;
    }
    *flow_status =fcframe.data[0]&0x0F;
    // if (flow_status !=0){
    //     return E_NOT_OK;
    // }
    *block_size =fcframe.data[1];
    *STmin =fcframe.data[2];
    printf("\nFC recieved : BS =%d, Stmin =%d\n",fcframe.data[1],fcframe.data[2]);
    return E_OK;
} 


static void IsoTP_DelayUS(uint32 microseconds){
    usleep(microseconds);
}

static Std_ReturnType IsoTP_GetSTminDelay(uint8 Stmin,uint32 *delay_us){
    if (delay_us==NULL){
        return E_NOT_OK;
    }
    if(Stmin<=0x7F){
        *delay_us=(uint32)Stmin*1000U;
        return E_OK;
    }
    if (Stmin>=0xF1 && Stmin<=0xF9){
        *delay_us=(uint32)(Stmin-0xF0)*1000U;
        return E_OK;
    }
    return E_NOT_OK;
}

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
        // Can_FrameType fcframe={0};
        // status=CanIf_Receive(&fcframe);
        // if (status !=E_OK){
        //     return E_NOT_OK;
        // }
        // uint8 frame_type;
        // status=CanIf_Receive(&fcframe);
        // if (status !=E_OK){
        //     return E_NOT_OK;
        // }
        // if (fcframe.dlc<3){
        //     return E_NOT_OK;
        // }
        // frame_type=(fcframe.data[0]>>4)&0x0F;
        // if (frame_type !=3){
        //     return E_NOT_OK;
        // }
        // uint8 flowstatus;
        // flowstatus=(fcframe.data[0]&0xF);
        uint8 block_size=0;
        uint8 flow_status=0;
        uint8 wait_count=0;
        uint8 STmin=0;
        while (1)
        {
            status = IsoTp_ReceiveFlowControl(&block_size,&flow_status,&STmin);
            if (status != E_OK){
                return E_NOT_OK;
            }
            if(flow_status==0){
                /*CTS recievied -continue transmission*/
                break;
            }
            else if (flow_status==1){
                /*wait condition*/
                wait_count++;
                if (wait_count>=3){
                    return E_NOT_OK;
                }
            } 
            else if (flow_status==2){
                return E_NOT_OK;/*  overflow*/
            }
            else {
                return E_NOT_OK;
            }     
        }
        printf("\n Flow status = %d\n ",flow_status);
        if (flow_status !=0){
            return E_NOT_OK;
        }
        // if (flowstatus==0){
            uint16 offset=6;
            uint8 sequence_number=1;
            // uint8 block_size=fcframe.data[1];
            uint8 cf_count=0;
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
                cf_count++;
                if (offset+bytes_to_copy<length){
                    uint32 delay_us=0;
                    status =IsoTP_GetSTminDelay(STmin,&delay_us);
                    if (status != E_OK){
                        return E_NOT_OK;
                    }
                    IsoTP_DelayUS(delay_us);
                    // IsoTP_DelayMS(STmin);
                }
                if (block_size !=0 && cf_count>=block_size){
                    uint8 new_block_size =0;
                    uint8 new_flow_status =0;
                    uint8 new_STmin=0;
                    status = IsoTp_ReceiveFlowControl(&new_block_size,&new_flow_status, &new_STmin);
                    if(status != E_OK){
                        return E_NOT_OK;
                    }
                    if (new_flow_status==0){
                        /*cts*/
                        block_size=new_block_size;
                        cf_count=0;
                        STmin=new_STmin;
                    }
                    else if (new_flow_status==1){
                        /*wait*/
                        return E_NOT_OK;
                    }
                    else if (new_flow_status==2){
                        return E_NOT_OK;
                    }
                    else{
                        return E_NOT_OK;
                    }
                }
                offset=offset+bytes_to_copy;
                sequence_number++;
            }
            //continue to send
        }
        // else if(flowstatus==1 ){
        //     //wait
        // }
        // else if (flowstatus ==2){
        //     //overflow
        // }
        // else{
        //     return E_NOT_OK;
        // }


    return E_OK;
        //multiple frane
    }
   

// }