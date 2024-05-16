
#include "tree_space.h"
#include <future>
#include "ui_tree_space.h"
#include <QLocale>
#include <QMessageBox>
#include <queue>
#include <QInputDialog>
#include "mainwindow.h"
#include <QFont>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include <qgraphicsitem.h>
#include <QMouseEvent>
#include "Item.h"
#include <random>
#include <QWheelEvent>
std::mt19937 mt(52);

tree_space::tree_space(QWidget *parent) :
    QWidget(parent), ui(new Ui::tree_space) {
    ui->setupUi(this);

    // QTimer {
    // if (mouse.pos
    // connect(isMousePressed, timer.start);
    //

    space = new QGraphicsView(this);
    space->setGeometry(25, 100, 550, 450);
    scene = new QGraphicsScene;
    space->setScene(scene);

    icon = new QPixmap;
    icon->load("/Users/antiplib/CLionProjects/tree-visuliaser/set.png");

    settings_icon = new QLabel(this);
    settings_icon->setGeometry(30, 10, 30, 30);
    settings_icon->setPixmap(*icon);
    settings_icon->setStyleSheet("border-radius: 20px;");

    any_items = new QPushButton(this);
    any_items->setGeometry(350, 40,  100, 50);
    any_items -> setStyleSheet("QPushButton {"
                              "background-color: #4B0082;"
                              "border-radius: 10px;"
                              "}");
    any_items->setText("add any elems");

    open_select_tree = new QPushButton(this);
    open_select_tree->setGeometry(25, 10, 30, 30);
    open_select_tree->setStyleSheet("QPushButton {"
                            "background-color: rgba(255, 255, 255, 0);"
                                    "border-radius: 20px;"
                                    "}");

    settings = new QLabel(this);
    settings->setGeometry(25, 10, 100, 200);
    settings->setStyleSheet("QLabel {"
                            "background-color: #000000;"
                            "border-radius: 15px;"
                            "}");
    settings->hide();

    close_select_tree = new QPushButton(settings);
    close_select_tree->setGeometry(85, 5, 10, 10);
    close_select_tree->setText("X");
    close_select_tree->setStyleSheet("QPushButton {"
                                     "background-color: red; "
                                     "border-radius: 3px;"
                                     "}");

    new_elem = new QPushButton(this);
    new_elem->setGeometry(475, 40,  100, 50);
    new_elem->setText("add elem");
    new_elem -> setStyleSheet("QPushButton {"
                              "background-color: #4B0082;"
                              "border-radius: 10px;"
                              "}");

    line_edit = new QLineEdit(this);
    line_edit->setGeometry(475, 10, 100, 25);
    line_edit->setStyleSheet("QLineEdit {"
                             "border-radius: 10px;"
                             "}");

    change_on_avl = new QPushButton(settings);
    change_on_avl->setGeometry(25, 15, 50, 30);
    change_on_avl->setText("avl");
    change_on_avl->setStyleSheet("QPushButton{"
                                    "background-color: #4B0082;"
                                    "border-radius: 7px;"
                                    "}");

    change_on_rb = new QPushButton(settings);
    change_on_rb->setGeometry(25, 50, 50, 30);
    change_on_rb->setText("rb");
    change_on_rb->setStyleSheet("QPushButton{"
                                    "background-color: #4B0082;"
                                    "border-radius: 7px;"
                                    "}");;

    change_on_kurevo = new QPushButton(settings);
    change_on_kurevo->setGeometry(25, 85, 50, 30);
    change_on_kurevo->setText("kurevo");
    change_on_kurevo->setStyleSheet("QPushButton{"
                                    "background-color: #4B0082;"
                                    "border-radius: 7px;"
                                    "}");

    change_on_splay = new QPushButton(settings);
    change_on_splay->setGeometry(25, 120, 50, 30);
    change_on_splay->setText("splay");
    change_on_splay->setStyleSheet("QPushButton{"
                                    "background-color: #4B0082;"
                                    "border-radius: 7px;"
                                    "}");

    clear = new QPushButton(settings);
    clear->setGeometry(25, 155, 50, 30);
    clear->setStyleSheet("QPushButton{"
                                    "background-color: #8B0000;"
                                    "border-radius: 7px;"
                                    "}");
    clear->setText("clear");
    clear->setEnabled(false);

    space->centerOn(3000, 50);
    connect(clear, &QPushButton::clicked,
        this, &tree_space::clear_space);
    connect(change_on_avl, &QPushButton::clicked,
        this, &tree_space::Change_on_avl);
    connect(change_on_splay, &QPushButton::clicked,
        this, &tree_space::Change_on_splay);
    connect(change_on_kurevo, &QPushButton::clicked,
        this, &tree_space::Change_on_kurevo);
    connect(change_on_rb, &QPushButton::clicked,
        this, &tree_space::Change_on_rb);
    connect(new_elem, &QPushButton::clicked,
        this, &tree_space::add_elem);
    connect(close_select_tree, &QPushButton::clicked,
        this, &tree_space::close_settings);
    connect(open_select_tree, &QPushButton::clicked,
        this, &tree_space::open_settings);
    connect(any_items, &QPushButton::clicked,
        this, &tree_space::add_any_elems);
    srand(time(0));
}

tree_space::~tree_space() {
    delete ui;
}

void tree_space::open_settings() {
    change_on_avl->setEnabled(true);
    change_on_rb->setEnabled(true);
    change_on_kurevo->setEnabled(true);
    change_on_splay->setEnabled(true);

    if(this->avl_change == nullptr) {
        this->change_on_avl->setEnabled(false);
    }
    if(this->rb_change == nullptr) {
        this->change_on_rb->setEnabled(false);
    }
    if(this->kurevo_change == nullptr) {
        this->change_on_kurevo->setEnabled(false);
    }
    if(this->splay_change == nullptr) {
        this->change_on_splay->setEnabled(false);
    }
    settings_icon->hide();
    settings->show();
}

void tree_space::close_settings() {
    settings_icon->show();
    settings->hide();
}

void tree_space::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Equal) {
        space->scale(1.4,1.4);
    } else if (event->key() == Qt::Key_Minus) {
        space->scale(.8, .8);
    }
}
void tree_space::wheelEvent(QWheelEvent *event)
{

    // Scale the view / do the zoom
    const double scaleFactor = 1.05;
    int numDegrees = event->angleDelta().y() / 7;
    int numSteps = numDegrees;

    if(numSteps > 0)
    {
        space->scale(1.0 / scaleFactor  , 1.0 / scaleFactor);

    }
    else if(numSteps < 0)
    {
        space->scale(scaleFactor , scaleFactor);

    }
}
void tree_space::add_elem() {
    clear->setEnabled(true);

    std::string n = line_edit->text().toStdString();
    if(n.size() == 0) {
        return;
    }
    int ans = 0;
    if(n[0] == '-') {
        for(int i = 1; i < n.size(); ++i) {
            ans += n[i] - '0';
            ans*=10;
        }
        ans/=10;
        ans = -ans;
    } else {
        for(int i = 0; i < n.size(); ++i) {
            ans += n[i] - '0';
            ans*=10;
        }
        ans/=10;

    }
    bool flag_s_in_keys = false;
    for(int i = 0; i < keys.size(); ++i) {
        if(keys[i] == ans) {
            flag_s_in_keys = true;
            break;
        }
    }
    if(!flag_s_in_keys) {
        if(!avl_change) {
            avl_tree = insert(avl_tree, ans);
            keys.push_back(ans);
            print_tree();
        }
        if(!splay_change) {
            splay_tree = insert(splay_tree, ans);
            keys.push_back(ans);
            print_tree();
        }
        if(!kurevo_change) {
            kurevo_tree = insert(kurevo_tree, ans,
                mt() % 10000000);
            keys.push_back(ans);
            print_tree();
        }
        if(!rb_change) {
            rb_tree = add(rb_tree, ans);
            keys.push_back(ans);
            print_tree();
        }
    }

}

int64_t bin_power(int n) {
    if(n == 0) {
        return 1;
    }
    return 2*bin_power(n-1);
}

void tree_space::print_avl() {
    if(!avl_tree) return;
    avl_tree->level = 0;
    fix_level(avl_tree);
    int c = 0;
    fill_curr_avl(avl_tree, c);
    int wide = 0;
    int max = 0;
    int ymax = 0;
    for(int i = 0; i < keys.size(); ++i) {
        int level = get_level_avl(avl_tree, keys[i]);
        int width = get_curr(avl_tree, keys[i])->cu * 20;
        if(width > max) {
            max = width;
        }
        if(level*90 > ymax) {
            ymax = level*90;
        }
        item = new Item(width, level*90, keys[i],
            0, 0, 0, 0,nullptr);
        scene->addItem(item);
        avl* search = avl_tree;
        while(search->key != keys[i]) {
            if(search->key > keys[i]) {
                search = search->left;
            } else {
                search = search->right;
            }
        }
        search->x = width;
        search->y = level * 90;
        connect(item, &Item::signal1,
        this, [this](bool){
            QPoint cursorPos = QCursor::pos();
            slot_of_Item(cursorPos.x(), cursorPos.y());
        });
        //add lines
    }
        for(int j = 0; j < keys.size(); ++j) {
            avl* search = avl_tree;
            while(search->key != keys[j]) {
                if(search->key > keys[j]) {
                    search = search->left;
                } else {
                    search = search->right;
                }
            }
            int x, y;
            x = search->x;
            y = search->y;
            QPen pen(Qt::white);

            if(search->right) {
                scene->addLine(x + 15, y+ 30, search->right->x + 15, search->right->y, pen);
            }
            if(search->left) {
                scene->addLine(x + 15, y + 30, search->left->x + 15, search->left->y, pen);
            }

    }

    space->setSceneRect (0,0,max + 50, ymax );
    //space->centerOn(avl_tree->x,avl_tree->y);

}
void tree_space::print_splay() {
    if(!splay_tree) return;
    splay_tree->level = 0;
    update_hight_splay(splay_tree);
    update_level_splay(splay_tree);
    int t = 0;
    fill_curr_splay(splay_tree, t);
    int wide = 0;
    int max =0 ;
    int ymax = 0;
    for(int i = 0; i < keys.size(); ++i) {
        int level = get_level_splay(splay_tree, keys[i]);
        int width = get_curr_splay(splay_tree,keys[i])->cu * 20;
        item = new Item(width, level*90, keys[i], 0,
            0, 0, 0,nullptr);
        if(width > max) max = width;
        if(level*90 > ymax) ymax = level*90;
        scene->addItem(item);
        splay* search = splay_tree;
        while(search->key != keys[i]) {
            if(search->key > keys[i]) {
                search = search->left;
            } else {
                search = search->right;
            }
        }
        search->x = width ;
        search->y = level * 90;
        connect(item, &Item::signal1,
        this, [this](bool){
            QPoint cursorPos = QCursor::pos();
            slot_of_Item(cursorPos.x(), cursorPos.y());
        });
    }
    for(int j = 0; j < keys.size(); ++j) {
        splay* search = splay_tree;
        while(search->key != keys[j]) {
            if(search->key > keys[j]) {
                search = search->left;
            } else {
                search = search->right;
            }
        }
        int x, y;
        x = search->x;
        y = search->y;
        QPen pen(Qt::white);

        if(search->right) {
            scene->addLine(x + 15, y+ 30, search->right->x + 15, search->right->y, pen);
        }
        if(search->left) {
            scene->addLine(x + 15, y + 30, search->left->x + 15, search->left->y, pen);
        }

    }


    space->setSceneRect (0,0,max + 50, ymax );
    //space->centerOn(splay_tree->x,splay_tree->y);
}

void tree_space::print_kurevo() {
    if(!kurevo_tree) return;
    kurevo_tree->level = 0;
    update_hight_kurevo(kurevo_tree);
    update_level_kurevo(kurevo_tree);
    int i = 0;
    fill_curr_kurevo(kurevo_tree, i );
    int wide = 0;
    int max = 0, ymax = 0;
    for(int i = 0; i < keys.size(); ++i) {
        int level = get_level_kurevo(kurevo_tree, keys[i]);
        int width = get_curr_kurevo(kurevo_tree, keys[i])->cu * 20;
        if(max < width) {
            max = width;
        }
        if(ymax < level*90) {
            ymax = level*90;
        }
        item = new Item(width, level*90, keys[i],
            1,get_prior(kurevo_tree, keys[i]),  0, 0,nullptr);
        scene->addItem(item);
        kurevo* search =kurevo_tree;
        while(search->key != keys[i]) {
            if(search->key > keys[i]) {
                search = search->left;
            } else {
                search = search->right;
            }
        }
        search->x = width ;
        search->y = level * 90;
        connect(item, &Item::signal1,
        this, [this](bool){
            QPoint cursorPos = QCursor::pos();
            slot_of_Item(cursorPos.x(), cursorPos.y());
        });

    }
    for(int j = 0; j < keys.size(); ++j) {
        kurevo* search = kurevo_tree;
        while(search->key != keys[j]) {
            if(search->key > keys[j]) {
                search = search->left;
            } else {
                search = search->right;
            }
        }
        int x, y;
        x = search->x;
        y = search->y;
        QPen pen(Qt::white);
        if(search->right) {
            scene->addLine(x + 15, y+ 30, search->right->x + 15, search->right->y, pen);
        }
        if(search->left) {
            scene->addLine(x + 15, y + 30, search->left->x + 15, search->left->y, pen);
        }
    }
    //space->centerOn(kurevo_tree->x,kurevo_tree->y);

    space->setSceneRect (0,0,max + 50, ymax );
    }

void tree_space::print_rb() {
    if(!rb_tree) return;
    rb_tree->level = 0;
    update_hight_rb(rb_tree);
    fix_level(rb_tree);
    int i = 0;
    fill_curr_rb(rb_tree, i);
    int wide = 0;
    int max = 0, ymax = 0;
    for(int i = 0; i < keys.size(); ++i) {
        int level = get_level_rb(rb_tree, keys[i]);
        int width = get_curr_rb(rb_tree, keys[i])->cu * 20;
        if(max < width) {
            max = width;
        }
        if(ymax < level*90) {
            ymax = level*90;
        }
        rb* search = rb_tree;
        while(search->key != keys[i]) {
            if(search->key > keys[i]) {
                search = search->left;
            } else {
                search = search->right;
            }
        }
        item = new Item(width, level*90, keys[i],
            0, 0, 1, search->is_red,nullptr);
        scene->addItem(item);
        search->x = width ;
        search->y = level * 90;
        connect(item, &Item::signal1,
        this, [this](bool){
            QPoint cursorPos = QCursor::pos();
            slot_of_Item(cursorPos.x(), cursorPos.y());
        });
        //add lines
    }
    for(int j = 0; j < keys.size(); ++j) {
        rb* search = rb_tree;
        while(search->key != keys[j]) {
            if(search->key > keys[j]) {
                search = search->left;
            } else {
                search = search->right;
            }
        }
        int x, y;
        x = search->x;
        y = search->y;
        QPen pen(Qt::white);

        if(search->right) {
            scene->addLine(x + 15, y+ 30, search->right->x + 15, search->right->y, pen);
        }
        if(search->left) {
            scene->addLine(x + 15, y + 30, search->left->x + 15, search->left->y, pen);
        }

    }

    space->setSceneRect (0,0,max + 50, ymax );
}


void tree_space::print_tree() {
    scene->clear();

    if(!avl_change) {
        print_avl();
    }
    if(!splay_change) {
        print_splay();
    }
    if(!kurevo_change) {
        print_kurevo();
    }
    if(!rb_change) {
        print_rb();
    }
}


void tree_space::Change_on_avl() {
    if(this->avl_change != nullptr) {
        this->avl_change->show();
        this->hide();
    }
}

void tree_space::Change_on_rb() {
    if(this->rb_change != nullptr) {
        this->rb_change->show();
        this->hide();
    }
}
void tree_space::Change_on_splay() {
    if(this->splay_change != nullptr) {
        this->splay_change->show();
        this->hide();

    }
}
void tree_space::Change_on_kurevo() {
    if(this->kurevo_change != nullptr) {
        this->kurevo_change->show();
        this->hide();

    }
}

void tree_space::add_any_elems() {
    srand(time(NULL));

    int n;
    bool is_active_clear = clear->isEnabled();
    clear->setEnabled(true);
    n = QInputDialog::getInt(this, "cnt", "->");
    if(n == 0) {
        clear->setEnabled(false);
    }

    for(int i = 0; i < n; ++i) {
        int q = rand()%(n*10);
        bool is = false;
        int cnt = 0;
        for(int j = 0; j < keys.size(); ++j) {
            ++cnt;
            if(keys[j] == q) {
                --i;
                is = true;
                break;
            }
        }
        if(is) {
            continue;
        }
        if(!avl_change) {
            avl_tree = insert(avl_tree, q);
        }
        if(!splay_change) {
            splay_tree = insert(splay_tree, q);
        }
        if(!kurevo_change) {
            kurevo_tree = insert(kurevo_tree, q, rand()%(n*1000));
        }
        if(!rb_change) {
            rb_tree = add(rb_tree, q);
        }
        keys.push_back(q);
    }
    print_tree();
    if(is_active_clear) {
        clear->setEnabled(true);
    }
}

void tree_space::clear_space() {
    clear->setEnabled(false);
    if(!avl_change) {
        if(avl_tree ==  nullptr) {
            return;
        }
        for(int i = 0; i < keys.size(); ++i) {
                avl_tree = remove(avl_tree, keys[i]);
        }
        keys.clear();
        avl_tree = nullptr;
        print_tree();
    }
    if(!splay_change) {
        if(splay_tree ==  nullptr) {
            return;
        }
        for(int i = 0; i < keys.size(); ++i) {
            splay_tree = del(splay_tree, keys[i]);
        }
        keys.clear();
        splay_tree = nullptr;
        print_tree();
    }
    if(!kurevo_change) {
        if(kurevo_tree ==  nullptr) {
            return;
        }
        for(int i = 0; i < keys.size(); ++i) {
            kurevo_tree = remove(kurevo_tree, keys[i]);
        }
        keys.clear();
        kurevo_tree = nullptr;
        print_tree();
    }
    if(!rb_change) {
        if(rb_tree ==  nullptr) {
            return;
        }
        for(int i = 0; i < keys.size(); ++i) {
            rb_tree = remove(rb_tree, keys[i]);
        }
        keys.clear();
        rb_tree = nullptr;
        print_tree();
    }
}

void tree_space::slot_of_Item(int xx, int yy) {
    yy-=270;
    xx-=460;
    int x = space->mapToScene(xx, yy).x() ;
    int y = space->mapToScene(xx, yy).y() ;
    if(!avl_change) {
        avl* p = avl_tree;
        while(p) {
            if(p->y <= y && p->y + 30 >= y) {
                if(x <= p->x + 30 && x >= p->x) {
                    for(int i = 0; i < keys.size(); ++i) {
                        if(keys[i] == p->key) {
                            keys.erase(keys.begin()+i);
                            break;
                        }
                    }
                    int k = p->key;
                    p = nullptr;
                    avl_tree = remove(avl_tree, k);
                    break;
                } else {
                    return;
                }
            }
            else if(x <= p->x + 15) {
                p = p->left;
            } else if(x>= p->x+15) {
                p = p->right;
            }
        }
        if(keys.size() == 0) clear->setEnabled(false);
        print_tree();
    }
    if(!splay_change) {
        splay* p = splay_tree;
        while(p) {
            if(p->y <= y && p->y + 30 >= y) {
                if(x <= p->x + 30 && x >= p->x) {
                    for(int i = 0; i < keys.size(); ++i) {
                        if(keys[i] == p->key) {
                            keys.erase(keys.begin()+i);
                            break;
                        }
                    }
                    int k = p->key;
                    p = nullptr;
                    splay_tree = del(splay_tree, k);
                    break;
                } else {
                    return;
                }
            }
            else if(x <= p->x + 15) {
                p = p->left;
            } else if(x>= p->x+15) {
                p = p->right;
            }
        }
        if(keys.size() == 0) clear->setEnabled(false);
        print_tree();
    }
    if(!kurevo_change) {
        kurevo* p = kurevo_tree;
        while(p) {
            if(p->y <= y && p->y + 30 >= y) {
                if(x <= p->x + 30 && x >= p->x) {
                    for(int i = 0; i < keys.size(); ++i) {
                        if(keys[i] == p->key) {
                            keys.erase(keys.begin()+i);
                            break;
                        }
                    }
                    int k = p->key;
                    p = nullptr;
                    kurevo_tree = remove(kurevo_tree, k);
                    break;
                } else {
                    return;
                }
            }
            else if(x <= p->x + 15) {
                p = p->left;
            } else if(x>= p->x+15) {
                p = p->right;
            }
        }
        if(keys.size() == 0) clear->setEnabled(false);
        print_tree();
    }
    if(!rb_change) {
        rb* p = rb_tree;
        while(p) {
            if(p->y <= y && p->y + 30 >= y) {
                if(x <= p->x + 30 && x >= p->x) {
                    for(int i = 0; i < keys.size(); ++i) {
                        if(keys[i] == p->key) {
                            keys.erase(keys.begin()+i);
                            break;
                        }
                    }
                    int k = p->key;
                    p = nullptr;
                    rb_tree = remove(rb_tree, k);
                    break;
                } else {
                    return;
                }
            }
            else if(x <= p->x + 15) {
                p = p->left;
            } else if(x>= p->x+15) {
                p = p->right;
            }
        }
        if(keys.size() == 0) clear->setEnabled(false);
        print_tree();
    }
}
