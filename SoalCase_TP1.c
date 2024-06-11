#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EMPLOYEES 5
#define MAX_ID_LENGTH 5
#define MAX_NAME_LENGTH 30
#define MAX_POSITION_LENGTH 50

// Struct node karyawan
struct Employee {
    int id;
    char name[MAX_NAME_LENGTH + 1];
    char birthplace[MAX_NAME_LENGTH + 1];
    char birthdate[MAX_NAME_LENGTH + 1];
    char position[MAX_POSITION_LENGTH + 1];
    struct Employee* next;
};

// Function untuk membuat node karyawan baru
struct Employee* createEmployee(int id, char* name, char* birthplace, char* birthdate, char* position) {
    struct Employee* new_employee = (struct Employee*)malloc(sizeof(struct Employee));
    new_employee->id = id;
    strncpy(new_employee->name, name, MAX_NAME_LENGTH);
    new_employee->name[MAX_NAME_LENGTH] = '\0';
    strncpy(new_employee->birthplace, birthplace, MAX_NAME_LENGTH);
    new_employee->birthplace[MAX_NAME_LENGTH] = '\0';
    strncpy(new_employee->birthdate, birthdate, MAX_NAME_LENGTH);
    new_employee->birthdate[MAX_NAME_LENGTH] = '\0';
    strncpy(new_employee->position, position, MAX_POSITION_LENGTH);
    new_employee->position[MAX_POSITION_LENGTH] = '\0';
    new_employee->next = NULL;
    return new_employee;
}

// Function untuk menambahkan node karyawan ke list
void pushEmployee(struct Employee** head_ref, int id, char* name, char* birthplace, char* birthdate, char* position) {
    struct Employee* new_employee = createEmployee(id, name, birthplace, birthdate, position);
    struct Employee* current;

    if (*head_ref == NULL || (*head_ref)->id >= new_employee->id) {
        new_employee->next = *head_ref;
        *head_ref = new_employee;
    } else {
        current = *head_ref;
        while (current->next != NULL && current->next->id < new_employee->id) {
            current = current->next;
        }
        new_employee->next = current->next;
        current->next = new_employee;
    }
}

// Function untuk menampilkan semua karyawan
void displayEmployees(struct Employee* node) {
    if (node == NULL) {
        printf("Database karyawan kosong.\n");
    } else {
        while (node != NULL) {
            printf("Employee ID: %d\n", node->id);
            printf("Nama Lengkap: %s\n", node->name);
            printf("Tempat Lahir: %s\n", node->birthplace);
            printf("Tanggal Lahir: %s\n", node->birthdate);
            printf("Jabatan: %s\n\n", node->position);
            node = node->next;
        }
    }
}

// Function untuk menghapus karyawan berdasarkan Employee ID
int deleteEmployee(struct Employee** head_ref, int id) {
    struct Employee* temp = *head_ref;
    struct Employee* prev = NULL;

    if (temp != NULL && temp->id == id) {
        *head_ref = temp->next;
        free(temp);
        printf("Karyawan dengan Employee ID %d telah dihapus.\n", id);
        return 1;
    }

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Karyawan dengan Employee ID %d tidak ditemukan.\n", id);
        return 0;
    }

    prev->next = temp->next;
    free(temp);
    printf("Karyawan dengan Employee ID %d telah dihapus.\n", id);
    return 1;
}

// Function untuk menghapus semua karyawan
void deleteAllEmployees(struct Employee** head_ref) {
    struct Employee* current = *head_ref;
    struct Employee* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head_ref = NULL;
    printf("Semua data karyawan telah dihapus.\n");
}

// Function untuk membaca string input dengan validasi panjang
void getInput(char* buffer, int maxLength) {
    fgets(buffer, maxLength, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}

// Function untuk eror check input int
int getIntegerInput() {
    char buffer[100];
    char *endptr;
    long value;

    while (1) {
        getInput(buffer, sizeof(buffer));
        value = strtol(buffer, &endptr, 10);

        if (endptr == buffer || *endptr != '\0' || value > 99999 || value <= 0) {
            printf("Input tidak valid. Masukkan angka yang valid: ");
        } else {
            return (int)value;
        }
    }
}


int main() {
    struct Employee* head = NULL;
    int choice, id, count = 0;
    char name[MAX_NAME_LENGTH + 1], birthplace[MAX_NAME_LENGTH + 1], birthdate[MAX_NAME_LENGTH + 1], position[MAX_POSITION_LENGTH + 1];

    do {
        printf("\nMenu:\n");
        printf("1. Push data karyawan\n");
        printf("2. Menampilkan semua daftar karyawan\n");
        printf("3. Hapus data karyawan berdasarkan Employee ID\n");
        printf("4. Hapus semua data karyawan\n");
        printf("5. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);
        getchar();  // To consume the newline character left by scanf

        switch (choice) {
            case 1:
                if (count >= MAX_EMPLOYEES) {
                    printf("Jumlah maksimum data karyawan tercapai.\n");
                    break;
                }

                printf("Masukkan Employee ID (maksimal 5 angka): ");
                id = getIntegerInput();

                printf("Masukkan Nama Lengkap (maksimal 30 karakter): ");
                getInput(name, sizeof(name));
                if (strlen(name) > MAX_NAME_LENGTH) {
                    printf("Nama Lengkap tidak valid.\n");
                    break;
                }

                printf("Masukkan Tempat Lahir (maksimal 30 karakter): ");
                getInput(birthplace, sizeof(birthplace));
                if (strlen(birthplace) > MAX_NAME_LENGTH) {
                    printf("Tempat Lahir tidak valid.\n");
                    break;
                }

                printf("Masukkan Tanggal Lahir (format: DD-MM-YYYY): ");
                getInput(birthdate, sizeof(birthdate));
                if (strlen(birthdate) > MAX_NAME_LENGTH) {
                    printf("Tanggal Lahir tidak valid.\n");
                    break;
                }

                printf("Masukkan Jabatan (maksimal 50 karakter): ");
                getInput(position, sizeof(position));
                if (strlen(position) > MAX_POSITION_LENGTH) {
                    printf("Jabatan tidak valid.\n");
                    break;
                }

                pushEmployee(&head, id, name, birthplace, birthdate, position);
                count++;
                break;
            case 2:
                displayEmployees(head);
                break;
            case 3:
                printf("Masukkan Employee ID yang akan dihapus: ");
                id = getIntegerInput();
                if (deleteEmployee(&head, id)) {
                    count--;
                }
                break;
            case 4:
                deleteAllEmployees(&head);
                count = 0;
                break;
            case 5:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (choice != 5);

    return 0;
}
