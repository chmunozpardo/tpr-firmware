// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef SX1278_H
#define SX1278_H

#include "system.h" // include processor files - each processor file is guarded.

#define _XTAL_FREQ 8000000

#define LORAMODE_REG

#define R_REG 0x00
#define W_REG 0x80

// Register common settings
#define REGFIFO             0x00
// Operation mode register
#define REGOPMODE           0x01
#define LONGRANGEMODE       0x80
#define ACCESSSHAREDREG     0x40
#define FSK                 0x00
#define OOK                 0x20
#define LOWFREQUENCYMODEON  0x08
#define SLEEPM              0x00
#define STANDBY             0x01
#define FSTX                0x02
#define TX                  0x03
#define FSRX                0x04
#define RXCONTINUOUS        0x05
#define RXSINGLE            0x06
#define CAD                 0x07

#define REGBITRATEMSB   0x02
#define REGBITRATELSB   0x03
#define REGFDEVMSB      0x04
#define REGFDEVLSB      0x05
#define REGFRFMSB       0x06
#define REGFRFMID       0x07
#define REGFRFLSB       0x08

// Register for the transmitter
#define REGPACONFIG         0x09
#define PASELECT            0x80
#define MAXPOWER            0x70
#define OUTPUTPOWER         0x0F

#define REGPARAMP           0x0A
#define MODULATIONSHAPING   0x60
#define PARAMP              0x0F

#define REGOCP              0x0B
#define OCPON               0x20
#define OCPTRIM             0x1F

// Register for the receiver
#define REGLNA              0x0C
#define LNAGAIN             0xE0
#define LNABOOSTLF          0x18
#define LNABOOSTHF          0x03


#ifndef LORAMODE_REG
// FSK/OOK Registers

#define REGRXCONFIG             0x0D
#define RESTARTRXONCOLLISION    0x80
#define RESTARTRXWITHOUTPLLLOCK 0x40
#define RESTARTRXWITHPLLLOCK    0x20
#define AFCAUTOON               0x10
#define AGCAUTOON               0x08
#define RXTRIGGER               0x07

#define REGRSSICONFIG       0x0E
#define RSSIOFFSET          0xF8
#define RSSISMOOTHING       0x07

#define REGRSSICOLLISION        0x0F
#define RSSICOLLISIONTHRESHOLD  0xFF

#define REGRSSITHRESH       0x10
#define RSSITHRESHOLD       0xFF

#define REGRSSIVALUE        0x11
#define RSSIVALUE           0xFF

#define REGRXBW             0x12
#define RXBWMANT            0x18
#define RXBWEXP             0x07

#define REGAFCBW            0x13
#define RXBWMANTAFC         0x18
#define RXBWEXPAFC          0x07

#define REGOOKPEAK          0x14
#define BITSYNCON           0x20
#define OOKTHRESHTYPE       0x18
#define OOKPEAKTHRESHSTEP   0x07

#define REGOOKFIX           0x15
#define OOKFIXEDTHRESHOLD   0xFF

#define REGOOKFAVG              0x16
#define OOKPEAKTHRESHDEC        0xE0
#define OOKAVERAGEOFFSET        0x0C
#define OOKAVERAGETHRESHFILT    0x03

#define REGAFCFEI           0x1A
#define AGCSTART            0x20
#define AFCCLEAR            0x02
#define AFCAUTOCLEARON      0x01

#define REGAFCMSB           0x1B
#define AFCVALUEMSB         0xFF

#define REGAFCLSB           0x1C
#define AFCVALUELSB         0xFF

#define REGFEIMSB           0x1D
#define FEIVALUEMSB         0xFF

#define REGFEILSB           0x1E
#define FEIVALUELSB         0xFF

#define REGPREAMBLEDETECT       0x1F
#define PREAMBLEDETECTORON      0x80
#define PREAMBLEDETECTORSIZE    0x60
#define PREAMBLEDETECTORTOl     0x1F

#define REGRXTIMEOUT1       0x20
#define TIMEOUTRXRSSI       0xFF

#define REGRXTIMEOUT2       0x21
#define TIMEOUTRXPREAMBLE   0xFF

#define REGRXTIMEOUT3       0x22
#define TIMEOUTSIGNALSYNC   0xFF

#define REGRXDELAY          0x23
#define INTERPACKETRXDELAY  0xFF

// RC Oscillator registers
#define REGOSC              0x24
#define RCCALSTART          0x08
#define CLKOUT              0x07

// Packet handling registers
#define REGPREAMPLEMSB      0x25
#define PREAMBLESIZEMSB     0xFF

#define REGPREAMPLELSB      0x26
#define PREAMBLESIZELSB     0xFF

#define REGSYNCCONFIG       0x27
#define AUTORESTARTRXMODE   0xC0
#define PREAMBLEPOLARITY    0x20
#define SYNCON              0x10
#define SYNCSIZE            0x07

#define REGSYNCVALUE1       0x28
#define REGSYNCVALUE2       0x29
#define REGSYNCVALUE3       0x2A
#define REGSYNCVALUE4       0x2B
#define REGSYNCVALUE5       0x2C
#define REGSYNCVALUE6       0x2D
#define REGSYNCVALUE7       0x2E
#define REGSYNCVALUE8       0x2F

#define REGPACKETCONFIG1    0x30
#define PACKETFORMAT        0x80
#define DCFREE              0x60
#define CRCON               0x10
#define CRCAUTOCLEAROFF     0x08
#define ADDRESSFILTERING    0x06
#define CRCWHITENINGTYPE    0x01

#define REGPACKETCONFIG2    0x31
#define DATAMODE            0x40
#define IOHOMEON            0x20
#define IOHOMEPOWERFRAME    0x10
#define BEACONON            0x08
#define PAYLOADLENGTHMSB    0x07

#define REGPAYLOADLENGTH    0x32
#define PAYLOADLENGTHLSB    0xFF

#define REGNODEADRS         0x33
#define NODEADDRESS         0xFF

#define REGBROADCASTADRS    0x34
#define BROADCASTADDRESS    0xFF

#define REGFIFOTHRESH       0x35
#define TXSTARTCONDITION    0x80
#define FIFOTHRESHOLD       0x3F

// Sequencer registers
#define REGSEQCONFIG1       0x36
#define SEQUENCERSTART      0x80
#define SEQUENCERSTOP       0x40
#define IDLEMODE            0x20
#define FROMSTART           0x18
#define LOWPOWERSELECTION   0x04
#define FROMIDLE            0x02
#define FROMTRANSMIT        0x01

#define REGSEQCONFIG2       0x37
#define FROMRECEIVE         0xE0
#define FROMRXTIMEOUT       0x18
#define FROMPACKETRECEIVED  0x07

#define REGTIMERRESOL       0x38
#define TIMER1RESOLUTION    0x0C
#define TIMER2RESOLUTION    0x03

#define REGTIMER1COEF       0x39
#define TIMER1COEFFICIENT   0xFF

#define REGTIMER2COEF       0x3A
#define TIMER2COEFFICIENT   0xFF

// Service registers
#define REGIMAGCAL          0x3B
#define AUTOIMAGECALON      0x80
#define IMAGECALSTART       0x40
#define IMAGECALRUNNING     0x20
#define TEMPCHANGE          0x08
#define TEMPTHRESHOLD       0x06
#define TEMPMONITOROFF      0x01

#define REGTEMP             0x3C
#define TEMPVALUE           0xFF

#define REGLOWBAT           0x3D
#define LOWBATON            0x08
#define LOWBATTRIM          0x07

// Status registers
#define REGIRQFLAGS1        0x3E
#define MODEREADY           0x80
#define RXREADY             0x40
#define TXREADY             0x20
#define PLLLOCK             0x10
#define RSSI                0x08
#define TIMEOUT             0x04
#define PREAMBLEDETECT      0x02
#define SYNCADDRESSMATCH    0x01

#define REGIRQFLAGS2        0x3F
#define FIFOFULL            0x80
#define FIFOEMPTY           0x40
#define FIFOLEVEL           0x20
#define FIFOOVERRUN         0x10
#define PACKETSENT          0x08
#define PAYLOADREADY        0x04
#define CRCOK               0x02
#define LOWBAT              0x01

// IO control registers
#define REGDIOMAPPINGS1     0x40
#define DIO0MAPPING         0xC0
#define DIO1MAPPING         0x30
#define DIO2MAPPING         0x0C
#define DIO3MAPPING         0x03

#define REGDIOMAPPINGS2     0x41
#define DIO4MAPPING         0xC0
#define DIO5MAPPING         0x30
#define MAPPREAMBLEDETECT   0x01

// Version registers
#define REGVERSION          0x42

// Additional registers
#define REGPLLHOP           0x44
#define FASTHOPON           0x80

#define REGTCXO             0x4B
#define XTAL                0x00
#define TCXO                0x10

#define REGPADAC            0x4D
#define PADAC               0x07

#define REGFORMERTEMP       0x5B
#define FORMERTEMP          0xFF

#define REGBITRATEFRAC      0x5D
#define BITRATEFRAC         0x0F

#define REGAGCREF           0x61
#define AGCREFERENCEVALUE   0x3F

#define REGAGCTHRESH1       0x62
#define AGCSTEP1            0x1F

#define REGAGCTHRESH2       0x63
#define AGCSTEP2            0xF0
#define AGCSTEP3            0x0F

#define REGAGCTHRESH3       0x64
#define AGCSTEP4            0xF0
#define AGCSTEP5            0x0F

// Low frequency additional registers
#define REGAGCREFLF         0x61
#define REGAGCTHRESH1LF     0x62
#define REGAGCTHRESH2LF     0x63
#define REGAGCTHRESH3LF     0x64
#define REGPLLLF            0x70
#define PLLBANDWIDTH        0xC0
#endif

#ifdef LORAMODE_REG
// LoRa page registers
#define REGFIFOADDRPTR          0x0D
#define FIFOADDRPTR             0xFF

#define REGFIFOTXBASEADDR       0x0E
#define FIFOTXADDRPTR           0xFF

#define REGFIFORXBASEADDR       0x0F
#define FIFORXADDRPTR           0xFF

#define REGFIFORXCURRENTADDR    0x10
#define FIFORXCURRENTADDR       0xFF

#define REGIRQFLAGSMASK         0x11
#define RXTIMEOUTMASK           0x80
#define RXDONEMASK              0x40
#define PAYLOADCRCERRORMASK     0x20
#define VALIDHEADERMASK         0x10
#define TXDONEMASK              0x08
#define CADDONEMASK             0x04
#define FHSSCHANGECHANNELMASK   0x02
#define CADDETECTMASK           0x01

#define REGIRQFLAGS             0x12
#define RXTIMEOUT               0x80
#define RXDONE                  0x40
#define PAYLOADCRCERROR         0x20
#define VALIDHEADER             0x10
#define TXDONE                  0x08
#define CADDONE                 0x04
#define FHSSCHANGECHANNEL       0x02
#define CADDETECT               0x01

#define REGRXNBBYTES           0x13

#define REGRXHEADERCNTVALUEMSB  0x14

#define REGRXHEADERCNTVALUELSB  0x15

#define REGRXPACKETCNTVALUEMSB  0x16

#define REGRXPACKETCNTVALUELSB  0x17

#define REGMODEMSTAT            0x18
#define RXCODINGRATE            0xE0
#define MODEMSTATUS             0x1F

#define REGPKTSNRVALUE          0x19

#define REGPKTRSSIVALUE         0x1A

#define REGRSSIVALUE            0x1B

#define REGHOPCHANNEL           0x1C
#define PLLTIMEOUT              0x80
#define CRCONPAYLOAD            0x40
#define FHSSPRESENTCHANNEL      0x3F

#define REGMODEMCONFIG1         0x1D
#define BW                      0xF0
#define CODINGRATE              0x0E
#define IMPLICITHEADERMODEON    0x01
#define EXPLICITHEADERMODEON    0x00

#define REGMODEMCONFIG2         0x1E
#define SPREADINGFACTOR         0xF0
#define TXCONTINUOUSMODE        0x08
#define RXPAYLOADCRCON          0x04
#define SYMBTIMEOUTMSB          0x03

#define REGSYMBTIMEOUTLSB       0x1F
#define SYMBTIMEOUTLSB          0xFF

#define REGPREAMBLEMSB          0x20
#define REGPREAMBLELSB          0x21
#define REGPAYLOADLENGTH        0x22
#define REGMAXPAYLOADLENGTH     0x23
#define REGHOPPERIOD            0x24
#define REGFIFORXBYTEADDR       0x25

#define REGMODEMCONFIG3         0x26
#define LOWDATARATEOPTIMIZE     0x08
#define AGCAUTOON               0x04

#define REGPPMCORRECTION        0x27

#define REGFEIMSB               0x28
#define FREQERRORMSB            0x0F

#define REGFEIMID               0x29
#define FREQERRORMID            0xFF

#define REGFEILSB               0x2A
#define FREQERRORLSB            0xFF

#define REGRSSIWIDEBAND         0x2C
#define RSSIWIDEBAND            0xFF

#define REGDETECTOPTIMIZE       0x31
#define DETECTIONOPTIMIZE       0x07

#define REGINVERTIQ             0x33
#define INVERTIQ                0x40

#define REGDETECTIONTHRESHOLD   0x37

#define REGSYNCWORD             0x39

#endif

#define PAYLOAD_SIZE    28
#define FXOSC           32000000.0
#define FSTEP           (FXOSC / 524288.0)

#define GATEWAY_ADDR    0xAA55135B
#define NODE_ADDR       0xAA55435A

void SX1278_init(void);
void SX1278_changeMode(unsigned char data);
void SX1278_transmitData(unsigned char *data, unsigned char length);
void SX1278_writeReg(unsigned char reg, unsigned char data);
unsigned char SX1278_readReg(unsigned char reg);

#endif