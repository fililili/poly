#include <memory>
#include <iostream>

template <typename derived>
struct erased_contain_ptr {
    erased_contain_ptr(void *ptr) : _ptr{ptr} { }
    erased_contain_ptr(const erased_contain_ptr& other) : _ptr{other.ptr} {}
    ~erased_contain_ptr() {
        auto pd = static_cast<derived*>(this);
        auto&& deleter = pd->get_deletor();
        deleter(_ptr);
    }

    template <typename T>
    T* get() const {
        void *ptr = _ptr;
        return static_cast<T*>(ptr);
    }
private:
    void *_ptr;
};

template <typename T>
struct contain_ptr : public erased_contain_ptr<contain_ptr<T> > {
    using base = erased_contain_ptr<contain_ptr<T> >;
    auto get_deletor() {
        return [](void *ptr) {
            auto p = static_cast<T*>(ptr);
            auto deletor = std::default_delete<T>{};
            deletor(p);
        };
    }
    T* get() const {
        return base::template get<T>();
    }

    contain_ptr(T *ptr) : base{ptr} {}
};

struct foo {
    foo() {
        std::cout << "ctor" << std::endl;
    }
    ~foo() {
        std::cout << "dtor" << std::endl;
    }
    int a {4};
};

int main() {
    contain_ptr p{new foo};
    std::cout << p.get()->a << std::endl;
}
