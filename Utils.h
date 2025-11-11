#include <utility>
#include <vector>
#include <algorithm>
#include <unordered_map>

template <typename T>
void removeValFromVector(std::vector<T*>& vect, T* object) {
    vect.erase(std::remove(vect.begin(), vect.end(), object), vect.end());
};

template <typename T>
struct ObjectWithFrequency{
    T t;
    int frequency;
    bool operator<(ObjectWithFrequency& otherObject) {
        return frequency < otherObject.frequency;
    }
};

template <typename T>
bool contains(std::vector<T*>& vect, T* object) {
    for (T* otherObj : vect) {
        if (otherObj == object) {
            return true;
        }
    }

    return false;
}


template <typename T>
class Counter {
    private:
        std::unordered_map<T, int> counter;
    public:

        std::vector<ObjectWithFrequency<T>> getSorted() const {

            std::vector<ObjectWithFrequency<T>> pairs;

            for (auto pair : counter) {
                pairs.push_back(ObjectWithFrequency<T>{pair.first, pair.second});
            }

            std::sort(pairs.begin(), pairs.end());

            return pairs;

        }

        typename std::unordered_map<T, int>::const_iterator begin() const {
            return counter.begin();
        }

        typename std::unordered_map<T, int>::const_iterator end() const {
            return counter.end();
        }

        void add(const std::vector<T>& objects ) {
            for (const T& obj : objects) {
                if (counter.find(obj) == counter.end()) {
                    counter[obj] = 1;
                }
                else {
                    counter[obj]++;
                }
            }
        }

        void add(T t) {
            if (counter.find(t) == counter.end()) {
                counter[t] = 1;
            }
            else {
                counter[t]++;
            }
        }

        int getCount(T& t) {
            if (counter.find(t) == counter.end()) {
                return 0;
            }

            return counter.at(t);
        }
};