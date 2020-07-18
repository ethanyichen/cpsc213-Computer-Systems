#include <unistd.h>
#include <string.h>
#include <stdlib.h>

struct str {
	int length;
	char* string;
};

char _str1[] = "Welcome! Please enter a name:\n";
char _str2[] = "Good luck, ";
char _str3[] = "The secret phrase is \"squeamish ossifrage\"";

struct str str1 = {30, _str1};
struct str str2 = {11, _str2};
struct str str3 = {43, _str3};


void print(struct str *s) {
	write(1, s->string, s->length);
}

void proof() {
    print(&str3);
}

int main() {
	char buf[128];
	print(&str1);
    int i = read(0, buf, 256);
	print(&str2);
	write(1, buf, i);
}