package Java;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        char playerSymbol = chooseSymbol("Крестик (X) выберите символ (#, *, ×, или X):", scanner, true);
        char opponentSymbol = chooseSymbol("Нолик (O) выберите символ (0, О, °, или •):", scanner, false);

        while (true) {
            char[][] gameBoard = {
                {' ', ' ', ' '},
                {' ', ' ', ' '},
                {' ', ' ', ' '}
            };

            char currentPlayer = playerSymbol;
            char opponentPlayer = opponentSymbol;

            while (true) {
                printGameBoard(gameBoard);

                System.out.println("Ход игрока " + currentPlayer + ". Куда вы поставите " + currentPlayer + "? (x,y)");
                String input = scanner.nextLine();

                if (input.equalsIgnoreCase("exit")) {
                    System.out.println("Игра завершена.");
                    return;
                }

                int[] coordinates = parseInput(input);
                if (coordinates != null) {
                    int x = coordinates[0] - 1;
                    int y = coordinates[1] - 1;

                    if (isValidMove(gameBoard, x, y)) {
                        gameBoard[x][y] = currentPlayer;
                    } else {
                        System.out.println("Некорректные координаты. Попробуйте снова.");
                        continue;
                    }

                    if (checkWin(gameBoard, currentPlayer)) {
                        printGameBoard(gameBoard);
                        System.out.println("Игрок " + currentPlayer + " победил! Поздравляем!");
                        break;
                    }

                    if (isBoardFull(gameBoard)) {
                        printGameBoard(gameBoard);
                        System.out.println("Ничья! Игра окончена.");
                        break;
                    }

                    currentPlayer = (currentPlayer == playerSymbol) ? opponentSymbol : playerSymbol;
                } else {
                    System.out.println("Некорректный формат ввода. Попробуйте снова.");
                }
            }

            System.out.println("Хотите начать новую игру? (Yes or something)");
            String playAgain = scanner.nextLine().toLowerCase();
            if (!playAgain.equalsIgnoreCase("yes")) {
                System.out.println("Игра завершена.");
                break;
            }
        }

        scanner.close();
    }

    public static void printGameBoard(char[][] gameBoard) {
        System.out.println("  1   2   3");
        for (int i = 0; i < gameBoard.length; i++) {
            System.out.print((i + 1) + " ");
            for (int j = 0; j < gameBoard[i].length; j++) {
                System.out.print(gameBoard[i][j]);
                if (j < gameBoard[i].length - 1) {
                    System.out.print(" | ");
                }
            }
            System.out.println();
            if (i < gameBoard.length - 1) {
                System.out.println(" ---+---+---");
            }
        }
    }

    public static char chooseSymbol(String message, Scanner scanner, boolean isPlayerX) {
        System.out.println(message);
        while (true) {
            String symbol = scanner.nextLine().toUpperCase();
            if (isPlayerX && (symbol.equals("#") || symbol.equals("*") || symbol.equals("×") || symbol.equals("X"))) {
                return symbol.charAt(0);
            } else if (!isPlayerX && (symbol.equals("0") || symbol.equals("О") || symbol.equals("°") || symbol.equals("•") || symbol.equals("O"))) {
                return symbol.charAt(0);
            } else {
                System.out.println("Некорректный символ. Пожалуйста, выберите из предложенных символов.");
            }
        }
    }

    public static boolean isValidMove(char[][] gameBoard, int x, int y) {
        return x >= 0 && x < 3 && y >= 0 && y < 3 && gameBoard[x][y] == ' ';
    }

    public static boolean checkWin(char[][] gameBoard, char symbol) {
        for (int i = 0; i < 3; i++) {
            if ((gameBoard[i][0] == symbol && gameBoard[i][1] == symbol && gameBoard[i][2] == symbol) ||
                (gameBoard[0][i] == symbol && gameBoard[1][i] == symbol && gameBoard[2][i] == symbol)) {
                return true;
            }
        }

        return (gameBoard[0][0] == symbol && gameBoard[1][1] == symbol && gameBoard[2][2] == symbol) ||
               (gameBoard[0][2] == symbol && gameBoard[1][1] == symbol && gameBoard[2][0] == symbol);
    }

    public static boolean isBoardFull(char[][] gameBoard) {
        for (char[] row : gameBoard) {
            for (char cell : row) {
                if (cell == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

    public static int[] parseInput(String input) {
        String sanitizedInput = input.replaceAll("[^\\d]", "");
        if (sanitizedInput.length() == 2) {
            int x = Character.getNumericValue(sanitizedInput.charAt(0));
            int y = Character.getNumericValue(sanitizedInput.charAt(1));
            if (x >= 1 && x <= 3 && y >= 1 && y <= 3) {
                return new int[]{x, y};
            }
        }
        return null;
    }
}
