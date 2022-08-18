QT += quick
QT += serialport
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += PROJECT_PATH=\\\"$${PWD}\\\"
RC_ICONS = resource/icon/port.ico
SOURCES += \
        src/CComSimulatorApp.cpp \
        src/COM/CHandleMessageThread.cpp \
        src/COM/CPortCom.cpp \
        src/Message/CPrimaryMessage.cpp \
        src/Message/CSecondaryMessage.cpp \
        src/Message/CMessage.cpp \
        src/Model/CAckMessageModel.cpp \
        src/Model/CLogModel.cpp \
        src/Model/CSendMessageModel.cpp \
        src/main.cpp

RESOURCES += resource/qml/qml.qrc \
    resource/icon/icon.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/CComSimulatorApp.h \
    src/COM/CHandleMessageThread.h \
    src/COM/CPortCom.h \
    src/DefConst.h \
    src/Message/CPrimaryMessage.h \
    src/Message/CSecondaryMessage.h \
    src/Message/CMessage.h \
    src/Model/CAckMessageModel.h \
    src/Model/CLogModel.h \
    src/Model/CSendMessageModel.h \
    src/enums.h
