#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <sstream>
#include <tuple>

class tree
{
public:
    using key_t   = uint64_t;
    using value_t = std::tuple<
                                uint8_t       /*0 - количество комнат*/,
                                double        /*1 - общая площадь*/,
                                double        /*2 - жилая площадь*/,
                                uint8_t       /*3 - дата постройки дома - день*/,
                                uint8_t       /*4 - дата постройки дома - месяц*/,
                                uint16_t      /*5 - дата постройки дома - год*/,
                                double        /*6 - запрашиваемая стоимость*/,
                                std::string   /*7 - телефон продавца*/
                             >;     //-- ОСНОВНОЙ тип элементов --
    using data_t  = std::tuple<key_t, value_t>;

private:
    struct node_t
    {
        data_t field;
        node_t *left = nullptr;
        node_t *right = nullptr;
        node_t(const data_t &t): field(t) { left = right = nullptr; }
        ~node_t() { left = right = nullptr; }
    } *root = nullptr;
    size_t size;

    void copy(node_t *node);
    void remove(node_t *parent, node_t *&node);

    friend void add(const tree::key_t &key, const tree::value_t &v, node_t *&node);
    friend void remove_from(node_t *&node);
    friend node_t *searching(const tree::key_t &key, node_t *node);
    friend size_t find_height(const size_t &s, node_t *node);

    friend std::string writing(std::string &ss, node_t *t);
public:
    tree(void) = default;
    virtual ~tree(void);
    tree(const data_t& d);
    tree(const std::initializer_list<data_t> &t);
    tree(const tree& other);
    tree(tree&& other) noexcept;                // -- конструктор переноса --
    tree &operator=(tree&& other) noexcept;     // -- операция перемещания --
    tree &operator=(const tree& other);
 // Количества ------------------
    bool empty() const noexcept;
    size_t count() const noexcept;              // -- количенство элементов --
    size_t height() const noexcept;             // -- высота дерева --
 // Поиск -----------------------
    data_t find(const key_t& key) const;
    node_t *find_max(node_t *node);
    node_t *find_parent(const tree::key_t &key, node_t *node);
// Модификаторы контейнера --
 // Вставить --
    bool insert(const key_t& key, const value_t& v);
    bool insert(const data_t& d);
 // Заменить --
    bool replace(const key_t& key, const value_t& v);
 // Удалить --
    bool erase(const key_t& key);              // удалить указанный
    void clear();                              // удалить все
 // обмен --
    void swap (tree &t) noexcept;        // обменять с заданным списком

    node_t *get_root() { return root; }

    void include(node_t *node);
    friend void combine(tree &t1, const tree &t2);

    std::string to_string() noexcept;

private:
    void key_checker(const key_t &k);

    class key_8{};
    class key_repit{};
};

#endif // TREE_H
