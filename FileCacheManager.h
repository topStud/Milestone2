//
// Created by topaz on 12/01/2020.
//

#ifndef MILESTONE2__FILECACHEMANAGER_H_
#define MILESTONE2__FILECACHEMANAGER_H_

#include <list>
#include <unordered_map>
#include <iostream>
#include <fstream>

#include "CacheManager.h"

#define CAPACITY 5

/**
 * FileCacheManager class.
 * responsible for all the Values
 * generated by the program.
 * @tparam Value
 */
template <typename Value>
class FileCacheManager : public CacheManager<Value> {
  std::list<std::string> least_recently_list;
  std::unordered_map<std::string, std::pair<Value, std::list<std::string>::iterator>> _cache;
  void write_value_to_file(const std::string&  key, Value value);
  Value read_from_file(const std::string& key, Value value);
  void erase_least_recently_used();
  void add_most_recently_used(std::string key, Value value);
 public:
  Value get(std::string key) override;
  void save(std::string key, Value value) override;
  bool exist_in_cache(std::string key) override;
};

/**
 * exist_in_cache function.
 * @tparam Value
 * @param key name of object.
 * @return true- the object is already exist, false- otherwise.
 */
template <typename Value>
bool FileCacheManager<Value>::exist_in_cache(std::string key) {
  if (_cache.find(key) != _cache.end())
    return true;
  else {
    std::ifstream in_file;
    in_file.open(key);

    // if file is open, it means that the file exists.
    if (in_file.is_open()) {
      in_file.close();
      return true;
    }
  }
  // file not in cache
  return false;
}

/**
 * save function.
 * by giving the function the key and value, saves it according to lru.
 * saves in map (to CAPACITY objects) and in a file.
 * @tparam Value
 * @param key - name of object.
 * @param value - value associated with key.
 */
template <typename Value>
void FileCacheManager<Value>::save(std::string key, Value value) {
  if (_cache.find(key) != _cache.end()) {
    least_recently_list.remove(key);
    least_recently_list.push_front(key);
    _cache[key].second = least_recently_list.begin();
    _cache[key].first = value;
  } else {
    if (_cache.size() == CAPACITY) {
      erase_least_recently_used();
    }
    add_most_recently_used(key, value);
  }
  write_value_to_file(key, value);
}

/**
 * add_most_recently_used function.
 * positions the object to be most recently used.
 * @tparam Value
 * @param key - object name.
 * @param value - value associated with key.
 */
template <typename Value>
void FileCacheManager<Value>::add_most_recently_used(std::string key, Value value) {
  least_recently_list.push_front(key);
  _cache.insert({key, {value, least_recently_list.begin()}});
}

/**
 * erase_least_recently_used function.
 * erases the lru form the O(1) access.
 * @tparam Value
 */
template <typename Value>
void FileCacheManager<Value>::erase_least_recently_used() {
  _cache.erase(least_recently_list.back());
  least_recently_list.erase(--least_recently_list.end());
}

/**
 * get function.
 * checks if the object is saved in the map, and returns the value of it.
 * if the object is not saved there, checks uf saved in a file. return it's value.
 * @tparam Value
 * @param key - object name.
 * @return the value of the object.
 */
template <typename Value>
Value FileCacheManager<Value>::get(std::string key) {
  // if in cache, updates the key to be most recently used
  if (_cache.find(key) != _cache.end()) {
    least_recently_list.remove(key);
    least_recently_list.push_front(key);
    _cache[key].second = least_recently_list.begin();
    return _cache[key].first;
  } else {
    Value lru_value;
    if (_cache.size() != 0)
      lru_value = _cache.find(least_recently_list.back())->second.first;
    // searches in files
    try {
      Value mru_value = read_from_file(key, lru_value);
      if (_cache.size() != 0)
        erase_least_recently_used();
      add_most_recently_used(key, mru_value);
      return mru_value;
    } catch (const char *e) {
      std::cerr << e << std::endl;
    }
  }
}

/**
 * read_from_file function.
 * opens a file according to the key and returns the data in the file- value.
 * @tparam Value
 * @param key - object name.
 * @param value - value associated with the object.
 * @return
 */
template <typename Value>
Value FileCacheManager<Value>::read_from_file(const std::string& key, Value value) {
  std::ifstream in_file;
  in_file.open(key);

  // checks if file opened
  if(!in_file.is_open()) {
    throw "file does not exist";
  }

  // checks that there are no errors
  if (!in_file.good()) {
    throw "error";
  }

  // read key's value
  //in_file >> value;
  std::getline(in_file, value);
  in_file.close();
  return value;
}

/**
 * write_value_to_file function.
 * opens a file according to the key's name and saves
 * there the value- writes to the function.
 * @tparam Value
 * @param key - object's name
 * @param value - the value associated with the object
 */
template <typename  Value>
void FileCacheManager<Value>::write_value_to_file(const std::string& key, Value value) {
  std::ofstream out_file;
  out_file.open(key);

  // checks if the file opened successfully
  if (!out_file.is_open()) {
    throw "file was not opened";
  }

  // checks if there are no errors
  if (!out_file.good()) {
    throw "error";
  }

  out_file << value;
  out_file.close();
}

#endif //MILESTONE2__FILECACHEMANAGER_H_
