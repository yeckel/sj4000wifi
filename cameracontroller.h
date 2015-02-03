#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDomDocument>

enum command{
    RECORDING=2001,CAMERA_MODE=3016,CAMERA_STATUS=3014,BATTERY_STATUS=3019, BYTES_LEFT=3017,SET_CAMERA_MODE=3001,
    SHOOT_FOTO=1001,SET_DATE=3005,SET_TIME=3006,FREE_SPACE_FOTOS=1003,FREE_SPACE_VIDEO=2009
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
    void getBatteryStatus();
    void freeSpaceLeft();
    void setDateTime();
    Camera_Modes cameraMode(){return mode;}

private:
    QNetworkReply *reply;
    QNetworkAccessManager qnam;
    void sendCommand(const int command, const int parameter);
    void sendCommand(const int command);
    void sendCommand(const int command, const QString &parameter);
    void sendHttpReq(const QString &request);
    bool request_running;
    void delay(const int time_ms = 500);
    void process_incomming_data(const QByteArray &data);
    Camera_Modes mode;

private slots:
    void httpFinished();
    void httpReadyRead();

public slots:
    void startRecording();
    void stopRecording();

signals:
    void cameraError();
    void dataFromCamera(QByteArray &data);
    void batteryStatus(int status);
    void cameraModeChanged(Camera_Modes mode);
    void spaceLeft(QString mbytes);
};

#endif // CAMERACONTROLLER_H
