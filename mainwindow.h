#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMultimedia>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <cameracontroller.h>
#include <QButtonGroup>

namespace Ui {
class MainWindow;
}

class QVideoWidget;
class QMediaPlayer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_playButton_clicked();
    void on_data_from_camera(QByteArray &data);
    void on_mode_button_toggled(int id, bool b);

protected:
    void resizeEvent(QResizeEvent *);

private:
    Ui::MainWindow *ui;
    QVideoWidget *mVideoWidget;
    QMediaPlayer *mMediaPlayer;
    QWidget *mVideoContainer;
    CameraController *cameraController;
    void cameraMode(const int mode);
    QButtonGroup *mode_group;
};

#endif // MAINWINDOW_H
