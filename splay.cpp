//
// Created by Владислав Отвагин on 08.05.2024.
//

#include "splay.h"
#include "avl.h"
#include <QtCore/qcompilerdetection.h>

splay::splay() {
    this-> left = this->right = 0;
}

 splay::splay(int key) {
    this->key = key;
    this-> left = this->right = 0;
}
 splay::~splay() {

}

splay * left_rotate(splay * q) {
    splay* p = q->right;
    q->right = p->left;
    p->left = q;
    return p;
}

splay* right_rotate(splay* p) {
    splay* q = p->left;
    p->left = q->right;
    q->right = p;
    return q;
}

splay* sp(splay* tree, int key) {
    if(!tree) return nullptr;
    if(tree->key == key) return tree;
    if(tree->key > key) {
        if(!tree->left) return tree;
        if (tree->left->key > key) //левый-левый(второй в ретурне)
        {
            tree->left->left = sp(tree->left->left, key);
            tree = right_rotate(tree);
        }
        else if (tree->left->key < key) // Левый-правый
        {
            tree->left->right = sp(tree->left->right, key);
            if (tree->left->right) {
                tree->left = left_rotate(tree->left);
            }
        }
        if(!tree->left) {
            return tree;
        } else {
            return right_rotate(tree);
        }
    }  else
    {
        if (!tree->right ) return tree;
        if (tree->right->key > key)
        {
            tree->right->left = sp(tree->right->left, key);
            if (tree->right->left)
                tree->right = right_rotate(tree->right);
        }
        else if (tree->right->key < key)
        {
            tree->right->right = sp(tree->right->right, key);
            tree = left_rotate(tree);
        }

        if(!tree->right ) return tree;
        return left_rotate(tree);
    }
}



splay * insert(splay *tree, int key) {
    splay * p = new splay(key);
    if(!tree) {
        return p;
    }
    splay* curr = tree;
    while(true) {
        if(curr->key < key) {
            if(!curr->right) {
                curr->right = p;
                return sp(tree, key);
            }
            curr = curr->right;
        } else if(curr->key > key) {
            if(!curr->left) {
                curr->left = p;
                return sp(tree, key);
            }
            curr = curr->left;
        } else {
            return sp(tree, key);
        }
    }
}

splay * find(splay *tree, int key) {
    return sp(tree, key);
}

splay*  findmin(splay* tree) {
    if(!tree) return nullptr;
    int min =tree->key;
    splay* curr = tree;
    while(curr->left) {
        curr = curr->left;
    }
    return sp(tree, curr->key);

}
splay*  merge(splay* one, splay* two) {
    two = findmin(two);
    if(!two) return one;
    two->left = one;
    return two;
}

splay*  del(splay*tree, int key) {
    if(!tree) return nullptr;
    tree = sp(tree, key);
    splay* curr = tree;
    tree = merge(curr->left, curr->right);
    delete curr;
    return tree;
}

void update_level_splay(splay *tree) {
     if(!tree) return;
    if(tree->right) {
        tree->right->level = tree->level + 1;
        update_level_splay(tree->right);
    }
     if(tree->left) {
         tree->left->level = tree->level + 1;
         update_level_splay(tree->left);
     }
}

int get_level_splay(splay *tree, int key) {
    if(!tree) {
        return 0;
    }
    if (tree->key == key) {
        return tree->level;
    }
    else if(tree->key > key) {
        return get_level_splay(tree->left, key);
    }
    else {
        return get_level_splay(tree->right, key);
    }
}

void update_hight_splay(splay* tree) {
     if(!tree) return;
     int hight = 1;
     tree->hight = 1;
     if(!tree->left && !tree->right) {
         return;
     }
     if(tree->right) {
         update_hight_splay(tree->right);
         tree->hight = tree->right->hight + 1;
     }
     if(tree->left) {
         update_hight_splay(tree->left);
         if(tree->left->hight > tree->hight - 1) {
             tree->hight = tree->left->hight + 1;
         }
     }
 }


int get_width_splay(splay *p, int width, int key) {
    if(!p) {
        return 0;
    }
    if(p->key == key) {
        return width;
    }

    if(p->key > key) {
        width -= avl_bin_power(p->hight-1);;
        return get_width_splay(p->left, width, key);
    }
    else {
        width +=avl_bin_power(p->hight-1);;
        return get_width_splay(p->right, width, key);
    }
}

void fill_curr_splay(splay*tree, int &curr) {
    ++curr;
    if(!tree) {
        return;
    }
    fill_curr_splay(tree->left, curr);
    tree->cu = curr;
    fill_curr_splay(tree->right, curr);
}

splay* get_curr_splay(splay*tree, int key) {
    splay*c = tree;
    if(!c) return nullptr;
    while(c && c->key != key) {
        if(c->key > key) c= c->left;
        else if(c->key < key) c = c->right;
    }
    return c;
}