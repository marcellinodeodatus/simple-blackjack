#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// Function to generate a random card value
int dealCard(bool isPlayer) {
    int card = rand() % 13;
    
    if (card >= 10)
        return 10;
    else if (card == 0 && isPlayer) {
        int choice;
        printf("You got an Ace! Choose its value (1 or 11): ");
        scanf("%d", &choice);
        while (choice != 1 && choice != 11) {
            printf("Invalid choice. Choose 1 or 11: ");
            scanf("%d", &choice);
        }
        return choice;
    }
    
    return card + 1;
}

// Function to determine if the computer should hit
bool shouldHit(int computerScore, int playerScore) {
    return (computerScore <= playerScore) && (computerScore < 17);
}

// Function to execute a turn
void executeTurn(int* score, bool isPlayer) {
    printf("Current score: %d\n", *score);
    
    bool hit;
    if (isPlayer) {
        char choice;
        printf("Do you want to hit? (y/n): ");
        scanf(" %c", &choice);
        hit = (choice == 'y' || choice == 'Y');
    } else {
        hit = shouldHit(*score, 0);  // Assuming player score as 0 for simplicity
    }
    
    if (hit) {
        int card = dealCard(isPlayer);
        printf("Received card: %d\n", card);
        *score += card;
        executeTurn(score, isPlayer);
    }
}

// Function to determine the winner
int determineWinner(int playerScore, int computerScore) {
    if (playerScore > 21 && computerScore > 21)
        return 0;  // Both players busted, no winner
    else if (playerScore > 21)
        return 2;  // Computer wins
    else if (computerScore > 21)
        return 1;  // Player wins
    
    if (abs(playerScore - 21) < abs(computerScore - 21))
        return 1;  // Player wins
    else if (abs(computerScore - 21) < abs(playerScore - 21))
        return 2;  // Computer wins
    
    return 0;  // It's a draw
}

int main() {
    srand(time(NULL));
    
    int playerScore = 0, computerScore = 0;
    
    // Deal initial cards
    for (int i = 0; i < 2; i++) {
        playerScore += dealCard(true);
        computerScore += dealCard(false);
    }
    
    executeTurn(&playerScore, true);
    executeTurn(&computerScore, false);
    
    int winner = determineWinner(playerScore, computerScore);
    if (winner == 1)
        printf("Player wins!\n");
    else if (winner == 2)
        printf("Computer wins!\n");
    else
        printf("It's a draw!\n");
    
    return 0;
}
