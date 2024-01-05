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

				for (exile::String arg : args)
				{
					if (arg[0] == '$')
					{
						if (arg == "$stacktrace")
						{
							exile::cme::CentralManagmentEngine& managment = engine.GetCME();
							engine.GetULP().Log(id, exile::LogLevel::Info, "cme stacktrace");
							for (const exile::String& entry : managment.GetStacktrace())
							{
								engine.GetULP().Log(id, exile::LogLevel::Info, entry);
							}
						}
						else if (arg == "$panic_msg")
						{
							exile::cme::CentralManagmentEngine& managment = engine.GetCME();
							engine.GetULP().Log(id, exile::LogLevel::Info, "cme panic message: \' %s \'", managment.GetPanicMessage().c_str());
						}
						else if (arg == "$dtcbuild")
						{
							engine.GetULP().Log(id, exile::LogLevel::Info, "core build date time: \'%s\'", EX_BUILD_DATETIME);
						}
						else if (arg == "$report")
						{
							engine.GetCME().GetCommandEngine().Execute("echo $dtcbuild");
							engine.GetCME().GetCommandEngine().Execute("echo $panic_msg");
							engine.GetCME().GetCommandEngine().Execute("echo $stacktrace");
						}
					}
					else
					{
						engine.GetULP().Log(id, exile::LogLevel::Info, arg);
					}
				}
				



				return EX_SUCCESS;
			}

		};
	}
}

#endif