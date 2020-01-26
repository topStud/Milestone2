//
// Created by topaz on 16/01/2020.
//

#ifndef MILESTONE2__SOLUTION_H_
#define MILESTONE2__SOLUTION_H_

#include <string>

/**
 * Solution interface.
 * @tparam T
 */
template <typename T>
class Solution {
    virtual void edit_solution_representation() = 0;
    virtual T get_solution() = 0;
};

#endif //MILESTONE2__SOLUTION_H_