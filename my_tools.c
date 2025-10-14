// misc functions
#include <stdio.h>

void remove_newline(char *text)
{
	text[strcspn(text, "\n")] = '\0';
}

void clear_screen()
{
	system("cls");
}

void pause()
{
	system("pause");
}

void underline(char* text)
{
	int counter;
	int length = strlen(text);
	printf("%s\n", text);
	for (counter = 0; counter < length; counter++)
	{
		printf("_");
	}
}

void read_text(char *text)
{
	scanf("%s", text);
	getchar();
}

void read_float(float *number)
{
	scanf("%f", number);
	getchar();
}

void update_message(char *id)
{
	printf("Account with account number: %s updated successfully.\n", id);
}

void delete_message(char *id)
{
	printf("Account with account number: %s deleted successfully.\n", id);
}

void account_not_found_message(char *id)
{
	printf("Account with account number: %s does not exist.\n", id);
}
