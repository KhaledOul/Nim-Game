//Mohamed Ali Al-Difai and Khaled Oulhaci                

#include <iostream>
#include <ctime>

using namespace std;

const int NUM_HEAPS = 5;
const int MAX_HEAPS = 100;


void printBoard(int heaps[]) {
    cout << "Current Board: ";
    for (int i = 0; i < NUM_HEAPS; ++i) {
        cout << "Heap " << i + 1 << ": " << heaps[i] << " ";
    }
    cout << endl;
}

bool isValidMove(int heap, int tokens, int heaps[]) {
    return (heap >= 0 && heap < NUM_HEAPS && heaps[heap] >= tokens && (tokens == 1 || (tokens == 2 && heaps[heap] > 1)));
}



bool isGameFinished(int heaps[]) {
    for (int i = 0; i < NUM_HEAPS; ++i) {
        if (heaps[i] > 0) {
            return false;
        }
    }
    return true;
}

int getPlayerMove(int player, int heaps[], const string& playerName) {
    int heap, tokens;
    do {
        cout << playerName << ", enter the heap number (1-" << NUM_HEAPS << ") and number of tokens to remove (1 or 2), separated by a space: ";
        cin >> heap >> tokens;
    } while (!isValidMove(heap - 1, tokens, heaps));
    return tokens;
}

void playGame(int player, int heaps[], const std::string& player1, const std::string& player2) {
    int tokens, heap;

    do {
        cout << ((player == 1) ? player1 : player2) << ", enter the heap number (1-" << NUM_HEAPS << ") and number of tokens to remove (1 or 2), separated by a space: ";
        cin >> heap >> tokens;
    } while (!isValidMove(heap - 1, tokens, heaps));

    heaps[heap - 1] -= tokens;
    std::cout << "Player " << player << " (" << ((player == 1) ? player1 : player2) << ") removed " << tokens << " tokens from Heap " << heap << "." << std::endl;
    printBoard(heaps);

    if (!isGameFinished(heaps)) {
        playGame(3 - player, heaps, player1, player2);
    }
    else {
        std::cout << "Player " << player << " (" << ((player == 1) ? player1 : player2) << ") wins!" << std::endl;
    }
}






// Function displaying the current state of the heaps
void displayHeaps(int heaps[], int numHeaps) {
    cout << "Current state of heaps : ";
    for (int i = 0; i < numHeaps; ++i) {
        cout << heaps[i] << " ";
    }
    cout << endl;
}

// Function calculating the binary weight of a number for (pc vs user)
int binaryWeight(int num) {
    int weight = 0;
    while (num > 0) {
        weight += num % 2;
        num /= 2;
    }
    return weight;
}

// Validating heap index input funtcion
int getValidHeapIndex(int numHeaps) {
    int heapIndex;
    do {
        cout << "Enter heap index you want to remove from (0 to " << numHeaps - 1 << "): ";
        cin >> heapIndex;
    } while (heapIndex < 0 || heapIndex >= numHeaps);
    return heapIndex;
}

void makeMove(int heaps[], int numHeaps, bool isPlayerTurn) {
    displayHeaps(heaps, numHeaps);

    int heapIndex = 0;
    int tokens = 0;

    if (isPlayerTurn) {
        do {
            heapIndex = getValidHeapIndex(numHeaps);
        } while (heaps[heapIndex] <= 0);  // Ensuring the heap is not empty

        do {
            cout << "Enter number of tokens (1 or 2): ";
            cin >> tokens;
        } while (tokens < 1 || tokens > 2 || heaps[heapIndex] < tokens);
    }
    else {
        // Algorithm for computer's move
        do {
            heapIndex = rand() % numHeaps;
        } while (heaps[heapIndex] <= 0);

        tokens = (heaps[heapIndex] == 1) ? 1 : 2;

        cout << "Computer's turn - Heap index: " << heapIndex << ", Tokens: " << tokens << endl;
    }

    // Update the heaps after a move
    heaps[heapIndex] -= tokens;

    // Determines the winner
    bool isEmpty = true;
    for (int i = 0; i < numHeaps; ++i) {
        if (heaps[i] > 0) {
            isEmpty = false;
            break;
        }
    }

    if (isEmpty) {
        if (isPlayerTurn) {
            cout << "Congratulations! You win!" << endl;
        }
        else {
            cout << "Computer wins! Better luck next time." << endl;
        }
    }
    else {
        // Recursive call for the next turn
        makeMove(heaps, numHeaps, !isPlayerTurn);
    }
}









void initializeHeaps(int heaps[], int totalTokens) {
    // Distribute the total tokens among the heaps
    for (int i = 0; i < NUM_HEAPS; ++i) {
        heaps[i] = totalTokens / NUM_HEAPS;
    }

    // Distribute the remaining tokens, if any
    int remainingTokens = totalTokens % NUM_HEAPS;
    for (int i = 0; i < remainingTokens; ++i) {
        heaps[i]++;
    }
}

int main() {
    srand(time(0));

    int choice;
    do {
        cout << "Choose an option:" << endl;
        cout << "1- Two players (user vs. user)" << endl;
        cout << "2- Two players (PC vs. user)" << endl;
        cout << "3- Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string player1, player2;
            int totalTokens;

            cout << "Enter Player 1's name: ";
            cin >> player1;
            cout << "Enter Player 2's name: ";
            cin >> player2;
            cout << "Enter the total number of tokens: ";
            cin >> totalTokens;

            int heaps[NUM_HEAPS];
            initializeHeaps(heaps, totalTokens);

            printBoard(heaps);
            playGame(1, heaps, player1, player2);
            break;
        }
        case 2: {
            int numHeaps;

            cout << "Enter the number of heaps: ";
            cin >> numHeaps;

            // Check for the maximum number of heaps
            if (numHeaps > MAX_HEAPS) {
                cout << "Error: Number of heaps exceeds the maximum limit." << endl;
                return 1;
            }

            // Initialize heaps based on binary number weights
            int heaps[MAX_HEAPS];
            for (int i = 0; i < numHeaps; ++i) {
                heaps[i] = 1 << i;
            }

            // Start the game
            makeMove(heaps, numHeaps, true);
            break;
        }
        case 3:
            cout << "Exiting the game....Goodbye!!!" << endl;
            break;
        default:
            cout << "Invalid choice! Please choose again (1-3)." << endl;
        }
    } while (choice != 3);

    return 0;
}


