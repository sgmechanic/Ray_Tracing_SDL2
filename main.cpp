#include "Header.h"

int main(int argc, char* args[])
{
	App TheApp;
	return TheApp.OnExecute();
	//LinAlgMatrix A;
	//A.PrintMatrix();
	//A.Elem(0, 1) = 3;
	//A.Elem(2, 3) = 8;
	//A.Elem(0, 2) = 4;
	//A.Inverse();
	//A.PrintMatrix();
	//A.Transpose();
	//A.PrintMatrix();
	//return 0;
	//LinAlgVector Test(std::vector<double>{1, 4, 2,2});
	//Test.PrintVector();
	//Test = A * Test;
	//Test.PrintVector();
	//return 0;


	//LinAlgMatrix B(std::vector<std::vector<double>>(4, std::vector<double>(2,0)));
	//B.PrintMatrix();
	//A.Join(B);
	//A.PrintMatrix();
	//A.Elem(0, 2) = 8;
	//A.PrintMatrix();
	//A.SwapRow(0, 1);
	//A.PrintMatrix();
	//return 0;
}

//Бойся своих каракуль с матрицами, все может из-за них не работать(Спокойно!)
 
//Вектор тоже нужно тестировать!!! И проверять норм ли я изобразил линейный оператор из этого всего!!!