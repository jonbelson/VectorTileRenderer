export module formats.mvt.operators:factory;

import std;

import core.json;
//import formats.mvt.operators;

using namespace core::json;

export class IOperator;


// Recursively parse the JSON expression and create the appropriate Operator tree.
export std::shared_ptr<IOperator> CreateOperatorFromJson(const json& data);

// Create an Operator that performs the task of a Function.
export std::shared_ptr<IOperator> CreateFunctionOperatorFromJson(const json& data);
