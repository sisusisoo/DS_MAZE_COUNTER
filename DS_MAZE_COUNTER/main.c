#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define MAZE_SIZE 11
//경로 탐색을 x,y 에서 행령에서 행을 x 열을 y로 했을때 열을 먼저+1 -1 하고 행을 +1 -1 하는 방식으로 했습니다
//수학적인 그래프로 x축을 먼저 움직였습니다.
//그결과 막다른길을 만나는건 한번뿐이고 돌아나오는 총횟수는 8번이 되었습니다. 
int failC = 0;
int flag = 0;
typedef struct Mouse
{
    short x;
    short y;
}Mouse;

typedef struct Stack
{
    Mouse data[MAX_SIZE];
    int top;
}Stack;

char maze[MAZE_SIZE][MAZE_SIZE] = {
        {'1','1','1','1','1','1','1','1','1','1'},
        {'m','1','0','1','0','0','0','1','0','1'},
        {'0','0','0','1','0','0','0','1','0','1'},
        {'0','1','0','0','0','1','1','0','0','1'},
        {'1','0','0','0','1','0','0','0','0','1'},
        {'1','0','0','0','1','0','0','0','0','1'},
        {'1','0','0','0','0','0','1','0','1','1'},
        {'1','0','1','1','1','0','1','1','0','1'},
        {'1','1','0','0','0','0','0','0','0','X'},
        {'1','1','1','1','1','1','1','1','1','1'}
};





void init(Stack* p)
{
    p->top = -1;
}

int is_full(Stack* p)
{
    return (p->top == MAX_SIZE - 1);
}

int is_empty(Stack* p)
{
    return (p->top == -1);
}

void push(Stack* p, Mouse data)
{
    if (is_full(p))
    {
        printf("스택이 꽉찼습니다\n"); return;
    }
    else
    {
        p->top++;
        p->data[p->top].x = data.x;
        p->data[p->top].y = data.y;
    }
}

Mouse pop(Stack* p)
{
    if (is_empty(p))
    {
        printf("스택이 비어있습니다\n");
        exit(1);
    }

    return p->data[(p->top)--];
}
Mouse peak(Stack* p)
{
    if (is_empty(p))
    {
        printf("스택이 비어있습니다\n");
        exit(1);
    }

    return p->data[(p->top)];
}

void FindWay(Stack* s, int x, int y)
{
    if (x < 0 || y < 0 || x > MAZE_SIZE || y > MAZE_SIZE) return;

    if (maze[x][y] != '1' && maze[x][y] != '.' && flag == 0)
    {
        flag = 1;

        Mouse tmp;
        tmp.x = x;
        tmp.y = y;

        push(s, tmp);
    }
}

int block(int x, int y) {

    //if (x < 0 || y < 0 || x > MAZE_SIZE || y > MAZE_SIZE) return;

    // printf("-%c,%c,%c,%c", maze[x + 1][y], maze[x - 1][y], maze[x][y+1], maze[x ][y-1]);


    //  printf("조건 **%d**", (maze[x + 1][y] != '1' && maze[x+1][y] != '.'));// 왜 계속  0 이 나오는 걸까??
 

        if (maze[x-1][y] != '1' && maze[x-1 ][y] != '.' && (x - 1) >= 0)
        {


            return 1;
        }
        else if (maze[x+1 ][y] != '1' && maze[x+1][y] != '.')
        {

            return 1;

        }
        else if (maze[x][y-1] != '1' && maze[x][y-1] != '.' && (y - 1) >= 0 )
        {

            return 1;

        }
        else if (maze[x][y+1] != '1' && maze[x][y+1] != '.' )
        {

            return 1;

        }
  
    else {

        return 0;//막혔다

    }


}


int main()
{
    Stack s;
    Mouse m;
    int i, j, x, y;

    init(&s);

    // 시작점 탐색
    for (i = 0; i < MAZE_SIZE; i++)
    {
        for (j = 0; j < MAZE_SIZE; j++)
        {
            if (maze[i][j] == 'm')
            {
                m.x = i;
                m.y = j;
            }
        }
    }

    printf("미로 \n");
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            if (maze[i][j] == '0') {
                printf("0");
            }
            else if (maze[i][j] == '1') {
                printf("1");
            }
            else if (maze[i][j] == '.') {
                printf(".");
            }
            else {
                printf("%c", maze[i][j]);
            }
        }
        printf("\n");
    }

    printf("\n이동 경로\n");
    printf("시작 (%d,%d) -> ", m.x, m.y);

    while (maze[m.x][m.y] != 'X')
    {
        x = m.x;
        y = m.y;

        maze[x][y] = '.'; // 방문한 곳을 표시

        // 이동 가능한 곳을 탐색
        FindWay(&s, x-1, y);
        FindWay(&s, x+1 , y);
        FindWay(&s, x, y-1 );
        FindWay(&s, x, y+1);

        if (is_empty(&s))
        {
            printf("이동경로를 찾을 수 없습니다. 실패 \n");
            return 0;
        }
        else if (block(x, y) == 0)//현재 좌표를 block =0 이아닐때는 ->push만  제대로 실행이 안됨 
        {
            failC++;
            m = pop(&s); // 현재 좌표를 변경
            printf("(%d,%d) -> ", m.x, m.y);
        }
        else if (block(x, y) != 0)//추후 삭제 검토---------------
        {
            m = peak(&s); // 현재 좌표를 변경
            printf("(%d,%d) -> ", m.x, m.y);
        }


        flag = 0;
        printf(" \n");
        for (int i = 0; i < MAZE_SIZE; i++) {
            for (int j = 0; j < MAZE_SIZE; j++) {
                if (maze[i][j] == '0') {
                    printf("0");
                }
                else if (maze[i][j] == '1') {
                    printf("1");
                }
                else if (maze[i][j] == '.') {
                    printf(".");
                }
                else {
                    printf("%c", maze[i][j]);
                }
            }
            printf("\n");
        }
        printf("fail Counter: %d \n", failC);
        printf("-------------------------------------------\n");
    }
    printf("\n");
    printf("fail Counter: %d \n",failC);
    printf("도착\n");
    printf("탐색 성공\n");

    return 0;
}