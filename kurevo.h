//
// Created by Владислав Отвагин on 21.04.2024.
//

#ifndef KUREVO_H
#define KUREVO_H
#include <utility>


class kurevo {
public:
    int hight;
    int level;
    int key;
    int prior;
    int x, y;
    int cu;
    kurevo* left;
    kurevo*right;
    kurevo();
    kurevo(int key);
    kurevo(int key, int p);
    ~kurevo();

};

extern kurevo* merge(kurevo* one, kurevo*two);
extern std::pair <kurevo*, kurevo*> split(kurevo*tree, int key);
extern kurevo*insert(kurevo* tree, int key, int p);
extern kurevo*remove(kurevo* tree, int key);
extern void update_hight_kurevo(kurevo*tree);
extern int get_level_kurevo(kurevo*tree, int key);
extern void update_level_kurevo(kurevo *tree);
extern int get_width_kurevo(kurevo* tree, int wide, int key);
extern int get_prior(kurevo*tree, int key);
extern void fill_curr_kurevo(kurevo*tree, int &curr );
extern kurevo* get_curr_kurevo(kurevo*tree, int key);
#endif //KUREVO_H
