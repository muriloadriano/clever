/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_CONCURRENT_THREAD_H
#define CLEVER_STD_CONCURRENT_THREAD_H

#include <iostream>

#include "core/cstring.h"
#include "core/type.h"

namespace clever { namespace modules { namespace std {

class Thread : public Type {
public:
	Thread()
		: Type("Thread") {}

	~Thread() {}

	virtual void init();

	CLEVER_METHOD(ctor);
	CLEVER_METHOD(start);
	CLEVER_METHOD(wait);
	CLEVER_METHOD(getResult);
};

}}} // clever::modules::std

#endif // CLEVER_STD_CONCURRENT_THREAD_H
