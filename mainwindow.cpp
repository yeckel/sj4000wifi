#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

static const QString videoStreamUrl = QString("rtsp://192.168.1.254/sjcam.mov");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cameraController = new CameraController(this);
    mVideoContainer = new QWidget(ui->videoFrame);
    mVideoContainer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    mMediaPlayer = new QMediaPlayer;
    mMediaPlayer->setMedia(QMediaContent(QUrl(videoStreamUrl)));

    mVideoWidget = new QVideoWidget(mVideoContainer);
    mVideoWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    mMediaPlayer->setVideoOutput(mVideoWidget);

    connect(ui->startRecButton,SIGNAL(clicked()), cameraController,SLOT(startRecording()));
    connect(ui->stopRecButton,SIGNAL(clicked()), cameraController,SLOT(stopRecording()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_playButton_clicked()
{
    resizeEvent(NULL);
    mMediaPlayer->play();    
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    mVideoContainer->setGeometry(0, 0, ui->videoFrame->width(), ui->videoFrame->height());
    mVideoWidget->setGeometry(0, 0, mVideoContainer->width(), mVideoContainer->height());
}
