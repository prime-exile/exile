#ifndef _EXILE_CORE_CME_SHELL_HPP_
#define _EXILE_CORE_CME_SHELL_HPP_

#include <exile/core/API.h>


namespace exile
{
	namespace cme
	{
		class CentralManagmentEngine;

		class IShell
		{
		protected:

			exile::cme::CentralManagmentEngine* centralManagmentEngine;

		public:
			IShell(exile::cme::CentralManagmentEngine* centralManagmentEngine)
				:centralManagmentEngine(centralManagmentEngine)

			{}

			IShell(const IShell&) = delete;

			virtual u8 IsOpen()
			{
				return false;
			}

			virtual void Update(){}

			exile::cme::IShell& operator=(exile::cme::IShell& other) = delete;
			exile::cme::IShell& operator==(exile::cme::IShell& other) = delete;

			virtual ~IShell(){}
		};
	}
}

#endif