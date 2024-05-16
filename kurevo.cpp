//
// Created by Владислав Отвагин on 21.04.2024.
//

#include "kurevo.h"
#include "avl.h"
#include "mainwindow.h"

kurevo::kurevo() {
    this->left = this->right = nullptr;

}

kurevo::kurevo(int key) {

    this->key = key;
    this->prior = rand() % 1000 * rand() % 10000;
}

kurevo::kurevo( int key, int p) {
    this->key = key;
    this->prior = p;
}

kurevo::~kurevo() {

}
std::pair <kurevo*, kurevo*> split(kurevo*tree, int key) {
    if(!tree)
        return {nullptr, nullptr};
    std::pair<kurevo*, kurevo*> nn;
    if(tree->key <= key) {
        nn = split(tree->right, key);
        tree->right =nn.first;
        return{tree, nn.second};
    }
    nn = split(tree->left, key);
    tree->left = nn.second;
    return{nn.first, tree};
}

kurevo* merge(kurevo*one, kurevo* two) {
    if(!one) return two;
    if(!two) return one;
    if(one->prior >= two->prior) {
        one->right = merge(one->right, two);
        return one;
    }
    two->left = merge(one, two->left);
    return two;
}

kurevo* insert(kurevo*tree, int key, int p) {
    auto nn = split(tree, key);
    tree = merge(nn.first, new kurevo(key, p));
    tree = merge(tree, nn.second);
    return tree;
}

kurevo* remove(kurevo*tree, int key) {
    auto nn = split(tree, key);
    auto q = split(nn.first, key - 1);
    return merge(q.first, nn.second);
}

void update_hight_kurevo(kurevo*tree) {
    if(!tree) return;
    int hight = 1;
    tree->hight = 1;
    if(!tree->left && !tree->right) {
        return;
    }
    if(tree->right) {
        update_hight_kurevo(tree->right);
        tree->hight = tree->right->hight + 1;
    }
    if(tree->left) {
        update_hight_kurevo(tree->left);
        if(tree->left->hight > tree->hight - 1) {
            tree->hight = tree->left->hight + 1;
        }
    }
}
int get_level_kurevo(kurevo *tree, int key) {
    if(!tree) {
        return 0;
    }
    if (tree->key == key) {
        return tree->level;
    }
    else if(tree->key > key) {
        return get_level_kurevo(tree->left, key);
    }
    else {
        return get_level_kurevo(tree->right, key);
    }
}

void update_level_kurevo(kurevo *tree) {
    if(!tree) return;
    if(tree->right) {
        tree->right->level = tree->level + 1;
        update_level_kurevo(tree->right);
    }
    if(tree->left) {
        tree->left->level = tree->level + 1;
        update_level_kurevo(tree->left);
    }
}

int get_width_kurevo(kurevo *p, int width, int key) {
    if(!p) {
        return 0;
    }
    if(p->key == key) {
        return width;
    }

    if(p->key > key) {
        width -= avl_bin_power(p->hight-1);
        return get_width_kurevo(p->left, width, key);
    }
    else {
        width +=avl_bin_power(p->hight-1);
        return get_width_kurevo(p->right, width, key);
    }
}

int get_prior(kurevo*tree, int key) {
    kurevo * curr = tree;
    int cnt = 0;

    while(cnt < 100000) {
        ++cnt;
        if(curr->key > key) {
            curr = curr->left;
        } else if(curr->key < key) {
            curr = curr->right;
        }
        else {
            return curr->prior;
        }
    }
}

void fill_curr_kurevo(kurevo*tree, int &curr) {
    ++curr;
    if(!tree) {
        return;
    }
    fill_curr_kurevo(tree->left, curr);
    tree->cu = curr;
    fill_curr_kurevo(tree->right, curr);
}

kurevo* get_curr_kurevo(kurevo*tree, int key) {
    kurevo* c = tree;
    if(!c) return nullptr;
    while(c && c->key != key) {
        if(c->key > key) c= c->left;
        else if(c->key < key) c = c->right;
    }
    return c;
}