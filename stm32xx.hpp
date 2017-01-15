#include  <utility>

namespace stm32xx { // Begin of namespace stm32xx

template <typename T>
class base {
public:
    constexpr explicit base(T t)
        : m_value(std::move(t))
    {

    }

    T& value() noexcept
    {
        return m_value;
    }

    constexpr const T& value() const noexcept
    {
        return m_value;
    }

private:
    T m_value;
};

struct address : base<uint32_t> {
    using base::base;
};

struct offset : base<uint32_t> {
    using base::base;
};

constexpr address operator+(const address& a, const offset&b)
{
    return address(a.value() + b.value());
}

constexpr address operator+(const offset& a, const address& b)
{
    return address(a.value() + b.value());
}

constexpr offset operator+(const offset& a, const offset& b)
{
    return offset(a.value() + b.value());
}

constexpr offset operator-(const address&a, const address&b)
{
    return offset(a.value() - b.value());
}

constexpr address operator-(const address&a, const offset& b)
{
    return address(a.value() - b.value());
}

constexpr offset operator-(const offset& a, const offset& b)
{
    return offset(a.value() - b.value());
}

} // End of namespace stm32xx
