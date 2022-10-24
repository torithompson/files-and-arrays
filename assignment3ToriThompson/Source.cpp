#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

//Tori Thompson
//Assignment 3 - Analysis and display of wine store sales

using namespace std;

const int SIZE = 6;
const int QUARTERLY = 4;

void loadArrays(ifstream&, string[], double[][QUARTERLY], int&);
void computeSum(const double[][QUARTERLY], double[], const int);
void printReport(ofstream&, const string[], const double[][QUARTERLY], const double[], const int, const int);
void findWine(const double[][QUARTERLY], int&, int&, const int);
void mostWineSold(const double[], int&, const int);

int main()
{
	double salesAmt[SIZE][4];
	string wine[SIZE];
	double yearlySales[SIZE] = { 0.00 };
	int noWines;
	int highestRow, highestCol, mostSold;
	cout << fixed << setprecision(2);
	ifstream fin("wines.dat");
	if (!fin.is_open())
	{
		cout << "error opening wines.dat file - contact systems";
		system("pause");
		exit(-1);
	}
	ofstream fout("winesales.rpt");
	if (!fout.is_open())
	{
		cout << "error opening winesales.rpt file - contact systems";
		system("pause");
		exit(-2);
	}
	fout << fixed << setprecision(2);

	cout << "\n\nLoad arrays\n\n";
	loadArrays(fin, wine, salesAmt, noWines);
	cout << "\n\n=======================================================\n\n";

	cout << "\n\nCompute yearly Sale\n\n";
	computeSum(salesAmt, yearlySales, noWines);
	cout << "\n\n=======================================================\n\n";
	
	cout << "\n\nFind best selling wine and highest sales amount:\n\n";
	findWine(salesAmt, highestRow, highestCol, noWines);
	cout << "\n\n" << wine[highestRow] << " had the highest sales amount = $"
		<< salesAmt[highestRow][highestCol] << endl;
	cout << "\n\n=======================================================\n\n";

	cout << "\n\nFind the most sold wine:\n\n";
	mostWineSold(yearlySales, mostSold, noWines);
	cout << "\n\n Most sold wine is " << wine[mostSold] << endl;

	cout << "\n\n=======================================================\n\n";
	printReport(fout, wine, salesAmt, yearlySales, mostSold, noWines);
	cout << "\n\n=======================================================\n\n";

	cout << "program ended successfully" << endl;
	cout << "\n\n Printing wines.dat file\n\n";
	system("type wines.dat");
	cout << "\n\n Printing winesales.rpt file\n\n";
	system("type winesales.rpt");
	system("pause");
}
/// <summary>
/// Load the arrays with information from file, returning by reference number of wines added
/// </summary>
/// <param name="fin"></param>
/// <param name="typeWine"></param>
/// <param name="quarterlySales"></param>
/// <param name="noWines"></param>
void loadArrays(ifstream& fin, string typeWine[], double quarterlySales[][QUARTERLY], int& noWines)
{
	for (noWines = 0; noWines < SIZE; noWines++)
	{
		getline(fin, typeWine[noWines]);
		if (fin.eof())
			break;

		for (int col = 0; col < QUARTERLY; col++)
		{
			fin >> quarterlySales[noWines][col];
		}
		fin.ignore(80, '\n');
	}
}
/// <summary>
/// Compute sum of quarterly sales into yearly sales for each type of wine
/// </summary>
/// <param name="quarterlySales"></param>
/// <param name="yearlySales"></param>
/// <param name="noWines"></param>
void computeSum(const double quarterlySales[][QUARTERLY], double yearlySales[], const int noWines)
{
	double sum;
	for (int row = 0; row < noWines; row++)
	{
		sum = 0.0;
		for (int col = 0; col < QUARTERLY; col++)
		{
			sum += quarterlySales[row][col];
		}
		yearlySales[row] = sum;
	}
}
/// <summary>
/// Print wine name, sales, yearly sales and which wine sold the most to file 
/// </summary>
/// <param name="fout"></param>
/// <param name="wineName"></param>
/// <param name="quarterlySales"></param>
/// <param name="yearlySales"></param>
/// <param name="mostSold"></param>
/// <param name="noWines"></param>
void printReport(ofstream& fout, const string wineName[], const double quarterlySales[][QUARTERLY], const double yearlySales[], 
				const int mostSold, const int noWines)
{
	double sum = 0.0;
	fout << fixed << setprecision(2);
	fout << left << setw(40) << "Wine" << left << setw(45) << "Quarterly Sales" << endl;
	fout << right << setw(25) << "1st" << setw(15) << "2nd" << setw(15) << "3rd" << setw(15) << "4th" 
		<< setw(15) << "Yearly" << endl << endl;
	for (int row = 0; row < noWines; row++)
	{
		fout << left << setw(10) << wineName[row];
		for (int col = 0; col < QUARTERLY; col++)
			fout << right << setw(15) << quarterlySales[row][col];
		fout << right << setw(15) << yearlySales[row];
		if (row == mostSold)
			fout << "***most sold***";
		sum += yearlySales[row];
		fout << endl;
	}
	fout << endl;
	fout << "Total Sales Amount $" << sum << endl << endl;
}
/// <summary>
/// Running through quarterly sales to find highest amount and return by ref which row and column this is at
/// </summary>
/// <param name="quarterlySales"></param>
/// <param name="highestRow"></param>
/// <param name="highestCol"></param>
/// <param name="noWines"></param>
void findWine(const double quarterlySales[][QUARTERLY], int& highestRow, int& highestCol, const int noWines)
{
	highestCol = 0;
	for (int row = 0; row < noWines; row++)
	{
		for (int col = 0; col < QUARTERLY; col++)
		{
			if (quarterlySales[row][col] > quarterlySales[row][highestCol])
			{
				highestCol = col;
				highestRow = row;
			}
		}
	}
}
/// <summary>
/// Going through yearly sales to find the most wine sold for the year and returning this index value
/// </summary>
/// <param name="yearlySales"></param>
/// <param name="mostSold"></param>
/// <param name="noWines"></param>
void mostWineSold(const double yearlySales[], int& mostSold, const int noWines)
{
	mostSold = 0;
	for (int index = 0; index < noWines; index++)
	{
		if (yearlySales[index] > yearlySales[mostSold])
			mostSold = index;
	}
}
/*


Load arrays



=======================================================



Compute yearly Sale



=======================================================



Find best selling wine and highest sales amount:



Chardonnay had the highest sales amount = $50000.00


=======================================================



Find the most sold wine:



 Most sold wine is White


=======================================================



=======================================================

program ended successfully


 Printing wines.dat file

Red
200000.00       50000.00        57000.00        16800.00
Rose
25000.00        0.00            4500.00         7800.00
White
300000.00   4400.00     23000.00    5300.00
Sparkling
5000.50         0.00            60000.50        6500.00
Pinot Noir
60000.00        50640.00        59580.00        6000.00
Chardonnay
5400.50         50000.00        4060.00         9085.50

 Printing winesales.rpt file

Wine                                    Quarterly Sales
					  1st            2nd            3rd            4th         Yearly

Red             200000.00       50000.00       57000.00       16800.00      323800.00
Rose             25000.00           0.00        4500.00        7800.00       37300.00
White           300000.00        4400.00       23000.00        5300.00      332700.00***most sold***
Sparkling         5000.50           0.00       60000.50        6500.00       71501.00
Pinot Noir       60000.00       50640.00       59580.00        6000.00      176220.00
Chardonnay        5400.50       50000.00        4060.00        9085.50       68546.00

Total Sales Amount $1010067.00

Press any key to continue . . .
*/