#include <memory>


class no_crtp_shared_from_this : public std::enable_shared_from_this<no_crtp_shared_from_this>
{
public:
    template <class Down>
    std::shared_ptr<Down> dynamic_cast_shared_from_this() {
        return std::dynamic_pointer_cast<Down>(shared_from_this());
    }
    template <class Down>
    std::shared_ptr<Down> static_cast_shared_from_this() {
        return std::static_pointer_cast<Down>(shared_from_this());
    }
};
