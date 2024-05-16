//
// Created by Владислав Отвагин on 08.05.2024.
//

#ifndef SPLAY_H
#define SPLAY_H



class splay {

public:
    splay();
    splay(int key);
    ~splay();
    int level;
    int hight;
    int key;
    int x, y;
    int cu;
    splay* right = 0;
    splay * left = 0;

};
extern splay*left_rotate(splay*p);
extern splay* right_rotate(splay*p);
extern splay* sp(splay* tree, int key);
extern splay* insert(splay* tre, int key);
extern splay* del(splay*tree, int key);
extern splay *find(splay*tree, int key);
extern splay* findmin(splay*tree);
extern splay* removemin(splay*tree);
extern splay* merge(splay* t1, splay* t2);
extern int get_level_splay(splay*tree, int key);
extern void update_level_splay(splay*tree);
extern void update_hight_splay(splay*tree);
extern int get_width_splay(splay*tree, int width, int key);
extern void fill_curr_splay(splay*tree, int &curr );
extern splay* get_curr_splay(splay*tree, int key);

#endif //SPLAY_H
