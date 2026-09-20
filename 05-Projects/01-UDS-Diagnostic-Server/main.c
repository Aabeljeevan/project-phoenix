#include <stdio.h>

#include "can_if.h"
#include "can.h"
#include "isotp.h"
#include "uds.h"


int main(void)
{
    Std_ReturnType status;

    // Can_FrameType txFrame;
    Can_FrameType rxFrame;

    /* Initialize CAN Driver */

    status = Can_Init();

    if (status != E_OK)
    {
        printf("CAN Initialization Failed\n");
        return -1;
    }
    /*UDS*/
    uint8 uds_request[]={0x10,0x02};
    uint8 uds_response[8];
    uint16 uds_response_length=0U;
    status =Uds_ProcessRequest(uds_request,2U,uds_response,&uds_response_length);
    if (status ==E_OK){
        printf("\nUDS request Accepted\n");
        printf("\n UDS response\n");
        for (uint16 index =0U;index<uds_response_length;index++){
            printf("%02x",uds_response[index]);
        }
        printf("\n");
    }
    else{
        printf("\n uds reuest rejected\n");
    }

    /* Prepare CAN Frame */

    // txFrame.id = 0x7E0;
    // txFrame.dlc = 3;

    // txFrame.data[0] = 0x22;
    // txFrame.data[1] = 0xF1;
    // txFrame.data[2] = 0x90;

    /* Send Frame */
    uint8 data[] = {
        0x01, 0x02, 0x03, 0x04, 0x05,
        0x06, 0x07, 0x08, 0x09, 0x0A,
        0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
        0x10, 0x11, 0x12, 0x13, 0x14
    };

    status = IsoTp_Transmit(0x7E0, data, 20);
    // status = CanIf_Transmit(&txFrame);

    if (status != E_OK)
    {
        printf("CAN Transmission Failed\n");
        return -1;
    }

    /* Receive Frame */

    status = CanIf_Receive(&rxFrame);

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