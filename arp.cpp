#include "arp.h"

ARP::ARP(QObject *parent) : QObject(parent)
{

}

void ARP::sendPacket(pcap_t *h, const int &type, const QString &sMAC, const QString &sIP, const QString &tMAC, const QString &tIP)
{
    ARP_packet arpacket;
    buildPacket(&arpacket,type,sMAC,sIP,tMAC,tIP);

    if (pcap_sendpacket(h,(u_char*)&arpacket,sizeof(ARP_packet)) != 0)
    {
        QMessageBox::information(Q_NULLPTR,
                                 tr("ERROR"),
                                 tr("Error sending the packet:")+
                                 QString(pcap_geterr(h)));
        return;
    }
}

void ARP::buildPacket(ARP_packet *p,const int& type, const QString &sMAC, const QString &sIP, const QString &tMAC, const QString &tIP)
{
    p->arp.dest_ip = inet_addr(tIP.toLocal8Bit().data());
    p->arp.sour_ip = inet_addr(sIP.toLocal8Bit().data());
    memcpy(p->arp.dest_addr,
           Str2Hex(tMAC).data(),
           6);
    memcpy(p->arp.sour_addr,
           Str2Hex(sMAC).data(),
           6);
    memcpy(p->eth.dest_mac,
           p->arp.dest_addr,
           6);
    memcpy(p->eth.source_mac,
           p->arp.sour_addr,
           6);
    p->eth.eh_type = htons(0x0806);
    p->arp.hardware_type = htons(0x0001);
    p->arp.protocol_type = htons(0x0800);
    p->arp.option = htons(type);
    p->arp.add_len = (char)0x06;
    p->arp.pro_len = (char)0x04;
}
