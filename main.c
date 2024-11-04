#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generateBingoCard(int *card, size_t min, size_t max, size_t width, size_t height);
void displayBingoCard(int *card, size_t width, size_t height);

int main(int argc, char *argv[]) {
  size_t width = 5;
  size_t height = 5;
  size_t min = 1;
  size_t max = 99;
  size_t amountOfCards = 1;

  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
      printf("Help:\n");
      printf("Arguments\t\tType\t\tDefault\t\tDescription\n");
      printf("--width, -w\t\tint\t\t5\t\tHow wide your bingo card will be\n");
      printf("--height, -l\t\tint\t\t5\t\tHow high your bingo card will be\n");
      printf("--min, -m\t\tint\t\t1\t\tMinimum square value\n");
      printf("--max, -x\t\tint\t\t99\t\tMaximum square value\n");
      printf("--num, -n\t\tint\t\t1\t\tAmount of bingo cards generated\n");
      printf("--help, -h\t\tNone\t\tNone\t\tBrings you too this help menu\n");
      return 0;
    }

    if (i + 1 >= argc) {
      printf("Error: %s option requires an argument.\n", argv[i]);
      return 1;
    }
    if (strcmp(argv[i], "--width") == 0 || strcmp(argv[i], "-w") == 0) {
      width = atoi(argv[++i]);
    } else if (strcmp(argv[i], "--height") == 0 || strcmp(argv[i], "-l") == 0) {
      height = atoi(argv[++i]);
    } else if (strcmp(argv[i], "--min") == 0 || strcmp(argv[i], "-m") == 0) {
      min = atoi(argv[++i]);
    } else if (strcmp(argv[i], "--max") == 0 || strcmp(argv[i], "-x") == 0) {
      max = atoi(argv[++i]);
    } else if (strcmp(argv[i], "--num") == 0 || strcmp(argv[i], "-n") == 0) {
      amountOfCards = atoi(argv[++i]);
    } else {
      printf("Command %s not found.\n", argv[i]);
      return EXIT_FAILURE;
    }
  }

  // Error handling
  if (max - min < width * height) {
    fprintf(stderr,
            "Error: Range must be larger than the total number of squares.\n");
    return EXIT_FAILURE;
  }


  size_t minWidth = 4;
  size_t minHeight = 1;
  size_t minAmount = 1;

  if (width < minWidth) {
    fprintf(stderr, "Error: Width must be greater than or equal to %zu.\n",
            minWidth);
    return EXIT_FAILURE;
  }

  if (height < 1) {
    fprintf(stderr, "Error: Height must be greater than or equal to %zu.\n",
            minHeight);
    return EXIT_FAILURE;
  }

  if (amountOfCards < 1) {
    fprintf(stderr, "Error: Amount must be greater than or equal to %zu.",
            minAmount);
    return EXIT_FAILURE;
  }

  char *cardPadding = "\n\n\n";
  printf("%s", cardPadding);

  for (int _ = 0; _ < amountOfCards; ++_) {
    int *card = malloc(height * width * sizeof(int));
    if (card == NULL) {
      perror("Error: Failed to allocate memore to card.\n");
      return EXIT_FAILURE;
    }

    generateBingoCard(card, min, max, width, height);
    displayBingoCard(card, width, height);
    free(card);
    printf("%s", cardPadding);
  }

  return 0;
}


void generateBingoCard(int *card, size_t min, size_t max, size_t width, size_t height) {
  int range = max - min;
  int sizeIntArr = range * sizeof(int);
  int *intArr = malloc(sizeIntArr);

  if (intArr == NULL) {
    perror("Error: Failed to allocate memory to intArr.\n");
    exit(EXIT_FAILURE);
  }

  srand(time(NULL));
  for (int i = 0; i < range; ++i) {
    intArr[i] = min + i;
  }

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      int arrSize = range - width * i - j;
      int randomIndex = rand() % arrSize;
      card[i * width + j] = intArr[randomIndex];
      for (int k = randomIndex; k < arrSize - 1; ++k) {
        intArr[k] = intArr[k + 1];
      }
    }
  }

  free(intArr);
}

void displayBingoCard(int *card, size_t width, size_t height) {
  size_t tabWidth = 8;
  size_t totalWidth = tabWidth * width + 7;
  // Allocate memory for dashes
  char *dashes = malloc(totalWidth + 1); // +1 for the null terminator
  if (dashes == NULL) {
    perror("Error: Failed to allocate memory for dashes.\n");
    exit(EXIT_FAILURE);
  }

  // Fill dashes with '-'
  memset(dashes, '-', totalWidth);
  dashes[totalWidth] = '\0'; // Null-terminate the string

  // Allocate memory for roof and floor
  char *roof = malloc(totalWidth + 3); // +3 for "/\\\0"
  if (roof == NULL) {
    perror("Error: Failed to allocate memory for roof.\n");
    free(dashes);
    exit(EXIT_FAILURE);
  }

  char *floor = malloc(totalWidth + 3); // +3 for "\\/\0"
  if (floor == NULL) {
    perror("Error: Failed to allocate memory for floor.\n");
    free(dashes);
    free(roof);
    exit(EXIT_FAILURE);
  }

  char *headerFloor = malloc(totalWidth + 3);

  if (headerFloor == NULL) {
    perror("Error: Failed to allocate memore for header floor.\n");
    free(dashes);
    free(roof);
    free(floor);
    exit(EXIT_FAILURE);
  }

  // Create roof, floor and headerFloor strings
  strcpy(roof, "/");
  strcat(roof, dashes);
  strcat(roof, "\\");

  strcpy(floor, "\\");
  strcat(floor, dashes);
  strcat(floor, "/");

  strcpy(headerFloor, "|");
  strcat(headerFloor, dashes);
  strcat(headerFloor, "|");

  // Print the roof
  printf("%s\n", roof);

  char *padding =
      malloc(totalWidth / 2 - 17); // -17 because the half of the bingo banner
                                   // is 18 and then we add 1 for the \0
  memset(padding, ' ', totalWidth / 2 - 18);

  // Binfo meader
  printf("|%s__________.__                        %s|\n", padding, padding);
  printf("|%s\\______   \\__| ____    ____   ____   %s|\n", padding, padding);
  printf("|%s |    |  _/  |/    \\  / ___\\ /  _ \\_ %s|\n", padding, padding);
  printf("|%s |    |   \\  |   |  \\/ /_/  >  <_> ) %s|\n", padding, padding);
  printf("|%s |______  /__|___|  /\\___  / \\____/  %s|\n", padding, padding);
  printf("|%s        \\/        \\//_____/          %s|\n", padding, padding);
  printf("%s\n", headerFloor);

  // Print the bingo card
  for (int i = 0; i < height; ++i) {
    printf("|\t");
    for (int j = 0; j < width; ++j) {
      printf("%d\t", card[i * width + j]);
    }
    printf("|\n");
  }

  // Print the floor
  printf("%s\n", floor);

  // Free allocated memory
  free(headerFloor);
  free(dashes);
  free(roof);
  free(floor);
}
