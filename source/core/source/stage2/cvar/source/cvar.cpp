#define EXILE_PRIVATE
#include <exile/core/cvar.hpp>
#include <exile/core/thread/mutex.hpp>
#include <exile/core/hash.hpp>
#include <exile/core/containers/vector.hpp>

#define ContaintsKey(map, k)(map.find(k) != map.end())


namespace exile
{
	namespace core
	{
		template<class T>
		struct CVarArray
		{
			CVarStorage<T>* cvars;
			u32 lastCVar{0};

			CVarArray(u64 size)
			{
				cvars = exile::memory::AllocArray<CVarStorage<T>>(size);
			}
			
			void Alloc(u64 size)
			{
				if (cvars != NULL)
				{
					Clear();
				}
				cvars = exile::memory::AllocArray<CVarStorage<T>>(size);
			}

			CVarStorage<T>* GetCurrent(u32 index)
			{
				return &cvars[index];
			}

			void SetCurrent(u32 index, const T& val)
			{
				cvars[index].current = val;
			}

			void Clear()
			{
				if (cvars != NULL)
				{
					exile::memory::FreeArr(cvars);
				}
			}

			u32 Add(const T& initialValue, const T& currentValue, CVarDesc* desc)
			{
				u32 index = lastCVar;

				cvars[index].current = currentValue;
				cvars[index].initial = initialValue;
				cvars[index].desc = desc;

				desc->index = index;

				lastCVar += 1;

				return index;
			}

			~CVarArray()
			{
				Clear();
			}
		};

		class CVarSystemImpl final : public exile::core::CVarSystem
		{
		public:
			//EXILE_SINGLETONE(exile::core::CVarSystemImpl)

		private:

			std::mutex mutex;
			exile::UnorderedMap<u32, exile::core::CVarDesc> savedCVars;

			CVarArray<exile::String> stringCVars;
			CVarArray<f64> floatCVars;
			CVarArray<i32> intCVars;

		private:


			__forceinline CVarDesc* InitCVar(const char* name, const char* desc)
			{
				u32 hash = exile::hash::fnv1a32(name);
				savedCVars[hash] = CVarDesc{};

				CVarDesc& cvDesc = savedCVars[hash];

				cvDesc.name = name;
				cvDesc.desc = desc;

				return &cvDesc;
			}


			__forceinline u8 SetVariableValue(u32 hash, i32 val)
			{
				CVarDesc* desc = GetCVar(hash);
				if (desc == NULL) return EX_ERROR;

				intCVars.GetCurrent(desc->index)->current = val;
				return EX_SUCCESS;
			}

			//__forceinline u8 SetVariableValue(u32 hash, exile::String val)
			//{
			//	CVarDesc* desc = GetCVar(hash);
			//	if (desc == NULL) return EX_ERROR;

			//	stringCVars.GetCurrent(desc->index)->current = val;
			//	return EX_SUCCESS;
			//}


			__forceinline u8 SetVariableValue(u32 hash, const exile::String& val)
			{
				CVarDesc* desc = GetCVar(hash);
				if (desc == NULL) return EX_ERROR;

				stringCVars.GetCurrent(desc->index)->current = val;
				return EX_SUCCESS;
			}

			__forceinline u8 SetVariableValue(u32 hash, f64 val)
			{
				CVarDesc* desc = GetCVar(hash);
				if (desc == NULL) return EX_ERROR;

				floatCVars.GetCurrent(desc->index)->current = val;
				return EX_SUCCESS;
			}



		public:
			CVarSystemImpl(const u32 stringCVarsCount, const u32 floatCVarsCount, const u32 intCVarsCount)
				:stringCVars(stringCVarsCount), floatCVars(floatCVarsCount), intCVars(intCVarsCount)
			{

			}

			CVarSystemImpl()
				:stringCVars(200), floatCVars(1000), intCVars(1000)
			{

			}

			u8 Containts(u32 hash) override
			{
				return ContaintsKey(savedCVars, hash);
			}

			CVarDesc* GetCVar(u32 hash) override
			{
				std::unique_lock<std::mutex> lock(mutex);
				auto it = savedCVars.find(hash);

				if (it != savedCVars.end())
				{
					return &(*it).second;
				}

				return NULL;
			}

			CVarStorage<exile::String>* GetStringCVar(u32 index) override
			{
				return stringCVars.GetCurrent(index);
			}


			CVarStorage<exile::String>* GetStringCVar(const char* name) override
			{
				CVarDesc* desc = GetCVar(exile::hash::fnv1a32(name));
				return desc == NULL ? NULL : stringCVars.GetCurrent(desc->index);
			}

			CVarDesc* CreateStringCVar(const char* name, const char* desc, const exile::String& defaultValue, const exile::String& currentValue) override
			{
				std::unique_lock<std::mutex> lock(mutex);
				CVarDesc* v = InitCVar(name, desc);
				exAssertDebugFR(v == NULL, {}, NULL, "failed to initialize CVar %s, %s", name, desc);

				v->type = CVarDataType::String;

				stringCVars.Add(defaultValue, currentValue, v);

				return v;
			}

			CVarStorage<i32>* GetIntCVar(u32 index) override
			{
				return intCVars.GetCurrent(index);
			}

			CVarStorage<i32>* GetIntCVar(const char* name) override
			{
				CVarDesc* desc = GetCVar(exile::hash::fnv1a32(name));
				return desc == NULL ? NULL : intCVars.GetCurrent(desc->index);
			}
			CVarDesc* CreateIntCVar(const char* name, const char* desc, const i32 defaultValue, const i32 currentValue) override
			{
				std::unique_lock<std::mutex> lock(mutex);
				CVarDesc* v = InitCVar(name, desc);
				exAssertDebugFR(v == NULL, {}, NULL, "failed to initialize CVar %s, %s", name, desc);

				v->type = CVarDataType::Int;

				intCVars.Add(defaultValue, currentValue, v);

				return v;
			}

			CVarStorage<f64>* GetFloatCVar(u32 index) override
			{
				return floatCVars.GetCurrent(index);
			}

			CVarStorage<f64>* GetFloatCVar(const char* name) override
			{
				CVarDesc* desc = GetCVar(exile::hash::fnv1a32(name));
				return desc == NULL ? NULL : floatCVars.GetCurrent(desc->index);
			}

			CVarDesc* CreateFloatCVar(const char* name, const char* desc, const f64 defaultValue, const f64 currentValue) override
			{
				std::unique_lock<std::mutex> lock(mutex);
				CVarDesc* v = InitCVar(name, desc);
				exAssertDebugFR(v == NULL, {}, NULL, "failed to initialize CVar %s, %s", name, desc);

				v->type = CVarDataType::Float;

				floatCVars.Add(defaultValue, currentValue, v);

				return v;
			}


			u8 SetStringCVarVal(const char* name, const exile::String& val) override
			{
				return SetVariableValue(exile::hash::fnv1a32(name), val);
			}

			u8 SetStringCVarVal(u32 hash, const exile::String& val) override
			{
				return SetVariableValue(hash, val);
			}

			u8 SetIntCVarVal(const char* name, const i32 val)override
			{
				return SetVariableValue(exile::hash::fnv1a32(name), val);
			}

			u8 SetIntCVarVal(u32 hash, const i32 val)override
			{
				return SetVariableValue(hash, val);
			}

			u8 SetFloatCVarVal(const char* name, const f64 val)override
			{
				return SetVariableValue(exile::hash::fnv1a32(name), val);
			}

			u8 SetFloatCVarVal(u32 hash, const f64 val)override
			{
				return SetVariableValue(hash, val);
			}
		};
		
	}
}

static exile::core::CVarSystemImpl defaultImpl;

bool exile::core::CVarSystem::freeMemory = false;
exile::core::CVarSystem* exile::core::CVarSystem::impl = &defaultImpl;


void exile::core::CVarSystem::SetupImpl(CVarSystem* impl, bool freeMemory)
{
	exile::core::CVarSystem::freeMemory = freeMemory;
	exile::core::CVarSystem::impl = impl;
}

void exile::core::CVarSystem::SetupDefaultImpl()
{
	freeMemory = false;
	impl = &defaultImpl;
}


exile::core::CVarSystem* exile::core::CVarSystem::Get()
{
	return impl;
}

void exile::core::CVarSystem::Free()
{
	if (freeMemory) 
	{
		exile::memory::Free(impl);
	}
}


exile::core::AutoCVarFloat::AutoCVarFloat(const char* name, const char* description, double defaultValue)
{
	CVarSystem* cvars = CVarSystem::Get();
	u32 namehash = exile::hash::fnv1a32(name);
	if (cvars->Containts(namehash))
	{
		CVarDesc* desc = cvars->GetCVar(namehash);
		index = desc->index;
	}
	else
	{
		CVarDesc* desc = cvars->CreateFloatCVar(name, description, defaultValue, defaultValue);
		if (desc != NULL)
		{
			index = desc->index;
		}
	}
}

f64 exile::core::AutoCVarFloat::Get()
{
	return CVarSystem::Get()->GetFloatCVar(index)->current;
}

f64* exile::core::AutoCVarFloat::GetPtr()
{
	return &CVarSystem::Get()->GetFloatCVar(index)->current;
}

void exile::core::AutoCVarFloat::Set(f64 val)
{
	CVarSystem::Get()->GetFloatCVar(index)->current = val;
}

exile::core::AutoCVarInt::AutoCVarInt(const char* name, const char* description, i32 defaultValue)
{
	CVarSystem* cvars = CVarSystem::Get();
	u32 namehash = exile::hash::fnv1a32(name);
	if (cvars->Containts(namehash))
	{
		CVarDesc* desc = cvars->GetCVar(namehash);
		index = desc->index;
	}
	else
	{
		CVarDesc* desc = cvars->CreateIntCVar(name, description, defaultValue, defaultValue);
		if (desc != NULL)
		{
			index = desc->index;
		}
	}
}

i32 exile::core::AutoCVarInt::Get()
{
	return CVarSystem::Get()->GetIntCVar(index)->current;
}

i32* exile::core::AutoCVarInt::GetPtr()
{
	return &CVarSystem::Get()->GetIntCVar(index)->current;
}

void exile::core::AutoCVarInt::Set(i32 val)
{
	CVarSystem::Get()->GetIntCVar(index)->current = val;
}

exile::core::AutoCVarString::AutoCVarString(const char* name, const char* description, const exile::String& defaultValue)
{
	CVarSystem* cvars = CVarSystem::Get();
	u32 namehash = exile::hash::fnv1a32(name);
	if (cvars->Containts(namehash))
	{
		CVarDesc* desc = cvars->GetCVar(namehash);
		index = desc->index;
	}
	else
	{
		CVarDesc* desc = cvars->CreateStringCVar(name, description, defaultValue, defaultValue);
		if (desc != NULL)
		{
			index = desc->index;
		}
	}
}

const exile::String& exile::core::AutoCVarString::Get()
{
	return CVarSystem::Get()->GetStringCVar(index)->current;
}
exile::String* exile::core::AutoCVarString::GetPtr()
{
	return &CVarSystem::Get()->GetStringCVar(index)->current;
}

void exile::core::AutoCVarString::Set(const exile::String& val)
{
	CVarSystem::Get()->GetStringCVar(index)->current = val;
}