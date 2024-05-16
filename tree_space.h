//
// Created by Владислав Отвагин on 20.04.2024.
//

#ifndef TREE_SPACE_H
#define TREE_SPACE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QKeyEvent>
#include <QlineEdit>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>
#include "avl.h"
#include "Item.h"
#include "splay.h"
#include "kurevo.h"
#include "rb.h"

QT_BEGIN_NAMESPACE
namespace Ui { class tree_space; }
QT_END_NAMESPACE

class tree_space : public QWidget {
Q_OBJECT

public:
    explicit tree_space(QWidget *parent = nullptr);
    ~tree_space() override;
    avl *avl_tree;
    splay* splay_tree;
    kurevo* kurevo_tree;
    rb*rb_tree;
    QPushButton *any_items;
    QLabel *settings_icon;
    QLabel *settings;
    QPushButton *rb_button;
    QPushButton *avl_button;
    QPushButton *kurevo_button;
    QPushButton *splay_button;
    QPushButton *open_select_tree;
    QPushButton *close_select_tree;
    QPixmap *icon;
    QKeyEvent *plus_pressed;
    QKeyEvent *minus_pressed;
    QLineEdit *line_edit;
    QPushButton *new_elem;
    QGraphicsView *space;
    QGraphicsScene *scene;
    QPushButton *elem;
    QPushButton* change_on_avl;
    QPushButton* change_on_rb;
    QPushButton* change_on_splay;
    QPushButton* change_on_kurevo;
    std::vector <QPushButton> array_of_buttons;
    tree_space *rb_change = nullptr, *splay_change = nullptr,
    *kurevo_change = nullptr, *avl_change = nullptr;
    std::vector <int> keys = {};
    QPushButton * clear;
    Item * item;
    QGraphicsEllipseItem* ellipse;
    void slot_of_Item(int, int);
private:
    Ui::tree_space *ui;
    void print_kurevo();
    void print_avl();
    void print_splay();
    void print_rb();
    void clear_space();
    void print_tree();
    void Change_on_kurevo();
    void Change_on_rb();
    void Change_on_avl();
    void Change_on_splay();
    void open_settings();
    void close_settings();
    void add_elem();
    void add_any_elems();
    void del_etem(QPushButton * item);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
// signals:
//    void isMousePressed();
// public:
//    pair<int, int> getMousePos();
};


#endif //TREE_SPACE_H
