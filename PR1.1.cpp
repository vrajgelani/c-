#include <stdio.h>

void secondsToHMS(int totalSeconds) 
{
    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600) / 60;
    int seconds = totalSeconds % 60;

    printf("HH:MM:SS => %d:%02d:%02d\n", hours, minutes, seconds);
}

int hmsToSeconds(int hours, int minutes, int seconds) 
{
    return (hours * 3600) + (minutes * 60) + seconds;
}

int main() 
{
    int choice;
    printf("1. Convert seconds to HH:MM:SS\n");
    printf("2. Convert HH:MM:SS to seconds\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) 
	{
        int totalSeconds;
        printf("Enter total seconds: ");
        scanf("%d", &totalSeconds);
        secondsToHMS(totalSeconds);
    } 
	else if (choice == 2) 
	{
        int hours, minutes, seconds;
        printf("Enter hours: ");
        scanf("%d", &hours);
        printf("Enter minutes: ");
        scanf("%d", &minutes);
        printf("Enter seconds: ");
        scanf("%d", &seconds);
        int total = hmsToSeconds(hours, minutes, seconds);
        printf("Total seconds: %d\n", total);
    } 
	else
	{
        printf("Invalid choice.\n");
    }

}
/*
Input:
Enter hours: 4
Enter minutes: 34
Enter seconds: 30
Output:
Total seconds: 16470
*/