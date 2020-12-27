/**
 * @file disjoint-sets.h
 * Definition of disjoint sets class
 */

#pragma once

#include <vector>

using namespace std;

/**
 * Vector representing disjoint sets to generate maze. Each element 
 * stores the root element representing the disjoint set, and each 
 * root stores the negative size of the disjoint set.
 * @author Vaibhav Gupta
 */
class DisjointSets {
    public:
        /**
         * Constructor to create each element as a disjoint set.
         * @param elements Number of elements.
         */
        DisjointSets(int elements);
        
        /**
         * Recursively finds the root/element representing the disjoint set 
         * that contains the given element. Performs path compression.
         * @param elem Element in disjoint set to find root.
         * @returns Element representing disjoint set.
         */
        int find_root(int elem);

        /**
         * Performs set union by size (merges smaller set into larger set).
         * In case of identical set sizes, the second set is merged into 
         * the first.
         * @param a Element in disjoint set to union.
         * @param b Element in disjoint set to union.
         */
        void set_union(int a, int b);

        /**
         * Finds the size of the disjoint set that contains the given element.
         * @param elem Element in disjoint set to find size.
         * @returns Size of disjoint set.
         */
        int find_size(int elem);

        /**
         * Determines if two elements are in the same set or not.
         * @param a Element in disjoint set.
         * @param b Element in disjoint set.
         * @returns Boolean representing if both elements are in the same set
         * or not.
         */
        bool is_cycle(int a, int b);

    private:
        vector<int> sets;
};