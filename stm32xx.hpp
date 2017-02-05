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

    constexpr T value() const noexcept
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

struct alias_address : base<uint32_t> {
    using base::base;
};

constexpr address operator+(const address& a, const offset& b)
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

constexpr alias_address bit_band_alias(const address addr, uint32_t bitnum)
{
    return alias_address((addr.value() & 0xF0000000) + 0x02000000 + ((addr.value() & 0xFFFFF) << 5) + (bitnum << 2));
}

} // End of namespace stm32xx
