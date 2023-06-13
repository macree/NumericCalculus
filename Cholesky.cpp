// T2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{
	int n, i, j, varianta;
	double A[100][100], b[100];
	cout << "1-fisier 2-tastatura:\n";
	cin >> varianta;
	
	if (varianta == 1) {//CITIRE FISIER
		ifstream fin("matriceA.txt");
		ofstream fout("rezultat3.txt");

		fin >> n;

		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				fin >> A[i][j];

		for (i = 1; i <= n; i++)
			fin >> b[i];

		fout << "Matricea A:\n";
		for (i = 1; i <= n; i++)
		{
			for (j = 1; j <= n; j++)
				fout << A[i][j] << " ";
			fout << "\n";
		}

		fout << "Vectorul b este:\n";
		for (i = 1; i <= n; i++)
			fout << b[i] << " ";
		fout << "\n";

		//citirea de la tastatura
		/*cout << "Introdu dimensiunea matricii A: \n";
		cin >> n;

		cout << "Introdu valorile matricii A: \n";
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				cin >> A[i][j];
		for (i = 1; i <= n; i++)
		{
			for (j = 1; j <= n; j++)
				cout << A[i][j]<<" ";
			cout << "\n";
		}

		cout << "Introdu valorile vectorului b: \n";

		for (i = 1; i <= n; i++)
			cin >> b[i];*/

		int OK = 0, d[100];

		// vectorul cu elementele de pe diagonala matricii A
		for (i = 1; i <= n; i++)
		{
			if (A[i][i] == 0)
			{
				fout << "Matricea are pe diagonala cel putin o valoare de 0. Nu putem aplica descompunerea Cholesky.";
				return 0;
			}
			for (j = 1; j <= n; j++)
				if (A[i][j] < 0)
				{
					fout << "Matricea nu este pozitiva. Nu putem aplica descompunerea Cholesky.";
					return 0;
				}
			d[i] = A[i][i];
		}

		fout << "Vectorul d are urmatoarele valori:\n";
		for (i = 1; i <= n; i++)
			fout << d[i] << " ";
		fout << "\n";

		// verific daca este simetrica
		for (j = 1; j <= n; j++)
			for (i = 1; i <= n; i++)
				if (A[i][j] == A[j][i])
					OK = 1;
				else
				{
					OK = 0;
					break;
				}
		if (OK == 0)fout << "A NU este simetrica!\n";
		else
		{
			fout << "A este simetrica!\n";

			unsigned int detL = 1, detLt = 1, detA = 1;
			double L[100][100] = {};
			int zero = 0;

			/*for (int i = 1; i <=n; i++) {
				for (int j = 1; j <= i; j++) {
					unsigned int sum = 0;

					if (j == i) // summation for diagnols
					{
						for (int k = 1; k <= j-1; k++)
							sum += pow(A[j][k], 2);
						A[j][j] = sqrt(d[j] - sum); // 1 // i=2,j=1 1+
					}
					else {

						// Evaluating L(i, j) using L(j, j)
						for (int k = 1; k <j; k++)
							sum += (A[j][i] * A[j][k]);
						A[j][i] = (A[j][i] - sum) /d[j];
					}
				}
			}*/

			//calculez L si Lt
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= i; j++) {
					double sum = 0;

					if (j == i) // daca e diagonala
					{
						for (int k = 1; k <= j; k++)
							sum += pow(L[j][k], 2);
						L[j][j] = sqrt(A[j][j] - sum);
					}
					else {

						// daca nu aplic formula lui l(ik)
						for (int k = 0; k < j; k++)
							sum += (L[i][k] * L[j][k]);
						L[i][j] = (A[i][j] - sum) / L[j][j];
					}
				}
			}
			double jj = 0, times0, z = 1;
			fout << "Matricea L:\n";
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= i; j++) {
					A[i][j] = L[i][j];
					jj = j;
					fout << A[i][j] << " ";
				}
				//jj = jj + 1;
				if (jj + 1 > i && jj <= n) {
					times0 = n - jj;
					while (z <= times0)
					{
						fout << 0 << " ";
						z++;
					}
				}
				z = 1;
				fout << "\n";
			}
			/*for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) {
					fout << A[i][j] << " ";
				}
				fout << "\n";
			}*/


			/*fout << "Matricea Lt:\n";
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) {
					fout << A[j][i] << " ";
				}
				fout << "\n";
			}*/

			fout << "det(A)=det(L)*det(Lt): ";
			for (i = 1; i < n; i++)
				detA *= A[i][i];
			fout << pow(detA, 2) << "\n";

			fout << "Matricea A cu L si elementele initiale ale matricii A deasupra diagonalei:\n";
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) {
					fout << A[i][j] << " ";
				}
				fout << "\n";
			}

			/*fout << "Matricea L*Lt (A):\n";
			for (i = 1; i <= n; i++)
			{
				for (j = 1; j <= n; j++)
				{
					A[i][j + 1] = A[j + 1][i];
					fout << A[i][j] << " ";
				}
				fout << "\n";
			}*/

			// Calc. det(A)=det(L)*det(Lt)
			/*for (i = 1; i <= n; i++)
				detA = detA * pow(A[i][i], 2);
			fout << "det(A)=det(L)*det(Lt): " << detA << "\n";
			*/

			// L*y=b

			double vectorValoriY[100] = {};
			//226734

			// valoare y1
			vectorValoriY[1] = b[1] / A[1][1];

			//fout << "y1 " << vectorValoriY[1];
			//vectorValoriY[2] = (b[2] - A[2][1] * vectorValoriY[1]) / A[2][2];
			//fout << "y2 " << vectorValoriY[2];
			//vectorValoriY[3] = (b[3] - A[3][1] * vectorValoriY[1] - A[3][2] * vectorValoriY[2]) / A[3][3];
			//fout << "y3 " << vectorValoriY[3];

			for (i = 2; i <= n; i++)
			{
				j = 1;
				vectorValoriY[i] += b[i];
				while (j < i) {
					vectorValoriY[i] = vectorValoriY[i] - (A[i][j] * vectorValoriY[j]);
					j++;
				}
				vectorValoriY[i] /= A[i][i];
			}
			fout << "Vectorul cu valorile lui Y:\n";
			for (i = 1; i <= n; i++)
				fout << "Y" << i << ": " << vectorValoriY[i] << " ";
			fout << "\n";

			// Lt*x=Y* (vectorValoriY)

			double vectorValoriX[100] = {};
			//fout << vectorValoriY[n] <<" "<<A[n][n];

			// valoarea Xn
			vectorValoriX[n] = vectorValoriY[n] / A[n][n];
			//fout<<vectorValoriX[n];

			// Lt*x=y
			for (j = n - 1; j >= 1; j--)
			{
				i = n;
				vectorValoriX[j] += vectorValoriY[j];
				while (i >= j)
				{
					vectorValoriX[j] -= (A[i][j] * vectorValoriX[j - 1]);
					i--;
				}
				vectorValoriX[j] /= A[j][j];
			}

			fout << "X Cholesky. Vectorul cu valorile lui X:\n";
			for (i = 1; i <= n; i++)
				fout << "X" << i << ": " << vectorValoriX[i] << " ";
			fout << "\n";

			/*for (i = 1; i <= n; i++)
			{
				for (j = 1; j <= n; j++)
					fout<<A[i][j]<<" ";
				fout << "\n";
			}*/

			/*fout << "||X||2:\n";
			double sumX = 0;
			for (i = 1; i <= n; i++)
				sumX += pow(abs(vectorValoriX[i]), 2);
			sumX = sqrt(sumX);

			fout << sumX<<"\n";
			*/

			//DE DECOMENTAT CA SA CALCULEZE Ainit
			/*fout << "Ainit:\n";
			for (i = 1; i <= n; i++)
				A[i][i] = d[i];
			for (i = 2; i <= n; i++)
			{
				for (j = 1; j < i; j++)
					A[i][j] = A[j][i];
			}

			for (i = 1; i <= n; i++)
			{
				for (j = 1; j <= n; j++)
					fout << A[i][j] << " ";
				fout << "\n";
			}

			fout << "Ainit*Xchol-b:\n";
			double AiXchol[100][100] = {};
			//Ainit*Xchol
			for (i = 1; i <= n; i++)
				for (j = 1; j <= n; j++)
					for (int k = 1; k <= n; k++)
						AiXchol[i][j] += A[i][k] * vectorValoriX[k];


			/*for (i = 1; i <= n; i++)
			{
				for (j = 1; j <= n; j++)
					fout << AiXchol [i] [j] << " ";
				fout << "\n";
			}

			j = 1;
			for (i = 1; i <= n; i++)
				AiXchol[i][j] -= b[i];

			for (i = 1; i <= n; i++)
				fout << AiXchol[i][j] << "\n";

			double normaAXcholb = 0;
			for (i = 1; i <= n; i++)
				normaAXcholb += pow(AiXchol[i][j], 2);
			fout << "normaAXcholb: " << sqrt(normaAXcholb); */

			// A^-1

			double vectorValoriY2[100] = {};
			double vectorValoriX2[100] = {};
			/*double vectorI[100] = {};// practic matricea I
			for (int i = 1; i <= n; i++)
			{
				vectorI[i]++;
			}*/
			
		
			double b[100] = {};
			int count = 1;
			
			fout << "Matricea A^(-1):\n";
			while (count <= n)
			{
				b[count]++;
			
			//b[1] = 0;
			//b[2] = 0;
			//b[3] = 1;

					// valoare y2-1
					//if (x == 1)
					vectorValoriY2[1] = b[1] / A[1][1];

					for (i = 2; i <= n; i++)
					{
						j = 1;
						vectorValoriY2[i] += b[i];
						while (j < i) {
							vectorValoriY2[i] = vectorValoriY2[i] - (A[i][j] * vectorValoriY2[j]);
							j++;
						}
						vectorValoriY2[i] /= A[i][i];
					}
					/*fout << "Vectorul cu valorile lui Y2:\n";
					for (i = 1; i <= n; i++)
						fout << "Y2-" << i << ": " << vectorValoriY2[i] << " ";
					fout << "\n";*/


					// Lt*x=Y* (vectorValoriY2)

					//double vectorValoriX2[100] = {};
					//fout << vectorValoriY[n] <<" "<<A[n][n];

					// valoarea Xn
					vectorValoriX2[n] = vectorValoriY2[n] / A[n][n];

					// Lt*x=y
					for (j = n - 1; j >= 1; j--)
					{
						//x = 0;
						vectorValoriX2[j] += vectorValoriY2[j];
						for (i = n; i > j; i--)
						{
							vectorValoriX2[j] = vectorValoriX2[j] + (-1) * (A[i][j] * vectorValoriX2[i]);
							//x++;
						}
						vectorValoriX2[j] /= A[j][j];
					}

					//fout << "vectorX2:\n";
					for (int i = 1; i <= n; i++)
					{
						fout << vectorValoriX2[i] << " ";
						vectorValoriX2[i] = 0;
						vectorValoriY2[i] = 0;
					}
					fout << "\n";
					b[count]--;
					count++;
			}
		}
	}
	else // CITIRE TASTATURA
	{
	cout << "Introdu dimensiunea n:\n";
	cin >> n;

	cout << "Introdu valori pt. matricea A:\n";
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			cin >> A[i][j];

	cout << "Introdu valori pt. b:\n";
	for (i = 1; i <= n; i++)
		cin >> b[i];

	cout << "Matricea A:\n";
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
			cout << A[i][j] << " ";
		cout << "\n";
	}

	cout << "Vectorul b este:\n";
	for (i = 1; i <= n; i++)
		cout << b[i] << " ";
	cout << "\n";

	//citirea de la tastatura
	/*cout << "Introdu dimensiunea matricii A: \n";
	cin >> n;

	cout << "Introdu valorile matricii A: \n";
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			cin >> A[i][j];
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
			cout << A[i][j]<<" ";
		cout << "\n";
	}

	cout << "Introdu valorile vectorului b: \n";

	for (i = 1; i <= n; i++)
		cin >> b[i];*/

	int OK = 0, d[100];

	// vectorul cu elementele de pe diagonala matricii A
	for (i = 1; i <= n; i++)
	{
		if (A[i][i] == 0)
		{
			cout << "Matricea are pe diagonala cel putin o valoare de 0. Nu putem aplica descompunerea Cholesky.";
			return 0;
		}
		for (j = 1; j <= n; j++)
			if (A[i][j] < 0)
			{
				cout << "Matricea nu este pozitiva. Nu putem aplica descompunerea Cholesky.";
				return 0;
			}
		d[i] = A[i][i];
	}

	cout << "Vectorul d are urmatoarele valori:\n";
	for (i = 1; i <= n; i++)
		cout << d[i] << " ";
	cout << "\n";

	// verific daca este simetrica
	for (j = 1; j <= n; j++)
		for (i = 1; i <= n; i++)
			if (A[i][j] == A[j][i])
				OK = 1;
			else
			{
				OK = 0;
				break;
			}
	if (OK == 0)cout << "A NU este simetrica!\n";
	else
	{
		cout << "A este simetrica!\n";

		double detL = 1, detLt = 1, detA = 1;
		double L[100][100] = {};
		int zero = 0;

		/*for (int i = 1; i <=n; i++) {
			for (int j = 1; j <= i; j++) {
				unsigned int sum = 0;

				if (j == i) // summation for diagnols
				{
					for (int k = 1; k <= j-1; k++)
						sum += pow(A[j][k], 2);
					A[j][j] = sqrt(d[j] - sum); // 1 // i=2,j=1 1+
				}
				else {

					// Evaluating L(i, j) using L(j, j)
					for (int k = 1; k <j; k++)
						sum += (A[j][i] * A[j][k]);
					A[j][i] = (A[j][i] - sum) /d[j];
				}
			}
		}*/

		//calculez L si Lt
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= i; j++) {
				double sum = 0;

				if (j == i) // daca e diagonala
				{
					for (int k = 1; k <= j; k++)
						sum += pow(L[j][k], 2);
					L[j][j] = sqrt(A[j][j] - sum);
				}
				else {

					// daca nu aplic formula lui l(ik)
					for (int k = 0; k < j; k++)
						sum += (L[i][k] * L[j][k]);
					L[i][j] = (A[i][j] - sum) / L[j][j];
				}
			}
		}
		double jj = 0, times0, z = 1;
		cout << "Matricea L:\n";
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= i; j++) {
				A[i][j] = L[i][j];
				jj = j;
				cout << A[i][j] << " ";
			}
			//jj = jj + 1;
			if (jj + 1 > i && jj <= n) {
				times0 = n - jj;
				while (z <= times0)
				{
					cout << 0 << " ";
					z++;
				}
			}
			z = 1;
			cout << "\n";
		}
		/*for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				fout << A[i][j] << " ";
			}
			fout << "\n";
		}*/


		/*fout << "Matricea Lt:\n";
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				fout << A[j][i] << " ";
			}
			fout << "\n";
		}*/

		cout << "det(A)=det(L)*det(Lt): ";
		for (i = 1; i < n; i++)
			detA *= A[i][i];
		cout << pow(detA, 2) << "\n";

		cout << "Matricea A cu L si elementele initiale ale matricii A deasupra diagonalei:\n";
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cout << A[i][j] << " ";
			}
			cout << "\n";
		}

		/*fout << "Matricea L*Lt (A):\n";
		for (i = 1; i <= n; i++)
		{
			for (j = 1; j <= n; j++)
			{
				A[i][j + 1] = A[j + 1][i];
				fout << A[i][j] << " ";
			}
			fout << "\n";
		}*/

		// Calc. det(A)=det(L)*det(Lt)
		/*for (i = 1; i <= n; i++)
			detA = detA * pow(A[i][i], 2);
		fout << "det(A)=det(L)*det(Lt): " << detA << "\n";
		*/

		// L*y=b

		double vectorValoriY[100] = {};
		//226734

		// valoare y1
		vectorValoriY[1] = b[1] / A[1][1];

		//fout << "y1 " << vectorValoriY[1];
		//vectorValoriY[2] = (b[2] - A[2][1] * vectorValoriY[1]) / A[2][2];
		//fout << "y2 " << vectorValoriY[2];
		//vectorValoriY[3] = (b[3] - A[3][1] * vectorValoriY[1] - A[3][2] * vectorValoriY[2]) / A[3][3];
		//fout << "y3 " << vectorValoriY[3];

		for (i = 2; i <= n; i++)
		{
			j = 1;
			vectorValoriY[i] += b[i];
			while (j < i) {
				vectorValoriY[i] = vectorValoriY[i] - (A[i][j] * vectorValoriY[j]);
				j++;
			}
			vectorValoriY[i] /= A[i][i];
		}
		cout << "Vectorul cu valorile lui Y:\n";
		for (i = 1; i <= n; i++)
			cout << "Y" << i << ": " << vectorValoriY[i] << " ";
		cout << "\n";

		// Lt*x=Y* (vectorValoriY)

		double vectorValoriX[100] = {};
		//fout << vectorValoriY[n] <<" "<<A[n][n];

		// valoarea Xn
		vectorValoriX[n] = vectorValoriY[n] / A[n][n];
		//fout<<vectorValoriX[n];

		// Lt*x=y
		for (j = n - 1; j >= 1; j--)
		{
			i = n;
			vectorValoriX[j] += vectorValoriY[j];
			while (i >= j)
			{
				vectorValoriX[j] -= (A[i][j] * vectorValoriX[j - 1]);
				i--;
			}
			vectorValoriX[j] /= A[j][j];
		}

		cout << "X Cholesky. Vectorul cu valorile lui X:\n";
		for (i = 1; i <= n; i++)
			cout << "X" << i << ": " << vectorValoriX[i] << " ";
		cout << "\n";
		
		/*
		cout << "||X||2:\n";
		double sumX = 0;
		for (i = 1; i <= n; i++)
			sumX += pow(abs(vectorValoriX[i]), 2);
		sumX = sqrt(sumX);

		cout << sumX;
		*/

		cout << "Ainit:\n";
		for (i = 1; i <= n; i++)
			A[i][i] = d[i];
		for (i = 2; i <= n; i++)
		{
			for (j = 1; j < i; j++)
				A[i][j] = A[j][i];
		}

		for (i = 1; i <= n; i++)
		{
			for (j = 1; j <= n; j++)
				cout << A[i][j] << " ";
			cout << "\n";
		}

		cout << "Ainit*Xchol-b:\n";
		double AiXchol[100][100] = {};
		//Ainit*Xchol
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				for (int k = 1; k <= n; k++)
					AiXchol[i][j] += A[i][k] * vectorValoriX[k];

		/*for (i = 1; i <= n; i++)
		{
			for (j = 1; j <= n; j++)
				fout << AiXchol [i] [j] << " ";
			fout << "\n";
		}*/

		j = 1;
		for (i = 1; i <= n; i++)
			AiXchol[i][j] -= b[i];

		for (i = 1; i <= n; i++)
			cout << AiXchol[i][j] << "\n";

		double normaAXcholb = 0;
		for (i = 1; i <= n; i++)
			normaAXcholb += pow(AiXchol[i][j], 2);
		cout << "normaAXcholb: " << sqrt(normaAXcholb);

	}
	}
	/*for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= i; j++)
			cout << lower[i][j] << " ";
		cout << "\n";
	}*/
	//afisarea lui L si Lt a matricii A
	/*
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= i; j++)
				fout << A[i][j] << " ";
		fout << "\n";
	}
	for (j = 1; j <= n; j++)
	{
		for (i = 1; i <= j; i++)
			fout << A[i][j] << " ";
		fout << "\n";
	}*/

	// detL
	/*for (i = 1; i <= n; i++)
	{
		detL = detL * d[i];// l11* l22 * l33 * ... lnn
		detLt = detL;
	}
	detA = detL * detLt;*/

	//afisarea transpusei
	/*for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
			fout << A[j][i] << " ";
		fout << "\n";
	}*/

	// calcularea lui L si L^t
	/*
	int L[100][100] = {}, Lt[100][100];
	// AL = L
	// Lower triangular matrix
	for (i = 1; i <= n; i++)
		for (j = 1; j <= i; j++)
			L[i][j] = A[i][j];

	// ALt Upper triangular matrix
	for (j = 1; j <= n; j++)
		for (i = 1; i <= n; i++)
			Lt [i][j] = L[j][i];
	*/
	// afisarea lui AL si ALt
	/*
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
			fout << AL[i][j]<<" ";
		fout << "\n";
	}
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
			fout << ALt[i][j]<<" ";
		fout << "\n";
	}
	*/

	/*
	unsigned int detL = 1, detLt=1;
	//detL = l11* l22* l33* ...lnn
	for (i = 1; i <= n; i++)
	{
		detL = detL * L[i][i];
		detLt = detLt * Lt[i][i];
	}
	fout <<"Determinantul lui L este: "<< detL<<"\n";
	fout <<"Determinantul lui Lt este: "<< detLt<<"\n";
	*/
}
