#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QSqlTableModel>
#include <QListWidgetItem>
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void item_double_press();
    void resolve_lrc(QString file_name);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();

    void on_verticalSlider_sliderMoved(int position);

    void on_verticalSlider_valueChanged(int value);

    void on_pushButton_14_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void update_position(qint64 position);

    void update_duration(qint64 duration);
    void on_pushButton_15_clicked();

    void on_pushButton_150_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_pushButton_15_released();

    void on_horizontalSlider_sliderReleased();

    void on_horizontalSlider_sliderPressed();

    void on_pushButton_12_clicked();

    void on_lineEdit_returnPressed();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_2_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_3_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_4_itemDoubleClicked(QListWidgetItem *item);

    void set_music_name();

    void on_pushButton_11_clicked();

    void set_like_icon();

    void set_play_icon();

    void set_lrc();

    void update_time();

    void on_pushButton_16_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_17_clicked();

private:
    Ui::Widget *ui;
    QPoint locate;
    QMediaPlayer *music=NULL;//音乐
    QString total_time;
    QString now_time;
    QMap<qint64,QString> lrc_map;
    QMediaPlaylist *playlist=NULL;//播放列表1
    QMediaPlaylist *playlist_2=NULL;//播放列表2
    QMediaPlaylist *playlist_3=NULL;//播放列表3
    QMediaPlaylist *playlist_4 = NULL;//历史
    QSqlTableModel *model_1;
    QSqlTableModel *model_2;
    QSqlTableModel *model_3;
    inline void init_space();
    inline void init_list();
    inline void init_else();
    void init_connect();
    void set_randommode(QMediaPlaylist *l);
    void set_listmode(QMediaPlaylist *l);
    void set_repeatemode(QMediaPlaylist *l);
    void set_loopmode(QMediaPlaylist *l);
    void button_5_released();
    void button_released();
    void button_6_released();
    void button_7_released();
    QString Time(qint64 time);
    QString like_icon_style();
    QString unlike_icon_style();
    qint64 previous_time;
    qint64 time_interval;
    QList<qint64> list;
};
#endif // WIDGET_H
