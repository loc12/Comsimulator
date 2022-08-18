#include "CComSimulatorApp.h"

CComSimulatorApp::CComSimulatorApp(QObject *parent)
    : QObject(parent)
{
    m_pLogModel = new CLogModel();
    m_pAckModel = new CAckMessageModel();
}

bool CComSimulatorApp::readConfigFile()
{
    bool r = true;
    QString projectPath(PROJECT_PATH);
    projectPath += CONFIG_FILE;
    if(QFile(projectPath).exists()){
        QSettings settings(projectPath, QSettings::IniFormat);
        settings.sync();
        settings.beginGroup("Setting");
        int primaryMsgNum = settings.value("Number of Primary Message", 0).toInt();
        int secondaryMsgNum = settings.value("Number of Secondary Message", 0).toInt();
        settings.endGroup();
        // Reading the primary message
        for(int i = 0; i < primaryMsgNum; i++){
            QString sectionMsg = "PrimaryMessage" + QString::number(i+1);
            settings.beginGroup(sectionMsg);
            // Read name of primary message
            QString name = settings.value("Name").toString();
            QString content = settings.value("Content").toString();
            QString responseMsgKey;
            QString responeMsg[MAX_REPONSE_MSG];
            for(int j = 0; j < MAX_REPONSE_MSG; j++){
                responseMsgKey = "ResponseMsg" + QString::number(j+1);
                responeMsg[j] = settings.value(responseMsgKey).toString();
            }
            if(name.size() > 0 && content.size() > 0){
                CPrimaryMessage primaryMessage;
                primaryMessage.setPrimaryMessage(new CMessage(name, content));
                m_sendMessageModel.push_back(new CSendMessageModel(name, content));
                QList<CMessage> list;
                for(int j = 0; j < MAX_REPONSE_MSG; j++){
                    list.append(CMessage("", responeMsg[j]));
                }
                primaryMessage.setAnsMessages(&list);
                m_primaryMessage.push_back(primaryMessage);
            }
            settings.endGroup();
        }

        // Reading the secondary message
        for(int i = 0; i < secondaryMsgNum; i++){
            QString sectionMsg = "SecondaryMessage" + QString::number(i+1);
            settings.beginGroup(sectionMsg);
            // Read name of secondary message
            QString name = settings.value("Name").toString();
            QString content = settings.value("Content").toString();
            QString responseMsgKey;
            QString responseNameKey;
            QString responeMsgValue[MAX_REPONSE_MSG];
            QString responeNameValue[MAX_REPONSE_MSG];
            for(int j = 0; j < MAX_REPONSE_MSG; j++){
                responseMsgKey = "ResponseMsg" + QString::number(j+1);
                responeMsgValue[j] = settings.value(responseMsgKey).toString();
                responseNameKey = "ResponseName" + QString::number(j+1);
                responeNameValue[j] = settings.value(responseNameKey).toString();
            }
            if(name.size() > 0 && content.size() > 0){
                CSecondaryMessage secondaryMessage;
                secondaryMessage.setSecondaryMessage(new CMessage(name, content));
                QList<CMessage*> list;
                for(int j = 0; j < MAX_REPONSE_MSG; j++){
                    list.append(new CMessage(responeNameValue[j], responeMsgValue[j]));
                }
                secondaryMessage.setAckMessages(list);
                m_secondaryMessage.push_back(secondaryMessage);
            }
            settings.endGroup();
        }
    }
    else {
        r = false;
    }
    return r;
}

void CComSimulatorApp::initApplication()
{
    qmlRegisterUncreatableType<ENUMS>("Enum", 1, 0, "Enum", "");
    QQmlContext* context = m_pEngine->rootContext();
    // Setting the width and height for the windows of application
    context->setContextProperty("WIDTH_SCREEN", WIDTH_SCREEN);
    context->setContextProperty("HEIGHT_SCREEN", HEIGHT_SCREEN);
    context->setContextProperty("MIN_WIDTH_SCREEN", MIN_WIDTH_SCREEN);
    context->setContextProperty("MIN_HEIGHT_SCREEN", MIN_HEIGHT_SCREEN);
    // Set the model to qml
    context->setContextProperty("logModel", m_pLogModel);
    context->setContextProperty("ackModel", m_pAckModel);
    context->setContextProperty("simulator", this);
    context->setContextProperty("portcom", m_portCom->getInstance());
    context->setContextProperty("sendMessages", QVariant::fromValue(m_sendMessageModel));
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    m_pEngine->load(url);
    if(m_pEngine->rootObjects().isEmpty())
        return;
    // Define the signal slot between Qml and C++

    QObject *rootObject = m_pEngine->rootObjects().first();
    QObject::connect(rootObject, SIGNAL(connectCom()), this, SLOT(onConnect()));
    QObject::connect(rootObject, SIGNAL(disconnectCom()), this, SLOT(onDisconnect()));
    QObject::connect(rootObject, SIGNAL(sendMessageToCpp(QString)), this, SLOT(onSendMessage(QString)));
//    QObject::connect(this, SIGNAL(showAckMessages()), rootObject, SLOT(displayAck()));
    QObject::connect(m_portCom->getInstance(), SIGNAL(receiveMsg(QString)), this, SLOT(onReceiveMessage(QString)));
    QObject::connect(this, SIGNAL(sendMessage()), m_portCom->getInstance(), SLOT(writeData()));
    m_pLogModel->addLogView("Start Application", "green");
}

void CComSimulatorApp::setQmlAppEngine(QQmlApplicationEngine *engine)
{
    if(engine != NULL){
        m_pEngine = engine;
    }
    else {
        m_pEngine = new QQmlApplicationEngine();
    }
}

void CComSimulatorApp::settingPortCom(const int &portNo, const int &baudRate, const int &dataBit, const int &parity)
{
    QString PortNameDef[ENUMS::E_COM_MAX] = {"COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9"};
    int BaudRateDef[ENUMS::E_BAUD_MAX] = {QSerialPort::Baud1200, QSerialPort::Baud2400, QSerialPort::Baud4800
                                         , QSerialPort::Baud9600, QSerialPort::Baud19200, QSerialPort::Baud38400
                                         , QSerialPort::Baud57600, QSerialPort::Baud115200};
    QSerialPort::DataBits DataBitsDef[ENUMS::E_DATA_SIZE_MAX] = {QSerialPort::Data5, QSerialPort::Data6, QSerialPort::Data7, QSerialPort::Data8};
    QSerialPort::Parity ParityDef[ENUMS::E_PARITY_MAX] = {QSerialPort::NoParity, QSerialPort::EvenParity, QSerialPort::OddParity};
    m_portCom->getInstance()->m_portComSetting.m_portNo     = PortNameDef[portNo];
    m_portCom->getInstance()->m_portComSetting.m_baudRate   = BaudRateDef[baudRate];
    m_portCom->getInstance()->m_portComSetting.m_dataBit    = DataBitsDef[dataBit];
    m_portCom->getInstance()->m_portComSetting.m_parity     = ParityDef[parity];
}

void CComSimulatorApp::onConnect()
{
    if(connectPortCom()){
        m_pLogModel->addLogView("Open Port COM success!", "green");
    }
    else {
        m_pLogModel->addLogView("Open Port COM fail!", "red");
    }
}

void CComSimulatorApp::onDisconnect()
{
    if(disconnectPortCom()){
        m_pLogModel->addLogView("Close Port COM success!", "red");
    }
    else {
        m_pLogModel->addLogView("Close Port COM fail!", "red");
    }
}

void CComSimulatorApp::onSendMessage(QString msg)
{
    if(m_portCom->getInstance()->getOpenStatus()){
        m_pLogModel->addLogView("Send message: " + msg, "black");
        // Send message to machine
        m_portCom->getInstance()->addSendMessage(msg);
        emit sendMessage();
    }
    m_pAckModel->clearAll();
}

void CComSimulatorApp::onReceiveMessage(QString msg)
{
    if(m_portCom->getInstance()->getOpenStatus()){
        m_pLogModel->addLogView("Receive message: " + msg, "black");
        QList<CSecondaryMessage>::iterator it;
        for(it = m_secondaryMessage.begin(); it != m_secondaryMessage.end(); ++it){
            if(it->getSecondaryMessage()->content() == msg){
                // The receive message already define in ini file
                // Show the ACK for this message
                QList<CMessage>::iterator i;
                for(int i = 0; i < MAX_REPONSE_MSG; i++){
                    if(it->m_ackMessages[i]->name().size() > 0){
                        m_pAckModel->addAckMessage(CMessage(it->m_ackMessages[i]->name(), it->m_ackMessages[i]->content()));
                    }
                }
                emit showAckMessages();
                break;
            }
        }
    }
}

bool CComSimulatorApp::connectPortCom()
{
    bool r = true;
    r = m_portCom->getInstance()->openPortCom();
    return r;
}

bool CComSimulatorApp::disconnectPortCom()
{
    bool r = true;
    r = m_portCom->getInstance()->closePortCom();
    return r;
}

