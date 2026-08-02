#include <stdio.h>

#include "include/can.h"

int main(void)
{
    Std_ReturnType status;

    Can_FrameType txFrame;
    Can_FrameType rxFrame;

    /* Initialize CAN Driver */

    status = Can_Init();

    if (status != E_OK)
    {
        printf("CAN Initialization Failed\n");
        return -1;
    }

    /* Prepare CAN Frame */

    txFrame.id = 0x7E0;
    txFrame.dlc = 3;

    txFrame.data[0] = 0x22;
    txFrame.data[1] = 0xF1;
    txFrame.data[2] = 0x90;

    /* Send Frame */

    status = Can_SendFrame(&txFrame);

    if (status != E_OK)
    {
        printf("CAN Transmission Failed\n");
        return -1;
    }

    /* Receive Frame */

    status = Can_ReceiveFrame(&rxFrame);

    if (status != E_OK)
    {
        printf("CAN Reception Failed\n");
        return -1;
    }

    /* Print Received Frame */

    printf("\n========== CAN RX ==========\n");

    printf("ID  : 0x%03X\n", rxFrame.id);

    printf("DLC : %d\n", rxFrame.dlc);

    printf("DATA: ");

    for (uint8 index = 0U; index < rxFrame.dlc; index++)
    {
        printf("%02X ", rxFrame.data[index]);
    }

    printf("\n============================\n");

    return 0;
}