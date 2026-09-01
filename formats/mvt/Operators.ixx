// Copyright (c) 2026 Jonathan Belson
// Licensed under the MIT License — use freely, keep this notice.
// SPDX-License-Identifier: MIT
// Full terms: see LICENSE in the project root.

module;

#//include "json.hpp"

//export module formats.mvt.expressions:operators;
export module formats.mvt.operators;

export import :camera;
export import :common;
export import :decision;
export import :feature;
export import :function;
export import :interpolate;
export import :lookup;
export import :math;
export import :string;
export import :types;
export import :variables;

import std;
import core.color;
import core.json;
import formats.mvt.feature;


using namespace core::json;



//template <typename... Types, typename Variant>
//constexpr bool AnyHoldAnyOfType(std::initializer_list<Variant> variants) noexcept
//{
//	return (...
//}



// Recursively parse the JSON expression and create the appropriate Operator tree.
export std::shared_ptr<IOperator> CreateOperatorFromJson(const json& data);

// Create an Operator that performs the task of a Function.
export std::shared_ptr<IOperator> CreateFunctionOperatorFromJson(const json& data);


