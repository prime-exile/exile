#ifndef _EXILE_CORE_CME_CMD_ECHO_HPP_
#define _EXILE_CORE_CME_CMD_ECHO_HPP_

#include <inttypes.h>

namespace exile
{
	namespace cme
	{
		class CmdEcho : public exile::cme::ICommand
		{
		public:

			u8 Execute(const exile::Vector<exile::String>& args) override
			{
				exile::core::Engine& engine = exGEngine;
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
						else if (arg == "$thread_id")
						{
							engine.GetULP().Log(id, exile::LogLevel::Info, "panic thread id = \'%" PRIu64 "\'", engine.GetCME().GetThreadId());
						}
						else if (arg == "$report")
						{
							engine.GetCME().GetCommandEngine().Execute("echo $dtcbuild");
							engine.GetCME().GetCommandEngine().Execute("echo $panic_msg");
							engine.GetCME().GetCommandEngine().Execute("echo $stacktrace");
							engine.GetCME().GetCommandEngine().Execute("echo $thread_id");
						}
						else
						{
							exile::String varName = arg.substr(1, arg.size());

							if (!exGEngine.GetEnv().Contains(varName))
							{
								engine.GetULP().Log(id, exile::LogLevel::Info, " variable \'%s\' not found", varName.c_str());
							}
							else
							{
								exile::core::VariableValue& val = exGEngine.GetEnv().GetVariable(varName).GetValue();
								switch (val.GetDataType())
								{
								case exile::core::VariableValueDataType::integer:
									engine.GetULP().Log(id, exile::LogLevel::Info, " %s=\'%" PRIu64 "\'", varName.c_str(), val.GetValue<u64>());
									break;
								case  exile::core::VariableValueDataType::string:
									exile::String* ptr = val.GetValue<exile::String*>();
									engine.GetULP().Log(id, exile::LogLevel::Info, " %s=\'%s\'", varName.c_str(), ptr->c_str());
									break;
								}
							}

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