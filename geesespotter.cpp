#include "geesespotter_lib.h"
#include <iostream>

char * create_board(std::size_t x_dim, std::size_t y_dim)
{
    // create dynamic char array for board 
    char * board = new char [x_dim*y_dim] {}; 

    // fills char array with 0 
        for(std::size_t k{0}; k < (x_dim*y_dim); k++) 
        {
            board[k] = 0; 
        }

    return board; 

}
void clean_board(char * board)
{
    // deletes the content and the address of the char array 
    delete [] board; 
    board = nullptr; 

}

void print_board(char * board, std::size_t x_dim, std::size_t y_dim)
{
    // prints out each y rows 
    int index{0}; 

    for(std::size_t i {0}; i < y_dim; i++)
    {
        // prints out each x rows 
        for(std::size_t j {0}; j < x_dim; j++)
        {
            // if field is revelaed, the value will be less than the value of the hidden bit 
            if((board[index] & marked_mask()) == marked_mask()) 
            {
                std::cout << "M"; 

            // if the value of the field is between 0x20 and 0x30 then it is hidden (hidden bit value is 0x20)
            } else if ((board[index] & hidden_mask()) == hidden_mask())
            {
                std::cout << "*";  

            // else, the field is marked 
            } else 
            {
                std::cout << (board[index] & value_mask()); 
            }

            index++; 

        }
        std::cout << std::endl; 
    }

}

void hide_board(char * board, std::size_t x_dim, std::size_t y_dim)
{
    for(std::size_t i = 0; i < (x_dim*y_dim); i++)
    {
        //board[i] &= value_mask(); 
        //board[i] |= hidden_mask(); 
    }
}


int mark(char * board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc, std::size_t y_loc)
{
    
    // finds index of the coordinate
    int index{-1}; 
    for(std::size_t i{0}; i < y_loc; i++)
    {
        for(std::size_t j{0}; j < x_dim; j++)
        {
            index++; 
        }
    }

    for (std::size_t k{0}; k < x_loc + 1; k++)
    {
        index++; 
    }

// if its not hidden, return 2

if((board[index] & hidden_mask()) != hidden_mask())
    {
        return 2; 
    }
// if its marked, unmark and return 0 + vise versa 

    board[index] = board[index] ^ marked_mask(); 
        return 0; 

} 

int indexFinder(char*board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc, std::size_t y_loc)
{
    // finds index of the coordinate
    if(x_loc < 0|| x_loc > x_dim)
    {
        // std::cout << "Not found" << std::endl; 
        return -1; 
    }else if(y_loc > y_dim || y_loc < 0)
    {
        // std::cout << "Not found"<< std::endl; 
        return -1; 
    }

    int index{-1}; 
    for(std::size_t i{0}; i < y_loc; i++)
    {
        for(std::size_t j{0}; j < x_dim; j++)
        {
            index++; 
        }
    }

    for (std::size_t k{0}; k < x_loc + 1; k++)
    {
        index++; 
    }
    
    return index; 
    
}


int gooseCounter (char * board, std::size_t x_dim, std::size_t y_dim, int row, int col)
{

    int n{0};
    int row1 = row; 
    int col1 = col; 
    int index {0}; 
    
    // calculate upper left
    row = row1-1;
    col = col1-1; 
    index = indexFinder(board, x_dim, y_dim, row, col); 
    if(index != -1)
    {
        if (((board[index] & value_mask())) == 9)
        {
            n++; 
        }
    }

    // calculate top; 
    row = row1-1; 
    col = col1; 
    index = indexFinder(board,x_dim, y_dim, row, col);
    if(index != -1)
    {
        if((board[index] & value_mask()) == 9 )
        {
            n++; 
        }
    }

    // calculate upper right 
    row = row1-1; 
    col = col1 + 1; 
    index = indexFinder(board, x_dim,y_dim, row, col); 
    if(index != -1)
    {
    if(((board[index] & value_mask())) == 9)        {
            n++; 
        }
    }

    // calculate left
    row = row1; 
    col = col1-1; 
    index = indexFinder(board, x_dim,y_dim, row, col); 
    if(index != -1)
    {
if(((board[index] & value_mask())) == 9)        {
            n++; 
        }
    }

    // calculate right
    row = row1; 
    col = col1 + 1; 
    index = indexFinder(board, x_dim,y_dim, row, col); 
    if(index != -1)
    {
if(((board[index] & value_mask())) == 9)        {
            n++; 
        }
    }

    // calculate lower left: 
    row = row1 +1; 
    col = col1 - 1; 
    index = indexFinder(board, x_dim,y_dim, row, col); 
    if(index != -1)
    {
 if(((board[index] & value_mask())) == 9)
        {
            n++; 
        }
    }

    // calculate bottom 
    row = row1+1; 
    col = col1; 
    index = indexFinder(board, x_dim,y_dim, row, col); 
    if(index != -1)
    {
        if(((board[index] & value_mask())) == 9)
        {
            n++; 
        }
    }

    // calculate lower right 
    row = row1 + 1; 
    col = col1 + 1; 
    index = indexFinder(board, x_dim,y_dim, row, col); 
    if(index != -1)
    {
if(((board[index] & value_mask())) == 9)
        {
            n++; 
        }
    }

    std::cout<<"n from goosecountwer: "<<n<<std::endl;

    return n; 
   
}


void compute_neighbours(char * board, std::size_t x_dim, std::size_t y_dim)
{
    int indexcounter{0};
    int row {0}; 
    int col{0};  
 

    for(std::size_t y{0}; y < y_dim; y++)
    {
        col = 0; 
        for(std::size_t x{0}; x < x_dim; x++)
        {
            if((board[indexcounter] & value_mask()) != 9)
            {
                board[indexcounter] = gooseCounter(board, x_dim, y_dim, row, col); 
            }
            indexcounter++; 
            col++; 
        }

        row++;
    }

}
bool is_game_won(char * board, std::size_t x_dim, std::size_t y_dim)
{
    return false; 
}
int reveal(char * board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc, std::size_t y_loc)
{

    // finds index of the coordinate
    int index{-1}; 
    for(std::size_t i{0}; i < y_loc; i++)
    {
        for(std::size_t j{0}; j < x_dim; j++)
        {
            index++; 
        }
    }

    for (std::size_t k{0}; k < x_loc + 1; k++)
    {
        index++; 
    }

    // if the value at the index is 0, reveal the 8 adjacent tiles - not complete 


    if((board[index] & marked_mask()) == marked_mask()) // if the board is marked, return 1
    {
        return 1; 
    } else if ((board[index] & hidden_mask()) != hidden_mask()) // if the board is not hidden (revealed), return 2
    {
        return 2; 
    }else // else: return 0
    {
        return 0; 
    }
    

    return 0; 
}