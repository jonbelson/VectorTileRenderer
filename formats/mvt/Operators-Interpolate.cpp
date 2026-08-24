// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#include <cassert>

module formats.mvt.operators:interpolate;

import std;
import formats.mvt.feature;
import formats.mvt.parser;
import core.geometry;
import core.json;

import :common;

using namespace core::json;



// [ "interpolate", interpolation, input, stop_input_1, stop_output_1, stop_input_n, stop_output_n ]: OutputType
// OutputType is number, array of number, color.

bool OperatorInterpolate::ParseInterpolation(const json& array)
{
	// Attempt to read 'interpolation' parameters.
	if (array.is_array() && array.size() > 0)
	{
		if (std::string type; TryReadString(array[0], type))
		{
			if (type == "linear")
			{
				mType = Type::Linear;
				mBase = { 1.0f };
			}
			else if (type == "exponential")
			{
				if (array.size() == 2)
				{
					mType = Type::Exponential;
					mBase = JsonTypeToValue(array[1]);
				}
			}
			else if (type == "cubic-bezier")
			{
				if (array.size() == 5)
				{
					mType = Type::CubicBezier;
					mX1 = JsonTypeToValue(array[1]);
					mY1 = JsonTypeToValue(array[2]);
					mX2 = JsonTypeToValue(array[3]);
					mY2 = JsonTypeToValue(array[4]);
				}
			}
			return true;
		}
	}
	return false;
}

bool OperatorInterpolate::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "interpolate") && data.size() >= 5 )
	{
		if (IsStringOfValue(data[0], "interpolate"))
		{
			if (ParseInterpolation(data[1]))
			{
				mInput = JsonTypeToValue(data[2]);

				// Read each input/output pair of stops.
				size_t numPairs = (data.size() - 3)/2;

				for (int i = 3; i < 3 + 2*numPairs; i+=2)
				{
					Stop stop{};
					if (!TryReadFloat(data[i], stop.input))
						return false;
					stop.output = JsonTypeToValue(data[i + 1]);

					mStops.push_back(std::move(stop));
				}

				return true;
			}
		}
	}

	return false;
}







Value OperatorInterpolate::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	Value result{};

	Value input = GetValue(mInput, feature, zoom);

	//if (std::holds_alternative<float>(input))
	if (input.IsFloat())
	{
		//		float inputValue = std::get<float>(input);
		float inputValue = input.GetFloat();

		// Figure out which 'stop' pair the input falls into.
		size_t numStops = mStops.size();

		if (numStops > 0)
		{
			if (inputValue <= mStops.front().input)
			{
				result = mStops[0].output;
			}
			else if (inputValue > mStops.back().input)
			{
				result = mStops.back().output;
			}
			else
			{
				for (size_t i = 0; i < numStops - 1; i++)
				{
					float stopInput1 = mStops[i].input;
					float stopInput2 = mStops[i + 1].input;

					if (inputValue > stopInput1 && inputValue <= stopInput2)
					{
						if (mType == Type::Linear || mType == Type::Exponential)
						{
							Value base = GetValue(mBase, feature, zoom);
							if (base.IsFloat())
							{
								float baseValue = std::get<float>(base);
								float ratio = GetExponentialRatio(stopInput1, stopInput2, inputValue, baseValue);

								Value output1 = GetValue(mStops[i].output, feature, zoom);
								Value output2 = GetValue(mStops[i + 1].output, feature, zoom);
								result = std::visit(ExponentialOperator(ratio), output1, output2);
							}
						}
						else
						{
							Value x1 = GetValue(x1, feature, zoom);
							Value y1 = GetValue(y1, feature, zoom);
							Value x2 = GetValue(x2, feature, zoom);
							Value y2 = GetValue(y2, feature, zoom);

							if (AllHoldType<float>(x1, y1, x2, y2))
							{
								// Perform cubic-bezier interpolation.
								assert(false);

							}

						}

						break;
					}

				}
			}
		}
	}

	// XXX https://docs.mapbox.com/style-spec/reference/expressions/#interpolate
	// OutputType can be float, FloatArray, or Color (though the colour may be in string form).
	//result = GetValue(result, feature, zoom);

	//if (result.IsAnyOfTypes<float, FloatArray, std::string, Color>())
	//{
	//}

	return GetValue(result, feature, zoom);
}


// ["step", number, output, input1, output1, input2, output2, ...]: value
bool OperatorStep::ParseFromJson(const json& data)
{
	if (IsOperatorOfType(data, "step") && data.size() >= 3 )
	{
		mInput = JsonTypeToValue(data[1]);
		mOutput0 = JsonTypeToValue(data[2]);

		size_t numStops = data.size() - 3;

		// Should be an even number of stops since they're in pairs.
		if (numStops%2 == 1) return false;

		size_t numPairs = numStops/2;

		for (int i=3; i<2 + 2*numPairs; i+=2)
		{
			InputOutput inputOutput;

			// Each input can be a single item or an array of inputs.
			inputOutput.input = std::move(JsonTypeToValue(data[i]));
			inputOutput.output = JsonTypeToValue(data[i + 1]);

			mInputOutputs.push_back(std::move(inputOutput));
		}

		return true;
	}

	return false;
}

Value OperatorStep::Evaluate(const mvt::feature::Feature& feature, float zoom)
{
	Value result{};

	if (mInputOutputs.empty())
	{
		return GetValue(mOutput0, feature, zoom);
	}

	Value input = GetValue(mInput, feature, zoom);

	if (input.IsFloat())
	{
		float inputValue = input.GetFloat();

		for (const auto& inputOutput : mInputOutputs)
		{
			Value stopInput = GetValue(inputOutput.input, feature, zoom);

			if (!stopInput.IsFloat()) return {};

			float stopInputValue = stopInput.GetFloat();

			if (stopInputValue <= inputValue)
			{
				return GetValue(inputOutput.output, feature, zoom);
			}
		}

		// No stopInputs less that the input value, so return the default output.
		return GetValue(mOutput0, feature, zoom);
	}

	return {};
}
