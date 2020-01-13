//
// Created by topaz on 12/01/2020.
//

#ifndef MILESTONE2__CACHEMANAGER_H_
#define MILESTONE2__CACHEMANAGER_H_

#include <string>

template <typename Value>
class CacheManager {
 public:
  virtual bool exist_in_cache(std::string key) = 0;
  virtual Value get(std::string key) = 0;
  virtual void save(std::string key, Value value) = 0;
};

#endif //MILESTONE2__CACHEMANAGER_H_
