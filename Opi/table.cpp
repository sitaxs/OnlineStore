

#include"table.h"

void printLine(const vector<int>& widths) {
	int total = 1;
	for (int w : widths) {
		total += w + 2;
	}
	cout << setfill('-') << setw(total) << "" << setfill(' ') << '\n';
}
//це розмір рядка та значення які будут записуватися в кожному рядку 
void printRow(const vector<string>& value, const vector<int>& widths) {
	cout << left;
	for (int i = 0; i < value.size(); i++) {
		cout << "| " << setw(widths[i]) << value[i];
	}
	cout << endl;
}

// самий вівід таблиці 
void printTable(const vector<string>& headers,
	const vector<int>& widths,
	const vector<vector<string>>& rows) {
	printLine(widths);
	printRow(headers, widths);   // заголовок — такий самий рядок
	printLine(widths);
	for (const vector<string>& row : rows) {
		printRow(row, widths);
	}
	printLine(widths);
}