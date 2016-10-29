#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
      adhandle(Q_NULLPTR)
{
    setUi();
    getNetCard();
    initConnect();
}

MainWidget::~MainWidget()
{

}

void MainWidget::setUi()
{
    sourceGroup = new QGroupBox(tr("Source"),this);
    targetGroup = new QGroupBox(tr("Target"),this);

    lbsourceMAC = new QLabel(tr("SourceMAC:"),sourceGroup);
    lbsourceMAC->setAlignment(Qt::AlignRight);
    lbsourceIP = new QLabel(tr("SourceIP:"),sourceGroup);
    lbsourceIP->setAlignment(Qt::AlignRight);

    lbtargetMAC = new QLabel(tr("TargetMAC:"),targetGroup);
    lbtargetMAC->setAlignment(Qt::AlignRight);
    lbtargetIP = new QLabel(tr("TargetIP:"),targetGroup);
    lbtargetIP->setAlignment(Qt::AlignRight);

    lesourceMAC = new QLineEdit(sourceGroup);
    lesourceMAC->setInputMask("HH:HH:HH:HH:HH:HH;_");
    lesourceIP = new QLineEdit(sourceGroup);
    lesourceIP->setInputMask("000.000.000.000;_");

    letargetMAC = new QLineEdit(targetGroup);
    letargetMAC->setInputMask("HH:HH:HH:HH:HH:HH;_");
    letargetIP = new QLineEdit(targetGroup);
    letargetIP->setInputMask("000.000.000.000;_");

    sourceLayout = new QGridLayout(sourceGroup);
    sourceLayout->addWidget(lbsourceMAC,0,0);
    sourceLayout->addWidget(lesourceMAC,0,1);
    sourceLayout->addWidget(lbsourceIP,1,0);
    sourceLayout->addWidget(lesourceIP,1,1);

    targetLayout = new QGridLayout(targetGroup);
    targetLayout->addWidget(lbtargetMAC,0,0);
    targetLayout->addWidget(letargetMAC,0,1);
    targetLayout->addWidget(lbtargetIP,1,0);
    targetLayout->addWidget(letargetIP,1,1);

    hostInfoLayout = new QHBoxLayout();
    hostInfoLayout->addWidget(sourceGroup);
    hostInfoLayout->addWidget(targetGroup);

    cbnetcardInfo = new QComboBox(this);
    lbnetCard = new QLabel(tr("NetCard:"),this);
    lbcardDescription = new QLabel(this);
    cardLayout = new QHBoxLayout();
    cardLayout->addWidget(lbnetCard);
    cardLayout->addWidget(cbnetcardInfo);
    cardLayout->addWidget(lbcardDescription);
    cardLayout->addStretch();

    sendLayout = new QHBoxLayout();
    btsend = new QPushButton(tr("Send"),this);
    cbpackeType = new QComboBox(this);
    cbpackeType->addItem(tr("Request"),1);
    cbpackeType->addItem(tr("Reply"),2);
    sendLayout->addWidget(cbpackeType);
    sendLayout->addWidget(btsend);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(cardLayout);
    mainLayout->addLayout(hostInfoLayout);
    mainLayout->addLayout(sendLayout);
}

void MainWidget::initConnect()
{
    connect(cbnetcardInfo,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            [this](int index){
        lbcardDescription->setText(cbnetcardInfo->itemData(index,Qt::UserRole).toString());
    });
    connect(btsend,&QPushButton::clicked,this,&MainWidget::sendSlot);
}

bool MainWidget::getNetCard()
{
    if(pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        QMessageBox::information(this,
                                 tr("ERROR"),
                                 tr("Error in pcap_findalldevs:")+QString(errbuf));
        return false;
    }

    /* Print the list */
    for(d=alldevs; d; d=d->next)
    {
        cbnetcardInfo->addItem(d->name,d->description);
    }
    if(cbnetcardInfo->count() == 0)
    {
        QMessageBox::information(this,
                                 tr("ERROR"),
                                 tr("No interfaces found!"));
        return false;
    }
    return true;
}

void MainWidget::sendSlot()
{
    int index = cbnetcardInfo->currentIndex();
    int i = 0;
    for(d = alldevs;i < index;++i,d = d->next);

    adhandle = pcap_open_live(d->name,
                   65535,
                   1,
                   1000,
                   errbuf);

    if(adhandle == Q_NULLPTR)
    {
        char msg[256] = {0};
        qsnprintf(msg,256,"Unable to open the adapter. %s is not supported by WinPcap", d->name);
        QMessageBox::information(this,
                                 tr("ERROR"),
                                 msg);
        return;
    }

    arp.sendPacket(adhandle,
                   cbpackeType->currentData(Qt::UserRole).toInt(),
                   lesourceMAC->text(),
                   lesourceIP->text(),
                   letargetMAC->text(),
                   letargetIP->text());

    pcap_close(adhandle);
    adhandle = Q_NULLPTR;
}
