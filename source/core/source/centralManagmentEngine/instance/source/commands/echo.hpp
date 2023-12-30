#ifndef _EXILE_CORE_CME_CMD_ECHO_HPP_
#define _EXILE_CORE_CME_CMD_ECHO_HPP_

namespace exile
{
	namespace cme
	{
		class CmdEcho : public exile::cme::ICommand
		{
		public:

			u8 Execute(const exile::Vector<exile::String>& args) override
			{
				exile::core::Engine& engine = exile::core::Engine::Get();
				exile::LogId id = engine.GetULP().GetCoreId();
				engine.GetULP().Log(id, exile::LogLevel::Info, args[0]);

				return EX_SUCCESS;
			}

		};
	}
}

#endif