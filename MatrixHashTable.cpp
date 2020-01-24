//
// Created by topaz on 24/01/2020.
//

#include "MatrixHashTable.h"
MatrixHashTable* MatrixHashTable::collection_ = nullptr;
MatrixHashTable::~MatrixHashTable() {
  delete collection_;
}

MatrixHashTable* MatrixHashTable::get_instance() {
  if (collection_ == nullptr) {
    collection_ = new MatrixHashTable;
  }
  return collection_;
}

bool MatrixHashTable::does_matrix_exist(const std::string& matrix_str) {
  return matrix_map.find(matrix_str) != matrix_map.end();
}

std::string MatrixHashTable::get_matrix_name(const std::string& matrix_str) {
  return matrix_map[matrix_str];
}

void MatrixHashTable::add_to_table(const std::string& matrix_str, const std::string& matrix_name) {
  matrix_map.insert({matrix_str, matrix_name});
}