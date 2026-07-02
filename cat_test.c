#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <ctype.h>

#define __NR_get_cat_color 473
#define __NR_set_cat_color 474

// ANSI colors (high intensity)
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define WHITE   "\033[97m"
#define ORANGE  "\033[33m"
#define GRAY    "\033[90m"

const char* get_color_name(int color)
{
    switch (color)
    {
        case 0: return "Black";
        case 1: return "White";
        case 2: return "Orange";
        case 3: return "Gray";
        default: return "Unknown";
    }
}

const char* get_color_code(int color)
{
    switch (color)
    {
        case 0: return BLACK;
        case 1: return WHITE;
        case 2: return ORANGE;
        case 3: return GRAY;
        default: return RESET;
    }
}

void print_cat(int color)
{
    const char* c = get_color_code(color);

    printf("%s", c);

    printf("         ##                                                                    \n");
    printf("       .##                                                                     \n");
    printf("       ##                                                     ##               \n");
    printf("      ###                                                   ####               \n");
    printf("      ###                                                 ########             \n");
    printf("       ####                                              ###########           \n");
    printf("         #######                                       #############           \n");
    printf("           #####################################  ###################          \n");
    printf("                   #############################################               \n");
    printf("                     #########################################                 \n");
    printf("                     ########################################                  \n");
    printf("                     ########################################                  \n");
    printf("                     #######################################                   \n");
    printf("                    ########################################                   \n");
    printf("                    ########################################                   \n");
    printf("                  -#################         ###############                   \n");
    printf("                 ########## #######          #####    ######.                  \n");
    printf("                ########    ######           ####       ######                 \n");
    printf("               ####.        #####            ###          #####                \n");
    printf("               ###          ####            ####            ####               \n");
    printf("               ##             ###           ###               ####             \n");
    printf("               ###              ###-        ###                 ####           \n");
    printf("               ###                ###        ###                               \n");

    printf("%s", RESET);
}

int main()
{
    int color;
    int choice;
    char answer;

    color = syscall(__NR_get_cat_color);

    printf("\nCurrent cat color: %s\n\n", get_color_name(color));
    print_cat(color);

    printf("\nChange the cat color? (Y/N): ");
    scanf(" %c", &answer);

    if (toupper(answer) == 'Y')
    {
        printf("\n0 - Black\n");
        printf("1 - White\n");
        printf("2 - Orange\n");
        printf("3 - Gray\n");

        printf("\nChoose: ");
        scanf("%d", &choice);

        syscall(__NR_set_cat_color, choice);

        color = syscall(__NR_get_cat_color);

        printf("\nNew cat color: %s\n\n", get_color_name(color));
        print_cat(color);
    }

    return 0;
}
