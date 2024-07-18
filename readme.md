C++20?? implementation of a type-safe library for working with VISCA.

The library contains only types, program behavior should be set manually.

## adding new packet type
There are 2 auxiliary classes that encode values in VISCA packets
* VISCA::Pack <N> - specifies a byte that is encoded as 0xNq where q is the payload and N is a constant
* VISCA::PackByte - specifies an auxiliary type, which is useful when parsing a protocol by byte-by-byte, inherited from Pack
* VISCA::Packed<N> - specifies a sequence of N bytes that are encoded as 0x0q 0x0q 0x0q 0x0q 0x0q, where q is a number encoded in Big Endian

There are also 2 classes that define specific fields for the VISCA package
* VISCA::Address - encodes the address of the packet
* VISCA::Terminator - encodes the byte-terminator of a packet
## example (fixed it, plz, ilb lazy)
<code>
Here is an example of an ACK command, which is encoded as follows
  z0 4y FF, where z is the device address and y is the command socket number
  Let's break down this example
		z0 is an address byte for which we have VISCA::Address type
		4y is an encoded socket value, for which we have VISCA::Pack<4> type (first octet).
		FF is a terminator for which we have VISCA::Terminator type.
	As a result, we get this structure
struct ACK
{
  VISCA::Address address;
  VISCA::Pack<4> socket;
  VISCA::Terminator terminator;
};

 Here is an example of an ACK command, which is encoded as follows
		8x 01 01 04 47 0q 0q 0q 0q 0q 0q 0q FF, where x is the device address and q is the zoom value in "parrots"
	Let's break down this example
    8x is an address byte, for which we have the VISCA::Address type.
    01 04 47 is constants, for which we have the const uint8_t[3] type.
    0q 0q 0q 0q 0q 0q is the encoded zoom value, for which we have the VISCA::Packed<4> type (4 bytes).
    FF is a terminator for which we have VISCA::Terminator type.
	As a result, we get this structure
	struct Direct
	{
		VISCA::Address address;
		const uint8_t command[3] = { 0x01, 0x04, 0x47 };
		VISCA::Packed<4> data;
		VISCA::Terminator terminator;
	};
</code>
	
	!!Be careful with alignment, if you use a type other than uchar8_t\char8_t alignment can change the packet size!!!
