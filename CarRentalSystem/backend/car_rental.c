#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------------- STRUCTURES ---------------- */

struct Car {
    int id;
    char name[30];
    float price;
    int available;   // 1 = available, 0 = booked
};

struct Booking {
    char customer[30];
    char phone[15];
    int carId;
    int days;
    float total;
};

/* ---------------- ADMIN FUNCTIONS ---------------- */

/* ADD CAR */
void addCar() {
    FILE *fp = fopen("cars.dat", "ab");
    struct Car c;

    printf("\nEnter Car ID: ");
    scanf("%d", &c.id);

    printf("Enter Car Name: ");
    scanf("%s", c.name);

    printf("Enter Price per Day: ");
    scanf("%f", &c.price);

    c.available = 1;

    fwrite(&c, sizeof(c), 1, fp);
    fclose(fp);

    printf("✅ Car added successfully\n");
}

/* VIEW CARS */
void viewCars() {
    FILE *fp = fopen("cars.dat", "rb");
    struct Car c;

    if (!fp) {
        printf("❌ No car data found\n");
        return;
    }

    printf("\nID\tName\t\tPrice\tStatus\n");
    printf("----------------------------------------\n");

    while (fread(&c, sizeof(c), 1, fp)) {
        printf("%d\t%s\t\t%.2f\t%s\n",
               c.id,
               c.name,
               c.price,
               c.available ? "Available" : "Booked");
    }

    fclose(fp);
}

/* DELETE CAR */
void deleteCar() {
    FILE *fp = fopen("cars.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    struct Car c;
    int delId, found = 0;

    printf("\nEnter Car ID to delete: ");
    scanf("%d", &delId);

    while (fread(&c, sizeof(c), 1, fp)) {
        if (c.id == delId) {
            found = 1;
            continue; // skip this car
        }
        fwrite(&c, sizeof(c), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("cars.dat");
    rename("temp.dat", "cars.dat");

    if (found)
        printf("✅ Car deleted successfully\n");
    else
        printf("❌ Car ID not found\n");
}

/* ---------------- USER FUNCTIONS ---------------- */

/* BOOK CAR */
void bookCar() {
    FILE *fc = fopen("cars.dat", "rb+");
    FILE *fb = fopen("bookings.dat", "ab");

    struct Car c;
    struct Booking b;
    int found = 0;

    printf("\nCustomer Name: ");
    scanf("%s", b.customer);

    printf("Phone Number: ");
    scanf("%s", b.phone);

    printf("Car ID: ");
    scanf("%d", &b.carId);

    printf("Number of Days: ");
    scanf("%d", &b.days);

    while (fread(&c, sizeof(c), 1, fc)) {
        if (c.id == b.carId && c.available == 1) {
            found = 1;
            c.available = 0;

            b.total = b.days * c.price;

            fseek(fc, -sizeof(c), SEEK_CUR);
            fwrite(&c, sizeof(c), 1, fc);

            fwrite(&b, sizeof(b), 1, fb);

            printf("\n✅ Booking Successful");
            printf("\n💰 Total Bill: ₹%.2f\n", b.total);
            break;
        }
    }

    if (!found) {
        printf("\n❌ Car not available or invalid ID\n");
    }

    fclose(fc);
    fclose(fb);
}

/* VIEW BOOKINGS */
void viewBookings() {
    FILE *fp = fopen("bookings.dat", "rb");
    struct Booking b;

    if (!fp) {
        printf("❌ No booking history found\n");
        return;
    }

    printf("\nCustomer\tPhone\tCarID\tDays\tTotal\n");
    printf("------------------------------------------------\n");

    while (fread(&b, sizeof(b), 1, fp)) {
        printf("%s\t\t%s\t%d\t%d\t%.2f\n",
               b.customer,
               b.phone,
               b.carId,
               b.days,
               b.total);
    }

    fclose(fp);
}

/* ---------------- MAIN MENU ---------------- */

int main() {
    int choice;

    do {
        printf("\n\n===== CAR RENTAL MANAGEMENT SYSTEM =====");
        printf("\n1. Add Car (Admin)");
        printf("\n2. View Cars");
        printf("\n3. Delete Car (Admin)");
        printf("\n4. Book Car");
        printf("\n5. View Booking History");
        printf("\n6. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addCar(); break;
            case 2: viewCars(); break;
            case 3: deleteCar(); break;
            case 4: bookCar(); break;
            case 5: viewBookings(); break;
            case 6: printf("👋 Exiting system...\n"); break;
            default: printf("❌ Invalid choice\n");
        }
    } while (choice != 6);

    return 0;
}
