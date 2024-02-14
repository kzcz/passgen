#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
char *symbols = "@#$&_-()=%+?!/:*\";[]{}<>~^`~";
inline char chrinrange(char min, char max)
{
	//char min<=x<max
	return (rand() % (max - min)) + min;
}
inline char choice(char *a, char length)
{
	return a[rand() % length];
}
int main()
{
	
	puts("Password generator");
	int bufsize;
	printf("<Enter password length>");
	scanf("%d", &bufsize);
	char *selectop = malloc(5); // 5 = 4+1
	char ops = 0;
	int i;
	memset(selectop, 0, 5);
	srand(time(0) * 73 + 31);
	//It could change
	puts("Options:");
	puts("1 -> Nums");
	puts("2 -> Symbols");
	puts("3 -> Uppercase letters");
	puts("4 -> Lowercase letters");
	printf("%s", "<Enter options> ");
	scanf("%s", selectop);
	for (i = 0; i < 5; i++)
	{
		// We could assume selectop[i] its an actual number, but this is safer
		switch (selectop[i])
		{
		case '1':
			ops |= 1;
			break;
		case '2':
			ops |= 2;
			break;
		case '3':
			ops |= 4;
			break;
		case '4':
			ops |= 8;
			break;
		default:
			break;
		}
	}
	//I know it's ugly but it works
	char len = (ops & 1) + ((ops >> 1) & 1) + ((ops >> 2) & 1) + ((ops >> 3) & 1);
	char *base = malloc(bufsize + 1);// +1 for NUL
	if(!base){
		printf("Couldn't allocate %d bytes of memory.\n",bufsize+1);
		return 1;
		}
	char *chrset = malloc(4); // bruh
	for (i = 0; i < bufsize; i++)
	{
		if (ops & 1)
		{
			*chrset = chrinrange('0', '9' + 1);
			chrset++;
		}
		if (ops & 2)
		{
			*chrset = choice(symbols, strlen(symbols));
			chrset++;
		}
		if (ops & 4)
		{
			*chrset = chrinrange('A', 'Z' + 1);
			chrset++;
		}
		if (ops & 8)
		{
			*chrset = chrinrange('a', 'z' + 1);
			chrset++;
		}
		chrset -= len;
		*base = choice(chrset, len);
		base++;
	}
	// No memleaks :D
	free(chrset);
	*base = 0;
	base -= bufsize;
	//More coming soon
	puts("Formats:");
	puts("a -> Ascii");
	puts("z -> Character index");
	puts("x -> Hexadecimal");
	puts("c -> C Array of chars");
	puts("p -> Python Byte list");
	fflush(stdin); // System Dependent but the alternative looks bad
	char style = 0;
	printf("<Enter format>");
	scanf("%c", &style);
	switch (style)
	{
	case 'a':
		printf("Password : %s", base);
		break;
	case 'z':
	case 'x':
		//Idk why but the ; is needed
		;
		char *fmt, *fmt2;// Lose performance for file size
		if (style == 'z')
		{
			fmt = "%d, ";
			fmt2 = "%d";
		}
		else
		{
			fmt = "%x ";
			fmt2 = "%x";
		}
		printf("Password : ");
		while (*(base + 1))
		{
			printf(fmt, *base);
			base++;
		}
		printf(fmt2, *base);
		puts("");
		break;
	case 'c':
		printf("unsigned char password[] = {");
		while (*(base + 1))
		{
			printf("'%c', ", *base);
			base++;
		}
		printf("'%c'};\n", *base);
		printf("int password_length = %d;\n", bufsize);
		break;
	case 'p':
		printf("py_bytes=bytes([");
		while (*(base + 1))
		{
			printf("%d, ", *base);
			base++;
		}
		printf("%d])\n", *base);
		break;
	default:
		printf("Unknown format %c", style);
	
	}
	free(base);
}
