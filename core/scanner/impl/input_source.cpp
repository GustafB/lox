#include "input_source.h"
#include <iostream>

namespace LoxInterpreter {

InputSource::InputSource(std::istream& is) noexcept
: d_bytes{std::istreambuf_iterator<Byte>{is}, std::istreambuf_iterator<Byte>{}}
, d_curr{std::begin(d_bytes)}
, d_token_start{std::begin(d_bytes)}
, d_end{std::end(d_bytes)}
, d_linum{0}
{ }

auto
InputSource::extract(std::size_t l_offset, std::size_t r_offset)
    -> std::string
{
    std::cout << "extract=" << std::string{d_token_start, d_curr + 1} << "\n";
    std::string literal = std::string{d_token_start + l_offset, d_curr + 1};
    return literal;
}

auto
InputSource::reset_start()
    -> void
{
    d_token_start = d_curr;
}

auto
InputSource::advance()
    -> Byte
{
    ++d_curr;
    ++d_linpos;
    return *(d_curr - 1);
}

auto
InputSource::peek() const
    -> Byte
{
    return peek_n();
}

auto
InputSource::peek_n(int n) const
    -> Byte
{
    return eof() ? '\0' : *(d_curr + n);
}

auto
InputSource::eof() const
    -> bool
{
    return d_curr >= d_end;
}

auto
InputSource::linum() const
    -> std::size_t
{
    // d_linpos = 0;
    return d_linum;
}

auto
InputSource::linpos() const
    -> std::size_t
{
    return d_linpos;
}

}
