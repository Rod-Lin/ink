#include <math.h>
#include "bignum.h"
#include "interface.h"
#include "core/object.h"
#include "core/native/general.h"

using namespace ink;

InkMod_ModuleID ink_native_bignum_mod_id;

Ink_TypeTag getBigNumericType(Ink_InterpreteEngine *engine)
{
	return engine->getEngineComAs<Ink_TypeTag>(ink_native_bignum_mod_id)[0];
}

Ink_Object *Ink_BigNumeric::clone(Ink_InterpreteEngine *engine)
{
	Ink_Object *new_obj = new Ink_BigNumeric(engine, value);

	cloneHashTable(this, new_obj);

	return new_obj;
}

Ink_Object *Ink_BigNumeric::cloneDeep(Ink_InterpreteEngine *engine)
{
	engine->addDeepCloneTrace(this);
	Ink_Object *new_obj = new Ink_BigNumeric(engine, value);

	cloneDeepHashTable(engine, this, new_obj);

	return new_obj;
}

Ink_Object *InkNative_BigNumeric_Add(Ink_InterpreteEngine *engine, Ink_ContextChain *context, Ink_ArgcType argc, Ink_Object **argv, Ink_Object *this_p)
{
	Ink_Object *base = context->searchSlot(engine, "base");

	ASSUME_BASE_TYPE(engine, BIGNUMERIC_TYPE);

	if (!checkArgument(false, argc, argv, 1, BIGNUMERIC_TYPE)
		&& !checkArgument(engine, argc, argv, 1, INK_NUMERIC)) {
		return NULL_OBJ;
	}
	Ink_Bignum_NumericValue val = argv[0]->type == INK_NUMERIC
							  ? as<Ink_Numeric>(argv[0])->value
							  : as<Ink_BigNumeric>(argv[0])->value;

	return new Ink_BigNumeric(engine, as<Ink_BigNumeric>(base)->value + val);
}

Ink_Object *InkNative_BigNumeric_Sub(Ink_InterpreteEngine *engine, Ink_ContextChain *context, Ink_ArgcType argc, Ink_Object **argv, Ink_Object *this_p)
{
	Ink_Object *base = context->searchSlot(engine, "base");

	ASSUME_BASE_TYPE(engine, BIGNUMERIC_TYPE);

	if (!checkArgument(false, argc, argv, 1, BIGNUMERIC_TYPE)
		&& !checkArgument(engine, argc, argv, 1, INK_NUMERIC)) {
		return NULL_OBJ;
	}
	Ink_Bignum_NumericValue val = argv[0]->type == INK_NUMERIC
							  ? as<Ink_Numeric>(argv[0])->value
							  : as<Ink_BigNumeric>(argv[0])->value;

	return new Ink_BigNumeric(engine, as<Ink_BigNumeric>(base)->value - val);
}

Ink_Object *InkNative_BigNumeric_Mul(Ink_InterpreteEngine *engine, Ink_ContextChain *context, Ink_ArgcType argc, Ink_Object **argv, Ink_Object *this_p)
{
	Ink_Object *base = context->searchSlot(engine, "base");

	ASSUME_BASE_TYPE(engine, BIGNUMERIC_TYPE);

	if (!checkArgument(false, argc, argv, 1, BIGNUMERIC_TYPE)
		&& !checkArgument(engine, argc, argv, 1, INK_NUMERIC)) {
		return NULL_OBJ;
	}
	Ink_Bignum_NumericValue val = argv[0]->type == INK_NUMERIC
							  ? as<Ink_Numeric>(argv[0])->value
							  : as<Ink_BigNumeric>(argv[0])->value;

	return new Ink_BigNumeric(engine, as<Ink_BigNumeric>(base)->value * val);
}

Ink_Object *InkNative_BigNumeric_Div(Ink_InterpreteEngine *engine, Ink_ContextChain *context, Ink_ArgcType argc, Ink_Object **argv, Ink_Object *this_p)
{
	Ink_Object *base = context->searchSlot(engine, "base");

	ASSUME_BASE_TYPE(engine, BIGNUMERIC_TYPE);

	if (!checkArgument(false, argc, argv, 1, BIGNUMERIC_TYPE)
		&& !checkArgument(engine, argc, argv, 1, INK_NUMERIC)) {
		return NULL_OBJ;
	}

	Ink_Bignum_NumericValue val = argv[0]->type == INK_NUMERIC
							  ? as<Ink_Numeric>(argv[0])->value
							  : as<Ink_BigNumeric>(argv[0])->value;
	Ink_Bignum_NumericValue ret = 0;

	if (val == 0) {
		InkWarn_Divided_By_Zero(engine);
		return NULL_OBJ;
	}

	if (argc > 1 && argv[1]->type == INK_NUMERIC) {
		ret = as<Ink_BigNumeric>(base)->value.dividedBy(val, as<Ink_Numeric>(argv[1])->value);
	} else {
		ret = as<Ink_BigNumeric>(base)->value / val;
	}

	return new Ink_BigNumeric(engine, ret);
}

Ink_Object *InkNative_BigNumeric_Mod(Ink_InterpreteEngine *engine, Ink_ContextChain *context, Ink_ArgcType argc, Ink_Object **argv, Ink_Object *this_p)
{
	Ink_Object *base = context->searchSlot(engine, "base");

	ASSUME_BASE_TYPE(engine, BIGNUMERIC_TYPE);

	if (!checkArgument(false, argc, argv, 1, BIGNUMERIC_TYPE)
		&& !checkArgument(engine, argc, argv, 1, INK_NUMERIC)) {
		return NULL_OBJ;
	}
	Ink_Bignum_NumericValue val = argv[0]->type == INK_NUMERIC
							  ? as<Ink_Numeric>(argv[0])->value
							  : as<Ink_BigNumeric>(argv[0])->value;

	return new Ink_BigNumeric(engine, as<Ink_BigNumeric>(base)->value % val);
}

Ink_Object *InkNative_BigNumeric_Equal(Ink_InterpreteEngine *engine, Ink_ContextChain *context, Ink_ArgcType argc, Ink_Object **argv, Ink_Object *this_p)
{
	Ink_Object *base = context->searchSlot(engine, "base");

	ASSUME_BASE_TYPE(engine, BIGNUMERIC_TYPE);

	if (!checkArgument(false, argc, argv, 1, BIGNUMERIC_TYPE)
		&& !checkArgument(engine, argc, argv, 1, INK_NUMERIC)) {
		return NULL_OBJ;
	}
	Ink_Bignum_NumericValue val = argv[0]->type == INK_NUMERIC
							  ? as<Ink_Numeric>(argv[0])->value
							  : as<Ink_BigNumeric>(argv[0])->value;

	return new Ink_BigNumeric(engine, as<Ink_BigNumeric>(base)->value == val);
}

Ink_Object *InkNative_BigNumeric_NotEqual(Ink_InterpreteEngine *engine, Ink_ContextChain *context, Ink_ArgcType argc, Ink_Object **argv, Ink_Object *this_p)
{
	Ink_Object *base = context->searchSlot(engine, "base");

	ASSUME_BASE_TYPE(engine, BIGNUMERIC_TYPE);

	if (!checkArgument(false, argc, argv, 1, BIGNUMERIC_TYPE)
		&& !checkArgument(engine, argc, argv, 1, INK_NUMERIC)) {
		return NULL_OBJ;
	}
	Ink_Bignum_NumericValue val = argv[0]->type == INK_NUMERIC
							  ? as<Ink_Numeric>(argv[0])->value
							  : as<Ink_BigNumeric>(argv[0])->value;

	return new Ink_BigNumeric(engine, as<Ink_BigNumeric>(base)->value != val);
}

Ink_Object *InkNative_BigNumeric_Greater(Ink_InterpreteEngine *engine, Ink_ContextChain *context, Ink_ArgcType argc, Ink_Object **argv, Ink_Object *this_p)
{
	Ink_Object *base = context->searchSlot(engine, "base");

	ASSUME_BASE_TYPE(engine, BIGNUMERIC_TYPE);

	if (!checkArgument(false, argc, argv, 1, BIGNUMERIC_TYPE)
		&& !checkArgument(engine, argc, argv, 1, INK_NUMERIC)) {
		return NULL_OBJ;
	}
	Ink_Bignum_NumericValue val = argv[0]->type == INK_NUMERIC
							  ? as<Ink_Numeric>(argv[0])->value
							  : as<Ink_BigNumeric>(argv[0])->value;

	return new Ink_BigNumeric(engine, as<Ink_BigNumeric>(base)->value > val);
}

Ink_Object *InkNative_BigNumeric_Less(Ink_InterpreteEngine *engine, Ink_ContextChain *context, Ink_ArgcType argc, Ink_Object **argv, Ink_Object *this_p)
{
	Ink_Object *base = context->searchSlot(engine, "base");

	ASSUME_BASE_TYPE(engine, BIGNUMERIC_TYPE);

	if (!checkArgument(false, argc, argv, 1, BIGNUMERIC_TYPE)
		&& !checkArgument(engine, argc, argv, 1, INK_NUMERIC)) {
		return NULL_OBJ;
	}
	Ink_Bignum_NumericValue val = argv[0]->type == INK_NUMERIC
							  ? as<Ink_Numeric>(argv[0])->value
							  : as<Ink_BigNumeric>(argv[0])->value;

	return new Ink_BigNumeric(engine, as<Ink_BigNumeric>(base)->value < val);
}

Ink_Object *InkNative_BigNumeric_GreaterOrEqual(Ink_InterpreteEngine *engine, Ink_ContextChain *context, Ink_ArgcType argc, Ink_Object **argv, Ink_Object *this_p)
{
	Ink_Object *base = context->searchSlot(engine, "base");

	ASSUME_BASE_TYPE(engine, BIGNUMERIC_TYPE);

	if (!checkArgument(false, argc, argv, 1, BIGNUMERIC_TYPE)
		&& !checkArgument(engine, argc, argv, 1, INK_NUMERIC)) {
		return NULL_OBJ;
	}
	Ink_Bignum_NumericValue val = argv[0]->type == INK_NUMERIC
							  ? as<Ink_Numeric>(argv[0])->value
							  : as<Ink_BigNumeric>(argv[0])->value;

	return new Ink_BigNumeric(engine, as<Ink_BigNumeric>(base)->value >= val);
}

Ink_Object *InkNative_BigNumeric_LessOrEqual(Ink_InterpreteEngine *engine, Ink_ContextChain *context, Ink_ArgcType argc, Ink_Object **argv, Ink_Object *this_p)
{
	Ink_Object *base = context->searchSlot(engine, "base");

	ASSUME_BASE_TYPE(engine, BIGNUMERIC_TYPE);

	if (!checkArgument(false, argc, argv, 1, BIGNUMERIC_TYPE)
		&& !checkArgument(engine, argc, argv, 1, INK_NUMERIC)) {
		return NULL_OBJ;
	}
	Ink_Bignum_NumericValue val = argv[0]->type == INK_NUMERIC
							  ? as<Ink_Numeric>(argv[0])->value
							  : as<Ink_BigNumeric>(argv[0])->value;

	return new Ink_BigNumeric(engine, as<Ink_BigNumeric>(base)->value <= val);
}

Ink_Object *InkNative_BigNumeric_Add_Unary(Ink_InterpreteEngine *engine, Ink_ContextChain *context, Ink_ArgcType argc, Ink_Object **argv, Ink_Object *this_p)
{
	Ink_Object *base = context->searchSlot(engine, "base");

	ASSUME_BASE_TYPE(engine, BIGNUMERIC_TYPE);

	return new Ink_BigNumeric(engine, as<Ink_BigNumeric>(base)->value);
}

Ink_Object *InkNative_BigNumeric_Sub_Unary(Ink_InterpreteEngine *engine, Ink_ContextChain *context, Ink_ArgcType argc, Ink_Object **argv, Ink_Object *this_p)
{
	Ink_Object *base = context->searchSlot(engine, "base");

	ASSUME_BASE_TYPE(engine, BIGNUMERIC_TYPE);

	return new Ink_BigNumeric(engine, -as<Ink_BigNumeric>(base)->value);
}

Ink_Object *InkNative_BigNumeric_ToString(Ink_InterpreteEngine *engine, Ink_ContextChain *context, Ink_ArgcType argc, Ink_Object **argv, Ink_Object *this_p)
{
	Ink_Object *base = context->searchSlot(engine, "base");

	ASSUME_BASE_TYPE(engine, BIGNUMERIC_TYPE);

	return new Ink_String(engine, as<Ink_BigNumeric>(base)->value.toString());
}

void Ink_BigNumeric::Ink_BigNumericMethodInit(Ink_InterpreteEngine *engine)
{
	setSlot("+", new Ink_FunctionObject(engine, InkNative_BigNumeric_Add));
	setSlot("-", new Ink_FunctionObject(engine, InkNative_BigNumeric_Sub));
	setSlot("*", new Ink_FunctionObject(engine, InkNative_BigNumeric_Mul));
	setSlot("/", new Ink_FunctionObject(engine, InkNative_BigNumeric_Div));
	setSlot("%", new Ink_FunctionObject(engine, InkNative_BigNumeric_Mod));
	setSlot("div", new Ink_FunctionObject(engine, InkNative_BigNumeric_Div));
	setSlot("==", new Ink_FunctionObject(engine, InkNative_BigNumeric_Equal));
	setSlot("!=", new Ink_FunctionObject(engine, InkNative_BigNumeric_NotEqual));
	setSlot(">", new Ink_FunctionObject(engine, InkNative_BigNumeric_Greater));
	setSlot("<", new Ink_FunctionObject(engine, InkNative_BigNumeric_Less));
	setSlot(">=", new Ink_FunctionObject(engine, InkNative_BigNumeric_GreaterOrEqual));
	setSlot("<=", new Ink_FunctionObject(engine, InkNative_BigNumeric_LessOrEqual));
	setSlot("+u", new Ink_FunctionObject(engine, InkNative_BigNumeric_Add_Unary));
	setSlot("-u", new Ink_FunctionObject(engine, InkNative_BigNumeric_Sub_Unary));
	setSlot("to_str", new Ink_FunctionObject(engine, InkNative_BigNumeric_ToString));

	return;
}

Ink_Object *InkNative_Bignum_Constructor(Ink_InterpreteEngine *engine, Ink_ContextChain *context, Ink_ArgcType argc, Ink_Object **argv, Ink_Object *this_p)
{
	Ink_Object *ret = NULL_OBJ;

	if (checkArgument(false, argc, argv, 1, INK_STRING)) {
		ret = new Ink_BigNumeric(engine, as<Ink_String>(argv[0])->getValue());
	} else if (checkArgument(engine, argc, argv, 1, INK_NUMERIC)) {
		ret = new Ink_BigNumeric(engine, as<Ink_Numeric>(argv[0])->value);
	}
	context->getLocal()->context->setSlot("this", ret);

	return ret;
}

struct com_cleaner_arg {
	InkMod_ModuleID id;
	com_cleaner_arg(InkMod_ModuleID id)
	: id(id)
	{ }
};

void InkNative_Bignum_EngineComCleaner(Ink_InterpreteEngine *engine, void *arg)
{
	com_cleaner_arg *tmp = (com_cleaner_arg *)arg;
	free(engine->getEngineComAs<Ink_TypeTag>(tmp->id));
	delete tmp;
	return;
}

void InkMod_Bignum_bondTo(Ink_InterpreteEngine *engine, Ink_Object *bondee)
{
	bondee->setSlot("bignum", new Ink_FunctionObject(engine, InkNative_Bignum_Constructor));
	return;
}

Ink_Object *InkMod_Bignum_Loader(Ink_InterpreteEngine *engine, Ink_ContextChain *context, Ink_ArgcType argc, Ink_Object **argv, Ink_Object *this_p)
{
	if (!checkArgument(engine, argc, 2)) {
		return NULL_OBJ;
	}

	Ink_Object *apply_to = argv[1];

	InkMod_Bignum_bondTo(engine, apply_to);

	return NULL_OBJ;
}

extern "C" {
	void InkMod_Loader(Ink_InterpreteEngine *engine, Ink_ContextChain *context)
	{
		Ink_Object *tmp;
		Ink_TypeTag *type_p = NULL;

		if (!engine->getEngineComAs<Ink_TypeTag>(ink_native_bignum_mod_id)) {
			type_p = (Ink_TypeTag *)malloc(sizeof(Ink_TypeTag));

			type_p[0] = (Ink_TypeTag)engine->registerType("bignum");

			engine->addEngineCom(ink_native_bignum_mod_id, type_p);
			engine->addDestructor(Ink_EngineDestructor(InkNative_Bignum_EngineComCleaner,
													   new com_cleaner_arg(ink_native_bignum_mod_id)));

			context->getGlobal()->context->setSlot("$bignum", tmp = new Ink_BigNumeric(engine, "0"));
			tmp->derivedMethodInit(engine);
		}

		Ink_Object *bignum_pkg = addPackage(engine, context, "bignum", new Ink_FunctionObject(engine, InkMod_Bignum_Loader));

		InkMod_Bignum_bondTo(engine, bignum_pkg);
	}

	int InkMod_Init(InkMod_ModuleID id)
	{
		ink_native_bignum_mod_id = id;
		return 0;
	}
}