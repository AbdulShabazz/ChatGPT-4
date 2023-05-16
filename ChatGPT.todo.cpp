#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>
// input
std::vector<
std::vector<std::string>> Theorem_0 = 
{
	{"1","+","1","+","1","+","1"},
	{"4"}
};

std::vector<
std::vector<std::string>> Axiom_1 = 
{
	{"1","+","1"},
	{"2"}
};

std::vector<
std::vector<std::string>> Axiom_2 = 
{
	{"2","+","2"},
	{"4"}
};

/**
// Reserved Symbols //
"root": 0
"lhs_reduction": 2
"lhs_expansion": 3
"rhs_reduction": 5
"rhs_expansion": 7
"0": 11
"=": 13
"{": 17
"}": 19
"[: 23
"]": 29
"(": 31
")": 37
"Theorem_": 41
"Axiom_": 43
"lemma_": 47

// Temporary Symbols //
"1": 53
"2": 57
"4": 59
"+": 61
*/

// formalized input for a recurrent neural network (ie. A 4D Vector) //
std::vector<
std::vector<
std::vector<std::size_t>>> RouteMap3DVecUInt64 =
{
	// {{opcode,axiom_N},{lhs}, {rhs}} //
	{{ 41,11 },{ 53,61,53,61,53,61,53 },{ 43 }},
	{{ 43,53 },{ 57,61,57 },{ 41 }},
	{{ 43,57 },{ 41,61,41 },{ 43 }}
};

// formalized output for a recurrent neural network (ie. A 4D Vector) //
std::vector<
std::vector<
std::vector<std::size_t>>> Result3DVecUInt64 =
{
	// {{opcode,axiom_N},{lhs}, {rhs}} //
	{{ 41,11,0 },{ 53,61,53,61,53,61,53 },{ 43 }}, // theorem_0 root: 1 + 1 + 1 + 1 = 4 //
	{{ 7,43,57 },{ 57,61,53,61,53 },{ 43 }}, // rhs_expansion via axiom_2: 2 + 1 + 1 = 4 //
	{{ 7,43,53 },{ 57,61,57 },{ 43 }}, // rhs_expansion via axiom_1: 2 + 2 = 4 //
	{{ 7,43,53 },{ 59 },{ 59 }} // rhs_expansion via axiom_1: 4 = 4 // QED
};

/**
// output //
auto Proofstep = 
{
	// {{lhs}, {rhs}} //
	{{"1","+","1","+","1","+","1"},{"4"}},
	{{"2","+","1","+","1"},{"4"}},
	{{"2","+","2"},{"4"}},
	{{"4"},{"4"}}
};

// output //
auto AxiomCommitLog = 
{
	"rhs_expansion via Axiom_2",
	"rhs_expansion via Axiom_1",
	"rhs_expansion via Axiom_1"
};
*/
