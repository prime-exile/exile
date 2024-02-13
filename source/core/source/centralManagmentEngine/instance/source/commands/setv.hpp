#ifndef _EXILE_CORE_CME_CMD_SETV_HPP_
#define _EXILE_CORE_CME_CMD_SETV_HPP_

#include <exile/core/instance.hpp>

namespace exile
{
	namespace cme
	{
		class CmdCreateV : public exile::cme::ICommand
		{
		protected:
			inline void SetV(const char* name, const char* desc, exile::core::CVarDataType dt, const char* currentValue, const char* defaultValue = (const char*)NULL)
			{
				exile::core::CVarSystem* cvars = exile::core::CVarSystem::Get();

				if (cvars->Containts(exile::hash::fnv1a32(name)))
				{
					switch (dt)
					{
					case exile::core::String:
					{
						cvars->SetStringCVarVal(name, currentValue);
					}
					break;
					case exile::core::Int:
					{
						cvars->SetIntCVarVal(name, atoi(currentValue));
					}
					break;
					case exile::core::Float:
					{
						cvars->SetFloatCVarVal(name, atof(currentValue));
					}
					break;
					}
				}
				else
				{
					switch (dt)
					{
					case exile::core::String:
					{
						cvars->CreateStringCVar(name, desc, defaultValue, currentValue);
					}
						break;
					case exile::core::Int:
					{
						cvars->CreateIntCVar(name, desc, atoi(defaultValue), atoi(currentValue));
					}
						break;
					case exile::core::Float:
					{
						cvars->CreateFloatCVar(name, desc, atof(defaultValue), atof(currentValue));
					}
						break;
					}
				}

			}

			i32 ReadArg(exile::String& out, const exile::Vector<exile::String>& args, i32 start = 0)
			{
				i32 counter = start;
				const exile::String& farg = args[counter];
				u32 len = args.size();
				if (farg[0] == '\"')
				{
					if (farg[farg.size() - 1] == '\"')
					{
						out = farg.substr(1, farg.size() - 2);
						counter += 1;
						return counter;
					}

					for (; counter < len; counter += 1)
					{
						const exile::String& arg = args[counter];
						const i32 argLen = arg.size();

						if (arg[0] == '\"')
						{
							out += arg.substr(1, argLen);
						}
						else if (arg[argLen - 1] == '\"')
						{
							out += " ";
							out += arg.substr(0, argLen - 1);
							counter += 1;
							break;
						}
						else
						{
							out += " ";
							out += arg;
						}
					}
				}
				else
				{
					out = args[counter];
					counter += 1;
				}

				return counter;
			}


			exile::core::CVarDataType StringToDataType(const char* str)
			{
				if (strcmp(str, "Int") == 0)
				{
					return exile::core::CVarDataType::Int;
				}
				else if (strcmp(str, "Float") == 0)
				{
					return exile::core::CVarDataType::Float;
				}
				else if (strcmp(str, "String") == 0)
				{
					return exile::core::CVarDataType::String;
				}
			}
		public:

			virtual const char* GetName() override
			{
				return "createV";
			}
			
			// CreateV (dt) (name) (val) (dval) (desc)
			virtual u8 Execute(const exile::Vector<exile::String>& args) override
			{
				u64 argsCount = args.size();
				exile::UniversalLoggingProtocol* ulp = exile::UniversalLoggingProtocol::Get();
				const exile::LogId& id = ulp->GetCoreId();

				if (argsCount <= 4)
				{
					ulp->Log(id, exile::LogLevel::Error, "failed to execute command setV, not enough arguments");
					return EX_ERROR;
				}
				else if (argsCount > 4)
				{
					const exile::String& dt = args[0];
					const exile::String& name = args[1];
					exile::String value;
					i32 counter = ReadArg(value, args, 2);
					exile::String dval;
					counter = ReadArg(dval, args, counter);
					exile::String desc;
					counter = ReadArg(desc, args, counter);
					SetV(name.c_str(), desc.c_str(), StringToDataType(dt.c_str()), value.c_str(), dval.c_str());
				}

				return EX_SUCCESS;
			}

		};
		class CmdSetV : public CmdCreateV
		{
			const char* GetName() override
			{
				return "setV";
			}

			// SetV (dt) (name) (value)
			u8 Execute(const exile::Vector<exile::String>& args) override
			{
				u64 argsCount = args.size();
				exile::UniversalLoggingProtocol* ulp = exile::UniversalLoggingProtocol::Get();
				const exile::LogId& id = ulp->GetCoreId();

				if (argsCount < 2)
				{
					ulp->Log(id, exile::LogLevel::Error, "failed to execute command setV, not enough arguments");
					return EX_ERROR;
				}
				else if (argsCount > 2)
				{
					const exile::String& dt = args[0];
					const exile::String& name = args[1];
					exile::String value;
					i32 counter = ReadArg(value, args, 2);
					SetV(name.c_str(), "", StringToDataType(dt.c_str()), value.c_str());
				}

				return EX_SUCCESS;
			}
		};
	}
}

#endif