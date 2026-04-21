module;

#include "json.hpp"
#include <cassert>

module formats.mvt.expressions;

import std;
import formats.mvt.feature;
import formats.mvt.parser;
import core.color;

using json = nlohmann::json;

using namespace core::color;
using namespace mvt::feature;




// Figure out the JSON is an Expression or a Function or just raw data.
bool Expression::ParseFromJson(const nlohmann::json& data)
{
	mValue = JsonTypeToValue(data);

	return !mValue.IsNull();
}

Value Expression::Evaluate(const mvt::feature::Feature& feature, float zoom) const
{
	return GetValue(mValue, feature, zoom);
}


StringExpression::StringExpression(const nlohmann::json& data)
{
	if (ParseFromJson(data))
	{
	}
}

std::string StringExpression::GetValue(const mvt::feature::Feature& feature, float zoom) const
{
	Value value = Evaluate(feature, zoom);

	if (std::holds_alternative<std::string>(value)) return std::get<std::string>(value);

	return mDefault;
}


StringArrayExpression::StringArrayExpression(const nlohmann::json& data)
{
	if (ParseFromJson(data))
	{
	}
}

StringArray StringArrayExpression::GetValue(const mvt::feature::Feature& feature, float zoom) const
{
	Value value = Evaluate(feature, zoom);

	if (std::holds_alternative<StringArray>(value)) return std::get<StringArray>(value);

	return mDefault;
}



// Try to figure out if Filter is defined using the old format or Expressions.
static bool IsOldFilterFormat(const json& data)
{
	if (data.is_array() && data.size() > 0 && data[0].is_string())
	{
		// Easy case - if the first string is not a known Operation, it's likely to be in the old format.
		if (!IsJsonExpression(data)) return true;

		std::string type = data[0].get<std::string>();

		// Now try to distinguish between the old and new filter expressions that share keywords.
		if (IsStringOfValue(type, "has"))
		{
			if (data.size() == 2 && !data[1].is_array())
			{
				return true;
			}
		}
		else if (IsStringOfValue(type, "==") || IsStringOfValue(type, "!=") ||IsStringOfValue(type, ">") ||IsStringOfValue(type, "<") ||IsStringOfValue(type, "<="))
		{
			// Expressions very unlikely to have two literal strings as values.
			if (data.size() == 3 && data[1].is_string() && (data[2].is_string() || data[2].is_number() || data[2].is_boolean()))
			{
				return true;
			}
		}
		else if (IsStringOfValue(type, "in"))
		{
			// Expression "in" only has two value arguments.
			if (data.size() >= 3)
			{
				return true;
			}
		}
		else if (IsStringOfValue(type, "all"))
		{
			// Bit trickier as this could be the old format or an Operator. Check the individual parameters to see if they're the old or new format.
			for (size_t i=1; i<data.size(); i++)
			{
				bool isOldFormat = IsOldFilterFormat(data[i]);
				if (isOldFormat) return true;
			}
			return false;
		}
		else if (IsStringOfValue(type, "any"))
		{
			// Bit trickier as this could be the old format or an Operator. Check the individual parameters to see if they're the old or new format.
			for (size_t i = 1; i<data.size(); i++)
			{
				bool isOldFormat = IsOldFilterFormat(data[i]);
				if (isOldFormat) return true;
			}
			return false;
		}

	}
	return false;
}


OperatorPtr CreateOperatorFromJson(const std::string& jsonExpression)
{
	OperatorPtr exprOp;

	try
	{
		json expression = json::parse(jsonExpression);
		exprOp = CreateOperatorFromJson(expression);
	}
	catch (const json::parse_error& e)
	{
		std::cerr << "JSON parse error: " << e.what() << std::endl;
	}

	return exprOp;
}



static std::map<std::string_view, FilterExistential> ExistentialOperatorMap {
	{ "has", FilterExistential::Has},
	{ "!has", FilterExistential::NotHas}
};

static std::map<std::string_view, FilterComparison> ComparisonOperatorMap {
	{ "==", FilterComparison::Equal },
	{ "!=", FilterComparison::NotEqual },
	{ ">", FilterComparison::GreaterThan },
	{ ">=", FilterComparison::GreaterThanEqual },
	{ "<", FilterComparison::LessThan },
	{ "<=", FilterComparison::LessThanEqual }
};

static std::map<std::string_view, FilterMembership> MembershipOperatorMap {
	{ "in", FilterMembership::In },
	{ "!in", FilterMembership::NotIn }
};

static std::map<std::string_view, FilterCombining> CombiningOperatorMap {
	{ "all", FilterCombining::All },
	{ "any", FilterCombining::Any },
	{ "none", FilterCombining::None }
};


// https://docs.mapbox.com/style-spec/reference/other/#other-filters
static bool TryReadFilterValue(const json& data, Value& value)
{
	if (float f{}; TryReadFloat(data, f))
	{
		value = { f };
		return true;
	}
	else if (std::string s; TryReadString(data, s))
	{
		value = { s };
		return true;
	}
	else if (bool b{}; TryReadBool(data, b))
	{
		value = { b };
		return true;
	}
	return false;
}

// Create FilterOperator equivalent of Existential, Comparison and Set membership operators.
std::unique_ptr<_FilterOperator> CreateFilterOperator(const json& data)
{
	if (data.is_array() && data.size() > 0)
	{
		std::string type;
		if (TryReadString(data[0], type))
		{
			{
				auto it = ExistentialOperatorMap.find(type);
				if (it != ExistentialOperatorMap.end())
				{
					std::string key;
					if (TryReadString(data[1], key))
					{
						return std::make_unique<FilterOperatorExistential>(it->second, key);
					}
				}
			}

			{
				auto it = ComparisonOperatorMap.find(type);
				if (it != ComparisonOperatorMap.end())
				{
					std::string key;
					Value value;
					if (TryReadString(data[1], key) && TryReadFilterValue(data[2], value))
					{
						return std::make_unique<FilterOperatorComparison>(it->second, key, value);
					}
				}
			}

			{
				auto it = MembershipOperatorMap.find(type);
				if (it != MembershipOperatorMap.end() && data.size() >= 3)
				{
					std::string key;
					std::vector<Value> values;
					if (TryReadString(data[1], key))
					{
						for (size_t i = 2; i < data.size(); i++)
						{
							values.push_back(JsonTypeToValue(data[i]));
						}
						return std::make_unique<FilterOperatorMembership>(it->second, key, values);
					}
				}
			}
		}
	}

	return nullptr;
}


bool FilterExpression::ParseFromJson(const nlohmann::json& data)
{
	if (data.is_array() && data.size() > 0)
	{
		if (!IsOldFilterFormat(data))
		{
			return Expression::ParseFromJson(data);
		}

		// It's the old format, so convert it to the equialent Operator tree.
		std::string type = data[0].get<std::string>();

		if (type == "all" || type == "any" || type == "none")
		{
			auto it = CombiningOperatorMap.find(type);
			if (it != CombiningOperatorMap.end())
			{
				std::vector< std::unique_ptr<_FilterOperator> > filters;
				for (size_t i= 1; i < data.size(); i++)
				{
					auto filter = CreateFilterOperator(data[i]);
					if (filter)
					{
						filters.push_back(std::move(filter));
					}
				}

				std::shared_ptr<IOperator> combiningFilter = std::make_shared<FilterOperatorCombining>(it->second, filters);
				mValue = combiningFilter;
			}
		}
		else
		{
			std::unique_ptr<_FilterOperator> filter = CreateFilterOperator(data);
			if (filter)
			{
				std::shared_ptr<IOperator> spfilter { std::move(filter) };
				mValue = spfilter;
			}
		}
	}

	return false;
}

bool FilterExpression::GetValue(const mvt::feature::Feature& feature, float zoom) const
{
	// If no Filter was defined, Layer should be displayed.
	if (mValue.IsNull()) return true;

	Value value = Evaluate(feature, zoom);

	if (std::holds_alternative<bool>(value)) return std::get<bool>(value);

	return false;
}



ColorExpression::ColorExpression(const nlohmann::json& data)
{
	ParseFromJson(data);
}

bool ColorExpression::ParseFromJson(const nlohmann::json& data)
{
	if (Expression::ParseFromJson(data))
	{
		// Special case: if the Value is a string, attempt to convert it into a Color.
		if (std::holds_alternative<std::string>(mValue))
		{
			std::string s = std::get<std::string>(mValue);
			Color colour(s);
			if (colour.IsValid())
			{
				mValue = colour;
			}
		}
	}

	return !mValue.IsNull();
}

Color ColorExpression::GetValue(const mvt::feature::Feature& feature, float zoom) const
{
	Value value = Evaluate(feature, zoom);

	if (std::holds_alternative<Color>(value)) return std::get<Color>(value);

	if (std::holds_alternative<std::string>(value))
	{
		Color c(std::get<std::string>(value));
		if (c.IsValid())
		{
			return c;
		}
	}

	return mDefault;
}


FloatExpression::FloatExpression(const nlohmann::json& data)
{
	if (ParseFromJson(data))
	{
		;
	}
}


float FloatExpression::GetValue(const mvt::feature::Feature& feature, float zoom) const
{
	Value value = Evaluate(feature, zoom);

	if (std::holds_alternative<float>(value)) return std::get<float>(value);

	return mDefault;
}


FloatArrayExpression::FloatArrayExpression(const nlohmann::json& data)
{
	if (ParseFromJson(data))
	{
		;
	}
}

FloatArray FloatArrayExpression::GetValue(const mvt::feature::Feature& feature, float zoom) const
{
	Value value = Evaluate(feature, zoom);

	if (std::holds_alternative<FloatArray>(value)) return std::get<FloatArray>(value);

	return mDefault;
}




BoolExpression::BoolExpression(const json& data)
{
	if (ParseFromJson(data))
	{
		;
	}
}

bool BoolExpression::GetValue(const mvt::feature::Feature& feature, float zoom) const
{
	Value value = Evaluate(feature, zoom);

	if (std::holds_alternative<bool>(value)) return std::get<bool>(value);

	return mDefault;
}


