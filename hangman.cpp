#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cctype>

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

using namespace std;

// List of words to guess
const vector<string> WORD_LIST = {
    "apple", "banana", "orange", "grape", "cherry", "peach", "lemon", "melon"
};

void print_hangman(int tries) {
    static const vector<string> hangman_stages = {
        "  +---+\n      |\n      |\n      |\n     ===",
        "  +---+\n  O   |\n      |\n      |\n     ===",
        "  +---+\n  O   |\n  |   |\n      |\n     ===",
        "  +---+\n  O   |\n /|   |\n      |\n     ===",
        "  +---+\n  O   |\n /|\\  |\n      |\n     ===",
        "  +---+\n  O   |\n /|\\  |\n /    |\n     ===",
        "  +---+\n  O   |\n /|\\  |\n / \\  |\n     ==="
    };
    cout << hangman_stages[tries] << endl;
}

string get_word() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int idx = rand() % WORD_LIST.size();
    return WORD_LIST[idx];
}

void display_word(const string& word, const vector<bool>& guessed) {
    for (size_t i = 0; i < word.size(); ++i) {
        if (guessed[i])
            cout << word[i] << " ";
        else
            cout << "_ ";
    }
    cout << endl;
}

bool play_again() {
    char answer;
    cout << "Do you want to play again? (y/n): ";
    cin >> answer;
    return (answer == 'y' || answer == 'Y');
}

void clear_screen() {
    system(CLEAR_SCREEN);
}

int main() {
    cout << "=== Welcome to Hangman! ===" << endl;
    do {
        clear_screen(); // Blank the screen before each new round

        string word = get_word();
        vector<bool> guessed(word.size(), false);
        vector<char> wrong_guesses;
        int tries = 0, max_tries = 6;
        bool won = false;

        while (tries <= max_tries) {
            print_hangman(tries);
            cout << "\nWord: ";
            display_word(word, guessed);
            cout << "Wrong guesses: ";
            for (char c : wrong_guesses) cout << c << " ";
            cout << "\nGuess a letter: ";
            char guess;
            cin >> guess;
            guess = tolower(guess);

            if (!isalpha(guess)) {
                cout << "Please enter a valid letter.\n";
                continue;
            }

            bool found = false;
            for (size_t i = 0; i < word.size(); ++i) {
                if (tolower(word[i]) == guess && !guessed[i]) {
                    guessed[i] = true;
                    found = true;
                }
            }
            if (!found) {
                if (find(wrong_guesses.begin(), wrong_guesses.end(), guess) == wrong_guesses.end()) {
                    wrong_guesses.push_back(guess);
                    tries++;
                } else {
                    cout << "You already guessed that letter!\n";
                }
            }

            if (all_of(guessed.begin(), guessed.end(), [](bool v){ return v; })) {
                won = true;
                break;
            }
        }

        if (won) {
            clear_screen(); // Clear the screen before showing the congrats message
            cout << "🎉 Congratulations! You guessed the word: " << word << " 🎉" << endl;
        } else {
            print_hangman(tries);
            cout << "\nGame over! The word was: " << word << endl;
        }
    } while (play_again());

    cout << "Thanks for playing Hangman!\n";
    return 0;
}