struct singer {
    void sing() {}
};

struct dancer {
    void dance() {}
};

// both singer and cancer is virtual inheritance
template <typename idol>
struct base_idol {
    void sing_and_dance() {
        auto&& i = static_cast<idol&>(*this);

        auto&& s = static_cast<singer&>(i);
        auto&& d = static_cast<dancer&>(i);

        s.sing();
        d.dance();
    }
};

struct idol : public singer, public dancer, public base_idol<idol> {};


// singer is virtual inheritance, dancer is normal inheritance
template <typename idol>
struct base_idol_1 : public singer {
    void sing_and_dance() {
        auto&& i = static_cast<idol&>(*this);

        auto&& s = static_cast<singer&>(*this);
        auto&& d = static_cast<dancer&>(i);

        s.sing();
        d.dance();
    }
};

struct idol_1 : public dancer, public base_idol_1<idol_1> {};

int main() {
    idol i;
    i.sing_and_dance();

    idol_1 i1;
    i1.sing_and_dance();
}
