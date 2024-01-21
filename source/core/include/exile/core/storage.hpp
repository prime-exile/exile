#ifndef _EXILE_CORE_STORAGE_HPP_
#define _EXILE_CORE_STORAGE_HPP_

#include <exile/core/API.h>
#include <exile/core/memory.hpp>
#include <exile/core/containers/string.hpp>
#include <exile/core/containers/unordered_map.hpp>
#include <exile/core/string/u64ToString.hpp>

#define ContaintsKey(map, k)(map.find(k) != map.end())
#define ContaintsSym(s)(std::find_if(s.begin(), s.end(), ::isalpha) != s.end())

namespace exile
{
	namespace core
	{
		enum class VariableValueDataType
		{
			none,
			integer,
			string
		};
		
		class VariableValue
		{
			VariableValueDataType dt;
			void* data;

		public:

			VariableValue()
				:data(NULL), dt(VariableValueDataType::none)
			{

			}

			template<class T>
			VariableValue(T val)
				
			{
				if constexpr (std::is_same_v<u64, T> || std::is_same_v<i64, T>)
				{
					data = (void*)val;
					dt = VariableValueDataType::integer;
				}
				else if constexpr (std::is_same_v<exile::String, T> || std::is_same_v<const char*, T>)
				{
					data = reinterpret_cast<void*>(exile::memory::Alloc<exile::String>(val));
					dt = VariableValueDataType::string;
				}
			}

			__forceinline VariableValue(const VariableValue& other)
			{
				switch (other.dt)
				{
				case VariableValueDataType::string:
					data = reinterpret_cast<void*>(exile::memory::Alloc<exile::String>(
						reinterpret_cast<exile::String*>(other.data)->c_str()));
					dt = VariableValueDataType::string;
					break;
				case VariableValueDataType::integer:
					data = other.data;
					dt = VariableValueDataType::integer;
					break;
				}
			}

			__forceinline VariableValue& operator=(const VariableValue& other)
			{
				switch (other.dt)
				{
				case VariableValueDataType::string:
					data = reinterpret_cast<void*>(exile::memory::Alloc<exile::String>(
						reinterpret_cast<exile::String*>(other.data)->c_str()));
					dt = VariableValueDataType::string;
					break;
				case VariableValueDataType::integer:
					data = other.data;
					dt = VariableValueDataType::integer;
					break;
				}

				return *this;
			}

			template<class T>
			__forceinline T GetValue()
			{
				return reinterpret_cast<T>(data);
			}

			template<class T>
			__forceinline void SetValue(T val)
			{
				if constexpr (std::is_same_v<u64, T> || std::is_same_v<i64, T>)
				{
					data = val;
					dt = VariableValueDataType::integer;
				}
				else if constexpr (std::is_same_v<exile::String, T> || std::is_same_v<const char*, T>)
				{
					data = reinterpret_cast<void*>(exile::memory::Alloc<exile::String>(val));
					dt = VariableValueDataType::string;
				}
			}

			__forceinline VariableValueDataType GetDataType()
			{
				return dt;
			}
			
			~VariableValue()
			{
				if (data != NULL)
				{
					switch (dt)
					{
					case exile::core::VariableValueDataType::string:
						exile::memory::Free(reinterpret_cast<exile::String*>(data));
						break;
					default:
						break;
					}
				}
			}
		};


		class Variable
		{

			VariableValue value;
			exile::String desc;
		public:

			__forceinline Variable()
			{}

			__forceinline Variable(const VariableValue& value)
				:value(value)
			{}

			__forceinline Variable(const exile::String& desc)
				:desc(desc)
			{}

			__forceinline Variable(const VariableValue& value, const exile::String& desc)
				:value(value), desc(desc)
			{}

			__forceinline const exile::String& GetDesc()
			{
				return desc;
			}

			VariableValue& GetValue()
			{
				return value;
			}

			void SetValue(const VariableValue& newValue)
			{
				value = newValue;
			}
		};

		class EnvironmentStorage
		{
		private:

#if !defined(EXILE_DISABLE_VAR_STORAGE)
			exile::UnorderedMap<exile::String, Variable> vars;
#endif
		public:
			EnvironmentStorage()
			{}

			EnvironmentStorage(const PluginDepencyManager& other) = delete;

			__forceinline u8 Contains(const exile::String& name)
			{
#if !defined(EXILE_DISABLE_VAR_STORAGE)
				return ContaintsKey(vars, name);
#else 
				return EX_FALSE;
#endif
			}

			__forceinline Variable* GetVariable(const exile::String& name)
			{
#if defined(EXILE_DISABLE_VAR_STORAGE)
				return NULL;
#else 
				if (!ContaintsKey(vars, name)) return NULL;
				return &vars[name];
#endif
			}

			__forceinline u8 RegisterVariable(const exile::String& name, const Variable& info)
			{
#if defined(EXILE_DISABLE_VAR_STORAGE)
				return EX_SUCCESS;
#else
				exAssertFR(ContaintsKey(vars, name), {}, EX_ERROR, "failed to register variable '%s', variable with this name already exists", name.c_str());
				vars[name] = info;
				return EX_SUCCESS;
#endif

			}

			__forceinline u8 RegisterVariable(const exile::String& name, const exile::String value)
			{
#if defined(EXILE_DISABLE_VAR_STORAGE)
				return EX_SUCCESS;
#else
				exAssertFR(ContaintsKey(vars, name), {}, EX_ERROR, "failed to register variable '%s', variable with this name already exists", name.c_str());
				vars[name] = Variable(VariableValue(value));
				return EX_SUCCESS;
#endif
			}

			__forceinline u8 RegisterVariableAuto(const exile::String& name, const exile::String newValue)
			{
#if defined(EXILE_DISABLE_VAR_STORAGE)
				return EX_SUCCESS;
#else
				exAssertFR(ContaintsKey(vars, name), {}, EX_ERROR, "failed to register variable '%s', variable with this name already exists", name.c_str());
				if (ContaintsSym(newValue))
				{
					vars[name] = Variable(VariableValue(newValue));
				}
				else
				{
					vars[name] = Variable(VariableValue(atoll(newValue.c_str())));
				}
				
				return EX_SUCCESS;
#endif
			}

			exile::core::EnvironmentStorage& operator=(exile::core::PluginManager& other) = delete;
			exile::core::EnvironmentStorage& operator==(exile::core::PluginManager& other) = delete;

		};
	}
}

#endif	