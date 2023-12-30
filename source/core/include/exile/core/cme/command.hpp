#ifndef _EXILE_CORE_CME_COMMAND_HPP_
#define _EXILE_CORE_CME_COMMAND_HPP_

#include <exile/core/API.h>
#include <exile/core/containers/vector.hpp>
#include <exile/core/containers/string.hpp>

namespace exile
{
	namespace cme
	{
		class ICommand
		{
		public:
			virtual u8 Execute(const exile::Vector<exile::String>& args)
			{
				return EX_SUCCESS;
			}

		};
	}
}

#endif