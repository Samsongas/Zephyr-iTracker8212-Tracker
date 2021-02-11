/* AT Commands to be sent to BG96 */
const char GPRS-CFG_1[30] = "AT+QCFG=\"nbsibscramble\",0";
const char GPRS-CFG_2[30] = "AT+QCFG=\"band\",0,0,80,1";
const char GPRS-CFG_3[30] = "AT+QCFG=\"nwscanmode\",3,1";
const char GPRS-CFG_4[30] = "AT+QCFG=\"nwscanseq\",030201,1";
const char GPRS-CFG_5[30] = "AT+QCFG=\"iotopmode\",1,1";
const char GPRS-CFG_6[30] = "AT+QCFG=\"servicedomain\",1,1";
const char GPRS-GDCONT[30] = "AT+CGDCONT=1,\"IP\",\"internet\"";
const char GPRS-FUN[10] = "AT+CFUN=1";
const char GPRS-OPS[30] = "AT+COPS=1,2,\"22001\",0";
const char GPRS-IACT[20] = "AT+QIACT=1";
/* add ip and port as 79.114.83.116\",16666" */
char GPRS-IOPEN[50] = "AT+QIOPEN=1,0,\"TCP\",\"";
char GPRS-ICLOSE[30] = "AT+QICLOSE=0";
char GPRS-ISENDEX[30] = "AT+QISENDEX=0,\"48656C6C6F\"";

/* BG96 responses */
const char GPRS-OK[] = "OK" /* OK message */