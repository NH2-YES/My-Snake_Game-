#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>

#define WIDTH 20
#define HEIGHT 10
#define FOOD '*'

typedef enum{
    STOP = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

struct Point {
    int x;
    int y;
};

struct Snake{
    struct Point body[100];
    int lenght;
    Direction direction;
};

struct Food{
    struct Point position;
};

void draw_board(struct Snake snake, struct Food food);
void input(struct Snake *snake);
void logic(struct Snake *snake, struct Food *food);
void generateFood(struct Food *food, struct Snake *snake);
int collision(struct Snake snake);

int main(){
    struct Snake snake;
    struct Food food;

    snake.lenght=1;
    snake.body[0].x = WIDTH/2;
    snake.body[0].y = HEIGHT/2;
    snake.direction = RIGHT;

    generateFood(&food,&snake);

    while(1){
        draw_board(snake, food);
        input(&snake);
        logic(&snake, &food);

        if(collision(snake)){
            printf("Game over! Score: %d\n", snake.lenght-1);
            break;
        }
        Sleep(200);
    }
    return 0;
}

void draw_board(struct Snake snake, struct Food food){
    system("cls");

    for(int y=0; y<HEIGHT; y++){
        for(int x=0; x<WIDTH; x++){
            if(x==0 || x==WIDTH-1 || y==0 || y==HEIGHT-1){
                printf("M");
            } else if(x==food.position.x && y==food.position.y){
                printf("%c", FOOD);
            }else{
                int issnakebody = 0;
                for(int i=0; i<snake.lenght; i++){
                    if(snake.body[i].x == x && snake.body[i].y == y){
                        printf("O");
                        issnakebody = 1;
                        break;
                    }
                }
                if(!issnakebody){
                    printf(" ");
                }
            }
        }
        printf("\n");
    }

}

void input(struct Snake *snake){
    if(_kbhit()){
        switch(_getch()){
            case 72:
            if(snake->direction!=DOWN) snake->direction = UP;
            break;
            case 80:
            if(snake->direction!=UP) snake->direction = DOWN;
            break;
            case 75:
            if(snake->direction!=RIGHT) snake->direction = LEFT;
            break;
            case 77:
            if(snake->direction!=LEFT) snake->direction = RIGHT;
            break;

        }
    }
}

void logic(struct Snake *snake, struct Food *food){
    for(int i = snake->lenght-1; i>0; i--){
        snake->body[i]=snake->body[i-1];
    }

    switch(snake->direction){
        case UP:
            snake->body[0].y--;
            break;
        case DOWN:
            snake->body[0].y++;
            break;
        case LEFT:
            snake->body[0].x--;
            break;
        case RIGHT:
            snake->body[0].x++;
            break;    
    }

    if(snake->body[0].x==food->position.x && snake->body[0].y==food->position.y){
        snake->lenght++;
        generateFood(food,snake);
    }
}      

void generateFood(struct Food *food, struct Snake *snake){
    int valid= 0;
    while(!valid){
    food->position.x = rand() % (WIDTH-2)+1;
    food->position.y = rand() % (HEIGHT-2)+1;

    valid=1;

    for(int i=0; i<snake->lenght; i++){
        if(snake->body[i].x==food->position.x && snake->body[i].y==food->position.y){
            valid=0;
            break;
        }
    }

    }

}
int collision(struct Snake snake){
    if(snake.body[0].x <=0 || snake.body[0].x >=WIDTH-1 || snake.body[0].y<=0 || snake.body[0].y>=HEIGHT-1){
        return 1;

    }
    for(int i=1; i<snake.lenght; i++){
        if(snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y){
            return 1;
                
        }
        
    }

        return 0;  

    } 


  