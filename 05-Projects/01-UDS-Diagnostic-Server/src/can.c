#include "can.h"
#include <unistd.h>
#include <stdio.h>
/*--------------------------------------------------------------
 * CAN Driver Initialization
 *-------------------------------------------------------------*/

Std_ReturnType Can_Init(void)
{
    printf("CAN Driver Initialized\n");

    return E_OK;
}

/*--------------------------------------------------------------
 * CAN Frame Transmission
 *-------------------------------------------------------------*/

Std_ReturnType Can_SendFrame(const Can_FrameType *frame)
{
    uint8 index;

    if (frame == NULL)
    {
        return E_NOT_OK;
    }
    
    printf("\n========== CAN TX ==========\n");
    printf("ID  : 0x%03X\n", frame->id);
    printf("DLC : %d\n", frame->dlc);

    if(frame->dlc >8U)
    {
        return E_NOT_OK;
    }

    printf("DATA: ");


    for (index = 0; index < frame->dlc; index++)
    {
        printf("%02X ", frame->data[index]);
    }

    printf("\n");
    printf("============================\n");

    return E_OK;
}

/*--------------------------------------------------------------
 * CAN Frame Reception
 *-------------------------------------------------------------*/

Std_ReturnType Can_ReceiveFrame(Can_FrameType *frame)
{
    static uint8 recieve_count =0;
    if (frame == NULL)
    {
        return E_NOT_OK;
    }

    /* Dummy Frame */

    frame->id = 0x7E8;
    frame->dlc = 3;

    // frame->data[0] = 0x50;
    // frame->data[1] = 0x01;
    // frame->data[2] = 0x00;
    if (recieve_count==0){
        frame->data[0] = 0x30;/*ct*/
    }else{
        frame->data[0] = 0x30;/*cts*/
    }
    frame->data[1] = 0x02;
    frame->data[2] = 0x00;
    recieve_count++;

    return E_OK;
}