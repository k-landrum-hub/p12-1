/*
* korbin landrum 
* p12-1
* leaving on a jet plane
*/

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Symbolic constants
const int COLUMNS = 4;      // Seats A, B, C, D
const int ROWS = 13;        // Rows 1 through 13
const int TOTAL_SEATS = 50; // 12 * 4 + 2 = 50 seats
const int ERROR = -1;
const char OCCUPIED = 'X';
const char EMPTY_SLOT = ' ';

// Function prototypes
int findRowIndex(int thisRow);
int findSeatIndex(char thisSeat);
void displaySeatColumn(char seats[][ROWS], int column);
void displaySeatingChart(char seats[][ROWS]);

int main() {
    // Initialize the 2D seating chart: seats[column][row]
    char seats[COLUMNS][ROWS];
    char seatLetters[COLUMNS] = { 'A', 'B', 'C', 'D' };

    for (int col = 0; col < COLUMNS; col++) {
        for (int row = 0; row < ROWS; row++) {
            // Row 13 (index 12) only has seats A (0) and B (1)
            if (row == ROWS - 1 && (col == 2 || col == 3)) {
                seats[col][row] = EMPTY_SLOT;
            }
            else {
                seats[col][row] = seatLetters[col];
            }
        }
    }

    int reservedCount = 0;
    string input;

    // Display initial seating chart
    displaySeatingChart(seats);

    // Loop until all seats are filled or user quits
    while (reservedCount < TOTAL_SEATS) {
        cout << "Enter a seat or Q to quit: ";
        cin >> input;

        // Check for quit condition
        if (input == "Q" || input == "q") {
            break;
        }

        int rowIdx = ERROR;
        int colIdx = ERROR;

        // Ensure input has at least 2 characters (e.g., "1A") before parsing
        if (input.length() >= 2) {
            char seatChar = toupper(input.back());
            string rowPart = input.substr(0, input.length() - 1);

            // Check that all preceding characters are digits
            bool isDigits = true;
            for (char c : rowPart) {
                if (!isdigit(static_cast<unsigned char>(c))) {
                    isDigits = false;
                    break;
                }
            }

            if (isDigits) {
                int rowNum = stoi(rowPart);
                rowIdx = findRowIndex(rowNum);
                colIdx = findSeatIndex(seatChar);
            }
        }

        // Validate seat existence (including checking 13C and 13D)
        if (rowIdx == ERROR || colIdx == ERROR || seats[colIdx][rowIdx] == EMPTY_SLOT) {
            cout << "Sorry, no such seat exists on the CRJ 200." << endl;
        }
        // Check if seat is already reserved
        else if (seats[colIdx][rowIdx] == OCCUPIED) {
            cout << "Sorry, that seat is already occupied." << endl;
        }
        // Reserve the seat
        else {
            seats[colIdx][rowIdx] = OCCUPIED;
            reservedCount++;
        }

        // Re-display the chart after each attempt
        displaySeatingChart(seats);
    }
}

// findRowIndex: given user input, returns appropriate row index into arrays.
// @param thisRow - integer indicating row selected by the user
// @return appropriate index into 2-D array if the specified row is valid, ERROR otherwise
int findRowIndex(int thisRow) {
    if (thisRow >= 1 && thisRow <= ROWS) {
        return thisRow - 1;
    }
    return ERROR;
}

// findSeatIndex: given user input, returns appropriate column index into seating chart array.
// @param thisSeat - character indicating selected seat within row
// @return appropriate index into 2-D array if the specified seat is valid, ERROR otherwise
int findSeatIndex(char thisSeat) {
    switch (toupper(thisSeat)) {
    case 'A': return 0;
    case 'B': return 1;
    case 'C': return 2;
    case 'D': return 3;
    default:  return ERROR;
    }
}


void displaySeatColumn(char seats[][ROWS], int column) {
    for (int row = 0; row < ROWS; row++) {
        // Avoid trailing space on rows C and D where row 13 does not exist
        if (row == ROWS - 1 && seats[column][row] == EMPTY_SLOT) {
            break;
        }
        if (row > 0) {
            cout << " ";
        }
        cout << seats[column][row];
    }
    cout << endl;
}

// print the complete seating chart with aisle row numbers
void displaySeatingChart(char seats[][ROWS]) {
    displaySeatColumn(seats, 3); // Seat D
    displaySeatColumn(seats, 2); // Seat C
    cout << endl;
    cout << "                  1 1 1 1" << endl;
    cout << "1 2 3 4 5 6 7 8 9 0 1 2 3" << endl;
    cout << endl;
    displaySeatColumn(seats, 1); // Seat B
    displaySeatColumn(seats, 0); // Seat A
}
