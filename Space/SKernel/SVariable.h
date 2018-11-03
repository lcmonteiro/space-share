#include <initializer_list>
#include <iostream>
#include <vector>
#include <map>

template <typename Key>
class SVariable : public std::map<Key, SVariable<Key>>
{
    using Map = std::map<Key, SVariable<Key>>;
  public:
    /**
     * public types
     */
    using Type = Key;
    /**
     * constructors
     */
    using Map::Map;

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
     * serialize 
     */
    friend std::ostream &operator<<(std::ostream &out, const SVariable &var) {
       if(!var.empty()) {
            out << "[";
            for(auto& v : var){
                out << v.first << v.second;
            }
            out << "]";
        }
        return out;
    }
    friend std::istream &operator>>(std::istream &in, SVariable &var) {
        class myctype : public std::ctype<char> {
                static mask* make_table(std::vector<char> spaces) {
                        static std::vector<mask> table(
                                std::ctype<char>::classic_table(),
                                std::ctype<char>::classic_table() + std::ctype<char>::table_size
                        );
                        for(auto s :spaces) {
                            table[s] |= space;
                        }
                        return table.data();
                }
        public:
                myctype(std::vector<char> s ) : std::ctype<char>(make_table(s)) {
                }
        };
        static myctype ct({'[',']'});
        
        in.imbue(std::locale(in.getloc(), new myctype({'[',']'})));

        while(in.good()){    
            Key k;
            in >> k;
            switch(in.get()) {
                case '[' :{
                    var.emplace(k, SVariable());
                    in >> var[k];
                    break;
                }
                case ']' :{
                    var.emplace(k, SVariable());
                    return in;
                }
                default:{
                    return in;
                }
            }
        }
        return in;
    }
};