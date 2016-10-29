#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include "global.h"
#include "arp.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
private:
    ARP arp;
    pcap_if_t *alldevs;
    pcap_if_t *d;
    pcap_t *adhandle;
    char errbuf[PCAP_ERRBUF_SIZE];

    void setUi();
    void initConnect();
    bool getNetCard();
    void sendSlot();
    QGroupBox* sourceGroup;
    QGroupBox* targetGroup;

    QLabel* lbsourceMAC;
    QLabel* lbsourceIP;
    QLabel* lbtargetMAC;
    QLabel* lbtargetIP;

    QLineEdit* lesourceMAC;
    QLineEdit* lesourceIP;
    QLineEdit* letargetMAC;
    QLineEdit* letargetIP;

    QHBoxLayout* hostInfoLayout;
    QHBoxLayout* cardLayout;
    QVBoxLayout* mainLayout;
    QGridLayout* sourceLayout;
    QGridLayout* targetLayout;
    QHBoxLayout* sendLayout;

    QPushButton* btsend;
    QComboBox* cbpackeType;

    QComboBox* cbnetcardInfo;
    QLabel* lbnetCard;
    QLabel* lbcardDescription;

};

#endif // MAINWIDGET_H
