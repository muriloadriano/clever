/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/environment.h"
#include "core/value.h"

namespace clever {

Environment* Environment::activate(Environment* outer) const
{
	Environment* env = new Environment(outer ? outer : m_outer, false);

	if (m_temp) {
		env->m_temp = new Environment(NULL, false);

		env->m_temp->m_data.reserve(m_temp->m_data.size());

		for (size_t i = 0, size = m_temp->m_data.size(); i < size; ++i) {
			env->m_temp->m_data.push_back(m_temp->m_data[i]->clone());
		}
	}

	if (!m_data.empty()) {
		env->m_data.reserve(m_data.size());

		for (size_t i = 0, size = m_data.size(); i < size; ++i) {
			env->pushValue(m_data[i]->clone());
		}
	}

	return env;
}

Value* Environment::getValue(const ValueOffset& offset) const
{
	if (offset.first == 0) { // local
		clever_assert(offset.second < m_data.size(),
				"`offset.second` must be within `m_data` limits.");

		return m_data[offset.second];
	}

	size_t depth = offset.first;
	Environment* env = m_outer;

	while (env && --depth) {
		env = env->m_outer;
	}

	clever_assert(depth == 0,
			"`depth` must be zero, otherwise we failed to find the environment.");
	clever_assert(offset.second < env->m_data.size(),
			"`offset.second` must be within `m_data` bounds.");
	clever_assert_not_null(env);

	return env->m_data[offset.second];
}

} // clever
