#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

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

    periodic_refresh = new QTimer(this);
    periodic_refresh->setInterval(30000); //30s

    connect(ui->startRecButton,SIGNAL(clicked()), cameraController,SLOT(startRecording()));
    connect(ui->stopRecButton,SIGNAL(clicked()), cameraController,SLOT(stopRecording()));

    connect(periodic_refresh,SIGNAL(timeout()),this,SLOT(periodic_check()));

    connect(mode_group,SIGNAL(buttonToggled(int,bool)),this,SLOT(on_mode_button_toggled(int,bool)));
    connect(cameraController,SIGNAL(batteryStatus(int)),ui->batteryBar,SLOT(setValue(int)));
    connect(cameraController,SIGNAL(cameraModeChanged(Camera_Modes)),this,SLOT(cameraMode(Camera_Modes)));
    connect(cameraController,SIGNAL(spaceLeft(QString)),ui->labelSpaceLeft,SLOT(setText(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_playButton_clicked()
{
    resizeEvent(NULL);
    cameraController->isAvailable();
    periodic_check();

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

void MainWindow::cameraMode(Camera_Modes mode)
{

    QUrl streamUrl;
    mode_group->blockSignals(true);    
    switch (mode) {
    case MODE_VIDEO:
            ui->radioButtonVideo->setChecked(true);
            ui->labelStart->setText(tr("Video Recording"));
            ui->stopRecButton->setEnabled(true);
            streamUrl.setUrl(videoStreamUrl);
        break;
    case MODE_FOTO:
            ui->radioButtonFoto->setChecked(true);
            ui->labelStart->setText(tr("Foto Shooting"));
            ui->stopRecButton->setEnabled(false);
            streamUrl.setUrl(fotoStreamUrl);
        break;
    case MODE_TIMED_FOTO:
            ui->radioButtonTFoto->setChecked(true);
            ui->labelStart->setText(tr("Foto Shooting"));
            ui->stopRecButton->setEnabled(true);
            streamUrl.setUrl(fotoStreamUrl);
        break;
    case MODE_TIMED_VIDEO:
            ui->radioButtonTVideo->setChecked(true);
            ui->labelStart->setText(tr("Video Recording"));
            ui->stopRecButton->setEnabled(true);
            streamUrl.setUrl(videoStreamUrl);
        break;
    default:
        return;
        break;
    }
    periodic_refresh->start();
    mMediaPlayer->setMedia(QMediaContent(streamUrl));
    mode_group->blockSignals(false);
    mMediaPlayer->play();
}

void MainWindow::periodic_check()
{
    cameraController->getBatteryStatus();
    cameraController->freeSpaceLeft();
}

void MainWindow::on_actionSet_Date_Time_triggered()
{
    cameraController->setDateTime();
}
