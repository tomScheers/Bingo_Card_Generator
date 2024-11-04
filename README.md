# Bingo Card Generator
This is a simple bingo card generator written in C, it generates a bingo card based on multiple paramaters which can be passed in the form of flags

## Usage
1. Clone the repository and navigate to it:
```bash
git clone https://github.com/tomScheers/Bingo_Card_Generator
cd Bingo_Card_Generator
```
2. Compile and run the program:
```bash
gcc -o main main.c
./main
```
3. Pass down paramaters:
The project takes in multiple parameters which will change the way the bingo cards are generated, here's an overview:
| Arguments      | Type | Default | Description                         |
|----------------|------|---------|-------------------------------------|
| `--width`, `-w`  | int  | 5       | How wide your bingo card will be    |
| `--height`, `-l` | int  | 5       | How high your bingo card will be    |
| `--min`, `-m`    | int  | 1       | Minimum square value                |
| `--max`, `-x`    | int  | 99      | Maximum square value                |
| `--num`, `-n`    | int  | 1       | Amount of bingo cards generated     |
| `--help`, `-h`   | None | None    | Brings you to this help menu        |
