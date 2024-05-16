//
// Created by Владислав Отвагин on 20.04.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainwindow.h" resolved

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <ctime>
#include <random>
#include "kurevo.h"

mainwindow::mainwindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::mainwindow) {
    ui->setupUi(this);

    rb_button = new QPushButton(this);
    rb_button ->setGeometry(100, 175, 175, 50);
    rb_button -> setStyleSheet("background-color: rgba(255, 105, 180, 180); font-size: 20px; color: black; border-radius:15px;");
    rb_button ->setText("rb tree");

    avl_button = new QPushButton(this);
    avl_button ->setGeometry(325, 175, 175, 50);
    avl_button -> setStyleSheet("background-color: rgba(255, 105, 180, 180); font-size: 20px; color: black; border-radius: 15px;");
    avl_button ->setText("avl tree");

    kurevo_button = new QPushButton(this);
    kurevo_button ->setGeometry(100, 300, 175, 50);
    kurevo_button -> setStyleSheet("background-color: rgba(255, 105, 180, 180); font-size: 20px; color: black; border-radius: 15px;");
    kurevo_button ->setText("kurevo tree");

    splay_button = new QPushButton(this);
    splay_button ->setGeometry(325, 300, 175, 50);
    splay_button -> setStyleSheet("background-color: rgba(255, 105, 180, 180); font-size: 20px; color: black; border-radius: 15px;");
    splay_button ->setText("splay tree");

    select_tree = new QLabel(this);
    select_tree -> setGeometry(225, 50, 200, 50);
    select_tree -> setText("select tree");
    select_tree -> setStyleSheet("QLabel{font-size: 30pt;} ");

    rb_tree = new tree_space(nullptr);
    kurevo_tree = new tree_space(nullptr);
    avl_tree = new tree_space(nullptr);
    splay_tree = new tree_space(nullptr);

    rb_tree->setWindowTitle("rb_tree");
    avl_tree->setWindowTitle("avl_tree");
    splay_tree->setWindowTitle("splay_tree");
    kurevo_tree->setWindowTitle("kurevo_tree");

    rb_tree->kurevo_change = kurevo_tree;
    rb_tree->avl_change = avl_tree;
    rb_tree->splay_change = splay_tree;

    avl_tree->kurevo_change = kurevo_tree;
    avl_tree->rb_change = rb_tree;
    avl_tree->splay_change = splay_tree;

    splay_tree->kurevo_change = kurevo_tree;
    splay_tree->rb_change = rb_tree;
    splay_tree->avl_change = avl_tree;

    kurevo_tree->rb_change = rb_tree;
    kurevo_tree->avl_change = avl_tree;
    kurevo_tree->splay_change = splay_tree;

    connect(rb_button, &QPushButton::clicked, this, &mainwindow::select_rb_tree);
    connect(avl_button, &QPushButton::clicked, this, &mainwindow::select_avl_tree);
    connect(splay_button, &QPushButton::clicked, this, &mainwindow::select_splay_tree);
    connect(kurevo_button, &QPushButton::clicked, this, &mainwindow::select_kurevo_tree);
}

mainwindow::~mainwindow() {
    delete ui;
}

void mainwindow::select_rb_tree() {
    rb_tree->show();
    this->hide();

}

void mainwindow::select_avl_tree() {
    avl_tree->show();
    this->hide();

}

void mainwindow::select_kurevo_tree() {
    kurevo_tree->show();
    this->hide();

}

void mainwindow::select_splay_tree() {
    splay_tree->show();
    this->hide();

}




