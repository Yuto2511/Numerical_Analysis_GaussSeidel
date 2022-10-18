#include<stdio.h>
#include<stdlib.h>

//関数の宣言
int Gauss_Seidel();
int memory_secure(int);
int file_operation();
void input_elements();

//グローバル変数
double** matrix;
double* var_x;
int matrix_num = 0;
double buff = 0;

int main()
{
	int n = 0;
	char flag;
	printf("ファイルからパラメータを指定しますか? [Y/n]  ");
	scanf("%s", &flag);
	if(flag == 'Y' || flag == 'y') file_operation();
	else input_elements();

	while(Gauss_Seidel() != 1) n++;

	printf("\nround %d (", n+1);
	for(int i = 0; i < matrix_num-1; i++) printf("%12.10f, ", var_x[i]);
	printf("%12.10f)\n", var_x[matrix_num-1]);

	free(matrix);
	free(var_x);
	return 0;
}

//計算
int Gauss_Seidel()
{
	double sum = 0;
	for(int i = 0; i < matrix_num; i++){
		for(int j = 0; j < matrix_num; j++){
			if(i != j) sum += matrix[i][j] * var_x[j];
		}
		var_x[i] = (matrix[i][matrix_num] - sum) / matrix[i][i];
		sum = 0;
	}
	if(buff > var_x[0] * 0.999999999999 && buff < var_x[0] * 1.000000000001) return 1;
	
	buff = var_x[0];

	return 0;
}

//行列のパラメータを変更
int memory_secure(int num)
{
	var_x = (double*)malloc(sizeof(double) * num);

	matrix = (double**)malloc(sizeof(double*) * num);
	if(matrix == NULL) return -1;

	for(int i = 0; i < num; i++){
		matrix[i] = (double*)malloc(sizeof(double) * (num+1));
		if(matrix[i] == NULL) return -1;
	}

	for(int i = 0; i < num; i++) var_x[i] = 1;

	for(int i = 0; i < num; i++){
		for(int j = 0; j < num+1; j++){
			matrix[i][j] = 0;
		}
	}

	return 0;
}

//入力での行列指定
void input_elements()
{
	printf("何次正方行列か入力してください\n");
	scanf("%d", &matrix_num);

	memory_secure(matrix_num);

	printf("行列の要素とその解を入力してください\n");
	printf("3x3の例：1 2 3 10\n");
	printf("         4 5 6 11\n");
	printf("         7 8 9 12\n\n");

	for(int i = 0; i < matrix_num; i++){
		for(int j = 0; j < matrix_num+1; j++){
			scanf("%lf", &matrix[i][j]);
		}
	}
}

//ファイル操作での行列指定
int file_operation()
{
	FILE *fp;
	char fname[] = "matrix.txt";

	fp = fopen(fname, "r");
	if(fp == NULL){
		printf("ファイルを開けません\n");
		return -1;
	}

	fscanf(fp, "%d", &matrix_num);
	memory_secure(matrix_num);

	for(int i = 0; i < matrix_num; i++){
		for(int j = 0; j < matrix_num+1; j++){
			fscanf(fp, "%lf", &matrix[i][j]);
		}
	}

	for(int i = 0; i < matrix_num; i++){
		for(int j = 0; j < matrix_num+1; j++){
			printf("%0.0f ", matrix[i][j]);
		}
		printf("\n");
	}

	fclose(fp);

	return 0;
}
