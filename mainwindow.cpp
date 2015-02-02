#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDomDocument>
#include <QTimer>

static const QString videoStreamUrl = QString("rtsp://192.168.1.254/sjcam.mov");
static const QString fotoStreamUrl = QString("http://192.168.1.254:8192/");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mode_group = new QButtonGroup(this);
    mode_group->addButton(ui->radioButtonFoto,MODE_FOTO);
    mode_group->addButton(ui->radioButtonVideo,MODE_VIDEO);
    mode_group->addButton(ui->radioButtonTVideo,MODE_TIMED_VIDEO);
    mode_group->addButton(ui->radioButtonTFoto,MODE_TIMED_FOTO);

    cameraController = new CameraController(this);
    mVideoContainer = new QWidget(ui->videoFrame);
    mVideoContainer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    mMediaPlayer = new QMediaPlayer;    

    mVideoWidget = new QVideoWidget(mVideoContainer);
    mVideoWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    mMediaPlayer->setVideoOutput(mVideoWidget);

    connect(ui->startRecButton,SIGNAL(clicked()), cameraController,SLOT(startRecording()));
    connect(ui->stopRecButton,SIGNAL(clicked()), cameraController,SLOT(stopRecording()));

    connect(cameraController,SIGNAL(dataFromCamera(QByteArray&)),this,SLOT(on_data_from_camera(QByteArray&)));
    connect(mode_group,SIGNAL(buttonToggled(int,bool)),this,SLOT(on_mode_button_toggled(int,bool)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_playButton_clicked()
{
    resizeEvent(NULL);
    cameraController->isAvailable();
    //cameraController->batteryStatus();

}

void MainWindow::on_data_from_camera(QByteArray &data)
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
        int value = values.at(0).firstChild().nodeValue().toInt();
        switch (cmd) {
        case CAMERA_MODE:
                cameraMode(status);
            break;
        case BATTERY_STATUS:
                ui->batteryBar->setValue(value*100/5);
            break;
        case BYTES_LEFT:
            break;
        case SET_CAMERA_MODE:
            if (status == STATUS_OK){
                QEventLoop loop;
                QTimer::singleShot(500, &loop, SLOT(quit()));
                loop.exec();
                cameraController->isAvailable();
            }
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

void MainWindow::on_mode_button_toggled(int id, bool b)
{
    if(b){
        qDebug() << "handlung" << id;
        cameraController->setCameraMode(static_cast<Camera_Modes>(id));        
    }
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    mVideoContainer->setGeometry(0, 0, ui->videoFrame->width(), ui->videoFrame->height());
    mVideoWidget->setGeometry(0, 0, mVideoContainer->width(), mVideoContainer->height());
}

void MainWindow::cameraMode(const int mode)
{

    QUrl streamUrl;
    mode_group->blockSignals(true);
    switch (mode) {
    case MODE_VIDEO:
            ui->radioButtonVideo->setChecked(true);
            streamUrl.setUrl(videoStreamUrl);
        break;
    case MODE_FOTO:
            ui->radioButtonFoto->setChecked(true);
            streamUrl.setUrl(fotoStreamUrl);
        break;
    case MODE_TIMED_FOTO:
            ui->radioButtonTFoto->setChecked(true);
            streamUrl.setUrl(fotoStreamUrl);
        break;
    case MODE_TIMED_VIDEO:
            ui->radioButtonTVideo->setChecked(true);
            streamUrl.setUrl(videoStreamUrl);
        break;
    default:
        return;
        break;
    }

    mMediaPlayer->setMedia(QMediaContent(streamUrl));
    mode_group->blockSignals(false);
    mMediaPlayer->play();
}
