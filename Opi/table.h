#pragma once
#include "data.h"

void printLine(const vector<int>& widths);
void printRow(const vector<string>& value, const vector<int>& widths);
void printTable(const vector<string>& headers,
	const vector<int>& widths,
	const vector<vector<string>>& rows);