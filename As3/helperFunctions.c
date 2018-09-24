#include <stdio.h>

void outputToFile(char const *myString)
{
	FILE *fp;
	fp = fopen("unittestresults.out", "w");
	fprintf(fp, myString);
	fclose(fp);
}

/*int main()
{
	char const *myTest = "Hello World\n";
	outputToFile(myTest);
	return 0;
}*/