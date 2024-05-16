//
// Created by Владислав Отвагин on 21.04.2024.
//

#include "avl.h"



void fix_height(avl * p) {
    if(!p) {
        return;
    }
    int h1 = 1;
    int h2 = 1;
    if(p->left) {
        h1 += p->left->height;
    }
    if(p->right) {
        h2 += p->right->height;
    }
    if(h1 > h2) {
        p->height = h1;
    }
    else {
        p->height = h2;
    }

}

int b_facror(avl *p) {
    int h1 = 0, h2 = 0;
    if(!p) {
        return 0;
    }
    if(p->right) {
        h1 = p->right->height;
    }
    if(p->left) {
        h2 = p->left->height;
    }
    return h1-h2;
}

avl* right_rotate(avl* p) // правый поворот вокруг p
{
    avl* q = p->left;
    p->left = q->right;
    q->right = p;
    fix_height(p);
    fix_height(q);
    return q;
}

avl* left_rotate(avl* q) // левый поворот вокруг q
{
    avl* p = q->right;
    q->right = p->left;
    p->left = q;
    fix_height(q);
    fix_height(p);
    return p;
}

avl * balance (avl *p) {
    fix_height(p);
    if(b_facror(p) == 2) {
        if(b_facror(p->right) < 0) {
            p->right = right_rotate(p->right);
        }
        return left_rotate(p);
    } else if(b_facror(p) == -2) {
        if(b_facror(p->left) > 0) {
            p->left = left_rotate(p->left);
        }
        return right_rotate(p);
    }
    return p;
}

avl* insert(avl* tree, int key) {
    if(tree == 0) {
        return new avl(key);
    }
    if(tree->key > key) {
        tree->left = insert(tree->left, key);
    } else if(tree->key < key){
        tree->right = insert(tree->right, key);
    } else {
        return tree;
    }
    return balance(tree);
}

void fix_level(avl* tree) {
    if(!tree) {
        return;
    }

    if(tree->left) {
            tree->left->level = tree->level + 1;
            fix_level(tree->left);
    }

    if(tree->right) {
            tree->right->level = tree->level + 1;
            fix_level(tree->right);
        }
}
int64_t avl_bin_power(int n) {
    if(n <= 0) {
        return 1;
    }
    if(n < 6) {
        return 2*avl_bin_power(n-1);
    } else {
        return 2*avl_bin_power(n-1);
    }
}

int get_width_avl(avl *p, int width, int key) {
    if(!p) {
        return 0;
    }
    if(p->key == key) {
        return width;
    }
    if(p->key > key) {
        width -= avl_bin_power(p->height - 1)*8;
        return get_width_avl(p->left, width, key);
    }
    else {
        width += avl_bin_power(p->height - 1)*8;
        return get_width_avl(p->right, width, key);
    }
}

int get_level_avl(avl *p, int key) {
    if(!p) {
        return 0;
    }
    if (p->key == key) {
        return p->level;
    }
    else if(p->key > key) {
        return get_level_avl(p->left, key);
    }
    else {
        return get_level_avl(p->right, key);
    }
}
avl* removemin(avl* p)
{
    if( p->left==0 )
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}
avl* findmin(avl*p) {
    if(!p->left) {
        return p;
    }
    return findmin(p->left);
}
avl* remove(avl* p, int key) {
    if(!p) {
        return nullptr;
    }
    if( key < p->key )
        p->left = remove(p->left,key);
    else if( key > p->key )
        p->right = remove(p->right,key);
    else {
        avl*l = p->left;
        avl*r = p->right;
        delete p;
        if(!r) return l;
        avl*min = findmin(r);
        min->right = removemin(r);
        min->left = l;
        return balance(min);
    }
    return balance(p);
}

avl* find_by_cords(avl*p, int x, int y, int wide, int height) {
    if(!p) return 0;
}


void fill_curr_avl(avl*tree, int &curr) {
    ++curr;
    if(!tree) {
        return;
    }
    fill_curr_avl(tree->left, curr);
    tree->cu = curr;
    fill_curr_avl(tree->right, curr);
}

avl* get_curr(avl*tree, int key) {
    avl*c = tree;
    if(!c) return nullptr;
    while(c && c->key != key) {
        if(c->key > key) c= c->left;
        else if(c->key < key) c = c->right;
    }
    return c;
}