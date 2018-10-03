#include <stdio.h>

enum face {
    up,
    down,
    left,
    right,
    front,
    back
};

enum piece {
    red_green_white,
    red_blue_white,
    red_blue_yellow,
    red_green_yellow,
    orange_blue_white,
    orange_blue_yellow,
    orange_green_white,
    orange_green_yellow
};

char *piece_names[] = {
    "red_green_white",
    "red_blue_white",
    "red_blue_yellow",
    "red_green_yellow",
    "orange_blue_white",
    "orange_blue_yellow",
    "orange_green_white",
    "orange_green_yellow"
};

// This is flawed because it only accounds for the position of the piece
// and does not consider the orientation.
enum piece pieces[] =
{

   /*
         red
       ______
      /0 /1  /|
     -------+ |
    /3  /2 /|/|  blue
    +--+--+ + |
    |  |  |/|4|
    +--+--+ |/
    |7 |5 |/        // the hidden piece is 6
    +--+--+
    */

    // 0
    red_green_white,
    // 1
    red_blue_white,
    // ...
    red_blue_yellow,
    red_green_yellow,
    orange_blue_white,
    orange_blue_yellow,
    orange_green_white,
    // 7
    orange_green_yellow
};

enum piece pieces_solved[] =
{
    red_green_white,
    red_blue_white,
    red_blue_yellow,
    red_green_yellow,
    orange_blue_white,
    orange_blue_yellow,
    orange_green_white,
    orange_green_yellow
};

enum piece *up_face[2][2] =
{
    {&pieces[orange_blue_yellow], &pieces[red_blue_yellow]},
    {&pieces[orange_blue_white], &pieces[red_blue_white]}
};

enum piece *down_face[2][2] = 
{
    {&pieces[red_green_yellow], &pieces[orange_green_yellow]},
    {&pieces[red_green_white], &pieces[orange_green_white]}
};

enum piece *left_face[2][2] =
{
    {&pieces[orange_blue_white], &pieces[red_blue_white]},
    {&pieces[orange_green_white], &pieces[red_green_white]}
};

enum piece *right_face[2][2] =
{
    {&pieces[red_blue_yellow], &pieces[orange_blue_yellow]},
    {&pieces[red_green_yellow], &pieces[orange_green_yellow]}
};

enum piece *front_face[2][2] =
{
    {&pieces[red_blue_white], &pieces[red_blue_yellow]},
    {&pieces[red_green_white], &pieces[red_green_yellow]}
};

enum piece *back_face[2][2] =
{
    {&pieces[orange_blue_yellow], &pieces[orange_blue_white]},
    {&pieces[orange_green_yellow], &pieces[orange_green_white]}
};

// return pointer to 2d array of pointers
enum piece *(*select_face(enum face face))[2][2]
{
    enum piece *(*face_arr)[2][2] = &up_face;
    switch(face)
    {
        case up:
            face_arr = &up_face;
            break;
        case down:
            face_arr = &down_face;
            break;
        case left:
            face_arr = &left_face;
            break;
        case right:
            face_arr = &right_face;
            break;
        case front:
            face_arr = &front_face;
            break;
        case back:
            face_arr = &back_face;
            break;
    }

    return face_arr;
}

void rotate_clock(enum face face)
{
    enum piece *(*face_arr)[2][2] = select_face(face);

    enum piece temp = *(*face_arr)[0][0];

    *(*face_arr)[0][0] = *(*face_arr)[1][0];
    *(*face_arr)[1][0] = *(*face_arr)[1][1];
    *(*face_arr)[1][1] = *(*face_arr)[0][1];
    *(*face_arr)[0][1] = temp;
}

void rotate_cclock(enum face face)
{
    enum piece *(*face_arr)[2][2] = select_face(face);

    enum piece temp = *(*face_arr)[0][1];

    *(*face_arr)[0][1] = *(*face_arr)[1][1];
    *(*face_arr)[1][1] = *(*face_arr)[1][0];
    *(*face_arr)[1][0] = *(*face_arr)[0][0];
    *(*face_arr)[0][0] = temp;
}

void print_face(enum face face)
{
    enum piece *(*face_arr)[2][2] = select_face(face);

    for(int row=0; row < 2; row++) {
        printf("%20s %20s\n",
                piece_names[*(*face_arr)[row][0]],
                piece_names[*(*face_arr)[row][1]]
                );
    }
}

// This is flawed because it does not account for different orientations
// of the cube uaba should solve but it does not.
int is_solved()
{
    for(int i=0; i < 8; i++)
    {
        if(pieces[i] != pieces_solved[i])
            return 0;
    }

    return 1;
}

// example ucbadarc -> up clock, back cclock, down cclock, right clock

void play(char *moves)
{
    for(int i=0; moves[i]; i+=2)
    {
        enum face face = up;
        switch(moves[i]) {
            case 'u':
                face = up;
                break;
            case 'd':
                face = down;
                break;
            case 'l':
                face = left;
                break;
            case 'r':
                face = right;
                break;
            case 'f':
                face = front;
                break;
            case 'b':
                face = back;
                break;
        }

        if(moves[i+1] == 'c')
            rotate_clock(face);
        else if(moves[i+1] == 'a')
            rotate_cclock(face);
    }
}

int main(int argc, char *argv[])
{
    if( argc == 2 )
    {
        play(argv[1]);

        if(is_solved())
        {
            printf("solved\n");
            return 0;
        }
        else
        {
            printf("not solved\n");
            return 1;
        }
    }

    return 0;
}
