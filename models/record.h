#pragma once

typedef enum RecordType {
  SMS_RECORD,
  CALL_RECORD,
  DATA_USAGE,
  SUBSCRIPTION,
  TAX,
  PAYMENT,
} RecordType;

typedef struct Record {
  unsigned int id;
  enum RecordType type;
  float val;
} Record;