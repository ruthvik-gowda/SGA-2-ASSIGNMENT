#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

typedef struct {
    int id;
    char name[20];
} Employee;

int main() {
    Employee emp;

    int fd = open("employees.dat", O_CREAT | O_RDWR, 0644);

    if (fd < 0) {
        perror("open");
        return 1;
    }

    Employee employees[] = {
        {101, "Alice"},
        {102, "Bob"},
        {103, "Charlie"}
    };

    write(fd, employees, sizeof(employees));

    emp.id = 102;
    strcpy(emp.name, "Robert");

    lseek(fd, sizeof(Employee), SEEK_SET);
    write(fd, &emp, sizeof(Employee));

    lseek(fd, 2 * sizeof(Employee), SEEK_SET);
    read(fd, &emp, sizeof(Employee));

    printf("Retrieved Record:\n");
    printf("ID: %d\n", emp.id);
    printf("Name: %s\n", emp.name);

    close(fd);

    return 0;
}
