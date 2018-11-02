#include <initializer_list>
#include <ostream>
#include <map>

template <typename Key>
class SVariable : public std::map<Key, SVariable<Key>>
{
    using Map = std::map<Key, SVariable<Key>>;
  public:
    using Map::Map;
    /**
     * constructors
     */
    SVariable() = default;

    SVariable(const Key &k) : Map() {
        this->atemplace(k, SVariable());
    }
    template <typename = std::enable_if_t<std::is_base_of<std::string, Key>::value>>
    SVariable(const char *k) : Map() {
        this->emplace(k, SVariable());
    }
    /**
     * operators 
     */
    operator Key() const {
        Key out{};
        for (auto &v : *this) out += v.first;
        return out;
    }
    /**
     * 
     */
    friend std::ostream &operator<<(std::ostream &out, const SVariable &var) {
        out << Key(var);
        return out;
    }
};

/* #include <iostream>
#include <string>
int main()
{
    int i{};
    SVariable<std::string> a{
        {"1", {{"2", "2"}, {"3", "4"}}}};

    std::cout << "-------->" << a["1"]["2"] << std::endl;
} */