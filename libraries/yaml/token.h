#pragma once

#ifndef TOKEN_H_62B23520_7C8E_11DE_8A39_0800200C9A66
#define TOKEN_H_62B23520_7C8E_11DE_8A39_0800200C9A66


#include "mark.h"
#include <ios>
#include <string>
#include <vector>

namespace YAML
{
	const std::string TokenNames[] = {
		"DIRECTIVE",
		"DOC_START",
		"DOC_END",
		"BLOCK_SEQ_START",
		"BLOCK_MAP_START",
		"BLOCK_SEQ_END",
		"BLOCK_MAP_END",
		"BLOCK_ENTRY",
		"FLOW_SEQ_START",
		"FLOW_MAP_START",
		"FLOW_SEQ_END",
		"FLOW_MAP_END",
		"FLOW_ENTRY",
		"KEY",
		"VALUE",
		"ANCHOR",
		"ALIAS",
		"TAG",
		"SCALAR"
	};

	struct Token {
		// enums
		enum STATUS { VALID, INVALID, UNVERIFIED };
		enum TYPE {
			DIRECTIVE,
			DOC_START,
			DOC_END,
			BLOCK_SEQ_START,
			BLOCK_MAP_START,
			BLOCK_SEQ_END,
			BLOCK_MAP_END,
			BLOCK_ENTRY,
			FLOW_SEQ_START,
			FLOW_MAP_START,
			FLOW_SEQ_END,
			FLOW_MAP_END,
			FLOW_ENTRY,
			KEY,
			VALUE,
			ANCHOR,
			ALIAS,
			TAG,
			SCALAR
		};

		// data
		Token(TYPE type_, const Mark& mark_): status(VALID), type(type_), mark(mark_) {}

		friend std::ostream& operator << (std::ostream& out, const Token& token) {
			out << TokenNames[token.type] << std::string(": ") << token.value;
			for(std::size_t i=0;i<token.params.size();i++)
				out << std::string(" ") << token.params[i];
			return out;
		}

		STATUS status;
		TYPE type;
		Mark mark;
		std::string value;
		std::vector <std::string> params;
	};
}

#endif // TOKEN_H_62B23520_7C8E_11DE_8A39_0800200C9A66
