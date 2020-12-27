/**
 * @file disjoint-sets.cpp
 * Implementation of disjoint sets class
 */

#include "disjoint-sets.h"

DisjointSets::DisjointSets(int elements) {
    sets.resize(elements, -1);
}

int DisjointSets::find_root(int elem) {
    if (sets[elem] < 0) {
        return elem;
    }
    int root = find_root(sets[elem]);
    sets[elem] = root;
    return root;
}

void DisjointSets::set_union(int a, int b) {
    int a_root = find_root(a);
    int b_root = find_root(b);

    int a_size = find_size(a);
    int b_size = find_size(b);

    if (a_size < b_size) {
        sets[a_root] = b_root;
        sets[b_root] -= a_size;
    } else {
        sets[b_root] = a_root;
        sets[a_root] -= b_size;
    }
}

int DisjointSets::find_size(int elem) {
    return -sets[find_root(elem)];
}

bool DisjointSets::is_cycle(int a, int b) {
    return find_root(a) == find_root(b);
}