
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EMPLOYEES 100
#define MAX_NAME_LENGTH 50
#define MAX_DEPT_LENGTH 30

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char department[MAX_DEPT_LENGTH];
    float salary;
    int age;
    char email[50];
    char phone[15];
} Employee;

Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;

void displayMenu();
void addEmployee();
void displayAllEmployees();
void searchEmployee();
void updateEmployee();
void deleteEmployee();
void sortEmployees();
void generateReport();
int findEmployeeById(int id);
int isEmailValid(const char *email);
int isPhoneValid(const char *phone);
void clearInputBuffer();

int main() {
    int choice;
    
    printf("=== EMPLOYEE MANAGEMENT SYSTEM ===\n");
    
    while(1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();
        
        switch(choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                displayAllEmployees();
                break;
            case 3:
                searchEmployee();
                break;
            case 4:
                updateEmployee();
                break;
            case 5:
                deleteEmployee();
                break;
            case 6:
                sortEmployees();
                break;
            case 7:
                generateReport();
                break;
            case 8:
                printf("Thank you for using the Employee Management System!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}

void displayMenu() {
    printf("\n=== MAIN MENU ===\n");
    printf("1. Add Employee\n");
    printf("2. Display All Employees\n");
    printf("3. Search Employee\n");
    printf("4. Update Employee\n");
    printf("5. Delete Employee\n");
    printf("6. Sort Employees\n");
    printf("7. Generate Report\n");
    printf("8. Exit\n");
    printf("=================\n");
}

void addEmployee() {
    if(employeeCount >= MAX_EMPLOYEES) {
        printf("Employee database is full!\n");
        return;
    }
    
    Employee newEmployee;
    
    printf("\n=== ADD NEW EMPLOYEE ===\n");
    
    // Generate automatic ID
    newEmployee.id = employeeCount + 1;
    printf("Employee ID: %d\n", newEmployee.id);
    
    // Get employee name
    printf("Enter name: ");
    fgets(newEmployee.name, MAX_NAME_LENGTH, stdin);
    newEmployee.name[strcspn(newEmployee.name, "\n")] = 0;
    
    // Get department
    printf("Enter department: ");
    fgets(newEmployee.department, MAX_DEPT_LENGTH, stdin);
    newEmployee.department[strcspn(newEmployee.department, "\n")] = 0;
    
    // Get salary
    printf("Enter salary: ");
    while(scanf("%f", &newEmployee.salary) != 1 || newEmployee.salary < 0) {
        printf("Invalid salary! Please enter a positive number: ");
        clearInputBuffer();
    }
    clearInputBuffer();
    
    // Get age
    printf("Enter age: ");
    while(scanf("%d", &newEmployee.age) != 1 || newEmployee.age < 18 || newEmployee.age > 65) {
        printf("Invalid age! Please enter age between 18-65: ");
        clearInputBuffer();
    }
    clearInputBuffer();
    
    // Get email with validation
    do {
        printf("Enter email: ");
        fgets(newEmployee.email, 50, stdin);
        newEmployee.email[strcspn(newEmployee.email, "\n")] = 0;
        if(!isEmailValid(newEmployee.email)) {
            printf("Invalid email format! Please try again.\n");
        }
    } while(!isEmailValid(newEmployee.email));
    
    // Get phone with validation
    do {
        printf("Enter phone number: ");
        fgets(newEmployee.phone, 15, stdin);
        newEmployee.phone[strcspn(newEmployee.phone, "\n")] = 0;
        if(!isPhoneValid(newEmployee.phone)) {
            printf("Invalid phone number! Please enter 10 digits.\n");
        }
    } while(!isPhoneValid(newEmployee.phone));
    
    employees[employeeCount++] = newEmployee;
    printf("Employee added successfully!\n");
}

void displayAllEmployees() {
    if(employeeCount == 0) {
        printf("No employees in the database!\n");
        return;
    }
    
    printf("\n=== ALL EMPLOYEES ===\n");
    printf("%-5s %-20s %-15s %-10s %-5s %-25s %-15s\n", 
           "ID", "Name", "Department", "Salary", "Age", "Email", "Phone");
    printf("--------------------------------------------------------------------------------\n");
    
    for(int i = 0; i < employeeCount; i++) {
        printf("%-5d %-20s %-15s $%-9.2f %-5d %-25s %-15s\n",
               employees[i].id,
               employees[i].name,
               employees[i].department,
               employees[i].salary,
               employees[i].age,
               employees[i].email,
               employees[i].phone);
    }
}

void searchEmployee() {
    if(employeeCount == 0) {
        printf("No employees in the database!\n");
        return;
    }
    
    int choice;
    printf("\n=== SEARCH EMPLOYEE ===\n");
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    clearInputBuffer();
    
    if(choice == 1) {
        int id;
        printf("Enter employee ID: ");
        scanf("%d", &id);
        clearInputBuffer();
        
        int index = findEmployeeById(id);
        if(index != -1) {
            printf("\nEmployee Found:\n");
            printf("ID: %d\n", employees[index].id);
            printf("Name: %s\n", employees[index].name);
            printf("Department: %s\n", employees[index].department);
            printf("Salary: $%.2f\n", employees[index].salary);
            printf("Age: %d\n", employees[index].age);
            printf("Email: %s\n", employees[index].email);
            printf("Phone: %s\n", employees[index].phone);
        } else {
            printf("Employee with ID %d not found!\n", id);
        }
    } else if(choice == 2) {
        char searchName[MAX_NAME_LENGTH];
        printf("Enter employee name: ");
        fgets(searchName, MAX_NAME_LENGTH, stdin);
        searchName[strcspn(searchName, "\n")] = 0;
        
        int found = 0;
        for(int i = 0; i < employeeCount; i++) {
            if(strcasecmp(employees[i].name, searchName) == 0) {
                if(!found) {
                    printf("\nEmployee(s) Found:\n");
                    found = 1;
                }
                printf("ID: %d, Name: %s, Department: %s, Salary: $%.2f\n",
                       employees[i].id, employees[i].name, 
                       employees[i].department, employees[i].salary);
            }
        }
        if(!found) {
            printf("No employee with name '%s' found!\n", searchName);
        }
    } else {
        printf("Invalid choice!\n");
    }
}

void updateEmployee() {
    if(employeeCount == 0) {
        printf("No employees in the database!\n");
        return;
    }
    
    int id;
    printf("Enter employee ID to update: ");
    scanf("%d", &id);
    clearInputBuffer();
    
    int index = findEmployeeById(id);
    if(index == -1) {
        printf("Employee with ID %d not found!\n", id);
        return;
    }
    
    printf("\n=== UPDATE EMPLOYEE (ID: %d) ===\n", id);
    printf("Current name: %s\n", employees[index].name);
    printf("Enter new name (press enter to keep current): ");
    char newName[MAX_NAME_LENGTH];
    fgets(newName, MAX_NAME_LENGTH, stdin);
    newName[strcspn(newName, "\n")] = 0;
    if(strlen(newName) > 0) {
        strcpy(employees[index].name, newName);
    }
    
    printf("Current department: %s\n", employees[index].department);
    printf("Enter new department (press enter to keep current): ");
    char newDept[MAX_DEPT_LENGTH];
    fgets(newDept, MAX_DEPT_LENGTH, stdin);
    newDept[strcspn(newDept, "\n")] = 0;
    if(strlen(newDept) > 0) {
        strcpy(employees[index].department, newDept);
    }
    
    printf("Current salary: $%.2f\n", employees[index].salary);
    printf("Enter new salary (enter -1 to keep current): ");
    float newSalary;
    scanf("%f", &newSalary);
    clearInputBuffer();
    if(newSalary >= 0) {
        employees[index].salary = newSalary;
    }
    
    printf("Current age: %d\n", employees[index].age);
    printf("Enter new age (enter -1 to keep current): ");
    int newAge;
    scanf("%d", &newAge);
    clearInputBuffer();
    if(newAge >= 18 && newAge <= 65) {
        employees[index].age = newAge;
    }
    
    printf("Employee updated successfully!\n");
}

void deleteEmployee() {
    if(employeeCount == 0) {
        printf("No employees in the database!\n");
        return;
    }
    
    int id;
    printf("Enter employee ID to delete: ");
    scanf("%d", &id);
    clearInputBuffer();
    
    int index = findEmployeeById(id);
    if(index == -1) {
        printf("Employee with ID %d not found!\n", id);
        return;
    }
    
    printf("Are you sure you want to delete employee %s (ID: %d)? (y/n): ", 
           employees[index].name, id);
    char confirm;
    scanf("%c", &confirm);
    clearInputBuffer();
    
    if(confirm == 'y' || confirm == 'Y') {
        for(int i = index; i < employeeCount - 1; i++) {
            employees[i] = employees[i + 1];
        }
        employeeCount--;
        printf("Employee deleted successfully!\n");
    } else {
        printf("Deletion cancelled.\n");
    }
}

void sortEmployees() {
    if(employeeCount == 0) {
        printf("No employees in the database!\n");
        return;
    }
    
    int choice;
    printf("\n=== SORT EMPLOYEES ===\n");
    printf("1. Sort by ID\n");
    printf("2. Sort by Name\n");
    printf("3. Sort by Salary (Descending)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    clearInputBuffer();
    
    for(int i = 0; i < employeeCount - 1; i++) {
        for(int j = 0; j < employeeCount - i - 1; j++) {
            int swap = 0;
            
            switch(choice) {
                case 1:
                    if(employees[j].id > employees[j + 1].id) swap = 1;
                    break;
                case 2:
                    if(strcasecmp(employees[j].name, employees[j + 1].name) > 0) swap = 1;
                    break;
                case 3:
                    if(employees[j].salary < employees[j + 1].salary) swap = 1;
                    break;
                default:
                    printf("Invalid choice!\n");
                    return;
            }
            
            if(swap) {
                Employee temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }
    
    printf("Employees sorted successfully!\n");
    displayAllEmployees();
}

void generateReport() {
    if(employeeCount == 0) {
        printf("No employees in the database!\n");
        return;
    }
    
    printf("\n=== EMPLOYEE REPORT ===\n");
    printf("Total employees: %d\n", employeeCount);
    
    // Calculate statistics
    float totalSalary = 0, avgSalary, maxSalary = 0, minSalary = employees[0].salary;
    int under30 = 0, between30_50 = 0, over50 = 0;
    
    for(int i = 0; i < employeeCount; i++) {
        totalSalary += employees[i].salary;
        if(employees[i].salary > maxSalary) maxSalary = employees[i].salary;
        if(employees[i].salary < minSalary) minSalary = employees[i].salary;
        
        if(employees[i].age < 30) under30++;
        else if(employees[i].age <= 50) between30_50++;
        else over50++;
    }
    avgSalary = totalSalary / employeeCount;
    
    printf("Salary Statistics:\n");
    printf("  Average salary: $%.2f\n", avgSalary);
    printf("  Highest salary: $%.2f\n", maxSalary);
    printf("  Lowest salary: $%.2f\n", minSalary);
    printf("  Total payroll: $%.2f\n", totalSalary);
    
    printf("\nAge Distribution:\n");
    printf("  Under 30: %d employees\n", under30);
    printf("  30-50: %d employees\n", between30_50);
    printf("  Over 50: %d employees\n", over50);
}

int findEmployeeById(int id) {
    for(int i = 0; i < employeeCount; i++) {
        if(employees[i].id == id) {
            return i;
        }
    }
    return -1;
}

int isEmailValid(const char *email) {
    int atCount = 0, dotCount = 0;
    for(int i = 0; email[i] != '\0'; i++) {
        if(email[i] == '@') atCount++;
        if(email[i] == '.') dotCount++;
    }
    return (atCount == 1 && dotCount >= 1);
}

int isPhoneValid(const char *phone) {
    if(strlen(phone) != 10) return 0;
    for(int i = 0; phone[i] != '\0'; i++) {
        if(!isdigit(phone[i])) return 0;
    }
    return 1;
}

void clearInputBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
