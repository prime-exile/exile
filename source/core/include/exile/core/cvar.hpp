#ifndef _EXILE_CORE_STORAGE_HPP_
#define _EXILE_CORE_STORAGE_HPP_

#include <exile/core/API.h>
#include <exile/core/memory.hpp>
#include <exile/core/containers/string.hpp>
#include <exile/core/containers/unordered_map.hpp>
#include <exile/core/string/u64ToString.hpp>

#include <algorithm>

#define ContaintsKey(map, k)(map.find(k) != map.end())
#define ContaintsSym(s)(std::find_if(s.begin(), s.end(), ::isalpha) != s.end())

namespace exile
{
	namespace core
	{

		enum CVarDataType
		{
			None,
			String,
			Int,
			Float
		};

		struct CVarDesc
		{
			exile::String name;
			exile::String desc;

			CVarDataType type;

			u32 index;

		};

		template<class T>
		struct CVarStorage
		{
			T initial;
			T current;

			CVarDesc* desc;

		};


		class EX_API CVarSystem
		{
			static bool freeMemory;
			static CVarSystem* impl;

		public:

			static void SetupImpl(CVarSystem* impl, bool freeMemory);
			static void SetupDefaultImpl();
			static void Free();

			static CVarSystem* Get();

			virtual CVarDesc* GetCVar(u32 hash) = 0;

			virtual u8 Containts(u32 hash) = 0;

			virtual CVarStorage<exile::String>* GetStringCVar(u32 index) = 0;
			virtual CVarStorage<exile::String>* GetStringCVar(const char* name) = 0;
			virtual CVarDesc* CreateStringCVar(const char* name, const char* desc, const exile::String& defaultValue, const exile::String& currentValue) = 0;
			virtual u8 SetStringCVarVal(const char* name, const exile::String& val) = 0;
			virtual u8 SetStringCVarVal(u32 hash, const exile::String& val) = 0;

			virtual CVarStorage<i32>* GetIntCVar(u32 index) = 0;
			virtual CVarStorage<i32>* GetIntCVar(const char* name) = 0;
			virtual CVarDesc* CreateIntCVar(const char* name, const char* desc, const i32 defaultValue, const i32 currentValue) = 0;
			virtual u8 SetIntCVarVal(const char* name, const i32 val) = 0;
			virtual u8 SetIntCVarVal(u32 hash, const i32 val) = 0;

			virtual CVarStorage<f64>* GetFloatCVar(u32 index) = 0;
			virtual CVarStorage<f64>* GetFloatCVar(const char* name) = 0;
			virtual CVarDesc* CreateFloatCVar(const char* name, const char* desc, const f64 defaultValue, const f64 currentValue) = 0;
			virtual u8 SetFloatCVarVal(const char* name, const f64 val) = 0;
			virtual u8 SetFloatCVarVal(u32 hash, const f64 val) = 0;
		};

		struct AutoCVar
		{
		protected:
			u32 index;

		};

		struct EX_API AutoCVarFloat : public AutoCVar
		{
			AutoCVarFloat(const char* name, const char* description, f64 defaultValue);

			f64 Get();
			f64* GetPtr();
			void Set(f64 val);
		};

		struct EX_API AutoCVarInt : public AutoCVar
		{
			AutoCVarInt(const char* name, const char* description, i32 defaultValue);

			i32 Get();
			i32* GetPtr();
			void Set(i32 val);
		};

		struct EX_API AutoCVarString : public AutoCVar
		{
			AutoCVarString(const char* name, const char* description, const exile::String& defaultValue);

			const exile::String& Get();
			exile::String* GetPtr();
			void Set(const exile::String& val);
		};
	}
}

#endif	