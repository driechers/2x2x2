#include <stdio.h>

enum piece {
    red,
    orange,
    yellow,
    green,
    blue,
    white,

    red_green,
    red_white,
    red_blue,
    red_yellow,
    green_orange,
    green_white,
    green_yellow,
    blue_white,
    blue_orange,
    blue_yellow,
    orange_white,
    orange_yellow,

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
    "red",
    "orange",
    "yellow",
    "green",
    "blue",
    "white",

    "red_green",
    "red_white",
    "red_blue",
    "red_yellow",
    "green_orange",
    "green_white",
    "green_yellow",
    "blue_white",
    "blue_orange",
    "blue_yellow",
    "orange_white",
    "orange_yellow",

    "red_green_white",
    "red_blue_white",
    "red_blue_yellow",
    "red_green_yellow",
    "orange_blue_white",
    "orange_blue_yellow",
    "orange_green_white",
    "orange_green_yellow"
};

enum piece pieces[] =
{
    red,
    orange,
    yellow,
    green,
    blue,
    white,

    red_green,
    red_white,
    red_blue,
    red_yellow,
    green_orange,
    green_white,
    green_yellow,
    blue_white,
    blue_orange,
    blue_yellow,
    orange_white,
    orange_yellow,

    red_green_white,
    red_blue_white,
    red_blue_yellow,
    red_green_yellow,
    orange_blue_white,
    orange_blue_yellow,
    orange_green_white,
    orange_green_yellow
};

enum piece pieces_solved[] =
{
    red,
    orange,
    yellow,
    green,
    blue,
    white,

    red_green,
    red_white,
    red_blue,
    red_yellow,
    green_orange,
    green_white,
    green_yellow,
    blue_white,
    blue_orange,
    blue_yellow,
    orange_white,
    orange_yellow,

    red_green_white,
    red_blue_white,
    red_blue_yellow,
    red_green_yellow,
    orange_blue_white,
    orange_blue_yellow,
    orange_green_white,
    orange_green_yellow
};

// yellow top
// green front
// orange right

enum piece *green_face[3][3] =
{
    {&pieces[red_green_yellow], &pieces[green_yellow], &pieces[orange_green_yellow]},
    {&pieces[red_green], &pieces[green], &pieces[green_orange]},
    {&pieces[red_green_white], &pieces[green_white], &pieces[orange_green_white]}
};

// yellow top
// blue front
// red right

enum piece *blue_face[3][3] =
{
    {&pieces[orange_blue_yellow], &pieces[blue_yellow], &pieces[red_blue_yellow]},
    {&pieces[blue_orange], &pieces[blue], &pieces[red_blue]},
    {&pieces[orange_blue_white], &pieces[blue_white], &pieces[red_blue_white]}
};

// blue top
// white front
// red right

enum piece *white_face[3][3] =
{
    {&pieces[orange_blue_white], &pieces[blue_white], &pieces[red_blue_white]},
    {&pieces[orange_white], &pieces[white], &pieces[red_white]},
    {&pieces[orange_green_white], &pieces[green_white], &pieces[red_green_white]}
};

// blue top
// orange front
// white right

enum piece *orange_face[3][3] =
{
    {&pieces[orange_blue_yellow], &pieces[blue_orange], &pieces[orange_blue_white]},
    {&pieces[orange_yellow], &pieces[orange], &pieces[orange_white]},
    {&pieces[orange_green_yellow], &pieces[green_orange], &pieces[orange_green_white]}
};

// blue top
// red front
// yellow right
enum piece *red_face[3][3] =
{
    {&pieces[red_blue_white], &pieces[red_blue], &pieces[red_blue_yellow]},
    {&pieces[red_white], &pieces[red], &pieces[red_yellow]},
    {&pieces[red_green_white], &pieces[red_green], &pieces[red_green_yellow]}
};

// blue top
// yellow front
// orange right
enum piece *yellow_face[3][3] =
{
    {&pieces[red_blue_yellow], &pieces[blue_yellow], &pieces[orange_blue_yellow]},
    {&pieces[red_yellow], &pieces[yellow], &pieces[orange_yellow]},
    {&pieces[red_green_yellow], &pieces[green_yellow], &pieces[orange_green_yellow]}
};

// return pointer to 2d array of pointers
enum piece *(*select_face(enum piece face))[3][3]
{
    enum piece *(*face_arr)[3][3] = &red_face;
    switch(face)
    {
        case red:
            face_arr = &red_face;
            break;
        case orange:
            face_arr = &orange_face;
            break;
        case yellow:
            face_arr = &yellow_face;
            break;
        case green:
            face_arr = &green_face;
            break;
        case blue:
            face_arr = &blue_face;
            break;
        case white:
            face_arr = &white_face;
            break;
    }

    return face_arr;
}

void rotate_clock(enum piece face)
{
    enum piece *(*face_arr)[3][3] = select_face(face);

    enum piece temp = *(*face_arr)[0][0];

    *(*face_arr)[0][0] = *(*face_arr)[2][0];
    *(*face_arr)[2][0] = *(*face_arr)[2][2];
    *(*face_arr)[2][2] = *(*face_arr)[0][2];
    *(*face_arr)[0][2] = temp;

    temp = *(*face_arr)[2][1];
    *(*face_arr)[2][1] = *(*face_arr)[1][2];
    *(*face_arr)[1][2] = *(*face_arr)[0][1];
    *(*face_arr)[0][1] = *(*face_arr)[1][0];
    *(*face_arr)[1][0] = temp;
}

void rotate_cclock(enum piece face)
{
    enum piece *(*face_arr)[3][3] = select_face(face);

    enum piece temp = *(*face_arr)[0][2];

    *(*face_arr)[0][2] = *(*face_arr)[2][2];
    *(*face_arr)[2][2] = *(*face_arr)[2][0];
    *(*face_arr)[2][0] = *(*face_arr)[0][0];
    *(*face_arr)[0][0] = temp;

    temp = *(*face_arr)[0][1];
    *(*face_arr)[0][1] = *(*face_arr)[1][2];
    *(*face_arr)[1][2] = *(*face_arr)[2][1];
    *(*face_arr)[2][1] = *(*face_arr)[1][0];
    *(*face_arr)[1][0] = temp;
}

void print_face(enum piece face)
{
    enum piece *(*face_arr)[3][3] = select_face(face);

    for(int row=0; row < 3; row++) {
        printf("%20s %14s %20s\n",
                piece_names[*(*face_arr)[row][0]],
                piece_names[*(*face_arr)[row][1]],
                piece_names[*(*face_arr)[row][2]]
                );
    }
}

int is_solved()
{
    for(int i=0; i < 26; i++)
    {
        if(pieces[i] != pieces_solved[i])
            return 0;
    }

    return 1;
}

// example rcbagaoc -> red clock, blue cclock, green cclock, orange clock

void play(char *moves)
{
    for(int i=0; moves[i]; i+=2)
    {
        enum piece face = red;
        switch(moves[i]) {
            case 'r':
                face = red;
                break;
            case 'o':
                face = orange;
                break;
            case 'y':
                face = yellow;
                break;
            case 'g':
                face = green;
                break;
            case 'b':
                face = blue;
                break;
            case 'w':
                face = white;
                break;
        }

        if(moves[i+1] == 'c')
            rotate_clock(face);
        else if(moves[i+1] == 'a')
            rotate_cclock(face);
    }
}

int main()
{
    play("rcbcocyagawcyarcbawawagc");

    char buffer[128] = "gawcwcbcraycwagcycoabara";

    play(buffer);

    if(is_solved())
    {
        printf("solved\n");
    }
    else
        printf("not solved\n");

    return 0;
}
