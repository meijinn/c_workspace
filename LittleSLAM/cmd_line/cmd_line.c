#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		printf("�R�}���h���C���������w�肵�Ă�������\n");

		return 0;
	}

	if (strcmp(argv[1], "help") == 0)
	{
		printf("---------------------------\n");
		printf("�����Z�Fadd 10 20\n");
		printf("�����Z�Fsub 30 10\n");
		printf("---------------------------\n");
	}
	else if (strcmp(argv[1], "add") == 0 && argc == 4)
	{
		printf("add:%d\n", atoi(argv[2]) + atoi(argv[3]));
	}
	else if (strcmp(argv[1], "sub") == 0 && argc == 4)
	{
		printf("sub:%d\n", atoi(argv[2]) - atoi(argv[3]));
	}
	else
	{
		printf("�T�|�[�g����Ă��Ȃ��R�}���h���C�������ł�\n");
	}

	return 0;
}