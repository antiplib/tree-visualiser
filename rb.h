//
// Created by Владислав Отвагин on 12.05.2024.
//

#ifndef RB_H
#define RB_H



class rb {
public:
    int key;
    int hight;
    int level = 0;
    int x, y;
    bool is_red;
    int cu;
    rb*left;
    rb*right;
    rb*parent;
    rb();
    rb(int key, rb* parent = nullptr);
    ~rb();
};
void update_hight_rb(rb* tree);

rb*remove(rb*tree, int key);
rb*add(rb*tree, int key);
rb*get_uncle(rb*tree);
rb*get_brother(rb*tree);
rb*get_grandpa(rb*tree);
rb*get_right_nep(rb*tree);
rb*get_left_nep(rb*tree);
rb*left_rotate(rb*tree);
rb*right_rotate(rb*tree);
void fix_level(rb*tree);
int get_width_rb(rb *p, int width, int key);
int get_level_rb(rb *p, int key);
rb* balance_after_add(rb* curr, rb* root);
extern void fill_curr_rb(rb*tree, int &curr);
extern rb* get_curr_rb(rb*tree, int key);
#endif //RB_H
