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

template <typename Value>
bool FileCacheManager<Value>::exist_in_cache(std::string key) {
  if (_cache.find(key) != _cache.end())
    return true;
  else {
    std::ifstream in_file;
    in_file.open(key);

    if (in_file.is_open()) {
      in_file.close();
      return true;
    }
  }
  return false;
}

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

template <typename Value>
void FileCacheManager<Value>::add_most_recently_used(std::string key, Value value) {
  least_recently_list.push_front(key);
  _cache.insert({key, {value, least_recently_list.begin()}});
}

template <typename Value>
void FileCacheManager<Value>::erase_least_recently_used() {
  _cache.erase(least_recently_list.back());
  least_recently_list.erase(--least_recently_list.end());
}

template <typename Value>
Value FileCacheManager<Value>::get(std::string key) {
  // if in cache, updates the key to be most recently used
  if (_cache.find(key) != _cache.end()) {
    least_recently_list.remove(key);
    least_recently_list.push_front(key);
    _cache[key].second = least_recently_list.begin();
    return _cache[key].first;
  } else {
    Value lru_value = _cache.find(least_recently_list.back())->second.first;
    // searches in files
    try {
      Value mru_value = read_from_file(key, lru_value);
      erase_least_recently_used();
      add_most_recently_used(key, mru_value);
      return mru_value;
    } catch (const char *e) {
      std::cerr << e << std::endl;
    }
  }
}

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
  in_file >> value;
  in_file.close();
  return value;
}

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
