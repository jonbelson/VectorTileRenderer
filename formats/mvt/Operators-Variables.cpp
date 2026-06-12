// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module formats.mvt.operators:variables;

import std;
import formats.mvt.feature;
import formats.mvt.parser;
import core.geometry;
import core.json;

import :common;

using namespace core::json;


using VarFrame = std::unordered_map<std::string, Value>;

class VarStack
{
	std::vector<VarFrame> mVarFrames;

public:
	VarStack() {}

	void PushFrame(void) { mVarFrames.emplace_back(); }
	void PopFrame(void) { if (!mVarFrames.empty()) { mVarFrames.pop_back(); } }

	void AddVar(const std::string& name, const Value& value)
	{
		if (!mVarFrames.empty())
		{
			mVarFrames.back()[name] = value;
		}
	}
	std::optional<Value> GetVar(const std::string& name) const
	{
		for (auto it = mVarFrames.rbegin(); it != mVarFrames.rend(); ++it)
		{
			const auto& frame = *it;
			auto varIt = frame.find(name);
			if (varIt != frame.end())
			{
				return varIt->second;
			}
		}

		return std::nullopt;
	}
};

thread_local VarStack gVarStack;




// [ "let", variable_name, value, variable_name, value, ..., OutputType ]: OutputType
bool OperatorLet::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "let") && data.size() >= 4 && data.size()%2 == 0)
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			return true;
		}
	}

	return false;
}

Value OperatorLet::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	if (mValues.size() >= 3)
	{
		gVarStack.PushFrame();

		for (size_t i=0; i<mValues.size() - 1; i+=2)
		{
			if (!mValues[i].IsString())
			{
				return {};
			}
			std::string name = mValues[i].GetString();

			gVarStack.AddVar(name, GetValue(mValues[i + 1], feature, zoom));
		}

		Value result = GetValue(mValues.back(), feature, zoom);

		gVarStack.PopFrame();

		return result;
	}

	return {};
}


bool OperatorVar::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "var") && data.size() == 2)
	{
		if (JsonArrayToValueArray(data, mValues, 1))
		{
			return mValues.size() == 1;
		}
	}

	return false;
}

Value OperatorVar::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	if (mValues.size() == 1)
	{
		if (auto name = mValues[0].TryGetString(); name.has_value())
		{
			if (auto var = gVarStack.GetVar(name.value()); var.has_value())
			{
				return var.value();
			}
		}
	}

	return {};
}

