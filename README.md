# M-ary Search and Binary Search Tree (BST) Implementation

## Overview

This project implements two key data structures: an **M-ary Search Algorithm** and a **Binary Search Tree (BST)** in C++. It provides functionality for inserting, searching, and evaluating performance on sequences of keys using both M-ary search and binary search tree traversal.

The project supports manual input of key sequences, random generation of keys, and input from files. It also includes options to evaluate search performance with varying `m` values for M-ary search and operations on a constructed BST.

## Features

- **M-ary Search Algorithm**:
  - Allows users to specify the degree (`m`) of the search, providing greater control over the search tree structure.
  - Supports efficient searching through sorted sequences of keys.
  - Provides performance evaluation of M-ary search over sequences of keys, including optimized search techniques.

- **Binary Search Tree (BST)**:
  - Allows users to create a BST from sorted sequences of keys.
  - Provides functions to insert, search, and display keys in the BST.
  - Offers evaluation of BST search performance on input sequences.
  - Includes formatted tree display and memory management.

## Usage

### 1. M-ary Search

The project allows you to search for a key in a sorted array using M-ary search, which generalizes binary search by splitting the array into `m` parts. You can test the efficiency of the search by varying `m` and evaluating the number of search steps for different sequences of keys.

### 2. Binary Search Tree (BST)

The project also provides functionality to construct a binary search tree from a sequence of keys. You can insert new keys, search for specific keys, and evaluate the performance of search operations.

### Menu Options

The program offers a set of menu options to work with both M-ary search and BSTs:

1. **M-ary Search on a Single Key**:
   - Search for a single key in a sorted array using M-ary search.
   
2. **Optimized M-ary Search for Key Sequences**:
   - Search for a sequence of keys and optimize search performance by finding an efficient order for searching.
   
3. **Evaluate M-ary Search Performance**:
   - Evaluate the number of steps taken for M-ary search with different values of `m` (2 to 6).
   
4. **Evaluate Optimized M-ary Search Performance**:
   - Compare the performance of optimized search techniques with standard M-ary search.
   
5. **Construct and Operate on a Binary Search Tree (BST)**:
   - Insert, search, and display keys in a BST constructed from the sorted key sequence.

## Example

Here's an example of how you can use the program:

- **Input**: You can provide a sequence of keys manually, generate them randomly, or load them from a file.
- **Search**: Select the search operation you want to perform (M-ary search or BST search).
- **Evaluate**: Evaluate the search performance using various values of `m` in M-ary search and compare it with the binary search tree.


## Future Enhancements

- **Extend the program** to handle deletion of nodes from the Binary Search Tree (BST).
- **Add graphical visualization** for the M-ary search process and the BST structure.

