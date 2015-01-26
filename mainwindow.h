#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMultimedia>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>

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

protected:
    void resizeEvent(QResizeEvent *);

private:
    Ui::MainWindow *ui;
    QVideoWidget *mVideoWidget;
    QMediaPlayer *mMediaPlayer;
    QWidget *mVideoContainer;
};

#endif // MAINWINDOW_H
