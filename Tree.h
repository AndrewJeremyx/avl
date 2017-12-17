#ifndef SECOND_LABA_TREE_H
#define SECOND_LABA_TREE_H


template <class K, class V>

class Tree {

public:

    typedef std::pair<const K, V> PairType;

    Tree() : _root(nullptr){}

    ~Tree() { delete _root; }

    bool Insert(K, V);

    bool Delete(K);

    PairType* Find(K);

private:

    struct Node {

        Node() = delete;

        Node(K key, V value, Node* parent = nullptr): l(nullptr), r(nullptr), p(parent), height(1), key_value(new std::pair<const K, V>(key, value)) {}

        ~Node() {
            delete l;
            l = nullptr;
            delete r;
            r = nullptr;
            if (this->p) {
                auto tmp = (this->p->l == this) ? &(this->p->l) : &(this->p->r);
                *tmp = nullptr;
            }
        };

        PairType* key_value;

        int height;

        Node* l;

        Node* r;

        Node* p;

        void fix_height() { this->height = std::max((this->r) ? this->r->height : 0,(this->l) ? this->l->height : 0) + 1; }
    };

    Node* _root;

    void RRotate(Node*);

    void LRotate(Node*);

    void _balance(Node*);

    void _delete(Node*);

    void _delete_leaf(Node*);

    void _delete_one_kid(Node*);

    void _delete_two_kid(Node*);

    Node* _find_next(Node*);

    int balance_f(Node*);

};
template <class K, class V>
void Tree<K, V>::_balance(Node * node) {
    auto tmp = node;
    while (tmp) {
        tmp->fix_height();
        if (balance_f(tmp) == 2) {
            if (balance_f(tmp->r) < 0) {
                RRotate(tmp->r);
            }
            LRotate(tmp);
        }
        if (balance_f(tmp) == -2) {
            if (balance_f(tmp->l) > 0) {
                LRotate(tmp->l);
            }
            RRotate(tmp);
        }
        tmp = tmp->p;
    }
}

template <class K, class V>
void Tree<K, V>::RRotate(Node* node) {
    auto tmp = (node->p) ? ((node->p->l == node) ? &(node->p->l) : &(node->p->r)) : &(_root);

    *tmp = node->l;
    node->l->p = node->p;
    node->l = (*tmp)->r;
    (*tmp)->r = node;
    node->p = *tmp;
    node->fix_height();
}

template <class K, class V>
void Tree<K, V>::LRotate(Node* node) {
    auto tmp = (node->p) ? ((node->p->l == node) ? &(node->p->l) : &(node->p->r)) : &(_root);

    *tmp = node->r;
    node->r->p = node->p;
    node->r = (*tmp)->l;
    (*tmp)->l = node;
    node->p = *tmp;
    node->fix_height();
}

template <class K, class V>
int Tree<K, V>::balance_f(Node* node) {
    return (node) ? (((node->r) ? node->r->height : 0) - ((node->l) ? node->l->height  : 0)) : 0;
};

template <class K, class V>
bool Tree<K, V>::Insert(K key, V value) {
    if (!_root) {
        _root = new Node(key, value);
        return 1;
    }

    auto tmp = _root;

    while (1) {

        if (key > tmp->key_value->first) {
            if (tmp->r) {
                tmp = tmp->r;
            }
            else {
                tmp->r = new Node(key, value, tmp);
                _balance(tmp);
                return 1;
            }
        } else if (key == tmp->key_value->first) {
            return 0;
        } else {
            if (tmp->l) {
                tmp = tmp->l;
            }
            else {
                tmp->l = new Node(key, value, tmp);
                _balance(tmp);
                return 1;
            }

        }
    }
}

template <class K, class V>
bool Tree<K, V>::Delete(K key) {
    if (!_root) {
        return 0;
    }

    auto tmp = _root;

    while (1) {
        if (key > tmp->key_value->first) {
            if (tmp->r) {
                tmp = tmp->r;
            }
            else {
                return 0;
            }
        } else if (key == tmp->key_value->first) {
            _delete(tmp);
            return 1;
        } else {
            if (tmp->l) {
                tmp = tmp->l;
            }
            else {
                return 0;
            }

        }
    }
}

template <class K, class V>
typename Tree<K, V>::PairType* Tree<K, V>::Find(K key) {
    auto tmp = _root;

    while (1) {
        if (tmp) {
            if (key > tmp->key_value->first) {
                if (tmp) {
                    tmp = tmp->r;
                }
            } else if (key == tmp->key_value->first) {
                return tmp->key_value;
            } else {
                if (tmp) {
                    tmp = tmp->l;
                }
            }
        }
        else {
            return nullptr;
        }
    }
}
template <class K, class V>
void Tree<K, V>::_delete(Node* node) {
    auto node_parent = node->p;
    if ( !( !!node->r || !!node->l ) ) {
        _delete_leaf(node);
    }
    else if (!!node->r != !!node->l) {
        _delete_one_kid(node);
    }
    else {
        _delete_two_kid(node);
    }
    if (node_parent) { _balance(node_parent); }
};
template <class K, class V>
void Tree<K, V>::_delete_leaf(Node* node) {
    if (node == _root) {
        _root = nullptr;
    }
    delete node;
};

template <class K, class V>
void Tree<K, V>::_delete_one_kid(Node* node) {
    auto son_of_father = (node->p) ? ((node->p->l == node) ? &(node->p->l) : &(node->p->r)) : &(_root); // just delete elem and fix relations
    auto son_of_deleted = (node->l) ? &(node->l) : &(node->r);
    *son_of_father = *son_of_deleted;
    (*son_of_deleted)->p = node->p;
    *son_of_deleted = nullptr;
    node->p = nullptr;
    delete node;
};

template <class K, class V>
void Tree<K, V>::_delete_two_kid(Node* node) {
    auto next = _find_next(node);
    delete node->key_value;
    node->key_value = new std::pair<const K, V>(next->key_value->first, next->key_value->second);
    _delete(next);
};

template <class K, class V>
typename Tree<K, V>::Node* Tree<K, V>::_find_next(Node* node) {
    if (node->r) {
        auto tmp = node->r;
        while (tmp->l) {
            tmp = tmp->l;
        }
        return tmp;
    }
    auto tmp = node;
    while (tmp->p->l != tmp) {
        tmp = tmp->p;
    }
    return tmp->p;

};
#endif
