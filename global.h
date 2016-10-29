#ifndef GLOBAL_H
#define GLOBAL_H
#include <QString>
#include <QByteArray>
#include <conio.h>
#include "pcap/pcap.h"
#include "Packet32.h"
#pragma pack (1)
struct ethernet_head
{
 unsigned char dest_mac[6];         //目标主机MAC地址
 unsigned char source_mac[6];       //源端MAC地址
 unsigned short eh_type;            //以太网类型
};
struct arp_head
{
 unsigned short hardware_type;          //硬件类型：以太网接口类型为1
 unsigned short protocol_type;          //协议类型：IP协议类型为0X0800
 unsigned char add_len;                 //硬件地址长度：MAC地址长度为6B
 unsigned char pro_len;                 //协议地址长度：IP地址长度为4B
 unsigned short option;                 //操作：ARP请求为1，ARP应答为2
 unsigned char sour_addr[6];            //源MAC地址：发送方的MAC地址
 unsigned long sour_ip;                 //源IP地址：发送方的IP地址
 unsigned char dest_addr[6];            //目的MAC地址：ARP请求中该字段没有意义；ARP响应中为接收方的MAC地址
 unsigned long dest_ip;                 //目的IP地址：ARP请求中为请求解析的IP地址；ARP响应中为接收方的IP地址
 unsigned char padding[18];
};
struct ARP_packet           //最终arp包结构
{
 ethernet_head eth;         //以太网头部
 arp_head arp;              //arp数据包头部
};
#pragma pack ()
static char ConvertHexChar(char ch)
{
    if((ch >= '0') && (ch <= '9'))
        return ch-0x30;
    else if((ch >= 'A') && (ch <= 'F'))
        return ch-'A'+10;
    else if((ch >= 'a') && (ch <= 'f'))
        return ch-'a'+10;
    else return (-1);
}
static QByteArray Str2Hex(const QString& str)
{
    QByteArray senddata;
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len/2);
    char lstr,hstr;
    for(int i=0; i<len; )
    {
        hstr=str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i >= len)
            break;
        lstr = str[i].toLatin1();
        hexdata = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16+lowhexdata;
        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    senddata.resize(hexdatalen);
    return senddata;
}

#endif // GLOBAL_H
