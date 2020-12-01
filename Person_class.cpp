#include <iostream>
#include <vector>

class Person {
public:
    void SetInfo(std::vector<int> vec) {
      for (int i = 0; i < vec.size(); i ++) {
          parameters.push_back(vec[i]);
      }
    }

    int Get(int index) {
        return parameters[index];
    }
    
private:
    std::vector<int> parameters;
};