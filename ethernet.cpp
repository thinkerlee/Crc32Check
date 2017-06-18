#include "ethernet.h"
#include "QString"
#include "string"
#include "cstdio"
#include "cstdlib"

Ethernet::Ethernet()
{

}

Ethernet::Ethernet(QString Preamble, QString SFD, QString TARGET_MAC, QString SOURCE_MAC,
             QString DATA)
{
    this->Preamble = FixData(Preamble);
    this->SFD = FixData(SFD);
    this->TARGET_MAC = FixData(TARGET_MAC);
    this->SOURCE_MAC = FixData(SOURCE_MAC);
    this->DATA = DATA;
    this->Length = QString::number(DATA.length() / 2, 16);
    this->InitCrc32Tab();
}

QString Ethernet::FixData(QString text)
{
    return text.replace(QString(":"), QString(""));
}

void Ethernet::SetEthernet(QString Preamble, QString SFD, QString TARGET_MAC, QString SOURCE_MAC,
            QString DATA)
{
    this->Preamble = Preamble;
    this->SFD = SFD;
    this->TARGET_MAC = TARGET_MAC.replace(QString(":"), QString(""));
    this->SOURCE_MAC = SOURCE_MAC.replace(QString(":"), QString(""));
    this->DATA = DATA;
    this->Length = QString::number(DATA.length() / 2, 16);
}

QString Ethernet::GetBin()
{
    QString  re;
    re = Hex2Bin(Preamble) + "---" + Hex2Bin(SFD) + "---"
         + Hex2Bin(TARGET_MAC) + "---" + Hex2Bin(SOURCE_MAC) + "---"
         + Hex2Bin(Length) + "---" + Hex2Bin(DATA);
    return re;
}

QString Ethernet::GetHex()
{
    QString  re;
    re = Preamble + SFD + TARGET_MAC +  SOURCE_MAC
         + this->GetLength() + DATA;
    return re;
}

QString Ethernet::Hex2Bin(QString hex)
{
    QString str;
    for (int i = 2; !hex.mid(i, i).isEmpty(); i++)
    {
        str += QString::number(hex.mid(i,i).toLongLong(0, 16), 2);
    }
        return str;
}

QString Ethernet::GetLength()
{
    return QString::number(this->DATA.length()-2, 16);
}

QString Ethernet::GetCheck(QString data)
{
    char* DATA = data.toLatin1().data();
    unsigned int CRC = GetCrc(DATA, strlen(DATA));
    char buf[128];
    sprintf(buf, "%08X", CRC);
    return "0x" + QString(buf);
}

QString Ethernet::GetData()
{
    return this->DATA;
}

 void Ethernet::InitCrc32Tab(){
  //生成Crc32查询表
  int i,j;
  unsigned int Crc;
  for (i = 0; i < 256; i++){
    Crc = i;
    for (j = 0; j < 8; j++){
      if (Crc & 1)
        Crc = (Crc >> 1) ^ 0xEDB88320;
      else
        Crc >>= 1;
    }
    Crc32Table[i] = Crc;
  }
}

unsigned int Ethernet::GetCrc(char* InStr,unsigned int len)
{
    //CRC32校验值
    unsigned int Crc=0xffffffff;
    for(int i=0; i < len; i++)
    {
      Crc = (Crc >> 8) ^ Crc32Table[(Crc & 0xFF) ^ InStr[i]];
    }

    Crc ^= 0xFFFFFFFF;
    return Crc;
}
