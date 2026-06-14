#ifndef HANDLE_HPP
#define HANDLE_HPP

#include <cstdint>

template < typename T, std::uint32_t Invalid = 0xFFFFFFFF >
class Handle
{
  public:
	Handle() = default;
	Handle(std::uint32_t index, std::uint32_t generation);

  public:
	auto isValid() const -> bool;
	auto getIndex() const -> std::uint32_t;
	auto getGen() const -> std::uint32_t;

  public:
	auto operator==(const Handle< T, Invalid >& other) const -> bool;
	auto operator!=(const Handle< T, Invalid >& other) const -> bool;

  private:
	static constexpr std::uint32_t INDEX_MASK		= 0x000FFFFF;
	static constexpr std::uint32_t GENERATION_MASK	= 0xFFF00000;
	static constexpr std::uint32_t GENERATION_SHIFT = 20;

	std::uint32_t handle_ = Invalid;
};

template < typename T, std::uint32_t Invalid >
Handle< T, Invalid >::Handle(std::uint32_t index, std::uint32_t generation)
{
	handle_ = ((generation & GENERATION_MASK) << GENERATION_SHIFT)
			  | (index & INDEX_MASK);
}

template < typename T, std::uint32_t Invalid >
auto Handle< T, Invalid >::isValid() const -> bool
{
	return handle_ != Invalid;
}

template < typename T, std::uint32_t Invalid >
auto Handle< T, Invalid >::getIndex() const -> std::uint32_t
{
	return handle_ & INDEX_MASK;
}

template < typename T, std::uint32_t Invalid >
auto Handle< T, Invalid >::getGen() const -> std::uint32_t
{
	return (handle_ >> GENERATION_SHIFT) & GENERATION_MASK;
}

template < typename T, std::uint32_t Invalid >
auto Handle< T, Invalid >::operator==(const Handle< T , Invalid>& other) const -> bool
{
	return handle_ == other.handle_;
}

template < typename T, std::uint32_t Invalid >
auto Handle< T, Invalid >::operator!=(const Handle< T, Invalid >& other) const -> bool
{
	return handle_ != other.handle_;
}

#endif // !HANDLE_HPP
