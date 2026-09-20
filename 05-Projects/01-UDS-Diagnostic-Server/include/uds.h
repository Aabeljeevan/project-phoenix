#ifndef UDS_H
#define UDS_H

#include "types.h"
#define UDS_NEGATIVE_RESPONSE              0x7FU
#define UDS_SERVICE_SESSION_CONTROL        0x10U
#define UDS_NRC_SUBFUNCTION_NOT_SUPPORTED  0x12U
#define UDS_SESSION_DEFAULT                0x01U

Std_ReturnType Uds_ProcessRequest(const uint8 *request,uint16 request_length,uint8 *response,uint16 *response_length);


#endif