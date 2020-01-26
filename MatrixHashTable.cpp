//
// Created by topaz on 24/01/2020.
//

#include <fstream>
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
  return std::to_string(matrix_map[matrix_str]);
}

void MatrixHashTable::add_to_table(const std::string& matrix_str) {
  matrix_map.insert({matrix_str, hash_(matrix_str)});
}

void MatrixHashTable::reload_table() {
  std::ifstream in_file;
  std::string temp{}, matrix_str{};
  int num_temp;
  in_file.open(SAVE_FILE);

  // file exists
  if (in_file.is_open()) {
    while (!in_file.eof()) {
      do {
        in_file >> temp;
        matrix_str += temp;
      } while (temp != "end");
      in_file >> num_temp;
      matrix_map.insert({matrix_str, num_temp});
    }
    in_file.close();
  }
}

void MatrixHashTable::save_table() {
  std::ofstream out_file;
  out_file.open(SAVE_FILE);

  for (std::pair<std::string, int> item : matrix_map) {
    out_file << item.first;
    out_file << item.second;
  }
}