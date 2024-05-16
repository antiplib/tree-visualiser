//
// Created by Владислав Отвагин on 21.04.2024.
//
#ifndef AVL_H
#define AVL_H

#pragma once

#include <iostream>
#include <valarray>
struct avl {
 int cu;
 int x = 0;
 int y = 0;
 int key;
 int height;
 avl * left = 0;
 avl * right  = 0;
 avl(int key) {
  this->key = key;
  this->height = 1;
  this->right = nullptr;
  this->left = nullptr;
 }
 int level = 0;
};
extern void fix_height(avl * p);
extern int b_facror(avl *p);
extern avl* right_rotate(avl* p);
extern avl* left_rotate(avl*p);
extern avl* insert(avl *p, int key);
extern avl* balancde(avl*p);
extern void fix_level(avl* tree);
extern int get_width_avl(avl *p, int width, int key);
extern int get_level_avl(avl *p, int key);
extern avl* remove(avl*p, int key);
extern int64_t avl_bin_power(int n);
extern void fill_curr_avl(avl*tree, int &curr );
extern avl* get_curr(avl*tree, int key);



#endif //AVL_H
