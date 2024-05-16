//
// Created by Владислав Отвагин on 20.04.2024.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <utility>
#include <random>
#include "tree_space.h"
QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE

class mainwindow : public QMainWindow {
Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = nullptr);
    ~mainwindow() override;
    QPushButton *rb_button;
    QPushButton *avl_button;
    QPushButton *kurevo_button;
    QPushButton *splay_button;
    QLabel *select_tree;
    tree_space *rb_tree;
    tree_space *avl_tree;
    tree_space *kurevo_tree;
    tree_space *splay_tree;
private:
    void select_rb_tree();
    void select_avl_tree();
    void select_kurevo_tree();
    void select_splay_tree();
    Ui::mainwindow *ui;
};


#endif //MAINWINDOW_H
