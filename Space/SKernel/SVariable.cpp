#include <initializer_list>
#include <iostream>
#include <string>
#include <map>
#include <list>

using namespace std;

template <class Key>
class SVariable
{
  public:
    using Map = map<Key, SVariable>;
    /**
     * constructors
     */
    SVariable() : __map() {
    }
    SVariable(const Key& k) : __map() {
        __map[k] = SVariable();
    }
    SVariable(const char* k) : __map() {
        __map[k] = SVariable();
    }
    SVariable(initializer_list<pair<const Key, SVariable>> l) : __map() {
        for (auto v : l) {
             __map[v.first] = v.second;
        }
    }
    /**
     * operators 
     */
    SVariable &operator[](Key k) {
        return __map[k];
    }
    operator Key() const {
        Key out = 0;
        for(auto& v :__map) out += v.first;
        return out;
    }
    friend ostream& operator<< (ostream &out, const SVariable &v){
        out << Key(v);
        return out;
    }
  private:
    Map __map;
};

int main()
{
    SVariable<float> a {
        {1, {
            {2, 2},
            {3, 4}
        }}
    };

    cout << "-------->" << a[1][2] << endl;
}