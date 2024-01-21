#ifndef _EXILE_CORE_CME_CMD_SETV_HPP_
#define _EXILE_CORE_CME_CMD_SETV_HPP_

#include <exile/core/instance.hpp>

namespace exile
{
	namespace cme
	{
		class CmdSetV : public exile::cme::ICommand
		{
		public:

			u8 Execute(const exile::Vector<exile::String>& args) override
			{
				u64 argsCount = args.size();
				if (argsCount < 2)
				{
					exGEngine.GetULP().Log(exGEngine.GetULP().GetCoreId(), exile::LogLevel::Error, "failed to execute command setV, not enough arguments");
					return EX_ERROR;
				}
				else if(argsCount > 2)
				{
					if (args[1][0] == '\"')
					{
						exile::String val = "";
						for (u64 i = 1; i < argsCount; i++)
						{
							exile::String carg = args[i];
							u64 cargLen = carg.size();
							if (carg[0] == '\"')
							{
								val += carg.substr(1, cargLen);
								val += ' ';
							}
							else if (carg[cargLen - 1] == '\"')
							{
								val += carg.substr(0, cargLen-1);
								break;
							}
							else
							{
								val += carg;
								val += ' ';
							}
						}
						exGEngine.GetEnv().RegisterVariableAuto(args[0], val);
					}
					else
					{
						exGEngine.GetULP().Log(exGEngine.GetULP().GetCoreId(), exile::LogLevel::Error, "unexpected value");
					}
				}
				else
				{
					exile::String carg = args[1];
					if (carg[0] == '\"')
					{
						carg.erase(std::remove(carg.begin(), carg.end(), '\"'), carg.end());
						exGEngine.GetEnv().RegisterVariable(args[0], carg);
						exGEngine.GetEnv().RegisterVariable(args[0], carg);
					}
					else
					{
						exGEngine.GetEnv().RegisterVariableAuto(args[0], carg);
					}
				}

				return EX_SUCCESS;
			}

		};
	}
}

#endif