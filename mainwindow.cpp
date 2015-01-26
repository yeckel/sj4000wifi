#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

static const QString videoStreamUrl = QString("rtsp://192.168.1.254/sjcam.mov");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mVideoContainer = new QWidget(ui->videoWidget);
    mVideoContainer->setStyleSheet("background-color: black;");

    mMediaPlayer = new QMediaPlayer;
    mMediaPlayer->setMedia(QMediaContent(QUrl(videoStreamUrl)));

    mVideoWidget = new QVideoWidget(mVideoContainer);
    mMediaPlayer->setVideoOutput(mVideoWidget);    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_playButton_clicked()
{
    mMediaPlayer->play();    
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    mVideoContainer->setGeometry(0, 0, ui->videoWidget->width(), ui->videoWidget->height());
    mVideoWidget->setGeometry(0, 0, mVideoContainer->width(), mVideoContainer->height());
}
