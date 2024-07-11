#pragma once

#include <bit>
#include <compare>
#include <cstddef>
#include <cstring>

namespace VISCA
{
//############################################################################//

	class Address final
	{
	//### member : bitmask ###//
	public:
		uint8_t destination : 3 = 0x00; //[2:0]
		uint8_t broadcast   : 1 = 0x00; //[3]
		uint8_t source      : 3 = 0x00; //[6:4]
	private:
		uint8_t magic       : 1 = 0x01; //[7]
	
	//### constructor ###//
	public:
		constexpr Address() noexcept = default;
		constexpr Address(uint8_t destination) noexcept :
			source     (0),
			broadcast  (0),
			destination(destination) {}
		constexpr Address(uint8_t source, uint8_t destination) noexcept :
			source     (source),
			broadcast  (0)     ,
			destination(destination) {}
		constexpr Address(uint8_t source, uint8_t broadcast, uint8_t destination) noexcept :
			source     (source)   ,
			broadcast  (broadcast),
			destination(destination) {}
	//### constructor : static ###//
	public:
		static constexpr Address FromByte(uint8_t value) { return std::bit_cast<Address>(value); }

	//### constant ###//
	public:
		static const Address IP_ACK; //VISCA Over IP
		static const Address IP_CMD; //VISCA Over IP
	};
	inline constexpr Address Address::IP_CMD{ 0b000, 0b0, 0b001 }; //0x81
	inline constexpr Address Address::IP_ACK{ 0b001, 0b0, 0b000 }; //0x90

	static_assert(sizeof(Address) == sizeof(uint8_t), "Good luck"); //На случай если битовая маска не будет равна байту

//############################################################################//

	class Terminator final
	{
		const uint8_t terminator = 0xFF;
	};

//############################################################################//

	// Упакованные значения задаются как 0xNx где N это константа а x значение
	template< size_t N >
		requires (N <= 0xF) //Только 4 битная константа
	struct Pack final
	{
	//### member : bitmask ###//
	private:
		uint8_t data  : 4 = 0x00; //[3:0]
		uint8_t magic : 4 =    N; //[7:4]
	
	//### constructor ###//
	public:
		Pack() = default;
		Pack(uint8_t value) : data( value ) {}
	
	//### operator ###//
	public:
		      operator uint8_t()               const noexcept { return data; }
		Pack& operator =(const uint8_t& right)       noexcept { data = right; return *this; }

		template< size_t M > bool operator ==(const Pack<M>& right) const
		{
			auto l = std::bit_cast<uint8_t>(*this);
			auto r = std::bit_cast<uint8_t>(right);
			return l == r;
		}
		template< size_t M > auto operator<=>(const Pack<M>& right) const noexcept
		{
			auto l = std::bit_cast<uint8_t>(*this);
			auto r = std::bit_cast<uint8_t>(right);
			return l <=> r;
		}
	};

	using PackByte = Pack<static_cast<size_t>(-1)>; //Тип используемый для анализа значения байта

	template<>
	struct Pack<static_cast<size_t>(-1)> final
	{
	//### member : bitmask ###//
	public:
		uint8_t data  : 4; //[3:0]
		uint8_t magic : 4; //[7:4]

	//### constructor ###//
	public:
		Pack() = default;
		Pack(uint8_t value) { *this = std::bit_cast<PackByte>(value); }

	//### operator ###//
	public:
		template< size_t M > bool operator ==(const Pack<M>& right) const
		{
			auto l = std::bit_cast<uint8_t>(*this);
			auto r = std::bit_cast<uint8_t>(right);
			return l == r;
		}
		template< size_t M > auto operator<=>(const Pack<M>& right) const noexcept
		{
			auto l = std::bit_cast<uint8_t>(*this);
			auto r = std::bit_cast<uint8_t>(right);
			return l <=> r;
		}
	};

	static_assert(sizeof(Pack<0>)  == sizeof(uint8_t), "Good luck"); //На случай если тип не будет равен байту
	static_assert(sizeof(PackByte) == sizeof(uint8_t), "Good luck"); //На случай если тип не будет равен байту

//############################################################################//

	// Упакованные значения кодируются как { 0x0A,0x0B } где AB составное число в кодировке Big Endian
	template< size_t N >
	struct Packed final
	{
	//### meta-type ###//
	public:
		using value_type = decltype(([]()
			{
					 if constexpr ( N <= 2  ) return uint8_t();
				else if constexpr ( N <= 4  ) return uint16_t();
				else if constexpr ( N <= 8  ) return uint32_t();
				else if constexpr ( N <= 16 ) return uint64_t();
				else return;
			})());
	
	//### member ###//
	private:
		Pack<0> data[N];
	
	//### constructor ###//
	public:
		Packed() = default;
		Packed(value_type value) noexcept { this->set(value); }
		//### constructor : static ###//
	public:
		static constexpr Address FromData(const uint8_t* address) { Packed retval; std::memcpy(retval, address, sizeof(retval)); return retval; }
	
	//### operator ###//
	public:
		operator value_type() const noexcept
		{
			value_type retval = 0;
		
			for( int n = 0; n < N; n++) //@TODO: зависит от кодировки байт в системе
			{
				retval <<= 4;
				retval |= data[n];
			}
		
			return retval;
		}
		Packed& operator =(value_type right) noexcept
		{
			//auto retval = this->value();
		
			for( int n = N - 1; n >= 0; n-- ) //@TODO: зависит от кодировки байт в системе
			{
				auto tmp = static_cast<uint8_t>(right); //по хорошему добавить бы проверку типов...
				data[n] = tmp;
				right >>= 4;
			}
		
			return *this;
		}
	
		auto operator ==(const Packed& right) const noexcept
		{
			bool retval = true;
		
			for( int i=0; i<N; i++ )
			{
				retval &= data[i] == right.data[i];
			}
		
			return retval;
		}
		auto operator !=(const Packed& right) const noexcept {return !(*this==right); }
	};

	template<> struct Packed<0> {}; //Тип не может иметь нулевой размер

//############################################################################//
}