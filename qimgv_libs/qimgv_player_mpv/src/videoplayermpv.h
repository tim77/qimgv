#ifndef VIDEOPLAYERMPV_H
#define VIDEOPLAYERMPV_H

#include "videoplayer.h"
#include <QKeyEvent>

#if defined QIMGV_PLAYER_MPV_LIBRARY
 #define TEST_COMMON_DLLSPEC Q_DECL_EXPORT
#else
 #define TEST_COMMON_DLLSPEC Q_DECL_IMPORT
#endif

class MpvWidget;

class VideoPlayerMpv : public VideoPlayer {
    Q_OBJECT
public:
    explicit VideoPlayerMpv(QWidget *parent = nullptr);
    bool openMedia(QString file);
    void setVideoUnscaled(bool mode);

public slots:
    void seek(int pos);
    void seekRelative(int pos);
    void pauseResume();
    void frameStep();
    void frameStepBack();
    void stop();
    void setPaused(bool mode);
    void setMuted(bool);
    void show();
    void hide();

protected:
    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void readSettings();

private:
    MpvWidget *m_mpv;

};

extern "C" TEST_COMMON_DLLSPEC VideoPlayer *CreatePlayerWidget();

#endif // VIDEOPLAYERMPV_H
