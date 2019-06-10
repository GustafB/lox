#ifndef INCLUDED_INPUT_SOURCE
#define INCLUDED_INPUT_SOURCE

#include <string>
#include <vector>
#include <iterator>
#include <istream>

namespace LoxInterpreter {

class Source
{
  protected:
    using Byte = char;
    using ByteContainer = std::vector<Byte>;
    using ByteIter = ByteContainer::const_iterator;

  public:
    virtual ~Source() { };

    virtual auto advance() -> Byte = 0;
    virtual auto peek() const -> Byte = 0;
    virtual auto peek_n(int n = 0) const -> Byte = 0;
    virtual auto eof() const -> bool = 0;
    virtual auto linum() const -> std::size_t = 0;
    virtual auto linpos() const -> std::size_t = 0;
    virtual auto extract(std::size_t l_offset = 0, std::size_t r_offset = 0) -> std::string = 0;
    virtual auto reset_start() -> void = 0;
};

class InputSource : public Source
{
  public:
    explicit InputSource(std::istream&) noexcept;

    InputSource(const InputSource&) = delete;
    InputSource& operator=(const InputSource&) = delete;
    InputSource(InputSource&&) = delete;
    InputSource& operator=(InputSource&&) = delete;

    auto advance() -> Byte override;
    auto peek() const -> Byte override;
    auto peek_n(int n = 0) const -> Byte override;
    auto eof() const -> bool override;
    auto linum() const -> std::size_t override;
    auto linpos() const -> std::size_t override;
    auto extract(std::size_t l_offset = 0, std::size_t r_offset = 0) -> std::string override;
    auto reset_start() -> void override;

  private:
    ByteContainer d_bytes;
    ByteIter d_curr;
    ByteIter d_token_start;
    ByteIter d_end;
    std::size_t d_linum;
    std::size_t d_linpos;

};

}

#endif
