#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDir>
#include <QSqlQuery>
#include <QMessageBox>
#include <QAbstractItemDelegate>
#include <QMap>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    init_space();
    init_list();
    init_else();
    init_connect();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init_list()
{
    QSqlQuery query;
    query.exec("select * from LocalMusic");
    while (query.next()) {
        QString name = query.value(1).toString();
        QString FileName = query.value(2).toString();
        if(!name.isEmpty()&&!FileName.isEmpty())
        {
            QListWidgetItem *item = new QListWidgetItem;
            item->setIcon(QIcon(":/image/image/Music_32px_1144946_easyicon.net.png"));
            item->setText(name);
            item->setToolTip(name);
            ui->listWidget->addItem(item);
            playlist->addMedia(QUrl::fromLocalFile(FileName));

        }
    }

    query.exec("select * from LikeMusic");
    while (query.next()) {
        QString name = query.value(1).toString();
        QString FileName = query.value(2).toString();
        if(!name.isEmpty()&&!FileName.isEmpty())
        {
            QListWidgetItem *item=new QListWidgetItem;
            item->setIcon(QIcon(":/image/image/like_outline_32px_1101681_easyicon.net.png"));
            item->setText(name);
            item->setToolTip(name);
            ui->listWidget_2->addItem(item);
            playlist_2->addMedia(QUrl::fromLocalFile(FileName));
        }
    }

    query.exec("select * from CollectMusic");
    while (query.next()) {
        QString name = query.value(1).toString();
        QString FileName = query.value(2).toString();
        if(!name.isEmpty()&&!FileName.isEmpty())
        {
            QListWidgetItem *item=new QListWidgetItem;
            item->setIcon(QIcon(":/image/image/list_32px_1142913_easyicon.net.png"));
            item->setText(name);
            item->setToolTip(name);
            ui->listWidget_3->addItem(item);
            playlist_3->addMedia(QUrl::fromLocalFile(FileName));
        }
    }
    music->setPlaylist(playlist);
}

void Widget::init_space()
{
    music = new QMediaPlayer(this);
    playlist=new QMediaPlaylist;
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    playlist_2=new QMediaPlaylist;
    playlist_2->setPlaybackMode(QMediaPlaylist::Loop);
    playlist_3=new QMediaPlaylist;
    playlist_3->setPlaybackMode(QMediaPlaylist::Loop);
    playlist_4=new QMediaPlaylist;
    playlist_4->setPlaybackMode(QMediaPlaylist::Loop);
    model_1=new QSqlTableModel(this);
    model_1->setTable("LocalMusic");
    model_1->select();
    model_2=new QSqlTableModel(this);//我喜欢列表数据库模型
    model_2->setTable("LikeMusic");
    model_2->select();
    model_3=new QSqlTableModel(this);//我的收藏数据库模型
    model_3->setTable("  CollectMusic");
    model_3->select();

}

void Widget::init_else()
{
    music->setPlaylist(playlist);
    ui->verticalSlider->setValue(music->volume());
    ui->verticalSlider->hide();
    ui->pushButton->clicked(true);
    ui->pushButton->setToolTip("本地音乐");
    ui->pushButton_5->setToolTip("喜欢的歌");
    ui->pushButton_6->setToolTip("收藏列表");
    ui->pushButton_7->setToolTip("最近播放");
    ui->pushButton_2->setToolTip("关闭");
    ui->pushButton_3->setToolTip("最大化");
    ui->pushButton_4->setToolTip("最小化");
    ui->pushButton_8->setToolTip("上一首");
    ui->pushButton_9->setToolTip("播放");
    ui->pushButton_10->setToolTip("下一首");
    ui->pushButton_15->setToolTip("添加本地音乐");
    ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget->setFrameShape(QListWidget::NoFrame);
    ui->listWidget_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_2->setFrameShape(QListWidget::NoFrame);
    ui->listWidget_3->setFrameShape(QListWidget::NoFrame);
    ui->listWidget_4->setFrameShape(QListWidget::NoFrame);
    ui->listWidget_5->setFrameShape(QListWidget::NoFrame);


}

void Widget::init_connect()
{
    connect(music,&QMediaPlayer::positionChanged,this,&Widget::update_position);
    connect(music,&QMediaPlayer::durationChanged,this,&Widget::update_duration);
    connect(music,&QMediaPlayer::currentMediaChanged,this,&Widget::set_music_name);
    connect(music,&QMediaPlayer::currentMediaChanged,this,&Widget::set_like_icon);
    connect(music,&QMediaPlayer::stateChanged,this,&Widget::set_play_icon);
    connect(music,&QMediaPlayer::currentMediaChanged,this,&Widget::set_lrc);
    connect(music,&QMediaPlayer::positionChanged,this,&Widget::update_time);
    //connect(ui->verticalSlider,SIGNAL)
}

void Widget::set_randommode(QMediaPlaylist *l)
{
    l->setPlaybackMode(QMediaPlaylist::Random);
    ui->pushButton_12->setStyleSheet("QPushButton"
     " {"
     "background-image: url(:/image/image/image/play-random.png);"
   "   background-repeat:no-repeat;"
    "  background-position:center center;"
   "   border:none;"

  "    }"

      "QPushButton:hover{"
    "  background-repeat:no-repeat;"
   "   background-position:center center;"
        "background-image: url(:/image/image/image-hover/play-random-hover.png);"

     " }"
     " QPushButton:pressed{"
      "background-repeat:no-repeat;"
     " background-position:center center;"

                                     "}");
}

void Widget::set_listmode(QMediaPlaylist *l)
{
    l->setPlaybackMode(QMediaPlaylist::Sequential);
    ui->pushButton_12->setStyleSheet("QPushButton"
     " {"
     "background-image: url(:/image/image/image/loop-list.png);"
   "   background-repeat:no-repeat;"
    "  background-position:center center;"
   "   border:none;"

  "    }"

      "QPushButton:hover{"
    "  background-repeat:no-repeat;"
   "   background-position:center center;"
        "background-image: url(:/image/image/image-hover/loop-list-hover.png);"

     " }"
     " QPushButton:pressed{"
      "background-repeat:no-repeat;"
     " background-position:center center;"

                                     "}");
}

void Widget::set_repeatemode(QMediaPlaylist *l)
{
    l->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    ui->pushButton_12->setStyleSheet("QPushButton"
     " {"
     "background-image: url(:/image/image/image/loop-one.png);"
   "   background-repeat:no-repeat;"
    "  background-position:center center;"
   "   border:none;"

  "    }"

      "QPushButton:hover{"
    "  background-repeat:no-repeat;"
   "   background-position:center center;"
        "background-image: url(:/image/image/image-hover/loop-one-hover.png);"

     " }"
     " QPushButton:pressed{"
      "background-repeat:no-repeat;"
     " background-position:center center;"

                                     "}");
}

void Widget::set_loopmode(QMediaPlaylist *l)
{
    l->setPlaybackMode(QMediaPlaylist::Loop);
    ui->pushButton_12->setStyleSheet("QPushButton"
     " {"
     "background-image: url(:/image/image/image/loop.png);"
   "   background-repeat:no-repeat;"
    "  background-position:center center;"
   "   border:none;"

  "    }"

      "QPushButton:hover{"
    "  background-repeat:no-repeat;"
   "   background-position:center center;"
        "background-image: url(:/image/image/image-hover/loop-hover.png);"

     " }"
     " QPushButton:pressed{"
      "background-repeat:no-repeat;"
     " background-position:center center;"

                                     "}");
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    locate = event->globalPos()-pos();
    setFocus();
    if(event->button()==Qt::LeftButton)
    setCursor(Qt::OpenHandCursor);

}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPos()-locate);
           event->accept();
           setCursor(Qt::ClosedHandCursor);

}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    locate=event->pos();
    event->accept();
    setCursor(Qt::ArrowCursor);
}

void Widget::on_pushButton_clicked()
{
    ui->listWidget->setSelectionMode(QListWidget::SingleSelection);
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton->setStyleSheet("QPushButton"
                                  "{"
                                  "background-image: url(:/image/image/image-hover/music-hover.png);"
                                  "background-repeat:no-repeat;"
                                  "background-position:center center;"
                                  "border:none;"

                                  "}"

                                  "QPushButton:hover{"

                                      "background-image: url(:/image/image/image-hover/music-hover.png);"
                                  "background-repeat:no-repeat;"
                                  "background-position:center center;"


                                  "}"
                                  "QPushButton:pressed{"
                                  "background-image: url(:/image/image/image/music.png);"
                                  "background-repeat:no-repeat;"
                                  "background-position:center center;"

                                  "}"
    );
    button_5_released();
    button_6_released();
    button_7_released();
}

void Widget::on_pushButton_5_clicked()
{
    ui->listWidget_2->setSelectionMode(QListWidget::SingleSelection);
    ui->stackedWidget->setCurrentIndex(1);
    ui->pushButton_5->setStyleSheet("QPushButton"
                                  "{"
                                  "background-image: url(:/image/image/image-hover/like-hover.png);"
                                  "background-repeat:no-repeat;"
                                  "background-position:center center;"
                                  "border:none;"

                                  "}"

                                  "QPushButton:hover{"

                                      "background-image: url(:/image/image/image-hover/like-hover.png);"
                                  "background-repeat:no-repeat;"
                                  "background-position:center center;"


                                  "}"
                                  "QPushButton:pressed{"
                                  "background-image: url(:/image/image/image/like.png);"
                                  "background-repeat:no-repeat;"
                                  "background-position:center center;"

                                  "}"
    );
    button_released();
    button_6_released();
    button_7_released();
}

void Widget::button_5_released()
{
    ui->pushButton_5->setStyleSheet("QPushButton"
                                  "{"
                                  "background-image: url(:/image/image/image/like.png);"
                                  "background-repeat:no-repeat;"
                                  "background-position:center center;"
                                  "border:none;"

                                  "}"

                                  "QPushButton:hover{"

                                      "background-image: url(:/image/image/image-hover/like-hover.png);"
                                  "background-repeat:no-repeat;"
                                  "background-position:center center;"


                                  "}"
                                  "QPushButton:pressed{"
                                  "background-image: url(:/image/image/image-hover/like-hover.png);"
                                  "background-repeat:no-repeat;"
                                  "background-position:center center;"

                                  "}"
                                    );
}

void Widget::button_released()
{
    ui->pushButton->setStyleSheet("QPushButton"
                                  "{"
                                  "background-image: url(:/image/image/image/music.png);"
                                  "background-repeat:no-repeat;"
                                  "background-position:center center;"
                                  "border:none;"

                                  "}"

                                  "QPushButton:hover{"

                                      "background-image: url(:/image/image/image-hover/music-hover.png);"
                                  "background-repeat:no-repeat;"
                                  "background-position:center center;"


                                  "}"
                                  "QPushButton:pressed{"
                                  "background-image: url(:/image/image/image-hover/music-hover.png);"
                                  "background-repeat:no-repeat;"
                                  "background-position:center center;"

                                  "}"
                                  );
}

void Widget::button_6_released()
{
    ui->pushButton_6->setStyleSheet("QPushButton"
                                  "{"
                                  "background-image: url(:/image/image/image/list.png);"
                                  "background-repeat:no-repeat;"
                                  "background-position:center center;"
                                  "border:none;"

                                  "}"

                                  "QPushButton:hover{"

                                      "background-image: url(:/image/image/image-hover/list-hover.png);"
                                  "background-repeat:no-repeat;"
                                  "background-position:center center;"


                                  "}"
                                  "QPushButton:pressed{"
                                  "background-image: url(:/image/image/image/list.png);"
                                  "background-repeat:no-repeat;"
                                  "background-position:center center;"

                                  "}"
                                    );
}

void Widget::button_7_released()
{
    ui->pushButton_7->setStyleSheet("QPushButton"
                                  "{"
                                  "background-image: url(:/image/image/image/play-resently.png);"
                                  "background-repeat:no-repeat;"
                                  "background-position:center center;"
                                  "border:none;"

                                  "}"

                                  "QPushButton:hover{"

                                      "background-image: url(:/image/image/image-hover/play-resently-hover.png);"
                                  "background-repeat:no-repeat;"
                                  "background-position:center center;"


                                  "}"
                                  "QPushButton:pressed{"
                                  "background-image: url(:/image/image/image-hover/play-resently-hover.png);"
                                  "background-repeat:no-repeat;"
                                  "background-position:center center;"

                                  "}"
                                    );
}

QString Widget::Time(qint64 time)
{
    qint64 seconds=time/1000;
    const qint64 minutes=seconds/60;
    seconds-=minutes*60;
    return QStringLiteral("%1:%2")
            .arg(minutes, 2, 10, QLatin1Char('0'))
            .arg(seconds, 2, 10, QLatin1Char('0'));
}

void Widget::on_pushButton_6_clicked()
{
    ui->listWidget_3->setSelectionMode(QListWidget::SingleSelection);
    ui->stackedWidget->setCurrentIndex(2);
    ui->pushButton_6->setStyleSheet("QPushButton"
                                  "{"
                                  "background-image: url(:/image/image/image-hover/list-hover.png);"
                                  "background-repeat:no-repeat;"
                                  "background-position:center center;"
                                  "border:none;"

                                  "}"

                                  "QPushButton:hover{"

                                      "background-image: url(:/image/image/image-hover/list-hover.png);"
                                  "background-repeat:no-repeat;"
                                  "background-position:center center;"


                                  "}"
                                  "QPushButton:pressed{"
                                  "background-image: url(:/image/image/image/list.png);"
                                  "background-repeat:no-repeat;"
                                  "background-position:center center;"

                                  "}"
    );
    button_5_released();
    button_released();
    button_7_released();
}

void Widget::on_pushButton_7_clicked()
{
    ui->listWidget_4->setSelectionMode(QListWidget::SingleSelection);
    ui->stackedWidget->setCurrentIndex(3);
    ui->pushButton_7->setStyleSheet("QPushButton"
                                      "{"
                                      "background-image: url(:/image/image/image-hover/play-resently-hover.png);"
                                      "background-repeat:no-repeat;"
                                      "background-position:center center;"
                                      "border:none;"

                                      "}"

                                      "QPushButton:hover{"

                                          "background-image: url(:/image/image/image-hover/play-resently-hover.png);"
                                      "background-repeat:no-repeat;"
                                      "background-position:center center;"


                                      "}"
                                      "QPushButton:pressed{"
                                      "background-image: url(:/image/image/image/play-resently.png);"
                                      "background-repeat:no-repeat;"
                                      "background-position:center center;"

                                      "}"
        );
    button_released();
    button_6_released();
    button_5_released();
}

void Widget::on_pushButton_2_clicked()
{
    QCoreApplication::quit();
}

void Widget::on_pushButton_4_clicked()
{
    showMinimized();
}

void Widget::on_pushButton_3_clicked()
{
    //showMaximized();
}

void Widget::on_pushButton_9_clicked()
{
    if(music->state()==QMediaPlayer::PlayingState)
    {
        music->pause();
    }
    else
    {
        music->play();
    }
}

void Widget::on_pushButton_8_clicked()
{
    if(music->playlist()==playlist)
    {
        on_pushButton_clicked();
        int playindex = playlist->currentIndex();

        if(--playindex<0)
            playindex=playlist->mediaCount()-1;
        playlist->setCurrentIndex(playindex);
        ui->stackedWidget->setCurrentIndex(0);
        ui->listWidget->scrollToItem(ui->listWidget->item(playindex));
        //ui->listWidget->item(playlist->currentIndex())->setSelected(true);

        //ui->label_2->setText(ui->listWidget->item(playindex)->text());
    }
    else if(music->playlist()==playlist_2)
    {
        on_pushButton_5_clicked();
        int playindex = playlist_2->currentIndex();
        if(--playindex<0)
            playindex=playlist_2->mediaCount()-1;
        playlist_2->setCurrentIndex(playindex);
        ui->stackedWidget->setCurrentIndex(1);
        ui->listWidget_2->scrollToItem(ui->listWidget_2->item(playindex));
        //ui->listWidget_2->item(playlist_2->currentIndex())->setSelected(true);
    }
    else if (music->playlist()==playlist_3)
    {
        on_pushButton_6_clicked();
        int playindex = playlist_3->currentIndex();
        if(--playindex<0)
            playindex=playlist_3->mediaCount()-1;
        playlist_3->setCurrentIndex(playindex);
        ui->stackedWidget->setCurrentIndex(2);
        ui->listWidget_3->scrollToItem(ui->listWidget_3->item(playindex));
        //ui->listWidget_3->item(playlist_3->currentIndex())->setSelected(true);
    }
    else if(music->playlist()==playlist_4)
    {
        on_pushButton_7_clicked();
        int playindex = playlist_4->currentIndex();
        if(--playindex<0)
            playindex=playlist_4->mediaCount()-1;
        playlist_4->setCurrentIndex(playindex);
        ui->stackedWidget->setCurrentIndex(3);
        ui->listWidget_4->scrollToItem(ui->listWidget_4->item(playindex));
        //ui->listWidget_4->item(playlist_4->currentIndex())->setSelected(true);
    }
    //music->play();
}

void Widget::on_pushButton_10_clicked()
{
    if(music->playlist()==playlist)
    {
        on_pushButton_clicked();
        int playindex = playlist->currentIndex();
        if(++playindex==playlist->mediaCount())
            playindex=0;
        playlist->setCurrentIndex(playindex);
        ui->stackedWidget->setCurrentIndex(0);
        ui->listWidget->scrollToItem(ui->listWidget->item(playindex));
        //ui->listWidget->item(playlist->currentIndex())->setSelected(true);
    }
    else if(music->playlist()==playlist_2)
    {
        on_pushButton_5_clicked();
        int playindex = playlist_2->currentIndex();
        if(++playindex==playlist_2->mediaCount())
            playindex=0;
        playlist_2->setCurrentIndex(playindex);
        ui->stackedWidget->setCurrentIndex(1);
        ui->listWidget_2->scrollToItem(ui->listWidget_2->item(playindex));
        //ui->listWidget_2->item(playlist_2->currentIndex())->setSelected(true);
    }
    else if (music->playlist()==playlist_3)
    {
        on_pushButton_6_clicked();
        int playindex = playlist_3->currentIndex();
        if(++playindex==playlist_3->mediaCount())
            playindex=0;
        playlist_3->setCurrentIndex(playindex);
        ui->stackedWidget->setCurrentIndex(2);
        ui->listWidget_3->scrollToItem(ui->listWidget_3->item(playindex));
        //ui->listWidget_3->item(playlist_3->currentIndex())->setSelected(true);
    }
    else if(music->playlist()==playlist_4)
    {
        on_pushButton_7_clicked();
        int playindex = playlist_4->currentIndex();
        if(++playindex==playlist_4->mediaCount())
            playindex=0;
        playlist_4->setCurrentIndex(playindex);
        ui->stackedWidget->setCurrentIndex(3);
        ui->listWidget_4->scrollToItem(ui->listWidget_4->item(playindex));
        //ui->listWidget_4->item(playlist_4->currentIndex())->setSelected(true);
    }
    //music->play();
}


void Widget::on_verticalSlider_valueChanged(int value)
{
    music->setVolume(value);
}

void Widget::on_pushButton_14_clicked()
{
    if(ui->verticalSlider->isHidden())
    {
        ui->verticalSlider->show();
    }
    else
    {
        ui->verticalSlider->hide();
    }
}

void Widget::on_horizontalSlider_valueChanged(int value)
{
}

void Widget::update_position(qint64 position)
{
    ui->horizontalSlider->setValue(position);
    now_time=Time(position);
    ui->label->setText(now_time+"/"+total_time);
}

void Widget::update_duration(qint64 durantion)
{
    ui->horizontalSlider->setRange(0,durantion);
    ui->horizontalSlider->setEnabled(durantion>0);
    ui->horizontalSlider->setPageStep(durantion/10);
    total_time = Time(durantion);
    now_time="00:00";
    ui->label->setText(now_time+"/"+total_time);
}


void Widget::on_pushButton_15_clicked()
{
    QSqlQuery query;
    query.exec("select * from LocalMusic");
    QStringList list=QFileDialog::getOpenFileNames(this,("文件"),"C://",("音频文件(*.mp3)"));
    if(!list.isEmpty())
    {
        for(int t=0;t<list.size();++t)
        {
            QListWidgetItem *item = new QListWidgetItem;
            QString path = QDir::toNativeSeparators(list.at(t));
            if(!path.isEmpty())
            {
                playlist->addMedia(QUrl::fromLocalFile(path));
                QString name = path.split("\\").last();
                name.remove(".mp3");
                item->setText(name);
                item->setIcon(QIcon(":/image/image/Music_32px_1144946_easyicon.net.png"));
                item->setToolTip(name);
                ui->listWidget->addItem(item);
                int id = qrand()%1000000;
                query.exec(QString("insert into LocalMusic values (%1,'%2','%3',%4)").arg(id).arg(name).arg(path).arg(0));
            }
        }
    }
}

void Widget::on_horizontalSlider_sliderMoved(int position)
{

    //music->setPosition(position);
}

void Widget::on_pushButton_15_released()
{

}

void Widget::on_horizontalSlider_sliderReleased()
{
    music->setPosition(ui->horizontalSlider->value());
}

void Widget::on_horizontalSlider_sliderPressed()
{
    music->setPosition(ui->horizontalSlider->value());
}

void Widget::on_pushButton_12_clicked()
{
    if(music->playlist()==playlist)
    {
        if(playlist->playbackMode()==QMediaPlaylist::Loop)
        {
            set_randommode(playlist);
        }
        else if(playlist->playbackMode()==QMediaPlaylist::Random)
        {
            set_listmode(playlist);
        }
        else if (playlist->playbackMode()==QMediaPlaylist::Sequential) {
            set_repeatemode(playlist);
        }
        else if(playlist->playbackMode()==QMediaPlaylist::CurrentItemInLoop)
        {
            set_loopmode(playlist);
        }
    }
    else if(music->playlist()==playlist_2)
    {
        if(playlist_2->playbackMode()==QMediaPlaylist::Loop)
        {
            set_randommode(playlist_2);
        }
        else if(playlist_2->playbackMode()==QMediaPlaylist::Random)
        {
            set_listmode(playlist_2);
        }
        else if (playlist_2->playbackMode()==QMediaPlaylist::Sequential) {
            set_repeatemode(playlist_2);
        }
        else if(playlist_2->playbackMode()==QMediaPlaylist::CurrentItemInLoop)
        {
            set_loopmode(playlist_2);
        }
    }
    else if(music->playlist()==playlist_3)
    {
        if(playlist_3->playbackMode()==QMediaPlaylist::Loop)
        {
            set_randommode(playlist_3);
        }
        else if(playlist_3->playbackMode()==QMediaPlaylist::Random)
        {
            set_listmode(playlist_3);
        }
        else if (playlist_3->playbackMode()==QMediaPlaylist::Sequential) {
            set_repeatemode(playlist_3);
        }
        else if(playlist_3->playbackMode()==QMediaPlaylist::CurrentItemInLoop)
        {
            set_loopmode(playlist_3);
        }
    }
    else if(music->playlist()==playlist_4)
    {
        if(playlist_4->playbackMode()==QMediaPlaylist::Loop)
        {
            set_randommode(playlist_4);
        }
        else if(playlist_4->playbackMode()==QMediaPlaylist::Random)
        {
            set_listmode(playlist_4);
        }
        else if (playlist_4->playbackMode()==QMediaPlaylist::Sequential) {
            set_repeatemode(playlist_4);
        }
        else if(playlist_4->playbackMode()==QMediaPlaylist::CurrentItemInLoop)
        {
            set_loopmode(playlist_4);
        }
    }
}

void Widget::on_lineEdit_returnPressed()
{

}

void Widget::item_double_press()
{

}

void Widget::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    music->setPlaylist(playlist);
    int index;
    for (int t=0;t<ui->listWidget->count();++t) {
        if(ui->listWidget->item(t)==item)
            index=t;
    }
    playlist->setCurrentIndex(index);
    music->play();
}

void Widget::on_listWidget_2_itemDoubleClicked(QListWidgetItem *item)
{
    music->setPlaylist(playlist_2);
    int index=0;
    for (int t=0;t<ui->listWidget_2->count();++t) {
        if(ui->listWidget_2->item(t)==item)
        {
            index=t;
            break;
        }
    }
    playlist_2->setCurrentIndex(index);
    music->play();
}

void Widget::on_listWidget_3_itemDoubleClicked(QListWidgetItem *item)
{
    music->setPlaylist(playlist_3);
    int index;
    for (int t=0;t<ui->listWidget_3->count();++t) {
        if(ui->listWidget_3->item(t)==item)
            index=t;
    }
    playlist_3->setCurrentIndex(index);
    music->play();
}

void Widget::on_listWidget_4_itemDoubleClicked(QListWidgetItem *item)
{
    music->setPlaylist(playlist_4);
    int index;
    for (int t=0;t<ui->listWidget_4->count();++t) {
        if(ui->listWidget_4->item(t)==item)
            index=t;
    }
    playlist_4->setCurrentIndex(index);
    music->play();
}

void Widget::set_music_name()
{
    if(music->playlist()==playlist)
    {
        ui->label_2->setText(ui->listWidget->item(playlist->currentIndex())->text());
        ui->listWidget->item(playlist->currentIndex())->setSelected(true);
    }
    else if(music->playlist()==playlist_2)
    {
        ui->label_2->setText(ui->listWidget_2->item(playlist_2->currentIndex())->text());
        ui->listWidget_2->item(playlist_2->currentIndex())->setSelected(true);
    }
    else if(music->playlist()==playlist_3)
    {
        ui->label_2->setText(ui->listWidget_3->item(playlist_3->currentIndex())->text());
        ui->listWidget_3->item(playlist_3->currentIndex())->setSelected(true);
    }
    else if(music->playlist()==playlist_4)
    {
        ui->label_2->setText(ui->listWidget_4->item(playlist_4->currentIndex())->text());
        ui->listWidget_4->item(playlist_4->currentIndex())->setSelected(true);
    }
}

void Widget::on_pushButton_11_clicked()
{
    if(ui->listWidget->count()==0&&ui->listWidget_2->count()==0&&ui->listWidget_3->count()==0&&ui->listWidget_4->count()==0){
        return;
    }
    if(music->playlist()==playlist)
    {
        int index=playlist->currentIndex();
        model_1->setTable("LocalMusic");
        model_1->select();
        int flag=model_1->data(model_1->index(index,3)).toInt();
        if(flag==0)
        {
            QSqlQuery query;
            QString name = ui->listWidget->item(playlist->currentIndex())->text();
            QString path = model_1->data(model_1->index(index,2)).toString();
            QListWidgetItem *item = new QListWidgetItem;
            item->setText(name);
            item->setIcon(QIcon(":/image/image/like_outline_32px_1101681_easyicon.net.png"));
            item->setToolTip(name);
            ui->listWidget_2->addItem(item);
            playlist_2->addMedia(QUrl::fromLocalFile(path));
            model_1->setData(model_1->index(index,3),1);
            model_1->submitAll();
            ui->pushButton_11->setStyleSheet(like_icon_style());
            //ui->pushButton_11->setToolTip("取消喜欢");
            query.exec("select * from LikeMusic");
            query.exec(QString("insert into LikeMusic values (%1,'%2','%3')").arg(qrand()%10000000).arg(name).arg(path));
        }
        else
        {
              QSqlQuery query;
              model_2->setTable("LikeMusic");
              model_2->select();
              QListWidgetItem *item = ui->listWidget->item(index);
              int row=0;
              for(int t=0;t<ui->listWidget_2->count();t++)
              {
                  if(ui->listWidget_2->item(t)->text()==item->text())
                  {
                      break;
                  }
                  row++;
              }
              if(row>=ui->listWidget_2->count())
              {
                  qDebug()<<"some error happen";
                  return;
              }

              delete ui->listWidget_2->takeItem(row);
              playlist_2->removeMedia(row);
              model_2->revertRow(row);
              model_2->submitAll();
              model_1->setData(model_1->index(index,3),0);
              ui->pushButton_11->setStyleSheet(unlike_icon_style());
              model_1->submitAll();
        }

    }
    else if(music->playlist()==playlist_2)
    {
        QSqlQuery query;
        model_2->setTable("LikeMusic");
        model_2->select();
        model_1->setTable("LocalMusic");
        model_1->select();
        int index = playlist_2->currentIndex();
        for(int t=0;t<ui->listWidget->count();++t)
        {
            if(ui->listWidget->item(t)->text()==ui->listWidget_2->item(index)->text())
            {
                model_1->setData(model_1->index(t,3),0);
                model_1->submitAll();
                break;
            }
        }
        delete  ui->listWidget_2->takeItem(index);
        if(playlist_2->mediaCount()==1)
        {
            on_pushButton_clicked();
            music->setPlaylist(playlist);
            music->pause();
        }
        playlist_2->removeMedia(index);
        model_2->removeRow(index);
        model_2->submitAll();
        if(index<ui->listWidget->count())
        {
            playlist_2->setCurrentIndex(index);
        }
        else {
            playlist_2->setCurrentIndex(0);
        }
    }
}

void Widget::set_like_icon()
{
    if(music->playlist()==playlist_2)
    {
        ui->pushButton_11->setStyleSheet(like_icon_style());
    }
    if(music->playlist()==playlist)
    {
        model_1->setTable("LocalMusic");
        model_1->select();
        int index=playlist->currentIndex();
        int flag = model_1->data(model_1->index(index,3)).toInt();
        if(flag==1)
        {
            ui->pushButton_11->setStyleSheet(like_icon_style());
        }
        else
        {
            ui->pushButton_11->setStyleSheet(unlike_icon_style());
        }
    }
}

void Widget::set_play_icon()
{
    if(music->state()==QMediaPlayer::PausedState)
    {
        ui->pushButton_9->setStyleSheet("QPushButton"
                                         "{"
                                         "background-image: url(:/image/image/image/pase.png);"
                                         "background-repeat:no-repeat;"
                                         "background-position:center center;"
                                         "border:none;"

                                         "}");
        ui->pushButton_9->setToolTip("播放");
    }
    else
    {
        ui->pushButton_9->setStyleSheet("QPushButton"
                                         "{"
                                         "background-image: url(:/image/image/image/播放.png);"
                                         "background-repeat:no-repeat;"
                                         "background-position:center center;"
                                         "border:none;"

                                         "}");
        ui->pushButton_9->setToolTip("暂停");
    }

}

QString Widget::like_icon_style()
{
    return
            "QPushButton"
             "{"
             "background-repeat:no-repeat;"
             "background-position:center center;"
             "border:none;"
             "background-image:url(:/image/image/like_32px_1101682_easyicon.net.png);"
             "}"

             "QPushButton:hover"
             "{"
             "background-repeat:no-repeat;"
             "background-position:center center;"
             "}"
             "QPushButton:pressed"
             "{"
             "background-repeat:no-repeat;"
             "background-position:center center;"
             "background-image:url(:/image/image/image/Ilike.png);"
            "}";
}

QString Widget::unlike_icon_style()
{
    return
            "QPushButton"
             "{"
             "background-repeat:no-repeat;"
             "background-position:center center;"
             "border:none;"
             "background-image:url(:/image/image/image/Ilike.png);"
             "}"

             "QPushButton:hover"
             "{"
             "background-repeat:no-repeat;"
             "background-position:center center;"

             "}"
             "QPushButton:pressed"
             "{"
             "background-repeat:no-repeat;"
             "background-position:center center;"
             "background-image:url(:/image/image/like_32px_1101682_easyicon.net.png);"
            "}";
}

void Widget::resolve_lrc(QString file_name)
{
    ui->listWidget_5->clear();
    lrc_map.clear();
    QString lyrcis =  file_name.remove(file_name.right(3))+"lrc";
    QFile file(lyrcis);
    if(!file.open(QIODevice::ReadOnly))
    {
        return;
    }
    QString all_text = QString(file.readAll());
    file.close();
    QStringList lines = all_text.split("\n");
    QRegExp rx("\\[\\d{2}:\\d{2}\\.\\d{3}\\]");
    foreach(QString line, lines)
    {
        QString temp = line;
        temp.replace(rx,"");
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(temp);
        ui->listWidget_5->addItem(item);
        int pos = rx.indexIn(line,0);
        while (pos!=-1) {
            QString cap = rx.cap(0);
            QRegExp regexp;
            regexp.setPattern("\\d{2}(?=:)");
            regexp.indexIn(cap);
            int minute = regexp.cap(0).toInt();
            regexp.setPattern("\\d{2}(?=\\.)");
            regexp.indexIn(cap);
            int second = regexp.cap(0).toInt();
            regexp.setPattern("\\d{3}(?=\\])");
            regexp.indexIn(cap);
            int millisecond = regexp.cap(0).toInt();
            qint64 totalTime = minute * 60000 + second * 1000 + millisecond;
            // 插入到lrc_map中
            lrc_map.insert(totalTime, temp);
            pos += rx.matchedLength();
            pos = rx.indexIn(line, pos);//匹配全部

        }
    }
}

void Widget::update_time()
{
    qint64 total_time_value = music->duration();
    qint64 time = music->position();
    if(!lrc_map.isEmpty()) {
            // 获取当前时间在歌词中的前后两个时间点
        qint64 previous = 0;
        qint64 later = 0;
        //keys()方法返回lrc_map列表
        foreach (qint64 value, lrc_map.keys()) {
            if (time >= value) {
                previous = value;
            } else {
                later = value;
                break;
            }
        }
        if (later == 0)
            later = total_time_value;
        QString current_lrc = lrc_map.value(previous);
        if(ui->listWidget_5->currentItem()==nullptr)
            ui->listWidget_5->setCurrentRow(0);

        if(current_lrc!=ui->listWidget_5->currentItem()->text())
        {
            int row = ui->listWidget_5->currentRow()+1;
            ui->listWidget_5->setCurrentRow(row);
            ui->listWidget_5->currentItem()->setSelected(true);

            ui->listWidget_5->scrollToItem(ui->listWidget_5->currentItem(),QAbstractItemView::PositionAtCenter);
        }
    }
}

void Widget::set_lrc()
{
    QString path = music->currentMedia().request().url().toString();
    path.replace("file:///","");
    resolve_lrc(path);
    previous_time=0;
}

void Widget::on_pushButton_16_clicked()
{
    bool flag = false;
    QString text = ui->lineEdit->text();
    ui->listWidget_4->clear();
    ui->pushButton_7->click();
    if(!text.isEmpty())
    {
        std::string music_name = text.toStdString().c_str();
        int count = ui->listWidget->count();
        for(int t =0;t < count; ++t)
        {
            QListWidgetItem *item = ui->listWidget->item(t);
            std::string item_name = item->text().toStdString();
            int position = item_name.find(music_name);
            if(position!=std::string::npos)
            {
                if(flag==false)
                    playlist_4->clear();
                flag = true;
                model_1->setTable("LocalMusic");
                model_1->select();
                playlist_4->addMedia(QUrl::fromLocalFile(model_1->data(model_1->index(t,2)).toString()));
                qDebug()<<model_1->data(model_1->index(t,2)).toString();
                QListWidgetItem *cur_item = new QListWidgetItem(item->icon(),item->text());
                ui->listWidget_4->addItem(cur_item);
            }
        }

    }
}

void Widget::on_pushButton_13_clicked()
{
    if(music->playlist()==playlist)
        ui->pushButton->click();
    else if(music->playlist()==playlist_2)
        ui->pushButton_5->click();
    else if(music->playlist()==playlist_3)
        ui->pushButton_6->click();
    else
        ui->pushButton_7->click();
}

void Widget::on_pushButton_17_clicked()
{
    QString FileName=QFileDialog::getOpenFileName(this,("文件"),"C://",("图片文件(*jpg *png)"));
    if(!FileName.isEmpty())
    {
        ui->frame->setStyleSheet(QString("QFrame#frame{border-radius:5px;border-image: url(%1);}").arg(FileName));
    }
}
