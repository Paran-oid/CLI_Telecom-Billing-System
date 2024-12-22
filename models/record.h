#pragma once

enum RecordType
{
    SMS_RECORD,
    CALL_RECORD,
    DATA_USAGE,
    SUBSCRIPTION,
    TAX,
    PAYMENT,
};

struct Record{
    unsigned int id;
    enum RecordType type;
    float val;
};