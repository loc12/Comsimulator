#ifndef DEFCONST_H
#define DEFCONST_H

#include <QString>

#define WIDTH_SCREEN        880
#define HEIGHT_SCREEN       560
#define MIN_WIDTH_SCREEN    880
#define MIN_HEIGHT_SCREEN   560

#define CONFIG_FILE "/SettingDef.ini"
#include <QtSerialPort/QSerialPort>

enum {
    ENDCHAR = 0x0D
};
#define MAX_REPONSE_MSG 5

enum PortNo {
    ePortNo_Com1 = 0,
    ePortNo_Com2,
    ePortNo_Com3,
    ePortNo_Com4,
    ePortNo_Com5,
    ePortNo_Com6,
    ePortNo_Com7,
    ePortNo_Com8,
};
enum BaudRate {
    eBaudRate_600 = 0,
    eBaudRate_1200,
    eBaudRate_4800,
    eBaudRate_9600,
};
enum DataSize{
    eDataSize_7bit = 0,
    eDataSize_8bit,
};
enum Parity{
    eParity_none,
    eParity_odd,
    eParity_even,
    eParity_mark,
};

typedef struct CPortComSetting{
    QString m_portNo;
    int m_baudRate;
    QSerialPort::DataBits m_dataBit;
    QSerialPort::Parity m_parity;
}CPortComSetting;


#endif // DEFCONST_H
