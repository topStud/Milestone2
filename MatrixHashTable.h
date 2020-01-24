//
// Created by topaz on 24/01/2020.
//

#ifndef MILESTONE2__MATRIXHASHTABLE_H_
#define MILESTONE2__MATRIXHASHTABLE_H_

#include <unordered_map>
class MatrixHashTable {
  std::unordered_map<std::string, std::string> matrix_map;
  static MatrixHashTable* collection_;
  MatrixHashTable()= default;
 public:
  static MatrixHashTable* get_instance();
  ~MatrixHashTable();
  void add_to_table(const std::string& matrix_str, const std::string& matrix_name);
  bool does_matrix_exist(const std::string& matrix_str);
  std::string get_matrix_name(const std::string& matrix_str);
};

#endif //MILESTONE2__MATRIXHASHTABLE_H_
