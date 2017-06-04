#include <QImage>
#include <QDebug>
#include <QMediaPlaylist>
#include <math.h>
#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
	ui->setupUi(this);
	setWindowTitle("Smetronom");
	paused = true;
	music = new QMediaPlayer(this);
	//  music->setMedia(QUrl("qrc:/samples/clap.wav"));
	ticks = 0;
	mStartTime = QDateTime::currentDateTime();
	timerspeed = 500;
	//    timerId = startTimer(timerspeed);
	// killTimer(timerId);
	qDebug() << "App running:" ;
	ui->maincounter->setStyleSheet("QLabel { background-color : green;margin-right:5px; color : black; border-radius:10px ;}");
	ui->lcdNumber_2->setPalette(Qt::black);
	bgplaylist = new QMediaPlaylist();
	// playlist->addMedia(QUrl("qrc:/samples/loop.wav"));
	music2 = new QMediaPlayer(this);
	// qreal rate = 0.50;
	//   music2->setMedia(QUrl("qrc:/samples/loop.wav"));
	//   music2->setPlaybackRate(rate);
	//music2->setVolume(50);
	//music2->setPlaybackRate(bgrate);
	music2->setPlaylist(bgplaylist);
	bgplaylist->setPlaybackMode(QMediaPlaylist::Loop);
	bgplaylist->addMedia(QUrl("qrc:/samples/loop.wav"));
	//  music2->play();
    bpc = 3;
    bpcplayed =0;
    bpccomplete = 0;
    ui->spinBox_2->setValue(120);
    ui->spinBox->setValue(bpccomplete);
    ui->spinBox_3->setValue(bpc);
 //   paused = true;

   connect(ui->pushButton_3, SIGNAL(clicked()),this, SLOT(resetsettings()));
   connect(ui->pushButton_4, SIGNAL(clicked()),this, SLOT(changeRate()));
}
//...............................................................................................................

Widget::~Widget()
{
  //  delete music;
    //delete playlist;

    delete ui;
}

//...............................................................................................................


void Widget::createToolBar()
{

}

void Widget::timerEvent(QTimerEvent *event)
{

    n = QTime::currentTime();
 //   ui->timeEdit->setTime(n);
    qDebug() << "Tick:" << n << bpc << timerspeed << fullticks;

    if(paused != true){

        if(bpcplayed == bpc){
		   ui->maincounter->setStyleSheet("QLabel { background-color : red;margin-right:5px; color : white;border-radius:10px; }");
		   ui->maincounter->setText(QString("%1").arg(ticks));

           music->setMedia(QUrl("qrc:/samples/kick.wav"));

           bpcplayed = 0;
           ticks = 0;
           bpccomplete++;
           ui->spinBox->setValue(bpccomplete);
        }
        else{
			ui->maincounter->setStyleSheet("QLabel { background-color : green; margin-right:5px;color : black;border-radius:10px ; }");
			ui->maincounter->setText(QString("%1").arg(ticks));
            music->setMedia(QUrl("qrc:/samples/clap.wav"));
        }
        if (music->state() == QMediaPlayer::PlayingState){
          music->setPosition(0);
        }
        else if (music->state() == QMediaPlayer::StoppedState){
			if(ticksmute == false){

			}
			else{
				music->play();
			}

          //music->setMedia(QUrl("qrc:/samples/kick.wav"));
          //music->play();
        }

        qint64 ms = mStartTime.msecsTo(QDateTime::currentDateTime());
        int h = ms / 1000 / 60 / 60;
        int m = (ms / 1000 / 60) - (h * 60);
        int s = (ms / 1000) - (m * 60);
        ms = ms - (s * 1000);
        QString diff = QString("%1:%2:%3").arg(h).arg(m).arg(s);
        ui->lcdNumber_2->display(diff);
        bpcplayed++;
        ticks++;
        fullticks++;
    }

}
//...............................................................................................................

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {

       case Qt::Key_P:
       {

             qDebug() << "press P" ;
                if(paused){
                   timerId = startTimer(timerspeed);
                    paused = false;
                 //   xt = QTime::currentTime();
                    //xt = QTime::currentTime().addSecs( 10 );
                }
                else{
                  paused = true;
                 killTimer(timerId);
//
                }
       }
     break;

         case Qt::Key_Escape:
        {
              qApp->exit();
           // qApp->quit();
        }
        break;
    default:
        QWidget::keyPressEvent(event);

    }
}

//...............................................................................................................


//...............................................................................................................

void Widget::on_pushButton_clicked()
{
    if(paused){

        paused = false;
        mStartTime = QDateTime::currentDateTime();
        ticks = 0;
        bpcplayed = 1;
        bpccomplete = 0;
        timerId = startTimer(timerspeed);

        //;xt = QTime::currentTime();
      //  xt = QTime::currentTime().addSecs( 10 );
    }
    else{


    }

}

void Widget::on_pushButton_2_clicked()
{
    if(paused){

    }
    else{

      killTimer(timerId);
      paused = true;
	  ui->maincounter->setText("0");
      ui->spinBox->setValue(0);
	  ui->lcdNumber_2->display("0:0:0");

    }
}



void Widget::on_spinBox_2_valueChanged(int arg1)
{
    if(paused){
    }
    else{
        killTimer(timerId);
         paused = true;
    }
	ui->maincounter->setText("0");
    ui->spinBox->setValue(0);
	ui->lcdNumber_2->display("0:0:0");
    mStartTime = QDateTime::currentDateTime();
    ticks = 0;
    bpcplayed = 1;
    bpccomplete = 0;
    double arg = (double) arg1;
    double num =  arg/60;
	qDebug() << "num" << 1000/num;
    timerspeed = 1000/num;

}

void Widget::resetsettings()
{
    if(paused){
    }
    else{
        killTimer(timerId);
         paused = true;
    }
	ui->maincounter->setText("0");
    ui->spinBox->setValue(0);
	ui->lcdNumber_2->display("0:0:0");
    mStartTime = QDateTime::currentDateTime();
    ticks = 0;
    bpcplayed = 1;
    bpccomplete = 0;
    bpc =  3;
    fullticks = 0;
    timerspeed = 500;
    ui->spinBox_2->setValue(120);
    ui->spinBox->setValue(bpccomplete);
    ui->spinBox_3->setValue(bpc);
    qDebug() << "reset" ;


}

void Widget::on_spinBox_3_valueChanged(int arg1)
{
    if(paused){
    }
    else{
        killTimer(timerId);
         paused = true;
    }
	ui->maincounter->setText("0");
    ui->spinBox->setValue(0);
	ui->lcdNumber_2->display("0:0:0");
    mStartTime = QDateTime::currentDateTime();
    ticks = 0;
    bpcplayed = 1;
    bpccomplete = 0;
    fullticks = 0;
    bpc =  arg1;
    qDebug() << "bcp changed" ;

}

void Widget::changeRate()
{
    qreal rate = 1.2;
  //    music2->setMedia(QUrl("qrc:/samples/loop.wav"));
  //music2->setPosition(0);
     //music2->setPlaybackRate(rate);
}

void Widget::on_btbgplay_clicked()
{

	//  qreal rate = 1.2;
    //    music2->setMedia(QUrl("qrc:/samples/loop.wav"));
    //music2->setPosition(0);
   //    music2->setPlaybackRate(rate);
	   music2->stop();

}

void Widget::on_pushButton_4_clicked()
{

 //   music2->setMedia(QUrl("qrc:/samples/loop.wav"));
  //  qreal rate1 = 1;
  //  music2->setPlaybackRate(rate1);
    //    music2->setPlaybackRate(name);
 //  music2->setPlaylist(playlist);
    music2->play();
    //sleep(2);
   // changeRate();

}



void Widget::on_btopen_clicked()
{


	QString filename = QFileDialog::getOpenFileName(this, tr("Open File"),"./",tr("Media files (*.mp3)"));




	if(!filename.isEmpty()) {
		bgplaylist->clear();
		bgplaylist->addMedia(QUrl::fromLocalFile(filename));
	}
}

void Widget::on_btmute_clicked()
{
	if(ticksmute == false){
		ticksmute = true;
	}
	else{
		ticksmute = false;
	}

}

void Widget::on_dial_valueChanged(int value)
{
	music->setVolume(value);
}

void Widget::on_dial_2_valueChanged(int value)
{
	music2->setVolume(value);
}

void Widget::on_bt_seek_right_clicked()
{
	quint64 pos = music2->position();
	music2->setPosition(pos + 1000);
}
