#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
class QNetworkReply;
class QNetworkRequest;

class CameraController : public QObject
{
    Q_OBJECT
public:
    CameraController(QObject *parent = 0);
    ~CameraController();        

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
};

#endif // CAMERACONTROLLER_H
