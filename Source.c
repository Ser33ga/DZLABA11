#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

#define COUNT 3
#define LIMIT_HOURS 3.0

struct Time {
	int hours;
	int minutes;
};

struct BikeRental {
	int id;
	char type[30];
	double rate;
	struct Time start;
	struct Time end;
};

double calculate_duration(struct Time start, struct Time end);
void print_rental(struct BikeRental r, double duration, double cost);
void process_rentals(struct BikeRental rentals[], int count);

void main() {
	struct BikeRental rentals[COUNT];
	int i;

	setlocale(LC_ALL, "RUS");

	printf("Программа учета проката велосипедов\n\n");

	for (i = 0; i < COUNT; i++) {
		printf("Ввод данных для записи %d:\n", i + 1);
		printf("Введите номер велосипеда: ");
		scanf("%d", &rentals[i].id);
		printf("Введите тип велосипеда: ");
		scanf("%29s", rentals[i].type);
		printf("Введите стоимость аренды за час (руб): ");
		scanf("%lf", &rentals[i].rate);
		printf("Введите время начала аренды (часы и минуты): ");
		scanf("%d %d", &rentals[i].start.hours, &rentals[i].start.minutes);
		printf("Введите время окончания аренды (часы и минуты): ");
		scanf("%d %d", &rentals[i].end.hours, &rentals[i].end.minutes);
		printf("\n");
	}

	process_rentals(rentals, COUNT);
}

double calculate_duration(struct Time start, struct Time end) {
	int start_min = start.hours * 60 + start.minutes;
	int end_min = end.hours * 60 + end.minutes;
	int diff = end_min - start_min;

	if (diff < 0) {
		diff += 24 * 60;
	}

	return (double)diff / 60.0;
}

void print_rental(struct BikeRental r, double duration, double cost) {
	printf("  Номер велосипеда: %d\n", r.id);
	printf("  Тип: %s\n", r.type);
	printf("  Тариф: %.2lf руб/ч\n", r.rate);
	printf("  Время аренды: %02d:%02d - %02d:%02d\n", r.start.hours, r.start.minutes, r.end.hours, r.end.minutes);
	printf("  Продолжительность: %.2lf ч\n", duration);
	printf("  Стоимость: %.2lf руб\n", cost);
}

void process_rentals(struct BikeRental rentals[], int count) {
	int i;
	int found = 0;
	double duration, cost;

	printf("--- Все записи проката ---\n");
	for (i = 0; i < count; i++) {
		duration = calculate_duration(rentals[i].start, rentals[i].end);
		cost = duration * rentals[i].rate;
		printf("\nЗапись %d:\n", i + 1);
		print_rental(rentals[i], duration, cost);
	}

	printf("\n--- Записи с продолжительностью аренды более %.0lf часов ---\n", LIMIT_HOURS);
	for (i = 0; i < count; i++) {
		duration = calculate_duration(rentals[i].start, rentals[i].end);
		if (duration > LIMIT_HOURS) {
			cost = duration * rentals[i].rate;
			printf("\nЗапись %d:\n", i + 1);
			print_rental(rentals[i], duration, cost);
			found++;
		}
	}

	if (found == 0) {
		printf("Записей с продолжительностью более %.0lf часов не найдено.\n", LIMIT_HOURS);
	}
}
