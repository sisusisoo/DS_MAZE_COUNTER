#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define MAZE_SIZE 11
//��� Ž���� x,y ���� ��ɿ��� ���� x ���� y�� ������ ���� ����+1 -1 �ϰ� ���� +1 -1 �ϴ� ������� �߽��ϴ�
//�������� �׷����� x���� ���� ���������ϴ�.
//�װ�� ���ٸ����� �����°� �ѹ����̰� ���Ƴ����� ��Ƚ���� 8���� �Ǿ����ϴ�. 
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
        printf("������ ��á���ϴ�\n"); return;
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
        printf("������ ����ֽ��ϴ�\n");
        exit(1);
    }

    return p->data[(p->top)--];
}
Mouse peak(Stack* p)
{
    if (is_empty(p))
    {
        printf("������ ����ֽ��ϴ�\n");
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


    //  printf("���� **%d**", (maze[x + 1][y] != '1' && maze[x+1][y] != '.'));// �� ���  0 �� ������ �ɱ�??
 

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

        return 0;//������

    }


}


int main()
{
    Stack s;
    Mouse m;
    int i, j, x, y;

    init(&s);

    // ������ Ž��
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

    printf("�̷� \n");
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

    printf("\n�̵� ���\n");
    printf("���� (%d,%d) -> ", m.x, m.y);

    while (maze[m.x][m.y] != 'X')
    {
        x = m.x;
        y = m.y;

        maze[x][y] = '.'; // �湮�� ���� ǥ��

        // �̵� ������ ���� Ž��
        FindWay(&s, x-1, y);
        FindWay(&s, x+1 , y);
        FindWay(&s, x, y-1 );
        FindWay(&s, x, y+1);

        if (is_empty(&s))
        {
            printf("�̵���θ� ã�� �� �����ϴ�. ���� \n");
            return 0;
        }
        else if (block(x, y) == 0)//���� ��ǥ�� block =0 �̾ƴҶ��� ->push��  ����� ������ �ȵ� 
        {
            failC++;
            m = pop(&s); // ���� ��ǥ�� ����
            printf("(%d,%d) -> ", m.x, m.y);
        }
        else if (block(x, y) != 0)//���� ���� ����---------------
        {
            m = peak(&s); // ���� ��ǥ�� ����
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
    printf("����\n");
    printf("Ž�� ����\n");

    return 0;
}