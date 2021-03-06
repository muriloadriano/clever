/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/clever.h"
#include "core/opcode.h"

namespace clever {

#ifdef CLEVER_DEBUG
const char* get_opcode_name(Opcode opnum)
{
#define CASE(s) case s: return #s
	switch (opnum) {
		CASE(OP_RET);
		CASE(OP_ASSIGN);
		CASE(OP_ADD);
		CASE(OP_SUB);
		CASE(OP_MUL);
		CASE(OP_DIV);
		CASE(OP_MOD);
		CASE(OP_JMP);
		CASE(OP_FCALL);
		CASE(OP_LEAVE);
		CASE(OP_SEND_VAL);
		CASE(OP_JMPZ);
		CASE(OP_PRE_INC);
		CASE(OP_PRE_DEC);
		CASE(OP_POS_INC);
		CASE(OP_POS_DEC);
		CASE(OP_JMPNZ);
		CASE(OP_AND);
		CASE(OP_OR);
		CASE(OP_EQUAL);
		CASE(OP_NEQUAL);
		CASE(OP_LOCK);
		CASE(OP_UNLOCK);
		CASE(OP_HALT);
		CASE(OP_GREATER);
		CASE(OP_GEQUAL);
		CASE(OP_LESS);
		CASE(OP_LEQUAL);
		CASE(OP_NEW);
		CASE(OP_MCALL);
		CASE(OP_SMCALL);
		CASE(OP_PROP_R);
		CASE(OP_SPROP_R);
		CASE(OP_PROP_W);
		CASE(OP_SPROP_W);
		CASE(OP_TRY);
		CASE(OP_CATCH);
		CASE(OP_THROW);
		CASE(OP_ETRY);
		CASE(OP_NOT);
		CASE(OP_BW_AND);
		CASE(OP_BW_OR);
		CASE(OP_BW_XOR);
		CASE(OP_BW_NOT);
		CASE(OP_BW_LS);
		CASE(OP_BW_RS);
		CASE(OP_SUBSCRIPT_W);
		CASE(OP_SUBSCRIPT_R);
		EMPTY_SWITCH_DEFAULT_CASE();
	}
#undef CASE
	return "UNKNOWN";
}
#endif

} // clever
