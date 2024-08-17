package Java;
import java.util.Random;
import java.util.Scanner;

public class Minesweeper {
	private static final int SIZE = 9;
	private static final int MINE_COUNT = 20;
	private static char[][] board;
	private static boolean[][] mines;
	private static boolean[][] uncovered;
	private static boolean[][] flagged;
	private static boolean firstMove;

	private static void initializeBoard() {
		board = new char[SIZE][SIZE];
		mines = new boolean[SIZE][SIZE];
		uncovered = new boolean[SIZE][SIZE];
		flagged = new boolean[SIZE][SIZE];
		firstMove = true;

		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				board[i][j] = ' ';
				mines[i][j] = false;
				uncovered[i][j] = false;
				flagged[i][j] = false;
			}
		}
	}

	private static void placeMines(int startRow, int startCol) {
		Random random = new Random();
		int minesToPlace = MINE_COUNT;

		while (minesToPlace > 0) {
			int row = random.nextInt(SIZE);
			int col = random.nextInt(SIZE);

			if (!mines[row][col] && (row != startRow || col != startCol) && isSafeInitialCell(startRow, startCol, row, col)) {
				mines[row][col] = true;
				minesToPlace--;
			}
		}
	}

	private static boolean isSafeInitialCell(int startRow, int startCol, int row, int col) {
		return Math.abs(startRow - row) > 1 || Math.abs(startCol - col) > 1;
	}

	private static int calculateAdjacentMines(int row, int col) {
		int count = 0;

		for (int i = row - 1; i <= row + 1; i++) {
			for (int j = col - 1; j <= col + 1; j++) {
				if (i >= 0 && i < SIZE && j >= 0 && j < SIZE && mines[i][j]) {
					count++;
				}
			}
		}

		return count;
	}

	private static void uncoverCell(int row, int col) {
		if (flagged[row][col]) {
			flagged[row][col] = false;
		} else {
			uncovered[row][col] = true;

			if (mines[row][col]) {
				printBoard();
				System.out.println("Вы проиграли! Игра окончена.");
				System.exit(0);
			}

			if (calculateAdjacentMines(row, col) == 0) {
				for (int i = row - 1; i <= row + 1; i++) {
					for (int j = col - 1; j <= col + 1; j++) {
						if (i >= 0 && i < SIZE && j >= 0 && j < SIZE && !uncovered[i][j] && !flagged[i][j]) {
							uncoverCell(i, j);
						}
					}
				}
			}
		}
	}

	private static void handleFlag(String input) {
		String[] inputParts = input.split("\\s");
		int row = Integer.parseInt(inputParts[1]) - 1;
		int col = Integer.parseInt(inputParts[2]) - 1;

		if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
			flagged[row][col] = !flagged[row][col];
		} else {
			System.out.println("Некорректные координаты для установки/снятия флага. Попробуйте снова.");
		}
	}

	private static void printBoard() {
		System.out.println("  1 2 3 4 5 6 7 8 9");
		for (int i = 0; i < SIZE; i++) {
			System.out.print((i + 1) + " ");
			for (int j = 0; j < SIZE; j++) {
				char cell;
				if (flagged[i][j]) {
					cell = '+';
				} else if (uncovered[i][j]) {
					cell = mines[i][j] ? 'X' : (char) (calculateAdjacentMines(i, j) + '0');
				} else {
					cell = ' ';
				}
				System.out.print(cell + " ");
			}
			System.out.println();
		}
	}

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		initializeBoard();

		System.out.println("Добро пожаловать в игру Сапер!");
		System.out.println("Введите координаты (например, '1 1') для открытия ячейки.");
		System.out.println("Для установки/снятия флага введите F x y (например, 'F 1 2').");

		while (true) {
			printBoard();
			System.out.print("Введите координаты или команду: ");
			String input = scanner.nextLine().trim();

			if (input.matches("\\d+\\s\\d+")) {
				String[] inputParts = input.split("\\s");
				int row = Integer.parseInt(inputParts[0]) - 1;
				int col = Integer.parseInt(inputParts[1]) - 1;

				if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
					if (firstMove) {
						placeMines(row, col);
						firstMove = false;
					}
					uncoverCell(row, col);
					if (mines[row][col]) {
						printBoard();
						System.out.println("Вы проиграли! Игра окончена.");
						break;
					}
				} else {
					System.out.println("Некорректные координаты. Попробуйте снова.");
				}
			} else if (input.matches("[Ff]\\s\\d+\\s\\d+")) {
				handleFlag(input);
			} else {
				System.out.println("Некорректный ввод. Попробуйте снова.");
			}
		}

		scanner.close();
	}
}
