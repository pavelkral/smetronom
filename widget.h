#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include <QPainter>
#include <QTime>
#include <QToolBar>
#include <QKeyEvent>
#include <QMediaPlayer>
namespace Ui
{
    class Widget;
}


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    QToolBar *fileToolBar;
    QMediaPlayer * music;
    QMediaPlayer *music2;
    int ticks;
    int timerspeed;
    int fullticks = 0;
	bool bgplay;
	QMediaPlaylist *bgplaylist;
	bool ticksmute = true;

protected:

    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);

public slots:

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_spinBox_2_valueChanged(int arg1);
    void resetsettings();
    void on_spinBox_3_valueChanged(int arg1);
    void changeRate();
    void on_btbgplay_clicked();
    void on_pushButton_4_clicked();
	void on_horizontalSlider_sliderReleased();
	void on_btopen_clicked();
	void on_btmute_clicked();

	void on_dial_valueChanged(int value);
	void on_dial_2_valueChanged(int value);

private:
    Ui::Widget *ui;
    void createToolBar();
    int timerId;
    bool paused = true;
	qreal bgrate = 1.0;
    bool mRunning;
    QTime n;
    int bpc;
    int bpcplayed;
    int bpccomplete;
    QDateTime mStartTime;

};

#endif // WIDGET_H
