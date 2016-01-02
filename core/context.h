#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include "object.h"

class Ink_ContextChain {
public:
	Ink_ContextChain *outer;
	Ink_ContextObject *context;
	Ink_ContextChain *inner;

	int debug_lineno;
	Ink_Object *debug_creater;

	Ink_ContextChain()
	{
		context = new Ink_ContextObject();
		outer = NULL;
		inner = NULL;
		debug_lineno = -1;
		debug_creater = NULL;
	}

	Ink_ContextChain(Ink_ContextObject *context)
	: context(context)
	{
		outer = NULL;
		inner = NULL;
		debug_lineno = -1;
		debug_creater = NULL;
	}

	Ink_ContextChain(Ink_HashTable *hash_table)
	{
		context = new Ink_ContextObject(hash_table);
		outer = NULL;
		inner = NULL;
		debug_lineno = -1;
		debug_creater = NULL;
	}

	inline void setDebug(int lineno, Ink_Object *creater)
	{
		debug_lineno = lineno;
		debug_creater = creater;
		return;
	}

	inline int getLineno()
	{ return debug_lineno; }
	inline Ink_Object *getCreater()
	{ return debug_creater; }

	Ink_ContextChain *addContext(Ink_ContextObject *c);
	void removeLast(bool if_delete = true);
	Ink_ContextChain *getGlobal();
	Ink_ContextChain *getLocal();
	Ink_Object *searchSlot(const char *slot_id); // from local
	Ink_HashTable *searchSlotMapping(const char *slot_id); // from local
	Ink_ContextChain *copyContextChain();

	static void disposeContextChain(Ink_ContextChain *head);

	~Ink_ContextChain()
	{ }
};

#endif