#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMultimedia>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <cameracontroller.h>
#include <QButtonGroup>
#include <QTimer>

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
    void on_mode_button_toggled(int id, bool b);
    void cameraMode(Camera_Modes mode);
    void periodic_check(void);

    void on_actionSet_Date_Time_triggered();

protected:
    void resizeEvent(QResizeEvent *);

private:
    Ui::MainWindow *ui;
    QVideoWidget *mVideoWidget;
    QMediaPlayer *mMediaPlayer;
    QWidget *mVideoContainer;
    CameraController *cameraController;    
    QButtonGroup *mode_group;
    QTimer *periodic_refresh;
};

#endif // MAINWINDOW_H
