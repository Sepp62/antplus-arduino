#include <CommonDataPages/TX/ANTPLUS_RequestDataPageMsg.h>
#include <CommonDataPages/ANTPLUS_CommonDataPagePrivateDefines.h>
#include <CommonDataPages/ANTPLUS_CommonDataPageDefines.h>
#include <ANTPLUS_PrivateDefines.h>

RequestDataPageMsg::RequestDataPageMsg() : BaseDataPageMsg() {
    setDataBuffer(_buffer);
    setDescriptorByte1(ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_DESCRIPTORBYTE1_INVALID);
    setDescriptorByte2(ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_DESCRIPTORBYTE2_INVALID);
    _buffer[ANTPLUS_DEFAULT_DATAPAGE_BYTE] = ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_NUMBER;
}

uint16_t RequestDataPageMsg::getSlaveSerialNumber() {
    return _buffer[ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_SLAVESERIALNUMBER_LSB_BYTE] | (_buffer[ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_SLAVESERIALNUMBER_MSB_BYTE] << ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_SLAVESERIALNUMBER_MSB_SHIFT);
}

uint8_t RequestDataPageMsg::getDescriptorByte1() {
    return _buffer[ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_DESCRIPTORBYTE1_BYTE];
}

uint8_t RequestDataPageMsg::getDescriptorByte2() {
    return _buffer[ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_DESCRIPTORBYTE2_BYTE];
}

uint8_t RequestDataPageMsg::getRequestedTransmissionResponseCount() {
    return _buffer[ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_REQUESTEDTRANSMISSIONRESPONSE_BYTE] & ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_REQUESTEDTRANSMISSIONRESPONSE_COUNT_MASK;
}

uint8_t RequestDataPageMsg::getRequestedTransmissionUseAcknowledged() {
    return _buffer[ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_REQUESTEDTRANSMISSIONRESPONSE_BYTE] & ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_REQUESTEDTRANSMISSIONRESPONSE_USEACKNOWLEDGED_MASK;
}

uint8_t RequestDataPageMsg::getRequestedPageNumber() {
    return _buffer[ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_REQUESTEDPAGENUMBER_BYTE];
}

uint8_t RequestDataPageMsg::getCommandType() {
    return _buffer[ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_COMMANDTYPE_BYTE];
}

void RequestDataPageMsg::setSlaveSerialNumber(uint16_t serialNumber) {
    _buffer[ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_SLAVESERIALNUMBER_LSB_BYTE] = serialNumber & ANTPLUS_DEFAULT_BYTE_MASK;
    _buffer[ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_SLAVESERIALNUMBER_MSB_BYTE] = serialNumber >> ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_SLAVESERIALNUMBER_MSB_SHIFT;
}

void RequestDataPageMsg::setDescriptorByte1(uint8_t descriptorByte) {
    _buffer[ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_DESCRIPTORBYTE1_BYTE] = descriptorByte;
}

void RequestDataPageMsg::setDescriptorByte2(uint8_t descriptorByte) {
    _buffer[ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_DESCRIPTORBYTE2_BYTE] = descriptorByte;
}

void RequestDataPageMsg::setRequestedTransmissionResponseCount(uint8_t count) {
     uint8_t temp = _buffer[ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_REQUESTEDTRANSMISSIONRESPONSE_BYTE] & ~ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_REQUESTEDTRANSMISSIONRESPONSE_COUNT_MASK;
     _buffer[ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_REQUESTEDTRANSMISSIONRESPONSE_BYTE] = temp | (count & ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_REQUESTEDTRANSMISSIONRESPONSE_COUNT_MASK);
}

void RequestDataPageMsg::setRequestedTransmissionUseAcknowledged(uint8_t useAcknowledged) {
    uint8_t temp = _buffer[ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_REQUESTEDTRANSMISSIONRESPONSE_BYTE] & ~ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_REQUESTEDTRANSMISSIONRESPONSE_USEACKNOWLEDGED_MASK;
    _buffer[ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_REQUESTEDTRANSMISSIONRESPONSE_BYTE] = temp | (useAcknowledged & ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_REQUESTEDTRANSMISSIONRESPONSE_USEACKNOWLEDGED_MASK);
}

void RequestDataPageMsg::setRequestedPageNumber(uint8_t pageNumber) {
    _buffer[ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_REQUESTEDPAGENUMBER_BYTE] = pageNumber;
}

void RequestDataPageMsg::setCommandType(uint8_t commandType) {
    if (commandType != ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_COMMANDTYPE_REQUESTDATAPAGEFROMSLAVE) {
        setSlaveSerialNumber(ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_SLAVESERIALNUMBER_INVALID);
    }
    _buffer[ANTPLUS_COMMON_DATAPAGE_REQUESTDATAPAGE_COMMANDTYPE_BYTE] = commandType;
}
