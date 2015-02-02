#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDomDocument>

enum command{
    RECORDING=2001,CAMERA_MODE=3016,CAMERA_STATUS=3014,BATTERY_STATUS=3019, BYTES_LEFT=3017,SET_CAMERA_MODE=3001
};
enum Camera_Modes{
    MODE_FOTO=0,MODE_VIDEO=1,MODE_TIMED_VIDEO=3,MODE_TIMED_FOTO=4
};

enum Camera_Status{
    STATUS_OK=0
};

QT_BEGIN_NAMESPACE
class QNetworkReply;
class QNetworkRequest;

class CameraController : public QObject
{
    Q_OBJECT
public:
    CameraController(QObject *parent = 0);
    ~CameraController();
    void isAvailable();
    void setCameraMode(Camera_Modes mode);
    void batteryStatus();

private:
    QNetworkReply *reply;
    QNetworkAccessManager qnam;
    void sendCommand(const int command, const int parameter);
    void sendCommand(const int command);
    void sendHttpReq(const QString &request);

private slots:
    void httpFinished();
    void httpReadyRead();

public slots:
    void startRecording();
    void stopRecording();

signals:
    void cameraError();
    void dataFromCamera(QByteArray &data);
};

#endif // CAMERACONTROLLER_H
