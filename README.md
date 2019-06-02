Simple spreadsheet
---

The goal of this semestral work is to make simple spreadsheet is C++.

The spreadsheet will suport following things:
	1) stings, numbers and functions in cells
	2) basic operators such as +, -, \*, /
	3) various basic math functions: sin, cos, abs, log, sqrt, sum
	4) links to other cells (=A2\*4)

Program will detect loop and won't allow expressions that would induce them

The spreadsheet will be able to be saved to a file in csv format (following basic rules written here: https://en.wikipedia.org/wiki/Comma-separated_values)

Finally the spreadsheet will implement aggregation functions such as: =AVG(D3:G5), =MAX(A1:A15), =COUNT(C5:D6)



#####Polymorphism

Parent class CCell and it's children CString, CNumber, CFunction.

