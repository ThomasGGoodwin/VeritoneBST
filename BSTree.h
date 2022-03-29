#pragma once

#include <cmath>
#include <climits>
#include <iostream>
#include <utility>
#include <vector>

class BSTree {
private:
    int*    _tree;
    size_t  _capacity;
    size_t  _size;
    size_t  _depth;

    void resize()
    {
        if(_tree == nullptr)
        {
            _tree = new int[1];
            _tree[0] = INT_MIN;
            _capacity = 1;
            _depth = 0;
        }
        else
        {
            _depth++;
            size_t new_capacity = _capacity + pow(2, _depth);
            int* new_tree       = new int[new_capacity];

            for(size_t i = 0; i < _capacity; i++)
                new_tree[i] = _tree[i];
            for(size_t i = _capacity; i < new_capacity; i++)
                new_tree[i] = INT_MIN;
            
            delete[] _tree;
            _tree     = new_tree;
            _capacity = new_capacity;
        }
    }

    size_t parent(size_t index) const { return (index - 1) / 2; }

    size_t left_child(size_t index) const { return index * 2 + 1; }

    size_t right_child(size_t index) const { return index * 2 + 2; }

    void insert_helper(int const x, size_t index)
    {
        if(_capacity <= index)
            resize();

        if(_tree[index] == INT_MIN)
        {
            _tree[index] = x;
            _size++;
        }
        else if(x < _tree[index])
            insert_helper(x, left_child(index));
        else
            insert_helper(x, right_child(index));
    }

    void print_debug(std::ostream& out = std::cout)
    {
        out << "DEBUG:" << std::endl;
        out << "Size: " << _size << std::endl;
        out << "Capacity: " << _capacity << std::endl;
        out << "Depth: " << _depth << std::endl;
        out << "Array: " << std::endl;
        for(size_t i=0; i< _capacity; i++)
        {
            if(_tree[i] == INT_MIN)
                out << "X ";
            else
                out << _tree[i] << " ";
        }
        out << std::endl << "---------------" << std::endl;
    }

public:
    BSTree(): _tree(nullptr), _capacity(0), _size(0), _depth(-1) {}

    BSTree(const BSTree& rhs): _tree(new int[rhs._capacity]),
                               _capacity(rhs._capacity),
                               _size(rhs._size),
                               _depth(rhs._depth)
    {
        for(size_t i = 0; i < _capacity; i++)
            _tree[i] = rhs._tree[i];
    }

    BSTree(BSTree&& rhs): _tree(rhs._tree),
                          _capacity(rhs._capacity),
                          _size(rhs._size),
                          _depth(rhs._depth)
    {
        rhs._tree     = nullptr;
        rhs._capacity = 0;
        rhs._size     = 0;
        rhs._depth    = -1;
    }

    BSTree& operator=(const BSTree& rhs)
    {
        if(this != &rhs)
        {
            clear();
            _tree = new int[rhs._capacity];
            for(size_t i = 0; i < rhs._capacity; i++)
                _tree[i] = rhs._tree[i];

            _capacity = rhs._capacity;
            _size     = rhs._size;
            _depth    = rhs._depth;
        }
        return *this;
    }

    BSTree& operator=(BSTree&& rhs)
    {
        if(this != &rhs)
        {
            clear();
            _tree     = rhs._tree;
            _capacity = rhs._capacity;
            _size     = rhs._size;
            _depth    = rhs._depth;

            rhs._tree     = nullptr;
            rhs._capacity = 0;
            rhs._size     = 0;
            rhs._depth    = -1;
        }
        return *this;
    }

    ~BSTree() { clear(); }

    void clear()
    {
        delete[] _tree;
        _tree     = nullptr;
        _size     = 0;
        _capacity = 0;
        _depth    = -1;
    }

    size_t size() const { return _size; }

    bool empty() const { return _size == 0; }

    void insert(int const x) { insert_helper(x, 0); }

    void print_tree(std::ostream& out = std::cout) const
    {
        if(empty()) return;
        size_t counter = 0;
        for(size_t i = 0; i < _depth+1; i++)
        {
            for(size_t j = 0; j < pow(2,i); j++)
            {
                if(_tree[counter] == INT_MIN)
                    out << "X ";
                else
                    out << _tree[counter] << " ";
                counter++;
            }
            out << std::endl;
        }
    }

    std::pair<std::vector<int>, int> maximum_depth_nodes() const
    {
        std::pair<std::vector<int>, int> ret;
        size_t start_index = pow(2, _depth) - 1;
        for(size_t i = start_index; i < _capacity; i++)
            if(_tree[i] != INT_MIN)
                ret.first.push_back(_tree[i]);
        ret.second = _depth;
        return ret;
    }
    
};

std::ostream& operator<<(std::ostream& out, BSTree const& tree)
{
    tree.print_tree(out);
    return out;
}
