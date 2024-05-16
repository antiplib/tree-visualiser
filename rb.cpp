//
// Created by Владислав Отвагин on 12.05.2024.
//

#include "rb.h"
#include "avl.h"
rb::rb(){}

rb::rb(int key, rb *parent) {
    this->parent = parent;
    this->key = key;
    this->left = this->right = nullptr;
    this->is_red = 1;
}

rb::~rb() {

}

rb *get_brother(rb *tree) {
    if(tree && tree->parent) {
        if(tree->parent->key > tree->key) {
            return tree->parent->right;
        }
        return  tree->parent->left;
    }
    return nullptr;
}

rb *get_grandpa(rb *tree) {
    if(tree && tree->parent)
        return tree->parent->parent;
    return nullptr;
}

rb *get_left_nep(rb *tree) {
    rb* b = get_brother(tree);
    if(b) {
        return b->left;
    }
    return nullptr;
}

rb *get_right_nep(rb *tree) {
    rb* b = get_brother(tree);
    if(b) {
        return b->right;
    }
    return nullptr;
}




rb* get_uncle(rb*tree){
    rb*g = tree->parent;
    return get_brother(g);
}
// Левый поворот вокруг узла x
rb* left_rotate(rb*x) {
    rb* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        return  y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    return y;
}

// Правый поворот вокруг узла x
rb* right_rotate(rb* y) {
    rb* x = y->left;
    y->left = x->right;
    if (x->right != nullptr) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nullptr) {
        return  x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
    return y;
}
void rotateLeft(rb* &root, rb* pt) {
    rb* pt_right = pt->right;

    pt->right = pt_right->left;
    if (pt->right != nullptr)
        pt->right->parent = pt;

    pt_right->parent = pt->parent;

    if (pt->parent == nullptr)
        root = pt_right;
    else if (pt == pt->parent->left)
        pt->parent->left = pt_right;
    else
        pt->parent->right = pt_right;

    pt_right->left = pt;
    pt->parent = pt_right;
}

void rotateRight(rb* &root, rb* pt) {
    rb* pt_left = pt->left;

    pt->left = pt_left->right;
    if (pt->left != nullptr)
        pt->left->parent = pt;

    pt_left->parent = pt->parent;

    if (pt->parent == nullptr)
        root = pt_left;
    else if (pt == pt->parent->left)
        pt->parent->left = pt_left;
    else
        pt->parent->right = pt_left;

    pt_left->right = pt;
    pt->parent = pt_left;
}

rb* balance_after_add(rb* curr, rb*root) {
    rb* parent = nullptr;
    rb* grandparent = nullptr;
    while ((curr != root) && (curr->is_red != 0) && (curr->parent->is_red == 1)) {
        parent = curr->parent;
        grandparent = curr->parent->parent;

        if (parent == grandparent->left) {
            rb* uncle = grandparent->right;

            if (uncle != nullptr && uncle->is_red == 1) {
                grandparent->is_red = 1;
                parent->is_red = 0;
                uncle->is_red = 0;
                curr = grandparent;
            } else {
                if (curr == parent->right) {
                    rotateLeft(root, parent);
                    curr = parent;
                    parent = curr->parent;
                }
                rotateRight(root, grandparent);
                std::swap(parent->is_red, grandparent->is_red);
                curr = parent;
            }
        } else {
            rb* uncle = grandparent->left;

            if (uncle != nullptr && uncle->is_red == 1) {
                grandparent->is_red = 1;
                parent->is_red = 0;
                uncle->is_red = 0;
                curr = grandparent;
            } else {
                if (curr == parent->left) {
                    rotateRight(root, parent);
                    curr = parent;
                    parent = curr->parent;
                }
                rotateLeft(root, grandparent);
                std::swap(parent->is_red, grandparent->is_red);
                curr = parent;
            }
        }
    }

    root->is_red = 0;
    return root;
}


rb*add(rb*tree, int key) {
    rb* curr = tree;
    if(!tree) {
        rb*curr= new rb(key);
        curr->is_red = false;
        return curr;
    }
    while(true) {
        if(curr->key > key) {
            if(curr->left)
                curr = curr->left;
            else {
                curr->left = new rb(key, curr);
                curr = curr->left;
                break;
            }
        } else if (curr->key < key){
            if(curr->right)
                curr = curr->right;
            else {
                curr->right = new rb(key, curr);
                curr = curr->right;
                break;
            }
        } else break;
    }
    if(curr->parent && curr->parent->is_red == false) return tree;

    return balance_after_add(curr, tree);
}


void fix_level(rb* tree) {
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

int get_width_rb(rb *p, int width, int key) {
    if(!p) {
        return 0;
    }
    if(p->key == key) {
        return width;
    }
    if(p->key > key) {
        width -= avl_bin_power(p->hight - 1)*8;
        return get_width_rb(p->left, width, key);
    }
    else {
        width += avl_bin_power(p->hight - 1)*8;
        return get_width_rb(p->right, width, key);
    }
}

int get_level_rb(rb *p, int key) {
    if(!p) {
        return 0;
    }
    if (p->key == key) {
        return p->level;
    }
    else if(p->key > key) {
        return get_level_rb(p->left, key);
    }
    else {
        return get_level_rb(p->right, key);
    }
}

void update_hight_rb(rb* tree) {
    if(!tree) return;
    int hight = 1;
    tree->hight = 1;
    if(!tree->left && !tree->right) {
        return;
    }
    if(tree->right) {
        update_hight_rb(tree->right);
        tree->hight = tree->right->hight + 1;
    }
    if(tree->left) {
        update_hight_rb(tree->left);
        if(tree->left->hight > tree->hight - 1) {
            tree->hight = tree->left->hight + 1;
        }
    }
}

rb* removemin(rb* p)
{
    if( p->left==0 )
        return p->right;
    p->left = removemin(p->left);
    return p;
}
rb* findmin(rb*p) {
    if(!p->left) {
        return p;
    }
    return findmin(p->left);
}

rb* remove(rb* p, int key) {
    if(!p) {
        return nullptr;
    }
    if( key < p->key )
        p->left = remove(p->left,key);
    else if( key > p->key )
        p->right = remove(p->right,key);
    else {

        rb*l = p->left;
        rb*r = p->right;
        delete p;
        if(!r) return l;
        rb*min = findmin(r);
        min->right = removemin(r);
        min->left = l;
        return min;
    }
    return p;
}

void fill_curr_rb(rb*tree, int &curr) {
    ++curr;
    if(!tree) {
        return;
    }
    fill_curr_rb(tree->left, curr);
    tree->cu = curr;
    fill_curr_rb(tree->right, curr);
}

rb* get_curr_rb(rb*tree, int key) {
    rb*c = tree;
    if(!c) return nullptr;
    while(c && c->key != key) {
        if(c->key > key) c= c->left;
        else if(c->key < key) c = c->right;
    }
    return c;
}