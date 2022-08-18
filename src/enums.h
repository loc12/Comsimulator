#ifndef ENUMS_H
#define ENUMS_H
#include <QObject>

class ENUMS : public QObject
{
    Q_OBJECT

    Q_ENUMS(ENUM_COMM_PORT_NAME)
    Q_ENUMS(ENUM_COMM_BAUDRATE)
    Q_ENUMS(ENUM_COMM_DATA_SIZE)
    Q_ENUMS(ENUM_COMM_PARITY)

public:
    enum ENUM_COMM_PORT_NAME {
        E_COM1 = 0,
        E_COM2,
        E_COM3,
        E_COM4,
        E_COM5,
        E_COM6,
        E_COM7,
        E_COM8,
        E_COM9,
        E_COM_MAX,
    };
    enum ENUM_COMM_BAUDRATE{
        E_BAUD_1200,
        E_BAUD_2400,
        E_BAUD_4800,
        E_BAUD_9600,
        E_BAUD_14400,
        E_BAUD_19200,
        E_BAUD_38400,
        E_BAUD_56000,
        E_BAUD_57600,
        E_BAUD_115200,
        E_BAUD_MAX,
    };
    enum ENUM_COMM_DATA_SIZE{
        E_DATA_SIZE_5 = 0,
        E_DATA_SIZE_6,
        E_DATA_SIZE_7,
        E_DATA_SIZE_8,
        E_DATA_SIZE_MAX,
    };
    enum ENUM_COMM_PARITY{
        E_PARITY_NONE = 0,
        E_PARITY_EVEN,
        E_PARITY_ODD,
        E_PARITY_MAX,
    };
};
//Q_DECLARE_METATYPE(ENUMS::ENUM_COMM_PORT_NAME)

#endif // ENUMS_H
