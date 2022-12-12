#include <iostream>
#include <vector>
#include <utility>
#include <queue>

template<typename T>
class Node {
    public:
        T m_data;
        Node *m_left;
        Node *m_right;

    public:
        Node();
        Node(T data);
        bool isLeaf();
        Node<T> *remove(T data, Node<T> *parent);
        T minValue();
};

template<typename T>
Node<T>::Node()
    : m_data(), m_left(NULL), m_right(NULL) {}

template<typename T>
Node<T>::Node(T data)
    : m_data(data), m_left(NULL), m_right(NULL) {}

template<typename T>
bool Node<T>::isLeaf() {
    return (m_left == NULL && m_right == NULL);
}

template<typename T>
class Tree {
    protected:
        Node<T> *m_root;
        int m_size;

    public:
        Tree();
        virtual ~Tree();
        int size();
        bool insert(T new_data);
        std::vector<T> infix();
        void infix(Node<T> *root, std::vector<T> &vec);
        std::pair<T, bool> search(T data);
        std::pair<T, bool> search(Node<T> *root, T data);
        bool remove(T data);
        std::vector<T> BFS();
        void processLevel(Node<T> *root, int level, std::vector<T> &vec);
        int height(Node<T> *root);
};

template<typename T>
Tree<T>::Tree() 
   : m_root(NULL), m_size(0) {}

template<typename T>
Tree<T>::~Tree() {
    std::vector<T> v = this->infix();

    for(T data : v) {
        this->remove(data);
    }
}

template<typename T>
int Tree<T>::size() {
   return m_size;
}

template<typename T>
bool Tree<T>::insert(T new_data) {
    auto new_node = new Node<T>(new_data);

    if(m_root == NULL) {
        m_size++;
        m_root = new_node;
        return true;
    }

    Node<T> *tmp = m_root;
    while(tmp != NULL) {
        if(tmp->m_data > new_data) {
            if(tmp->m_left == NULL) {
                tmp->m_left = new_node;
                m_size++;
                return true;
            }
            tmp = tmp->m_left;
        } else {
            if(tmp->m_right == NULL) {
                tmp->m_right = new_node;
                m_size++;
                return true;
            }

            tmp = tmp->m_right;
        }
    }

    return false;
}

template<typename T>
std::vector<T> Tree<T>::infix() {
    std::vector<T> output;

    output.reserve(m_size);

    this->infix(m_root, output);

    return output;
}

template<typename T>
void Tree<T>::infix(Node<T> *root, std::vector<T> &vec) {
    if(root != NULL) {
        this->infix(root->m_left, vec);
        vec.push_back(root->m_data);
        this->infix(root->m_right, vec);
    }
}

template<typename T> 
std::pair<T, bool> Tree<T>::search(T data) {
    return this->search(m_root, data);
}

template<typename T> 
std::pair<T, bool> Tree<T>::search(Node<T> *root, T data) {
    if(root == NULL) return std::make_pair(T(), false);

    if(root->m_data == data) {
        return std::make_pair(root->m_data, true);
    } else if(root->m_data > data) {
        return search(root->m_left, data);
    } else {
        return search(root->m_right, data);
    }
}

template<typename T>
bool Tree<T>::remove(T data) {
    if(m_root == NULL) return false;
    else {
        if(m_root->m_data == data) {
            Node<T> auxRoot;
            auxRoot.m_left = m_root;
            Node<T> *removedNode = m_root->remove(data, &auxRoot);
            m_root = auxRoot.m_left;

                if(removedNode != NULL) {
                    delete removedNode;
                    m_size--;
                    return true;
                } else {
                return false;
                }
        } else {
                Node<T> *removedNode = m_root->remove(data, NULL);

                if(removedNode != NULL) {
                    delete removedNode;
                    m_size--;
                    return true;
                } else {
                    return false;
                }
        }
    }
}

template<typename T>
Node<T> *Node<T>::remove(T data, Node<T> *parent) {
    if(data < m_data) {
        if(m_left != NULL) {
            return m_left->remove(data, this);
        } else {
            return NULL;
        }

    } else if(data > m_data) {
        if(m_right != NULL)
            return m_right->remove(data, this);
        else
            return NULL;
    } else {
        if(m_left != NULL && m_right != NULL) {
                m_data = m_right->minValue();
                return m_right->remove(m_data, this);
        } else if(parent->m_left == this) {
                parent->m_left = (m_left != NULL) ? m_left : m_right;
                return this;
        } else if(parent->m_right == this) {
                parent->m_right = (m_left != NULL) ? m_left : m_right;
                return this;
        }
    }

    return NULL;
}
 
template<typename T>
T Node<T>::minValue() {
      if(m_left == NULL) return m_data;
      else return m_left->minValue();
}

template<typename T>
void Tree<T>::processLevel(Node<T> *root, int level, std::vector<T> &vec) {
    if(root != NULL) {
        if(level == 0) {
            vec.push_back(root->m_data);
        } else {
            if(level > 0) {
                this->processLevel(root->m_left, level - 1, vec);
                this->processLevel(root->m_right, level - 1, vec);
            }
        }
    }
}

template<typename T>
std::vector<T> Tree<T>::BFS() {
    std::vector<T> vec;
    int level, height;
    
    vec.reserve(m_size);
    height = this->height(m_root);

    for(level = 0; level <= height; level++) {
        this->processLevel(m_root, level, vec);
    }

    return vec;
}

template<typename T>
int Tree<T>::height(Node<T> *root) {
    int left_height, right_height; 
    
    if(root != NULL) {
        left_height  = this->height(root->m_left);
        right_height = this->height(root->m_right);
        return (left_height > right_height ? left_height + 1 : right_height + 1);
    }
    else {
        return -1;
    }
}
