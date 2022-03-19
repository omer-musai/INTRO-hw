#include <stdio.h>
#include <stdbool.h>
#include <stdbool.h>

#define BOARD_MAX_SIDE 9
#define BOARD_MIN_SIDE 3
#define MIN_TOKENS 3

#define RED_SLOT_SYMBOL ('R')
#define YELLOW_SLOT_SYMBOL ('Y')
#define EMPTY_SLOT_SYMBOL (' ')


//----------------------- Message Identifiers --------------------------//
#define MSG_GET_BOARD_ROWS   0
#define MSG_GET_BOARD_COLS   1
#define MSG_GET_NUMBER_TOKENS 2


//--------------------------- Board Edges ------------------------------//

#define BOARD_VERT_SEP  '|'
#define BOARD_LEFT_ANG '\\'
#define BOARD_RIGHT_ANG '/'
#define BOARD_BOTTOM  '-'
#define BOARD_BOTTOM_SEP '-'

#define DIM 2
#define P_1 1
#define P_2 2
#define UNDO -1
#define REDO -2
#define TIE -1
#define MAX_ELEMENTS 81


void initBoard(char board[][BOARD_MAX_SIDE], int board_side[DIM]);

bool updateBoard(char board[][BOARD_MAX_SIDE], int board_side[], int plays_history[][DIM], char symbols_history[], int* player_move,
                    int col_counter[],int* player_turn, char* p1_color, int* tokens, int* undo_cnt, int* num_of_moves);

bool check_diagonal_lines(char board[][BOARD_MAX_SIDE], char symbol, int tokens, int player_turn, int player_move,
                         int col_counter[], int board_side[]);

bool check_row_column(char board[][BOARD_MAX_SIDE], char symbol, int tokens, int player_turn, int player_move, int col_counter[], int board_side[]);

bool board_full(int col_counter[], int board_side[]);

bool winner(char board[][BOARD_MAX_SIDE], char symbol, int tokens, int player_turn, int player_move, int col_counter[], int board_side[]);

bool undo(char board[][BOARD_MAX_SIDE], int board_side[],int plays_history[][DIM],
             int* undo_cnt, int* num_of_moves, int* player_turn, int col_counter[], bool* reprompt);

bool redo(char board[][BOARD_MAX_SIDE], int board_side[],int plays_history[][DIM], char symbols_history[],
             int* undo_cnt, int* num_of_moves, int* player_turn, int col_counter[], bool* reprompt);

bool opening(char board[][BOARD_MAX_SIDE], char* p1_color, int* rows, int* columns, int* tokens);
                

bool gameStillOn(char board[][BOARD_MAX_SIDE], int board_side[],
        int undo_streaks[][DIM], char undo_symbols[], int* undo_cnt, int* num_of_moves, int* player_turn,
        int col_counter[], int* player_move, char* p1_color, int* tokens, bool* reprompt);

//----------------------------------------------------------------------//


void print_welcome_message();
void print_read_game_params_message(int param);
void print_chose_color_message();
void print_chose_move_message(int player);
void print_enter_column_message();
void print_full_column_message();
void print_unavailable_undo_redo_message();
void opening_columns(int* columns, int* rows);
void opening_rows(int* rows);
void opening_color(char* p1_color);
void promptAgian(bool* reprompt, int* player_turn);
bool full_column(int col_counter[], int* player_move, int board_side[], bool* reprompt);
bool out_of_boundaries(int* player_move, int board_side[], bool* reprompt);
void update_pointers(int* undo_cnt, int plays_history[][DIM], int* num_of_moves, int* player_move, int board_side[], int col_counter[],
                   char symbols_history[], int* player_turn, char symbol);

/*
 * Outputs game board.
 *
 * board - contains spaces for empty cells, 'Y' or 'R' for
 *         respective player cells.
 * board_side - contains board dimensions {rows, cols}
 */
void print_board(char board[][BOARD_MAX_SIDE], int board_side[]);

/*
 * Outputs winner or tie message.
 *
 * player_id - the id to be output. Pass <0 for tie.
 */
void print_winner(int player_id);

//--------------------------- Main Program -----------------------------//


//15 lines
int main()
{
    int col_counter[BOARD_MAX_SIDE] = {0};
    int plays_history[MAX_ELEMENTS][DIM] = {{0}};
    char board[BOARD_MAX_SIDE][BOARD_MAX_SIDE];
    char symbols_history[MAX_ELEMENTS];

    int r =0, c =0, t =0, m=0, pt =P_1, un=0, nm=0;
    int *rows = &r, *columns = &c, *tokens = &t, *player_move = &m, *player_turn = &pt, *undo_cnt=&un, *num_of_moves = &nm;

    bool p =false;
    char s = EMPTY_SLOT_SYMBOL;
    char* p1_color = &s;
    bool* reprompt = &p;
    
    if(!opening(board, p1_color, rows, columns, tokens))
    {
        return 0;
    }
    
    int board_side[DIM] = {*rows, *columns};
    
    while(gameStillOn(board, board_side, plays_history, symbols_history, undo_cnt, num_of_moves, player_turn,
        col_counter, player_move, p1_color, tokens, reprompt))
    {}
    return 0; 
}



//get opening parameters from the user and inital board
//11 lines
bool opening(char board[][BOARD_MAX_SIDE], char* p1_color, int* rows, int* columns, int* tokens)           
{
    print_welcome_message();
    opening_color(p1_color);
    opening_rows(rows);
    opening_columns(columns, rows);

    while (*tokens < 3 || *tokens > *rows || *tokens > *columns)
    {
        print_read_game_params_message(MSG_GET_NUMBER_TOKENS);
        if(scanf("%d", tokens) == 0)
        {
            return false;
        } 
    }
    
    int board_side[DIM] = {*rows, *columns};
    initBoard(board, board_side); 
    return true;
}


void promptAgian(bool* reprompt, int* player_turn)
{
    if(!(*reprompt))
    {
        print_chose_move_message(*player_turn);
        print_enter_column_message();
    }

    *reprompt = false;
}

//check if the column is full
bool full_column(int col_counter[], int* player_move, int board_side[], bool* reprompt)
{
    if(col_counter[*player_move - 1] + 1 > board_side[0])
    {  
        *reprompt = true;
        print_full_column_message();
        print_enter_column_message();
        return true; 
    }
    return false;
}

bool out_of_boundaries(int* player_move, int board_side[], bool* reprompt)
{
    if((*player_move < 1 && *player_move != REDO && *player_move != UNDO ) ||  *player_move > board_side[1])
    {
        *reprompt = true;
        print_enter_column_message();
        return true;
    }
    return false;
}

//run the game: get player move, and update/undo/redo accordingly
//16 lines
bool gameStillOn(char board[][BOARD_MAX_SIDE], int board_side[],
        int plays_history[][DIM], char symbol_history[], int* undo_cnt, int* num_of_moves, int* player_turn,
        int col_counter[], int* player_move, char* p1_color, int* tokens, bool* reprompt)
{
    //checks if need to reprompt the user
    promptAgian(reprompt, player_turn);
    
    //prompt the user for next move
    if(scanf("%d", player_move) == 0)
    {
        return false;
    }

    //out of boundaries
    if(out_of_boundaries(player_move, board_side, reprompt))
    {
        return true;
    }
    
    if(*player_move == REDO)
    {
        return redo(board,board_side,plays_history,symbol_history,undo_cnt, num_of_moves, player_turn, col_counter, reprompt);
    }
   
    if(*player_move == UNDO)
    {
        return undo(board,board_side, plays_history, undo_cnt, num_of_moves, player_turn, col_counter, reprompt);
    }
   
    if(*player_move < 1 || *player_move > board_side[1])
    {
        return true;
    }
    
    if(full_column(col_counter, player_move, board_side, reprompt))
    {  
        return true; 
    }
    
    if(updateBoard(board,board_side,plays_history,symbol_history,player_move,col_counter,player_turn,p1_color,tokens,undo_cnt,num_of_moves))
    {
        return false;
    }
    return true;
}

//5 lines
void initBoard(char board[][BOARD_MAX_SIDE], int board_side[DIM])
{
    for (int i = 0; i < BOARD_MAX_SIDE; i++)
    {
        for (int j = 0; j < BOARD_MAX_SIDE; j++)
        {
            board[i][j] = EMPTY_SLOT_SYMBOL;
        }
    }
    print_board(board, board_side);
    return;
}

//update the board according to player move and check if the game ended
//15 lines
bool updateBoard(char board[][BOARD_MAX_SIDE], int board_side[], int plays_history[][DIM], char symbols_history[], int* player_move,
                    int col_counter[],int* player_turn, char* p1_color, int* tokens, int* undo_cnt, int* num_of_moves)
{
    char symbol = RED_SLOT_SYMBOL;
    if(*player_turn == 1)
    {
        symbol = *p1_color;
    }
    else if(*p1_color == RED_SLOT_SYMBOL)
    {
        symbol = YELLOW_SLOT_SYMBOL;
    }
    
    board[board_side[0] - col_counter[(*player_move)-1]-1][(*player_move)-1] = symbol;
    ++col_counter[(*player_move)-1];
    
    print_board(board, board_side);
    
    if(*player_move > 0 && winner(board, symbol, *tokens, *player_turn, *player_move, col_counter, board_side))
    {
        return true;
    }
    else if(board_full(col_counter, board_side))
    {
        print_winner(TIE);
        return true;
    }
    
    update_pointers(undo_cnt, plays_history, num_of_moves,player_move, board_side, col_counter, symbols_history, player_turn, symbol);
 
    return false; 
}

void update_pointers(int* undo_cnt, int plays_history[][DIM], int* num_of_moves, int* player_move, int board_side[], int col_counter[],
                   char symbols_history[], int* player_turn, char symbol)
{
    *undo_cnt =0;
    plays_history[*num_of_moves][1] = (*player_move) - 1;
    plays_history[*num_of_moves][0] = board_side[0] - col_counter[(*player_move)-1];
    symbols_history[*num_of_moves] = symbol;
    ++*num_of_moves;
    *player_turn = (*player_turn % DIM) + 1;
}

//12 lines
bool undo(char board[][BOARD_MAX_SIDE], int board_side[],int plays_history[][DIM],
             int* undo_cnt, int* num_of_moves, int* player_turn, int col_counter[], bool* reprompt)
{
    if(*num_of_moves != 0)
    {
        board[plays_history[(*num_of_moves)-1][0]][plays_history[(*num_of_moves)-1][1]] = EMPTY_SLOT_SYMBOL;
        print_board(board, board_side);

        --*num_of_moves;
        *player_turn = (*player_turn % P_2) + 1; 
        col_counter[plays_history[*num_of_moves][1]]--;
        ++*undo_cnt;
    }
    else
    {
        *reprompt = true;
        print_unavailable_undo_redo_message();
        print_enter_column_message();
    }
    return true;
}

//12 lines
bool redo(char board[][BOARD_MAX_SIDE], int board_side[],int plays_history[][DIM], char symbols_history[],
             int* undo_cnt, int* num_of_moves, int* player_turn, int col_counter[], bool* reprompt)
{
    if(*undo_cnt != 0)
    {
        board[plays_history[(*num_of_moves)][0]][plays_history[(*num_of_moves)][1]] = symbols_history[(*num_of_moves)];
        print_board(board, board_side);
        
        col_counter[plays_history[(*num_of_moves)][1]]++;
        ++*num_of_moves;
        *player_turn = (*player_turn % P_2) + 1; 
        --*undo_cnt;
    }
    else
    {
        *reprompt = true;
        print_unavailable_undo_redo_message();
        print_enter_column_message();
    }
    return true;
}

//check if there is a winner
//2 lines
bool winner(char board[][BOARD_MAX_SIDE], char symbol, int tokens, int player_turn, int player_move, int col_counter[], int board_side[])
{
   return (check_row_column(board, symbol, tokens, player_turn, player_move, col_counter, board_side)||
             check_diagonal_lines(board, symbol, tokens, player_turn, player_move, col_counter, board_side));
}

//check if the board is full
//4 lines
bool board_full(int col_counter[], int board_side[])
{
    for (int i =0; i < board_side[1]; i++)
    { 
        if(col_counter[i] < board_side[0])
        {
            return false;
        }
    }
    return true;
}

//check if we have a column or row streak of the same symbols
//14 lines
bool check_row_column(char board[][BOARD_MAX_SIDE], char symbol, int tokens, int player_turn, int player_move, int col_counter[], int board_side[])
{
    int row_cnt=0, col_cnt=0;
    for(int i=0; i < BOARD_MAX_SIDE; i++)
    {
        if(board[board_side[0] - col_counter[player_move-1]][i] == symbol)
        {
            row_cnt++;
        }
        else
        {
            row_cnt = 0;
        }
        if(board[i][player_move - 1] == symbol)
        {
            col_cnt++;
        }
        else
        {
            col_cnt = 0;
        }
        if(row_cnt == tokens|| col_cnt == tokens)
        {
            print_winner(player_turn);
            return true;
        }
    }
    return false;
}

//check if we have a diagonal line streak fo the same symbols
//16 lines
bool check_diagonal_lines(char board[][BOARD_MAX_SIDE], char symbol, int tokens, int player_turn,int player_move,int col_counter[],int board_side[])
{ 
    //locator to get to the start of the diagonal line we want to check according to the current row and colums
    int cnt1=0, cnt2=0, locator = player_move > col_counter[player_move -1] ? col_counter[player_move -1] - 1 : player_move - 1; 
    
    for (int i=0; i < BOARD_MAX_SIDE; i++)
    {
        //check if in boundaries
        if(board_side[0]-col_counter[player_move-1]+locator-i < BOARD_MAX_SIDE && board_side[0]-col_counter[player_move-1]+locator-i >=0 &&
            player_move - 1 - locator + i <BOARD_MAX_SIDE && player_move - 1 - locator + i >= 0)
        {
            if(board[board_side[0] - col_counter[player_move-1] + locator - i][player_move - 1 - locator + i] == symbol)
            {
                cnt1++;
            }
            else
            {
                cnt1 = 0;
            }   
        }
        //check if in boundaries
        if(board_side[0]-col_counter[player_move-1]+board_side[0]-1-locator-i<BOARD_MAX_SIDE&&player_move-1+board_side[0]-1-locator-i<BOARD_MAX_SIDE
            &&board_side[0]-col_counter[player_move-1]+board_side[0]-1-locator-i >=0 && player_move-1+board_side[0] -1 - locator-i >= 0)
            
        {
            if(board[board_side[0]-col_counter[player_move-1]+board_side[0]-1-locator-i][player_move-1+board_side[0] -1 - locator-i] == symbol)
            {
                cnt2++;
            }
            else
            {
                cnt2 = 0;
            }  
        }   
        
        if(cnt1 == tokens || cnt2 == tokens)
        {
            print_winner(player_turn);
            return true;
        }
    }
    return false;
}


void opening_color(char* p1_color)
{
    while (!(*p1_color == RED_SLOT_SYMBOL || *p1_color == YELLOW_SLOT_SYMBOL ))
    {
        print_chose_color_message();
        scanf(" %c", p1_color);
    } 
}

void opening_rows(int* rows)
{
    while (*rows < BOARD_MIN_SIDE || *rows > BOARD_MAX_SIDE)
    {
        print_read_game_params_message(MSG_GET_BOARD_ROWS);
        scanf("%d", rows);
    }
}

void opening_columns(int* columns, int* rows)
{
    while (*rows > *columns || *columns < BOARD_MIN_SIDE || *columns > BOARD_MAX_SIDE )
    {
       print_read_game_params_message(MSG_GET_BOARD_COLS);
       scanf("%d", columns);
    }
}


//---------------------- Printing Functions ----------------------------//

// message number 0 = "Welcome to 4-in-a-row game! \n"
void print_welcome_message()
{
    printf("Welcome to 4-in-a-row game! \n");
}


// message number 1 = "Please enter number of rows:"
// message number 2 = "Please enter number of columns:"
// message number 3 = "Please enter number of tokens:"
void print_read_game_params_message(int param)
{
	char const* const possible_params[] = {"rows", "columns", "tokens"};

    printf("Please enter number of %s: ", possible_params[param]);
}

// message number 4 = "Please choose starting color (Y)ellow or (R)ed: "
void print_chose_color_message()
{
    printf("Please choose starting color (Y)ellow or (R)ed: ");
}

// message number 5 = "Your move, player <player>. "
void print_chose_move_message(int player)
{
    printf("Your move, player %d. ", player);
}

// message number 6
void print_enter_column_message()
{
    printf("Please enter column: ");
}

void print_full_column_message()
{
    printf("Column full. ");
}

void print_unavailable_undo_redo_message()
{
    printf("No moves to undo/redo. ");
}

void print_board(char board[][BOARD_MAX_SIDE], int board_side[])
{
  /*assert(IS_IN_RANGEI(board_side[0], 0, BOARD_MAX_SIDE)
        && IS_IN_RANGEI(board_side[1], 0, BOARD_MAX_SIDE));*/

    for (int row = 0; row < board_side[0]; ++row)
    {
        printf("\n%c", BOARD_VERT_SEP);
        for (int col = 0; col < board_side[1]; ++col)
            printf("%c%c", board[row][col], BOARD_VERT_SEP);
    }
    printf("\n%c", BOARD_LEFT_ANG);
    for (int ii = 0; ii < board_side[1] - 1; ++ii)
        printf("%c%c", BOARD_BOTTOM, BOARD_BOTTOM_SEP);
    printf("%c%c\n", BOARD_BOTTOM, BOARD_RIGHT_ANG);
}

void print_winner(int player_id)
{
    if (player_id >= 0)
        printf("Player %d won! \n", player_id);
    else
        printf("That's a tie. \n");
}