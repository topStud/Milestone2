//
// Created by topaz on 24/01/2020.
//

#ifndef MILESTONE2__MATRIXHASHTABLE_H_
#define MILESTONE2__MATRIXHASHTABLE_H_

#include <unordered_map>
class MatrixHashTable {
  std::unordered_map<std::string, int> matrix_map;
  std::hash<std::string> hash_;
  static MatrixHashTable* collection_;
  MatrixHashTable()= default;
 public:
  static MatrixHashTable* get_instance();
  ~MatrixHashTable();
  void add_to_table(const std::string& matrix_str);
  bool does_matrix_exist(const std::string& matrix_str);
  std::string get_matrix_name(const std::string& matrix_str);
};

#endif //MILESTONE2__MATRIXHASHTABLE_H_
