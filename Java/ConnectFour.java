package Java;
import java.util.Scanner;

public class ConnectFour {
    public static void main(String[] args) {
        char[][] gameBoard = createGameBoard(6, 7);
        printGameBoard(gameBoard);

        Scanner scanner = new Scanner(System.in);
        char currentPlayer = 'A';

        while (true) {
            System.out.println("Игрок " + currentPlayer + ", выберите столбец (1-7): ");
            if (scanner.hasNextInt()) {
                int column = scanner.nextInt();
                if (column >= 1 && column <= 7 && isValidMove(gameBoard, column)) {
                    dropDisc(gameBoard, column, currentPlayer);
                    printGameBoard(gameBoard);

                    if (checkWin(gameBoard, currentPlayer)) {
                        System.out.println("Игрок " + currentPlayer + " победил! Поздравляем!");
                        break;
                    }

                    currentPlayer = (currentPlayer == 'A') ? 'B' : 'A';
                } else {
                    System.out.println("Некорректный ход. Попробуйте снова.");
                    scanner.next();
                }
            } else {
                System.out.println("Некорректный ход. Попробуйте снова.");
                scanner.next();
            }
        }

        scanner.close();
    }

    public static char[][] createGameBoard(int rows, int cols) {
        char[][] gameBoard = new char[rows][cols];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                gameBoard[i][j] = ' ';
            }
        }
        return gameBoard;
    }

    public static void printGameBoard(char[][] gameBoard) {
        for (int i = 0; i < gameBoard.length; i++) {
            for (int j = 0; j < gameBoard[i].length; j++) {
                System.out.print(gameBoard[i][j] + " | ");
            }
            System.out.println();
        }
        System.out.println("1 | 2 | 3 | 4 | 5 | 6 | 7 |");
        System.out.println("_________________________");
    }

    public static boolean isValidMove(char[][] gameBoard, int column) {
        return column >= 1 && column <= gameBoard[0].length && gameBoard[0][column - 1] == ' ';
    }

    public static void dropDisc(char[][] gameBoard, int column, char player) {
        for (int i = gameBoard.length - 1; i >= 0; i--) {
            if (gameBoard[i][column - 1] == ' ') {
                gameBoard[i][column - 1] = player;
                break;
            }
        }
    }

    public static boolean checkWin(char[][] gameBoard, char player) {
        for (int row = 0; row < gameBoard.length; row++) {
            for (int col = 0; col <= gameBoard[row].length - 4; col++) {
                if (gameBoard[row][col] == player &&
                    gameBoard[row][col + 1] == player &&
                    gameBoard[row][col + 2] == player &&
                    gameBoard[row][col + 3] == player) {
                    return true;
                }
            }
        }

        for (int row = 0; row <= gameBoard.length - 4; row++) {
            for (int col = 0; col < gameBoard[row].length; col++) {
                if (gameBoard[row][col] == player &&
                    gameBoard[row + 1][col] == player &&
                    gameBoard[row + 2][col] == player &&
                    gameBoard[row + 3][col] == player) {
                    return true;
                }
            }
        }

        for (int row = 3; row < gameBoard.length; row++) {
            for (int col = 0; col <= gameBoard[row].length - 4; col++) {
                if (gameBoard[row][col] == player &&
                    gameBoard[row - 1][col + 1] == player &&
                    gameBoard[row - 2][col + 2] == player &&
                    gameBoard[row - 3][col + 3] == player) {
                    return true;
                }
            }
        }

        for (int row = 0; row <= gameBoard.length - 4; row++) {
            for (int col = 0; col <= gameBoard[row].length - 4; col++) {
                if (gameBoard[row][col] == player &&
                    gameBoard[row + 1][col + 1] == player &&
                    gameBoard[row + 2][col + 2] == player &&
                    gameBoard[row + 3][col + 3] == player) {
                    return true;
                }
            }
        }

        return false;
    }
}
