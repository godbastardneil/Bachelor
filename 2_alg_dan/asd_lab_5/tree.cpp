#include "tree.h"

void tree::key_checker(const tree::key_t &k)
{
    node_t *tmp = root;
    if (k < 10000000 || k >= 100000000) { throw key_8(); }
    while (tmp != nullptr)
    {
        if (k == std::get<0>(tmp->field)) { throw key_repit(); }
        if (k < std::get<0>(tmp->field))
        {
            tmp = tmp->left;
        } else { tmp = tmp->right; }
    }
}

void tree::copy(tree::node_t *node)
{
    if (node != nullptr)
    {
        insert(node->field);
        copy(node->right);
        copy(node->left);
    }
}
void tree::remove(tree::node_t *parent, tree::node_t *&node)
{
    if (node)
    {
        if ((node->left) && (node->right))
        {
            tree::node_t *localMax = find_max(node);
            node->field = localMax->field;
            remove(find_parent(std::get<0>(localMax->field), node), localMax);
            return;
        } else if (node->left)
        {
            if (node == parent->left)
            {
                parent->left = node->left;
            } else { parent->right = node->left; }
        } else if (node->right)
        {
            if (node == parent->right)
            {
                parent->right = node->right;
            } else { parent->left = node->right; }
        } else
        {
            if (node == parent->left) {
                parent->left = nullptr;
            } else { parent->right = nullptr; }
        }
        delete node;
    }
}
size_t find_height(const size_t &s, tree::node_t *node)
{
    if (node == nullptr) { return s; }
    return std::max((s+1, find_height(s+1, node->left)), find_height(s+1, node->right));
}

void add(const tree::key_t &key, const tree::value_t &v, tree::node_t *&node)
{
    if (node == nullptr)
    {
        node = new tree::node_t(tree::data_t(key, v));
        node->left = node->right = nullptr;
    } else
    {
        if (key < std::get<0>(node->field))
        {
            add(key, v, node->left);
        } else { add(key, v, node->right); }
    }
}
void remove_from(tree::node_t *&node)
{
    if(node != nullptr)
    {
        remove_from(node->left);
        remove_from(node->right);
        delete node;
        node = nullptr;
    }
}
tree::node_t *searching(const tree::key_t &key, tree::node_t *node)
{
    if (key == std::get<0>(node->field))
    {
        return node;
    } else if (key < std::get<0>(node->field))
    {
        return searching(key, node->left);
    } else { return searching(key, node->right); }
    return nullptr;
}

tree::~tree(){ clear(); }

tree::tree(const tree::data_t &d) { insert(d); }

tree::tree(const std::initializer_list<tree::data_t> &t)
{
    for (const data_t &d: t) { insert(d); }
}

tree::tree(const tree &other) { copy(other.root); }

tree::tree(tree &&other) noexcept
{
    other.root = nullptr;
    other.size = 0;
}

tree &tree::operator=(tree &&other) noexcept
{
    if (this != &other) { swap(other); }
    return *this;
}

tree &tree::operator=(const tree &other)
{
    if (this != &other)
    {
        tree temp(other);
        swap(temp);
    }
    return *this;
}

bool tree::empty() const noexcept { return (size == 0); }

size_t tree::count() const noexcept { return size; }

size_t tree::height() const noexcept
{
    return find_height(0, root);
}

tree::data_t tree::find(const tree::key_t &key) const
{
    node_t *tmp =  searching(key, root);
    if (tmp != nullptr) { return tmp->field; }
    return data_t(0, value_t(0, 0, 0, 0, 0, 0, 0, ""));
}
tree::node_t *tree::find_parent(const tree::key_t &key, tree::node_t *node)
{
    if (node != nullptr)
    {
        if ((node->left) || (node->right))
        {
            if((node->left) && (key == std::get<0>(node->left->field)))
            {
                return node;
            } else if ((node->right) && (key == std::get<0>(node->right->field)))
            {
                return node;
            } else if (key < std::get<0>(node->field))
            {
                return find_parent(key, node->left);
            } else { return find_parent(key, node->right); }
        } else { return root; }
    } else { return root; }
}
tree::node_t *tree::find_max(tree::node_t *node)
{
    while (node->right) { node = node->right; }
    return node;
}

bool tree::insert(const tree::key_t &key, const tree::value_t &v)
{
    key_checker(key);
    add(key, v, root);
    ++size;
    return 0;
}

bool tree::insert(const tree::data_t &d) { return insert(std::get<0>(d), std::get<1>(d)); }

bool tree::replace(const tree::key_t &key, const tree::value_t &v)
{
    if (!empty())
    {
        node_t *toReplace = searching(key, root);
        toReplace->field = {key,v};
        return 1;
    }
    return 0;
}

bool tree::erase(const tree::key_t &key)
{
    node_t *parent = find_parent(key, root);
    if (parent != nullptr)
    {
        node_t *node = nullptr;
        if ((parent->left) && (std::get<0>(parent->left->field) == key))
        {
            node = parent->left;
        } else if ((parent->right) && (std::get<0>(parent->right->field) == key)) { node = parent->right; }
        remove(parent, node);
        return true;
    }
    return 0;
}

void tree::clear()
{
    remove_from(root);
    size = 0;
}

void tree::swap(tree &t) noexcept
{
    std::swap(root, t.root);
    std::swap(size, t.size);
}


void tree::include(tree::node_t *node)
{
    if (node != nullptr)
    {
        insert(node->field);
        include(node->left);
        include(node->right);
    }
}


void combine(tree &t1, const tree &t2)
{
    if (t1.root != t2.root) { t1.include(t2.root); }
}


std::string writing(std::string &ss, tree::node_t *t)
{
    if (t != nullptr)
    {
        tree::value_t vt = std::get<1>(t->field);
        ss += std::to_string(std::get<0>(t->field)) + ' '
           + std::to_string(std::get<0>(vt)) + ' '
           + std::to_string(std::get<1>(vt)) + ' '
           + std::to_string(std::get<2>(vt)) + ' '
           + std::to_string(std::get<3>(vt)) + std::to_string(std::get<4>(vt)) + std::to_string(std::get<5>(vt)) + ' '
           + std::to_string(std::get<6>(vt)) + ' '
           + (std::get<7>(vt)) + '\n';
        writing(ss, t->right);
        writing(ss, t->left);
    }
    return ss;
}
std::string tree::to_string() noexcept
{
    std::string ss;
    node_t *node = root;
    return writing(ss, node);
}
