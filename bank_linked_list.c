// Linked list program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_tools.c"

#define DATAFILE "Bank_accounts.dat"
#define length 20

typedef struct
{
	char account_number[20];
	char name[20];
	float balance;
}Bank;

struct node
{
	Bank account;
	struct node *next;
};

FILE *fp_data;

void show_menu();
void save_account();
void read_account();
void append_account_to_list();
void save_list_to_file();
void load_list();
void point_current_to_end();
void show_all();
void print_record(Bank *);
void update_account();
void update_name(char *);
//void update_message(char *);
//void delete_message(char *);
void update_balance(char *);
void delete_account();
//void pause();

struct node *start = NULL, *current, *new_node;
Bank temp_account;

void main()
{
	load_list();
	show_menu();
}

void show_menu()
{
	char choice;
	do
	{
		clear_screen();
		underline("BANK");
		printf("\n1. Save account\n2. Show all accounts\n3. Update account\n4. Delete account\n5. Exit\n-----------------\n");
		printf("Enter your choice: ");
		scanf(" %c", &choice);
		getchar();
		clear_screen();
		switch (choice)
		{
			case '1':
				save_account();
				break;
			case '2':
				show_all();
				break;
			case '3':
				update_account();
				break;
			case '4':
				delete_account();
				break;
			case '5':
				exit(1);
			default:
				printf("Invalid choice!");
		}
	}while (choice != '5');

}

void save_account()
{
	read_account();
	append_account_to_list();
	save_list_to_file();
	printf("Account saved successfully.\n");
	pause();
}

void read_account()
{
	printf("Enter account number: ");
	read_text(temp_account.account_number);
	printf("Enter name: ");
	read_text(temp_account.name);
	printf("Enter balance: ");
	read_float(&temp_account.balance);
	printf("Account read successfully.\n");
	pause();
}

void append_account_to_list()
{
	new_node = malloc(sizeof(struct node));
	new_node->account = temp_account;
	new_node->next = NULL;
	if (start == NULL)
	{
		start = new_node;
		current = new_node;
	}
	else
	{
		point_current_to_end();
		current->next = new_node;
		current = new_node;
	}
	printf("Account appended to linked list successfully.\n");
	pause();
}

void point_current_to_end()
{
	current = start;
	while (current->next != NULL)
	{
		current = current->next;
	}
}

void save_list_to_file()
{
	fp_data = fopen (DATAFILE, "wb");
	current = start;
	while (current != NULL)
	{
		temp_account = current->account;
		fwrite (&temp_account, sizeof(Bank), 1, fp_data);
		current = current->next;
	}
	fclose (fp_data);
	printf("Data saved into file successfully.\n");
	pause();
}

void load_list()
{
	fp_data = fopen (DATAFILE, "rb");
	while ( fread (&temp_account, sizeof(Bank), 1, fp_data) != 0)
	{
		new_node = malloc (sizeof(struct node));
		new_node->account = temp_account;
		new_node->next = NULL;
		if (start == NULL)
		{
			start = new_node;
		}
		else
		{
			current->next = new_node;
		}
		current = new_node;
	}
	fclose (fp_data);
	printf("Records loaded into linked list successfully.\n");
	pause();
}

void show_all()
{
	current = start;
	if (start == NULL)
	{
		printf("No records found!");
	}
	else
	{
		while (current != NULL)
		{
			//temp_account = current->account;
			print_record(&current->account);
			current = current->next;
		}
	}
	pause();
}

void print_record(Bank *account)
{
	printf("Account number: %s\nName: %s\nBalance: %.2f\n------------\n", account->account_number, account->name, account->balance);
}

void update_account()
{
	char choice;
	char account_number_to_update[length];
	printf("Enter account number to be updated: ");
	scanf("%s", account_number_to_update);
	printf("UPDATE\n------------\n1. update name\n2. update balance\n---------------\n");
	printf("Enter your choice to update: ");
	scanf(" %c", &choice);
	getchar();
	clear_screen();
	switch(choice)
	{
		case '1':
			update_name(account_number_to_update);
			break;
		case '2':
			update_balance(account_number_to_update);
			break;
		default:
			printf("Invalid choice!");
	}
}

void update_name(char *account_number_to_update)
{
	char new_name[length];
	printf("Enter new name: ");
	scanf("%s", new_name);
	current = start;
	while (current != NULL)
	{
		if (strcmp(account_number_to_update, current->account.account_number) == 0)
		{
			strcpy(current->account.name, new_name);
			break;
		}
		current = current->next;
	}
	if (current == NULL)
	{
		account_not_found_message(account_number_to_update);
		pause();
	}
	else
	{
		update_message(account_number_to_update);
		save_list_to_file();
	}
}

void update_balance(char *account_number_to_update)
{
	float new_balance;
	printf("Enter new balance: ");
	scanf("%f", &new_balance);
	current = start;
	while (current != NULL)
	{
		if (strcmp(account_number_to_update, current->account.account_number) == 0)
		{
			current->account.balance = new_balance;
			break;
		}
		current = current->next;
	}
	if (current == NULL)
	{
		account_not_found_message(account_number_to_update);
		pause();
	}
	else
	{
		update_message(account_number_to_update);
		save_list_to_file();
	}
}

void delete_account()
{
	struct node *before_current = NULL;
	char account_number_to_delete[length];
	printf("Enter account number to be deleted: ");
	scanf("%s", account_number_to_delete);
	current = start;
	while (current != NULL)
	{
		if (strcmp(account_number_to_delete, current->account.account_number) == 0)
		{
			if (before_current == NULL)
			{
				start = current->next;
				break;
			}
			else
			{
				before_current->next = current->next;
				break;
			}
		}
		before_current = current;
		current = current->next;
	}
	if (current == NULL)
	{
		account_not_found_message(account_number_to_delete);
		pause();
	}
	else
	{
		delete_message(account_number_to_delete);
		save_list_to_file();
	}
}
