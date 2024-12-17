#pragma once

#include "Public/PCH.h"
#include "Public/Core.h"

// TODO: Make sure you make std types not imported by making pointers to them.
template<class... Paramtypes>
class GameEngine_API MulticastDelegate
{
public:

	struct STDFunctionWrapper
	{
		std::function<void(Paramtypes...)> TheFunction;
		std::string FunctionName = "";
	};

	void Broadcast(Paramtypes... param)
	{
		for (auto currentPair : FunctionsPerObject)
		{
			const std::vector<STDFunctionWrapper>& functions = currentPair.second;
			for (const STDFunctionWrapper& currentFunction : functions)
			{
				currentFunction.TheFunction(param...);
			}
		}
	}
	
#define ADD_OBJECT(ClassType, ClassInstance, FunctionName) AddObject_Internal<ClassType>(ClassInstance, &ClassType::FunctionName, #FunctionName);

	void RemoveAll(void* inObjectToRemoveFrom)
	{
		if (FunctionsPerObject.count(inObjectToRemoveFrom))
		{
			FunctionsPerObject.erase(inObjectToRemoveFrom);
		}
	}

	// Call ADD_OBJECT instead of directly calling AddObject as it makes sure that name of the passed function pointer, and the function name is the same.
	template<class UserClass>
	void AddObject_Internal(UserClass* inObjectToAdd, void(UserClass::* inFunction)(Paramtypes...), const std::string& functionName)
	{
		if (inObjectToAdd == nullptr)
		{
			GameEngine_LOG(error, "MulticastDelegate::AddObject, inObjectToAdd is nullptr.");
			return;
		}

		if (inFunction == nullptr)
		{
			GameEngine_LOG(error, "MulticastDelegate::AddObject, inFunction is nullptr.");
			return;
		}

		if (functionName.length() == 0)
		{
			GameEngine_LOG(error, "MulticastDelegate::AddObject, functionName is empty string.");
			return;
		}

		if (FunctionsPerObject.count(inObjectToAdd))
		{
			const std::vector<STDFunctionWrapper>& currentFunctions = FunctionsPerObject.find(inObjectToAdd)->second;
			for (const STDFunctionWrapper& currentFunction : currentFunctions)
			{
				if (currentFunction.FunctionName == functionName)
				{
					// The function already exists.
					return;
				}
			}
		}

		constexpr int numberOfArguments = sizeof...(Paramtypes);
		std::function<void(Paramtypes...)> stdFunction;
		if constexpr (numberOfArguments == 1)
		{
			stdFunction = std::bind(inFunction, inObjectToAdd, std::placeholders::_1);
		}
		else if constexpr (numberOfArguments == 2)
		{
			stdFunction = std::bind(inFunction, inObjectToAdd, std::placeholders::_1, std::placeholders::_2);
		}
		else if constexpr (numberOfArguments == 3)
		{
			stdFunction = std::bind(inFunction, inObjectToAdd, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		}
		else if constexpr (numberOfArguments == 4)
		{
			stdFunction = std::bind(inFunction, inObjectToAdd, std::placeholders::_1, std::placeholders::_2,
				std::placeholders::_3, std::placeholders::_4);
		}
		else if constexpr (numberOfArguments == 5)
		{
			stdFunction = std::bind(inFunction, inObjectToAdd, std::placeholders::_1, std::placeholders::_2,
				std::placeholders::_3, std::placeholders::_4, std::placeholders::_5);
		}
		else if constexpr (numberOfArguments == 6)
		{
			stdFunction = std::bind(inFunction, inObjectToAdd, std::placeholders::_1, std::placeholders::_2,
				std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, std::placeholders::_6);
		}
		else
		{
			GameEngine_LOG(error, "MulticastDelegate::AddObject, passing more than 6 arguments.");
			return;
		}

		if (stdFunction == nullptr)
		{
			GameEngine_LOG(error, "MulticastDelegate::AddObject. Failed to construct the stdFunction");
			return;
		}

		STDFunctionWrapper wrapper;
		wrapper.TheFunction = stdFunction;
		wrapper.FunctionName = functionName;
		FunctionsPerObject[inObjectToAdd].push_back(wrapper);
	}

private:

	std::map<void*, std::vector<STDFunctionWrapper>> FunctionsPerObject;
};