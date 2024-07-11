#pragma once

#include "visca_common.hpp"

namespace VISCA
{
//############################################################################//

	struct IF_Clear
	{
		VISCA::Address    address;
		const uint8_t     command[3] = { 0x01, 0x00, 0x01 };
		VISCA::Terminator terminator;
	};
	struct Cancel
	{
		VISCA::Address    address;
		VISCA::Pack<2>    data;
		VISCA::Terminator terminator;
	};

//############################################################################//

	namespace Zoom
	{
		struct Stop
		{
			VISCA::Address    address;
			const uint8_t     command[3] = { 0x01, 0x04, 0x07 };
			const uint8_t     data       = { 0x00 };
			VISCA::Terminator terminator;
		};
		struct Tele
		{
			VISCA::Address    address;
			const uint8_t     command[3] = { 0x01, 0x04, 0x07 };
			const uint8_t     data       = { 0x02 };
			VISCA::Terminator terminator;
		};
		struct Wide
		{
			VISCA::Address    address;
			const uint8_t     command[3] = { 0x01, 0x04, 0x07 };
			const uint8_t     data       = { 0x03 };
			VISCA::Terminator terminator;
		};
		struct TeleEx
		{
			VISCA::Address    address;
			const uint8_t     command[3] = { 0x01, 0x04, 0x07 };
			//0x0 - low | 0x07 - hight
			VISCA::Pack<2>    data;
			VISCA::Terminator terminator;
		};
		struct WideEx
		{
			VISCA::Address    address;
			const uint8_t     command[3] = { 0x01, 0x04, 0x07 };
			//0x0 - low | 0x07 - hight
			VISCA::Pack<3>    data;
			VISCA::Terminator terminator;
		};
		struct Direct
		{
			VISCA::Address    address;
			const uint8_t     command[3] = { 0x01, 0x04, 0x47 };
			//0x0000 (wide) | 0x4000 (tele)
			VISCA::Packed<4>  data;
			VISCA::Terminator terminator;
		};
	}

//############################################################################//

	struct ZoomFocus
	{
		VISCA::Address    address;
		const uint8_t     command[3] = { 0x01, 0x04, 0x47 };
		VISCA::Packed<4>  zoom;
		VISCA::Packed<4>  focus;
		VISCA::Terminator terminator;
	};

//############################################################################//

	namespace Focus
	{
		struct Stop
		{
			VISCA::Address    address;
			const uint8_t     command[3] = { 0x01, 0x04, 0x08 };
			const uint8_t     data       = { 0x00 };
			VISCA::Terminator terminator;
		};
		struct Far
		{
			VISCA::Address    address;
			const uint8_t     command[3] = { 0x01, 0x04, 0x08 };
			const uint8_t     data       = { 0x02 };
			VISCA::Terminator terminator;
		};
		struct Near
		{
			VISCA::Address    address;
			const uint8_t     command[3] = { 0x01, 0x04, 0x08 };
			const uint8_t     data       = { 0x03 };
			VISCA::Terminator terminator;
		};
		struct FarEx
		{
			VISCA::Address    address;
			const uint8_t     command[3] = { 0x01, 0x04, 0x08 };
			VISCA::Pack<2>    data; // [slow 0:7 fast]
			VISCA::Terminator terminator;
		};
		struct NearEx
		{
			VISCA::Address    address;
			const uint8_t     command[3] = { 0x01, 0x04, 0x08 };
			VISCA::Pack<3>    data; // [slow 0:7 fast]
			VISCA::Terminator terminator;
		};
		struct Direct
		{
			VISCA::Address    address;
			const uint8_t     command[3] = { 0x01, 0x04, 0x48 };
			VISCA::Packed<4>  data;
			VISCA::Terminator terminator;
		};
		struct OnePushAF
		{
			VISCA::Address    address;
			const uint8_t     command[3] = { 0x01, 0x04, 0x18 };
			const uint8_t     data       = { 0x03 };
			VISCA::Terminator terminator;
		};
		struct MODE
		{
			VISCA::Address    address;
			const uint8_t     command[3] = { 0x01, 0x04, 0x38 };
			      uint8_t     data; //0x02 - auto | 0x03 - manual | 0x10 toggle
			VISCA::Terminator terminator;

			enum EValue
			{
				AUTO   = 0x02,
				MANUAL = 0x03,
				TOGGLE = 0x10,
			};
		};
	}

//############################################################################//
}