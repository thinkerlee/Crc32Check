#ifndef ETHERNET_PAG_H
#define ETHERNET_PAG_H
#include "QString"

class Ethernet
{
private:
    QString Preamble;
    QString SFD;
    QString TARGET_MAC;
    QString SOURCE_MAC;
    QString Length;
    QString DATA;
    QString CHECK;
    unsigned int Crc32Table[256];

public:
    Ethernet();
    Ethernet(QString Preamble, QString SFD, QString TARGET_MAC, QString SOURCE_MAC,
                QString DATA);

    void SetEthernet(QString Preamble, QString SFD, QString TARGET_MAC, QString SOURCE_MAC,
                 QString DATA);
    void InitCrc32Tab();
    QString GetLength();
    QString GetBin();
    QString GetHex();
    QString GetData();
    QString Hex2Bin(QString hex);
    QString GetCheck(QString data);
    QString FixData(QString);
    unsigned int GetCrc(char* InStr,unsigned int len);
};

#endif // ETHERNET_PAG_H
