#include "cameracontroller.h"
#include <QDebug>

const QString camera_set_command_url = "http://192.168.1.254/?custom=1&cmd=%1&par=%2";
const QString camera_get_command_url = "http://192.168.1.254/?custom=1&cmd=%1";


CameraController::CameraController(QObject *parent)
    :QObject(parent)
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

void CameraController::batteryStatus()
{
    sendCommand(BATTERY_STATUS);
}

void CameraController::startRecording()
{
    sendCommand(RECORDING,1);
}

void CameraController::stopRecording()
{
    sendCommand(RECORDING,0);
}

void CameraController::sendCommand(const int command, const int parameter)
{
    QString request = camera_set_command_url.arg(command).arg(parameter);
    sendHttpReq(request);
}

void CameraController::sendCommand(const int command)
{
    QString request = camera_get_command_url.arg(command);
    sendHttpReq(request);
}

void CameraController::sendHttpReq(const QString &request)
{
    reply = qnam.get(QNetworkRequest(request));
    connect(reply, SIGNAL(finished()),this, SLOT(httpFinished()));
    connect(reply, SIGNAL(readyRead()),this, SLOT(httpReadyRead()));
}

void CameraController::httpFinished()
{
    if (reply->error()) {
    }
    reply->deleteLater();
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
        emit dataFromCamera(data);

}

