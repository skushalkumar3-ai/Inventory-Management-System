#include <stdio.h>
#include <string.h>

#define MAX 100

struct Date
{
    int day, month, year;
};

union ExtraInfo
{
    float discount;
    int supplierCode;
};

struct Item
{
    int id;
    char name[50];
    int quantity;
    struct Date expiryDate;

    int choice; // 1 = Discount, 2 = Supplier Code
    union ExtraInfo info;
};

struct Item items[MAX];
int count = 0;

void addItem();
void displayItems();
void updateItem();
void deleteItem();
void searchItem();
void showExpiredItems();
void stockReport();
int isExpired(struct Date exp, struct Date current);

int main()
{
    int choice;

    do
    {
        printf("\n===== INVENTORY MANAGEMENT SYSTEM =====\n");
        printf("1. Add Item\n");
        printf("2. Update Item\n");
        printf("3. Delete Item\n");
        printf("4. Search Item By Name\n");
        printf("5. Display All Items\n");
        printf("6. Show Expired Items\n");
        printf("7. Stock Report\n");
        printf("8. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: addItem(); break;
            case 2: updateItem(); break;
            case 3: deleteItem(); break;
            case 4: searchItem(); break;
            case 5: displayItems(); break;
            case 6: showExpiredItems(); break;
            case 7: stockReport(); break;
            case 8: printf("Exiting...\n"); break;
            default: printf("Invalid Choice!\n");
        }

    } while(choice != 8);

    return 0;
}

void addItem()
{
    if(count >= MAX)
    {
        printf("Inventory Full!\n");
        return;
    }

    printf("\nEnter Item ID: ");
    scanf("%d", &items[count].id);

    printf("Enter Item Name: ");
    scanf(" %[^\n]", items[count].name);

    printf("Enter Quantity: ");
    scanf("%d", &items[count].quantity);

    printf("Enter Expiry Date (dd mm yyyy): ");
    scanf("%d %d %d",
          &items[count].expiryDate.day,
          &items[count].expiryDate.month,
          &items[count].expiryDate.year);

    printf("1. Discount\n2. Supplier Code\nChoose: ");
    scanf("%d", &items[count].choice);

    if(items[count].choice == 1)
    {
        printf("Enter Discount: ");
        scanf("%f", &items[count].info.discount);
    }
    else
    {
        printf("Enter Supplier Code: ");
        scanf("%d", &items[count].info.supplierCode);
    }

    count++;
    printf("Item Added Successfully!\n");
}

void displayItems()
{
    int i;

    if(count == 0)
    {
        printf("No Items Available!\n");
        return;
    }

    printf("\n----- ITEMS -----\n");

    for(i = 0; i < count; i++)
    {
        printf("\nID: %d", items[i].id);
        printf("\nName: %s", items[i].name);
        printf("\nQuantity: %d", items[i].quantity);

        printf("\nExpiry Date: %02d/%02d/%d",
               items[i].expiryDate.day,
               items[i].expiryDate.month,
               items[i].expiryDate.year);

        if(items[i].choice == 1)
            printf("\nDiscount: %.2f", items[i].info.discount);
        else
            printf("\nSupplier Code: %d", items[i].info.supplierCode);

        printf("\n-------------------\n");
    }
}

void updateItem()
{
    int id, i;

    printf("Enter Item ID to Update: ");
    scanf("%d", &id);

    for(i = 0; i < count; i++)
    {
        if(items[i].id == id)
        {
            printf("Enter New Quantity: ");
            scanf("%d", &items[i].quantity);

            printf("Enter New Expiry Date (dd mm yyyy): ");
            scanf("%d %d %d",
                  &items[i].expiryDate.day,
                  &items[i].expiryDate.month,
                  &items[i].expiryDate.year);

            printf("Item Updated Successfully!\n");
            return;
        }
    }

    printf("Item Not Found!\n");
}

void deleteItem()
{
    int id, i, j;

    printf("Enter Item ID to Delete: ");
    scanf("%d", &id);

    for(i = 0; i < count; i++)
    {
        if(items[i].id == id)
        {
            for(j = i; j < count - 1; j++)
            {
                items[j] = items[j + 1];
            }

            count--;
            printf("Item Deleted Successfully!\n");
            return;
        }
    }

    printf("Item Not Found!\n");
}

void searchItem()
{
    char searchName[50];
    int i, found = 0;

    printf("Enter Item Name to Search: ");
    scanf(" %[^\n]", searchName);

    for(i = 0; i < count; i++)
    {
        if(strstr(items[i].name, searchName) != NULL)
        {
            printf("\nItem Found!");
            printf("\nID: %d", items[i].id);
            printf("\nName: %s", items[i].name);
            printf("\nQuantity: %d\n", items[i].quantity);

            found = 1;
        }
    }

    if(!found)
        printf("No Matching Item Found!\n");
}

int isExpired(struct Date exp, struct Date current)
{
    if(exp.year < current.year)
        return 1;

    if(exp.year == current.year &&
       exp.month < current.month)
        return 1;

    if(exp.year == current.year &&
       exp.month == current.month &&
       exp.day < current.day)
        return 1;

    return 0;
}

void showExpiredItems()
{
    struct Date current;
    int i, found = 0;

    printf("Enter Current Date (dd mm yyyy): ");
    scanf("%d %d %d",
          &current.day,
          &current.month,
          &current.year);

    printf("\nExpired Items:\n");

    for(i = 0; i < count; i++)
    {
        if(isExpired(items[i].expiryDate, current))
        {
            printf("%s\n", items[i].name);
            found = 1;
        }
    }

    if(!found)
        printf("No Expired Items Found.\n");
}

void stockReport()
{
    int i;

    printf("\n====== STOCK REPORT ======\n");
    printf("ID\tName\t\tQty\n");

    for(i = 0; i < count; i++)
    {
        printf("%d\t%s\t\t%d\n",
               items[i].id,
               items[i].name,
               items[i].quantity);
    }

    printf("\nTotal Items: %d\n", count);
}