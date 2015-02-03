#include "cameracontroller.h"
#include <QDebug>
#include <QTimer>
#include <QEventLoop>
#include <QString>

const QString camera_set_int_command_url = "http://192.168.1.254/?custom=1&cmd=%1&par=%2";
const QString camera_set_str_command_url = "http://192.168.1.254/?custom=1&cmd=%1&str=%2";
const QString camera_get_command_url = "http://192.168.1.254/?custom=1&cmd=%1";


CameraController::CameraController(QObject *parent)
    :QObject(parent),request_running(false),mode(MODE_VIDEO)
{

}

CameraController::~CameraController()
{

}

void CameraController::isAvailable()
{
    sendCommand(CAMERA_MODE);
}

void CameraController::setCameraMode(Camera_Modes mode)
{
    sendCommand(SET_CAMERA_MODE,mode);
}

void CameraController::getBatteryStatus()
{
    sendCommand(BATTERY_STATUS);
}

void CameraController::freeSpaceLeft()
{
    sendCommand(BYTES_LEFT);
}

void CameraController::setDateTime()
{
    QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString time = QDateTime::currentDateTime().toString("HH:mm:ss");
    sendCommand(SET_DATE,date);
    sendCommand(SET_TIME,time);
}

void CameraController::startRecording()
{
    switch (mode) {
    case MODE_VIDEO:
    case MODE_TIMED_VIDEO:
        sendCommand(RECORDING,1);
        break;
    case MODE_FOTO:
    case MODE_TIMED_FOTO:
        sendCommand(SHOOT_FOTO,1);
        break;
    }
}

void CameraController::stopRecording()
{    
    switch (mode) {
    case MODE_VIDEO:
    case MODE_TIMED_VIDEO:
        sendCommand(RECORDING,0);
        break;
    case MODE_FOTO:
    case MODE_TIMED_FOTO:
        sendCommand(SHOOT_FOTO,1);
        break;
    }
}

void CameraController::sendCommand(const int command, const int parameter)
{
    QString request = camera_set_int_command_url.arg(command).arg(parameter);
    sendHttpReq(request);
}

void CameraController::sendCommand(const int command)
{
    QString request = camera_get_command_url.arg(command);
    sendHttpReq(request);
}

void CameraController::sendCommand(const int command, const QString &parameter)
{
    QString request = camera_set_str_command_url.arg(command).arg(parameter);
    sendHttpReq(request);
}

void CameraController::sendHttpReq(const QString &request)
{
    if (request_running)
        delay();
    request_running = true;
    reply = qnam.get(QNetworkRequest(request));
    connect(reply, SIGNAL(finished()),this, SLOT(httpFinished()));
    connect(reply, SIGNAL(readyRead()),this, SLOT(httpReadyRead()));
}

void CameraController::delay(const int time_ms)
{
    QEventLoop loop;
    QTimer::singleShot(time_ms, &loop, SLOT(quit()));
    loop.exec();
}

void CameraController::process_incomming_data(const QByteArray &data)
{
    QDomDocument xml_data;
    xml_data.setContent(data);
    qDebug() << data;
    QDomElement root = xml_data.documentElement();
    QDomNodeList cmds = root.elementsByTagName("Cmd");
    QDomNodeList statueses = root.elementsByTagName("Status");
    QDomNodeList values = root.elementsByTagName("Value");
    qDebug() << cmds.count();
    if (cmds.count() == 1 && statueses.count() == 1)
    {
        int cmd = cmds.at(0).firstChild().nodeValue().toInt();
        int status = statueses.at(0).firstChild().nodeValue().toInt();
        long int value = values.at(0).firstChild().nodeValue().toLong();
        switch (cmd) {
        case CAMERA_MODE:
                mode = static_cast<Camera_Modes>(status);
                emit cameraModeChanged(mode);
            break;
        case BATTERY_STATUS:
                emit batteryStatus(value==5?100:((4-value)*100/4));
            break;
        case SET_CAMERA_MODE:
            if (status == STATUS_OK){
                isAvailable();
            }
            break;
        case BYTES_LEFT:
            emit spaceLeft(QString("%1").arg(value/(1024*1024)));
            break;
        default:
            break;
        }
    }
    else if(cmds.count() == 25 && statueses.count() == 25)
    {
        //answer to req CAMERA_STATUS - get settings
    }
    else
    {
        //an error??
    }
}

void CameraController::httpFinished()
{
    if (reply->error()) {
    }
    reply->deleteLater();
    request_running = false;
}

void CameraController::httpReadyRead()
{
    QByteArray data = reply->readAll();    
    QDomDocument domDocument;
    if (!domDocument.setContent(data))
    {
        emit cameraError();        
    }
    else
        process_incomming_data(data);
    request_running = false;
}

