#include "uds.h"
#include <stddef.h>

Std_ReturnType Uds_ProcessRequest(const uint8 *request,uint16 request_length,uint8 *response,uint16 *response_length){
    uint8 service_id;
    uint8 sub_function;
    if (request==NULL){
        return E_NOT_OK;
    }
    if (response==NULL){
        return E_NOT_OK;
    }
    if (response_length==NULL){
        return E_NOT_OK;
    }
    if (request_length<2U){
        return E_NOT_OK;
    }
    service_id=request[0];
    if (service_id !=0x10U){
        return E_NOT_OK;
    }
    sub_function=request[1];
    if (sub_function==UDS_SESSION_DEFAULT){
        response[0]=0x50U;
        response[1]=0x01U;
        *response_length=2U;
        return E_OK;
    }
    response[0]=UDS_NEGATIVE_RESPONSE;
    response[1]=UDS_SERVICE_SESSION_CONTROL;
    response[2]=UDS_NRC_SUBFUNCTION_NOT_SUPPORTED;
    *response_length=3U;
    return E_OK;
}