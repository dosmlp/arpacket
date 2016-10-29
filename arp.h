#ifndef ARP_H
#define ARP_H

#include <QObject>
#include <QMessageBox>
#include "global.h"

class ARP : public QObject
{
    Q_OBJECT
public:
    explicit ARP(QObject *parent = 0);
    void sendPacket(pcap_t* h,
                    const int& type,
                    const QString& sMAC,
                    const QString& sIP,
                    const QString& tMAC,
                    const QString& tIP);

signals:

private:
    void buildPacket(ARP_packet* p,
                     const int& type,
                     const QString& sMAC,
                     const QString& sIP,
                     const QString& tMAC,
                     const QString& tIP);
};

#endif // ARP_H
