
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int z = 0, i = 0, j = 0, c = 0;

char a[16], ac[20], stk[15], act[10];

void check()
{

	strcpy(ac, "REDUCE TO E -> ");

	for (z = 0; z < c; z++)
	{

		if (stk[z] == '4')
		{
			printf("%s4", ac);
			stk[z] = 'E';
			stk[z + 1] = '\0';

			printf("\n$%s\t%s$\t", stk, a);
		}
	}

	for (z = 0; z < c - 2; z++)
	{

		if (stk[z] == '2' && stk[z + 1] == 'E' &&
			stk[z + 2] == '2')
		{
			printf("%s2E2", ac);
			stk[z] = 'E';
			stk[z + 1] = '\0';
			stk[z + 2] = '\0';
			printf("\n$%s\t%s$\t", stk, a);
			i = i - 2;
		}
	}

	for (z = 0; z < c - 2; z++)
	{

		if (stk[z] == '3' && stk[z + 1] == 'E' &&
			stk[z + 2] == '3')
		{
			printf("%s3E3", ac);
			stk[z] = 'E';
			stk[z + 1] = '\0';
			stk[z + 1] = '\0';
			printf("\n$%s\t%s$\t", stk, a);
			i = i - 2;
		}
	}
}

int main()
{
	printf("GRAMMAR is -\nE->2E2 \nE->3E3 \nE->4\n");

	printf("Enter a string: ");
	fgets(a, 100, stdin);

	c = strlen(a);
	a[c - 1] = '\0';

	strcpy(act, "SHIFT");

	printf("\nstack \t input \t action");

	printf("\n$\t%s$\t", a);

	for (i = 0; j < c; i++, j++)
	{

		printf("%s", act);

		stk[i] = a[j];
		stk[i + 1] = '\0';

		a[j] = ' ';

		printf("\n$%s\t%s$\t", stk, a);

		check();
	}

	check();

	if (stk[0] == 'E' && stk[1] == '\0')
		printf("Accept\n");

	printf("Reject\n");
}

/*


EXECUTION 1:

GRAMMAR is -
E->2E2
E->3E3
E->4
Enter a string: 32423

stack    input   action
$       32423$  SHIFT
$3       2423$  SHIFT
$32       423$  SHIFT
$324       23$  REDUCE TO E -> 4
$32E       23$  SHIFT
$32E2       3$  REDUCE TO E -> 2E2
$3E         3$  SHIFT
$3E3         $  REDUCE TO E -> 3E3
$E            $ Accept


EXECUTION 2:

GRAMMAR is -
E->2E2 
E->3E3 
E->4
Enter a string: 23243

stack    input   action
$       23243$  SHIFT
$2       3243$  SHIFT
$23       243$  SHIFT
$232       43$  SHIFT
$2324       3$  REDUCE TO E -> 4
$232E       3$  SHIFT
$232E3       $  Reject

 */