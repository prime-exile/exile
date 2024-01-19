#ifndef _EXILE_CORE_CME_CMD_EXIT_HPP_
#define _EXILE_CORE_CME_CMD_EXIT_HPP_

namespace exile
{
	namespace cme
	{
		class CmdExit : public exile::cme::ICommand
		{
		public:

			u8 Execute(const exile::Vector<exile::String>& args) override
			{
				exile::LogId id = exGEngine.GetULP().GetCoreId();

				exGEngine.GetCME().SetContinueExectionState(false);
				
				return EX_SUCCESS;
			}

		};
	}
}

#endif