//
// Created by topaz on 24/01/2020.
//

#include <fstream>
#include "MatrixHashTable.h"
MatrixHashTable* MatrixHashTable::collection_ = nullptr;

/**
 * destructor.
 * releases the memory of the only instance- collection_
 */
MatrixHashTable::~MatrixHashTable() {
  delete collection_;
}

/**
 * get_instance function.
 * if there is no instance created yet, creates a new one.
 * otherwise returns the existing one.
 * @return
 */
MatrixHashTable* MatrixHashTable::get_instance() {
  if (collection_ == nullptr) {
    collection_ = new MatrixHashTable;
  }
  return collection_;
}

/**
 * does_matrix_exist function.
 * @param matrix_str - a matrix represented by a string.
 * @return true- matrix exists, false- otherwise.
 */
bool MatrixHashTable::does_matrix_exist(const std::string& matrix_str) {
  return matrix_map.find(matrix_str) != matrix_map.end();
}

/**
 * get_matrix_name function.
 * @param matrix_str - a matrix represented by a string.
 * @return returns the unique name given to the matrix by hash table.
 */
std::string MatrixHashTable::get_matrix_name(const std::string& matrix_str) {
  return std::to_string(matrix_map[matrix_str]);
}

/**
 * add_to_table function.
 * determines the matrix's new name and adds it to the map.
 * @param matrix_str - a matrix represented by a string.
 */
void MatrixHashTable::add_to_table(const std::string& matrix_str) {
  matrix_map.insert({matrix_str, hash_(matrix_str)});
}

/**
 * reload_table function.
 * reads from a special file called SAVE_FILE
 * that contains all the matrices already created.
 * enters the data to the map.
 */
void MatrixHashTable::reload_table() {
  std::ifstream in_file;
  std::string temp{}, matrix_str{};
  int num_temp;
  in_file.open(SAVE_FILE);

  // file exists
  if (in_file.is_open()) {
    while (!in_file.eof()) {
      do {
        std::getline(in_file, temp);
        matrix_str += temp + '\n';
      } while (temp != "end" && !in_file.eof());
      if(in_file.eof())
      {
          break;
      }
      in_file >> num_temp;
      matrix_map.insert({matrix_str, num_temp});
      std::getline(in_file, temp);
      matrix_str.clear();
    }
    in_file.close();
  }
}

/**
 * save_table function.
 * writes all the data in the map to a special
 * file called SAVE_FILE.
 */
void MatrixHashTable::save_table() {
  std::ofstream out_file;
  out_file.open(SAVE_FILE, std::ios::trunc);

  for (std::pair<std::string, int> item : matrix_map) {
    out_file << item.first;
    out_file << item.second;
    out_file << '\n';
  }
  out_file.close();
}