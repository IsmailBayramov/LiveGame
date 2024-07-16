#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define HEIGHT 25
#define WIDTH 80
#define CELL 'o'
#define DEATH_CELL ' '

void read_field(char field[HEIGHT][WIDTH]);
void update_field(char field[HEIGHT][WIDTH], char new_field[HEIGHT][WIDTH]);
void print_field(char field[HEIGHT][WIDTH]);
void game_loop(char field[HEIGHT][WIDTH]);
int check_neighbors(char field1[HEIGHT][WIDTH], int i, int j);
void check_life(char field[HEIGHT][WIDTH], int *stop);
void game_over(char field[HEIGHT][WIDTH]);
void *second_thread_enter(void *arg);

int main() {
  int correct = 0;
  char field[HEIGHT][WIDTH];
  int speed = 500;
  int stop = 1;

  read_field(field);

  if (!isatty(fileno(stdin))) {
    if (freopen("/dev/tty", "r", stdin) == NULL) {
      fprintf(stderr, "n/a");
    }
  }

  int *args[2] = {&speed, &stop};

  pthread_t second_thread;
  int result = pthread_create(&second_thread, NULL, second_thread_enter, args);

  if (result != 0) {
    correct = 1;
  }

  if (correct != 1) {
    char new_field[HEIGHT][WIDTH];
    while (stop != 0) {
      printf("\033c");
      print_field(field);
      update_field(field, new_field);
      check_life(field, &stop);

      usleep(speed * 1000);

      if (stop == 0) {
        printf("\033c");
        game_over(field);
        print_field(field);
      }
    }
  }

  pthread_join(second_thread, NULL);

  return 0;
}

void read_field(char field[HEIGHT][WIDTH]) {
  int symb;

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (scanf("%d", &symb) != 1) {
        printf("Invalid matrix element\n");
      } else {
        if (symb == 1) {
          field[i][j] = CELL;
        } else if (symb == 0) {
          field[i][j] = DEATH_CELL;
        }
      }
    }
  }
}

void print_field(char field[HEIGHT][WIDTH]) {
  printf("\033c");

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      printf("%c", field[i][j]);
    }
    printf("\n");
  }
}

int check_neighbors(char field[HEIGHT][WIDTH], int x, int y) {
  int neighbor = 0;

  int i_minus = x - 1, j_minus = y - 1, i_plus = x + 1, j_plus = y + 1;

  if (i_minus < 0) {
    i_minus = HEIGHT - 1;
  }
  if (j_minus < 0) {
    j_minus = WIDTH - 1;
  }
  if (i_plus > HEIGHT - 1) {
    i_plus = i_plus % HEIGHT;
  }
  if (j_plus > WIDTH - 1) {
    j_plus = j_plus % WIDTH;
  }

  const int rows_num[] = {x,       x,      i_minus, i_plus,
                          i_minus, i_plus, i_minus, i_plus};
  const int cols_num[] = {j_minus, j_plus, y,      y,
                          j_minus, j_plus, j_plus, j_minus};

  for (int i = 0; i < 8; i++) {
    neighbor += (field[rows_num[i]][cols_num[i]] == CELL) ? 1 : 0;
  }

  return neighbor;
}

void update_field(char field[HEIGHT][WIDTH], char new_field[HEIGHT][WIDTH]) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      int alive_neighbors = check_neighbors(field, i, j);
      if (field[i][j] == DEATH_CELL && alive_neighbors == 3) {
        new_field[i][j] = CELL;
      } else if (field[i][j] == CELL &&
                 (alive_neighbors == 2 || alive_neighbors == 3)) {
        new_field[i][j] = CELL;
      } else {
        new_field[i][j] = DEATH_CELL;
      }
    }
  }

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      field[i][j] = new_field[i][j];
    }
  }
}

void check_life(char field[HEIGHT][WIDTH], int *stop) {
  int tmp = 0;
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (field[i][j] != CELL) {
        tmp++;
      }
    }
  }

  if (tmp == 2000) {
    *stop = 0;
  }
}

void game_over(char field[HEIGHT][WIDTH]) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (i >= 4 && i <= 19 && j == 28) {
        field[i][j] = 'G';
      } else if (i >= 4 && i <= 19 && j == 32) {
        field[i][j] = 'A';
      } else if (i >= 4 && i <= 19 && j == 36) {
        field[i][j] = 'M';
      } else if (i >= 4 && i <= 19 && j == 40) {
        field[i][j] = 'E';
      } else if (i >= 4 && i <= 19 && j == 46) {
        field[i][j] = ' ';
      } else if (i >= 4 && i <= 19 && j == 50) {
        field[i][j] = 'O';
      } else if (i >= 4 && i <= 19 && j == 54) {
        field[i][j] = 'V';
      } else if (i >= 4 && i <= 19 && j == 58) {
        field[i][j] = 'E';
      } else if (i >= 4 && i <= 19 && j == 62) {
        field[i][j] = 'R';
      } else {
        field[i][j] = DEATH_CELL;
      }
    }
  }
}

void *second_thread_enter(void *arg) {
  int **args = (int **)arg;
  int *speed = args[0];
  int *stop = args[1];

  while (*stop) {
    char enter;
    if (scanf("%c", &enter) != 1 || (enter == 'q' || enter == 'Q')) {
      *stop = 0;
    } else if (enter == '-') {
      *speed += 50;
    } else if (enter == '+') {
      if (*speed != 50) {
        *speed -= 50;
      }
    }
  }

  return NULL;
}