#include "cameracontroller.h"
#include <QDebug>

const QString camera_set_command_url = "http://192.168.1.254/?custom=1&cmd=%1&par=%2";
const QString camera_get_command_url = "http://192.168.1.254/?custom=1&cmd=%1";

enum command{
    RECORDING=2001
};


CameraController::CameraController(QObject *parent)
    :QObject(parent)
{

}

CameraController::~CameraController()
{

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
    QString request = camera_set_command_url.arg(command);
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

}

void CameraController::httpReadyRead()
{
    QByteArray data = reply->readAll();
    qDebug() << data;
}

