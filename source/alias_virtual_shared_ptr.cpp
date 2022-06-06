#include <memory>
#include <iostream>

struct vTable {
    virtual void foo() = 0;
};

template <typename T>
struct imp : public vTable{
    void foo() override {
        sp->foo();
    }
    std::shared_ptr<T> sp;
};

template <typename T>
std::shared_ptr<vTable> make_v_shared(std::shared_ptr<T> sp) {
    imp<T> *it = new imp<T>;
    it->sp = sp;
    vTable *pv = it;
    return std::shared_ptr<vTable>{pv};
}

struct real {
    void foo() {
        std::cout << "foo real" << std::endl;
    }
};

int main() {
    auto pt = std::make_shared<real>();
    auto pv = make_v_shared<real>(pt);
    pv->foo();
}
