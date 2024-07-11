#pragma once

#include "visca_common.hpp"

namespace VISCA
{
//############################################################################//

	struct ACK
	{
		VISCA::Address    address;
		VISCA::Pack<4>    socket;
		VISCA::Terminator terminator;
	};

//############################################################################//

	template< class T = void >
	struct Completion
	{
		VISCA::Address    address;
		VISCA::Pack<5>    socket;
		VISCA::Terminator terminator;
	};
	//@TODO
	/*template< class T >
	struct Completion<T>
	{
		VISCA::Address    address;
		VISCA::Pack<5>    socket;
		T                 data;
		VISCA::Terminator terminator;
	};*/

//############################################################################//

	struct Error
	{
		VISCA::Address    address;
		VISCA::Pack<6>    socket;
		uint8_t           error;
		VISCA::Terminator terminator;
	
		enum EValue
		{
			LENGHT        = 0x01,
			SYNTAX        = 0x02,
			BUFFER_FULL   = 0x03,
			CANCELLED     = 0x04,
			NO_SOCKET     = 0x05,
			NO_EXECUTABLE = 0x41,
		};
	};

//############################################################################//
}
