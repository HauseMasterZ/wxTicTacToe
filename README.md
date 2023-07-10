# Tic-Tac-Toe Game

This is a simple implementation of the Tic-Tac-Toe game using the wxWidgets library. The game features a graphical user interface (GUI) where players can take turns and try to win by getting three of their symbols in a row.

<p align="center">
  <img src="https://github.com/HauseMasterZ/face-encryptor/assets/113833707/4f13e09d-1c77-481b-b124-a50d00d3828c" alt="Home Page"/>
</p>




## Requirements

To run this application, you need to have the following:

- C++ compiler
- wxWidgets library

## Getting Started

1. Clone the repository:

   ```shell
   git clone https://github.com/your-username/tic-tac-toe.git
   ```
2. Build the project using your preferred C++ compiler. Make sure to link against the wxWidgets library.
   ```shell
   g++ MainFrame.cpp -o TicTacToe `wx-config --cxxflags --libs`
   ```
3. Run the compiled executable:
   ```shell
   ./TicTacToe
   ```
## How to Play
1. Launch the game and you will see the game board displayed on the screen.

2. The game starts with "Player X" turn. Each player takes turns by clicking on an empty cell in the grid.

3. The objective is to get three of your symbols (either "X" or "O") in a row, either horizontally, vertically, or diagonally.

4. The game ends when a player wins or there are no more empty cells on the grid, resulting in a draw.

5. To reset the game and start again, click the "Reset" button.

## Contributing
Contributions to the Face Encryptor project are welcome! If you have any bug reports, suggestions, or improvements, please feel free to submit a pull request or open an issue on the GitHub repository.

## License
This project is licensed under the [MIT License](LICENSE).

## Acknowledgements
* The code is based on the wxWidgets Tic-Tac-Toe sample.
* Thanks to the wxWidgets community for their support and resources.
