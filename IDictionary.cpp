#include "B_tree_node.cpp"

template <class Tkey, class Tdata> class IDictionary {
public:
    IDictionary(std::initializer_list<std::pair<Tkey, Tdata>> init_list) {
        for(auto pair:init_list)
            this->Add(pair.first, pair.second);
    }

    int GetSize() const{
        return tree.tree_size();
    }

    Tdata& Get(Tkey key) {
        tree.find_data(key);
    }

    Tdata Get(Tkey key) const { 
        tree.find_data(key);
    }

    bool Containskey(Tkey key) {
        return tree.ContainsKey(key);
    }

    void Add(Tkey key, Tdata data) {
        tree.add_new_node(key, data);
    }

    void Remove(Tkey key) {
        tree.delete_node(key);
    }
private:
   Binar_tree<Tkey, Tdata> tree;
};