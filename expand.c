//* gcc -o output expand.c && output

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void expand(char s1[], char s2[]);

int main(int argc, char const* argv[]) {
    char s2[100];

    // tests:
    expand("a-z", s2);
    printf("%s - %s\n", s2, strcmp(s2, "abcdefghijklmnopqrstuvwxyz") == 0 ? "OK" : "FAIL");
    expand("A-Z", s2);
    printf("%s - %s\n", s2, strcmp(s2, "ABCDEFGHIJKLMNOPQRSTUVWXYZ") == 0 ? "OK" : "FAIL");
    expand("0-9", s2);
    printf("%s - %s\n", s2, strcmp(s2, "0123456789") == 0 ? "OK" : "FAIL");
    expand("9-0", s2);
    printf("%s - %s\n", s2, strcmp(s2, "9876543210") == 0 ? "OK" : "FAIL");
    expand("d-a", s2);
    printf("%s - %s\n", s2, strcmp(s2, "dcba") == 0 ? "OK" : "FAIL");
    expand("G-B", s2);
    printf("%s - %s\n", s2, strcmp(s2, "GFEDCB") == 0 ? "OK" : "FAIL");
    expand("-a-z", s2);
    printf("%s - %s\n", s2, strcmp(s2, "abcdefghijklmnopqrstuvwxyz") == 0 ? "OK" : "FAIL");
    expand("a-z-", s2);
    printf("%s - %s\n", s2, strcmp(s2, "abcdefghijklmnopqrstuvwxyz") == 0 ? "OK" : "FAIL");
    expand("a", s2);
    printf("%s - %s\n", s2, strcmp(s2, "a") == 0 ? "OK" : "FAIL");
    expand("a-z0-9", s2);
    printf("%s - %s\n", s2, strcmp(s2, "abcdefghijklmnopqrstuvwxyz") == 0 ? "OK" : "FAIL");
    expand("A-z", s2);
    printf("%s - %s\n", s2, strcmp(s2, "ABCDEFGHIJKLMNOPQRSTUVWXYZ") == 0 ? "OK" : "FAIL");
    expand("a-Z", s2);
    printf("%s - %s\n", s2, strcmp(s2, "abcdefghijklmnopqrstuvwxyz") == 0 ? "OK" : "FAIL");

    return 0;
}

void expand(char s1[], char s2[])
{
    int len = strlen(s1);
    int nextplace = 0;
    int last;
    int item;

    // a-z and 0-9 case
    if (isalpha(s1[0]) && isalpha(s1[len - 1]) || isdigit(s1[0]) && isdigit(s1[len - 1])) {

        s2[nextplace++] = s1[0];
        item = s1[0];
        last = s1[len - 1];
    }
    // -a-z case:
    else if (!(isalpha(s1[0]) && isalpha(s1[len - 1]))) {
        int i = 0;
        item = s1[i];
        while (!isalpha(item)) {
            i++;
            item = s1[i];
        }

        last = s1[len - 1];
        while (!isalpha(last)) {
            i++;
            last = s1[i];
        }

        s2[nextplace++] = item;
    }

    // expand depending on item's letter case:
    if (isupper(item) && islower(last)) {
        last = toupper(last);

    } else if (islower(item) && isupper(last)) {
        last = tolower(last);
    }

    while (item != last) {
        // item will be the last item store in s2:
        s2[nextplace++] = (item < last) ? ++item : --item;
    }

    s2[nextplace] = '\0';
}
