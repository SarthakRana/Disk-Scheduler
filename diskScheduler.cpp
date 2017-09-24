#include <iostream>
#include <graphics.h>
#include <ctime>
#include <cstdio>
#include <conio.h>
#define mx getmaxx()
#define my getmaxy()

using namespace std;

long difference(long a,long b){
    return (a>b)?(a-b):(b-a);
}

int takeinput(int x,int y)
{
    char ch, str[100];
    int i=0;
    str[0]='\0';
    while(1)
    {
        ch=getch();
        if(ch==13) break;
        if(ch==8){i--; if(i<0)i=0; str[i]='\0';}
        else if(ch>='0' && ch<='9') {str[i++]=ch; str[i]='\0';}
        setfillstyle(1,BLACK);
        bar(x,y,mx,y+20);
        setcolor(WHITE);
        outtextxy(x,y,str);
    }
    return atoi(str);
}

class DiskScheduling{
    char *str, ch, s[100], val;
    long cyl, req, head, direc;
    int *a, *b, *c, count, x, d, pos, mi, prev;
    int left, right, top, bottom;
    int topgap, leftgap, bottomgap, linegap;
public:
    void initialize(string , int , int , int , int );
    void firstmenu(int );
    void start();
    void secondmenu(int );
    void drawBoundries(char * );
    void FCFS();
    void SSTF();
    void SCAN();
    void CSCAN();
    void LOOK();
    void CLOOK();
};
void DiskScheduling :: initialize(string work, int cyl = 1000, int req = 10, int head = 400, int direc = 0){
    this->cyl = cyl;
    this->req = req;
    this->head = head;
    this->direc = direc;
    str = new char[100];
    a = new int[req];
    b = new int[100];
    c = new int[100];

    topgap = 150;
    leftgap = 200;
    bottomgap = 100;
    linegap = 30;

    if(work == "random"){
        srand(time(NULL));
        for(int i=0; i<req; i++)
            a[i] = rand()%cyl;
    }
    else{
        cleardevice();
        settextstyle(4,0,3);
        outtextxy(mx/6,100,"POSITION INFO");

        settextstyle(3,0,3);
        for(int i = 0; i<req; i++){
            setfillstyle(1,BLACK);
            bar(mx/3,250,mx,300);
            sprintf(str,"Enter Position %ld : ",i+1);
            outtextxy(mx/3,250,str);
            a[i] = takeinput(3*mx/4,250);
        }
    }
}

void DiskScheduling :: firstmenu(int ch)
{
    setbkcolor(LIGHTBLUE);
    setfillstyle(WIDE_DOT_FILL,LIGHTGRAY);
    floodfill(1,1,WHITE);

    settextstyle(0,0,2);
    outtextxy(mx/8,my/6,"Select an option to continue : ");
    settextstyle(0,0,4);

    if(ch==0)
    {
        setfillstyle(1,WHITE);
        bar(200,4*my/12,900,4*my/12 + 40);
        setfillstyle(1,LIGHTBLUE);
        bar(200,6*my/12,900,6*my/12 + 40);
        bar(200,8*my/12,900,8*my/12 + 40);

        setbkcolor(WHITE);
        setcolor(BLUE);
        outtextxy(mx/6,4*my/12,"1. USE RANDOM VALUES");
        setbkcolor(LIGHTBLUE);
        setcolor(WHITE);
        outtextxy(mx/6,6*my/12,"2. INPUT NEW VALUES");
        outtextxy(mx/6,8*my/12,"3. EXIT");
    }

    if(ch==1)
    {
        setfillstyle(1,WHITE);
        bar(200,6*my/12,900,6*my/12 + 40);
        setfillstyle(1,LIGHTBLUE);
        bar(200,4*my/12,900,4*my/12 + 40);
        bar(200,8*my/12,900,8*my/12 + 40);

        setbkcolor(WHITE);
        setcolor(BLUE);
        outtextxy(mx/6,6*my/12,"2. INPUT NEW VALUES");
        setbkcolor(LIGHTBLUE);
        setcolor(WHITE);
        outtextxy(mx/6,4*my/12,"1. USE RANDOM VALUES");
        outtextxy(mx/6,8*my/12,"3. EXIT");
    }

    if(ch==2)
    {
        setfillstyle(1,WHITE);
        bar(200,8*my/12,900,8*my/12 + 40);
        setfillstyle(1,LIGHTBLUE);
        bar(200,4*my/12,900,4*my/12 + 40);
        bar(200,6*my/12,900,6*my/12 + 40);

        setbkcolor(WHITE);
        setcolor(BLUE);
        outtextxy(mx/6,8*my/12,"3. EXIT");
        setbkcolor(LIGHTBLUE);
        setcolor(WHITE);
        outtextxy(mx/6,4*my/12,"1. USE RANDOM VALUES");
        outtextxy(mx/6,6*my/12,"2. INPUT NEW VALUES");

    }
}

void DiskScheduling :: secondmenu(int ch)
{
    setbkcolor(LIGHTBLUE);
    setfillstyle(WIDE_DOT_FILL,LIGHTGRAY);
    floodfill(1,1,WHITE);

    settextstyle(0,0,2);
    outtextxy(mx/8,my/6,"Select an option to continue : ");
    settextstyle(0,0,3);

    if(ch==0)
    {
        setfillstyle(1,WHITE);
        bar(450,4*my/12,650,4*my/12 + 40);
        setfillstyle(1,LIGHTBLUE);
        bar(450,5*my/12,650,5*my/12 + 40);
        bar(450,6*my/12,650,6*my/12 + 40);
        bar(450,7*my/12,650,7*my/12 + 40);
        bar(450,8*my/12,650,8*my/12 + 40);
        bar(450,9*my/12,650,9*my/12 + 40);
        bar(450,10*my/12,650,10*my/12 + 40);

        setbkcolor(WHITE);
        setcolor(BLUE);
        outtextxy(mx/3,4*my/12,"1. FCFS");
        setbkcolor(LIGHTBLUE);
        setcolor(WHITE);
        outtextxy(mx/3,5*my/12,"2. SSTF");
        outtextxy(mx/3,6*my/12,"3. SCAN");
        outtextxy(mx/3,7*my/12,"4. CSCAN");
        outtextxy(mx/3,8*my/12,"5. LOOK");
        outtextxy(mx/3,9*my/12,"6. CLOOK");
        outtextxy(mx/3,10*my/12,"7. EXIT");
    }

    if(ch==1)
    {
        setfillstyle(1,WHITE);
        bar(450,5*my/12,650,5*my/12 + 40);
        setfillstyle(1,LIGHTBLUE);
        bar(450,4*my/12,650,4*my/12 + 40);
        bar(450,6*my/12,650,6*my/12 + 40);
        bar(450,7*my/12,650,7*my/12 + 40);
        bar(450,8*my/12,650,8*my/12 + 40);
        bar(450,9*my/12,650,9*my/12 + 40);
        bar(450,10*my/12,650,10*my/12 + 40);

        setbkcolor(WHITE);
        setcolor(BLUE);
        outtextxy(mx/3,5*my/12,"2. SSTF");
        setbkcolor(LIGHTBLUE);
        setcolor(WHITE);
        outtextxy(mx/3,4*my/12,"1. FCFS");
        outtextxy(mx/3,6*my/12,"3. SCAN");
        outtextxy(mx/3,7*my/12,"4. CSCAN");
        outtextxy(mx/3,8*my/12,"5. LOOK");
        outtextxy(mx/3,9*my/12,"6. CLOOK");
        outtextxy(mx/3,10*my/12,"7. EXIT");
    }

    if(ch==2)
    {
        setfillstyle(1,WHITE);
        bar(450,6*my/12,650,6*my/12 + 40);
        setfillstyle(1,LIGHTBLUE);
        bar(450,4*my/12,650,4*my/12 + 40);
        bar(450,5*my/12,650,5*my/12 + 40);
        bar(450,7*my/12,650,7*my/12 + 40);
        bar(450,8*my/12,650,8*my/12 + 40);
        bar(450,9*my/12,650,9*my/12 + 40);
        bar(450,10*my/12,650,10*my/12 + 40);

        setbkcolor(WHITE);
        setcolor(BLUE);
        outtextxy(mx/3,6*my/12,"3. SCAN");
        setbkcolor(LIGHTBLUE);
        setcolor(WHITE);
        outtextxy(mx/3,4*my/12,"1. FCFS");
        outtextxy(mx/3,5*my/12,"2. SSTF");
        outtextxy(mx/3,7*my/12,"4. CSCAN");
        outtextxy(mx/3,8*my/12,"5. LOOK");
        outtextxy(mx/3,9*my/12,"6. CLOOK");
        outtextxy(mx/3,10*my/12,"7. EXIT");
    }

    if(ch==3)
    {
        setfillstyle(1,WHITE);
        bar(450,7*my/12,650,7*my/12 + 40);
        setfillstyle(1,LIGHTBLUE);
        bar(450,4*my/12,650,4*my/12 + 40);
        bar(450,5*my/12,650,5*my/12 + 40);
        bar(450,6*my/12,650,6*my/12 + 40);
        bar(450,8*my/12,650,8*my/12 + 40);
        bar(450,9*my/12,650,9*my/12 + 40);
        bar(450,10*my/12,650,10*my/12 + 40);

        setbkcolor(WHITE);
        setcolor(BLUE);
        outtextxy(mx/3,7*my/12,"4. CSCAN");
        setbkcolor(LIGHTBLUE);
        setcolor(WHITE);
        outtextxy(mx/3,4*my/12,"1. FCFS");
        outtextxy(mx/3,5*my/12,"2. SSTF");
        outtextxy(mx/3,6*my/12,"3. SCAN");
        outtextxy(mx/3,8*my/12,"5. LOOK");
        outtextxy(mx/3,9*my/12,"6. CLOOK");
        outtextxy(mx/3,10*my/12,"7. EXIT");
    }

    if(ch==4)
    {
        setfillstyle(1,WHITE);
        bar(450,8*my/12,650,8*my/12 + 40);
        setfillstyle(1,LIGHTBLUE);
        bar(450,4*my/12,650,4*my/12 + 40);
        bar(450,5*my/12,650,5*my/12 + 40);
        bar(450,6*my/12,650,6*my/12 + 40);
        bar(450,7*my/12,650,7*my/12 + 40);
        bar(450,9*my/12,650,9*my/12 + 40);
        bar(450,10*my/12,650,10*my/12 + 40);

        setbkcolor(WHITE);
        setcolor(BLUE);
        outtextxy(mx/3,8*my/12,"5. LOOK");
        setbkcolor(LIGHTBLUE);
        setcolor(WHITE);
        outtextxy(mx/3,4*my/12,"1. FCFS");
        outtextxy(mx/3,5*my/12,"2. SSTF");
        outtextxy(mx/3,6*my/12,"3. SCAN");
        outtextxy(mx/3,7*my/12,"4. CSCAN");
        outtextxy(mx/3,9*my/12,"6. CLOOK");
        outtextxy(mx/3,10*my/12,"7. EXIT");
    }

    if(ch==5)
    {
        setfillstyle(1,WHITE);
        bar(450,9*my/12,650,9*my/12 + 40);
        setfillstyle(1,LIGHTBLUE);
        bar(450,4*my/12,650,4*my/12 + 40);
        bar(450,5*my/12,650,5*my/12 + 40);
        bar(450,6*my/12,650,6*my/12 + 40);
        bar(450,7*my/12,650,7*my/12 + 40);
        bar(450,8*my/12,650,8*my/12 + 40);
        bar(450,10*my/12,650,10*my/12 + 40);

        setbkcolor(WHITE);
        setcolor(BLUE);
        outtextxy(mx/3,9*my/12,"6. CLOOK");
        setbkcolor(LIGHTBLUE);
        setcolor(WHITE);
        outtextxy(mx/3,4*my/12,"1. FCFS");
        outtextxy(mx/3,5*my/12,"2. SSTF");
        outtextxy(mx/3,6*my/12,"3. SCAN");
        outtextxy(mx/3,7*my/12,"4. CSCAN");
        outtextxy(mx/3,8*my/12,"5. LOOK");
        outtextxy(mx/3,10*my/12,"7. EXIT");
    }

    if(ch==6)
    {
        setfillstyle(1,WHITE);
        bar(450,10*my/12,650,10*my/12 + 40);
        setfillstyle(1,LIGHTBLUE);
        bar(450,4*my/12,650,4*my/12 + 40);
        bar(450,5*my/12,650,5*my/12 + 40);
        bar(450,6*my/12,650,6*my/12 + 40);
        bar(450,7*my/12,650,7*my/12 + 40);
        bar(450,8*my/12,650,8*my/12 + 40);
        bar(450,9*my/12,650,9*my/12 + 40);

        setbkcolor(WHITE);
        setcolor(BLUE);
        outtextxy(mx/3,10*my/12,"7. EXIT");
        setbkcolor(LIGHTBLUE);
        setcolor(WHITE);
        outtextxy(mx/3,4*my/12,"1. FCFS");
        outtextxy(mx/3,5*my/12,"2. SSTF");
        outtextxy(mx/3,6*my/12,"3. SCAN");
        outtextxy(mx/3,7*my/12,"4. CSCAN");
        outtextxy(mx/3,8*my/12,"5. LOOK");
        outtextxy(mx/3,9*my/12,"6. CLOOK");

    }
}

void DiskScheduling :: drawBoundries(char *scheduling){

        //  Printing the type of the Scheduling
    settextstyle(4,0,5);
    outtextxy(mx/2 - 60,my/48,scheduling);

    count = 0;
    x = head;
    d = 0;
    pos = 0;

                //  Requests Representation
    settextstyle(3,0,1);
    setlinestyle(3,0,1);
    outtextxy(10, topgap-20, "Rep.");
    outtextxy(leftgap/2 - 30, topgap-20, "Request");

                //  Boundries of the graph

    settextstyle(3,0,1);
    setlinestyle(3,0,3);
        //  horizontal line
    line(leftgap-30, topgap, leftgap+(cyl-1)+30, topgap);
        //  leftmost line
    sprintf(str, "0");
    outtextxy(leftgap-5, topgap-50, str);
    line(leftgap,topgap-30,leftgap,my - bottomgap);
        //  rightmost line
    sprintf(str, "%d", cyl-1);
    outtextxy(leftgap+(cyl-1)-5, topgap-50, str);
    line(leftgap+(cyl-1),topgap-30,leftgap+(cyl-1),my - bottomgap);
}

void DiskScheduling :: start(){
    do{
        cleardevice();
        int i = 0;
        do
        {
            secondmenu(i);
            ch=getch();
            if(ch==13) break;
            if(ch==27) break;
            if(ch==KEY_UP) i--;
            if(ch==KEY_DOWN) i++;
            if(i == -1) i=6;
            if(i == 7) i=0;
        }while(1);

        setbkcolor(BLACK);

        val = 1;
        switch(i){
            case 0: FCFS();
                    break;

            case 1: SSTF();
                    break;

            case 2: SCAN();
                    break;

            case 3: CSCAN();
                    break;

            case 4: LOOK();
                    break;

            case 5: CLOOK();
                    break;

            case 6: val = 0;
                    break;
        }
    }while(val == 1);
}
void DiskScheduling :: FCFS(){
    cleardevice();

    drawBoundries("FCFS");

        //  Printing all the lines and requests
    settextstyle(1,0,1);
    for(int i=0;i<req;i++){
        x -= a[i];
        if(x < 0)
            x =- x;
        count += x;
        x = a[i];

        setlinestyle(3,0,1);

        sprintf(str, "%d", i+1);
        outtextxy(leftgap+a[i]-5, topgap-30, str);

        line(leftgap+a[i],topgap,leftgap+a[i],my - bottomgap);
        setlinestyle(0,0,1);
        if(i == 0)
            prev = head;
        else
            prev = a[i-1];

            //  Printing requests on the left side
        line(leftgap+prev, i*linegap+topgap, leftgap+a[i], i*linegap+topgap+linegap);
        sprintf(str,"%d \t -- \t %ld",i+1, a[i]);
        outtextxy(leftgap/20,i*linegap+topgap+10,str);

        getch();
        delay(50);
    }
    settextstyle(4,0,3);
    sprintf(str,"Total Head Movement : %ld Cylinders",count);
    outtextxy(mx/4,9*my/10,str);
    getch();
}
void DiskScheduling :: SSTF(){
    cleardevice();

    drawBoundries("SSTF");

        //  Printing all the lines and requests
    for(int i = 0; i<req; i++)
        b[i] = a[i];

    for(int i = 0; i<req; i++){
        mi = difference(b[i],x);
        pos = i;
        for(int j=i;j<req;j++)
            if(mi > difference(x,b[j])){
                pos = j;
                mi = difference(x,b[j]);
            }
        count += difference(x,b[pos]);
        x = b[pos];
        b[pos] = b[i];
        b[i] = x;
    }

    settextstyle(1,0,1);
    for(int i = 0; i<req; i++){
        setlinestyle(3,0,1);
        line(leftgap+b[i], topgap, leftgap+b[i], my - bottomgap);
        sprintf(str, "%d", i+1);
        outtextxy(leftgap+b[i]-5, topgap-30, str);

        setlinestyle(1,0,1);
        if(i == 0)
            prev = head;
        else
            prev = b[i-1];
        line(leftgap+prev,i*linegap+topgap,leftgap+b[i],i*linegap+topgap+linegap);
        sprintf(str,"%d \t -- \t %ld",i+1, b[i]);
        outtextxy(leftgap/20,i*linegap+topgap+10,str);

        getch();
    }

    settextstyle(4,0,3);
    sprintf(str,"Total Head Movement : %ld Cylinders",count);
    outtextxy(mx/4,9*my/10,str);
    getch();
}
void DiskScheduling :: SCAN()
{
    cleardevice();

    drawBoundries("SCAN");

    for(int i = 0; i<req; i++)
        b[i] = a[i];

    if(direc == 0){
        for(int i = 0; i<req; i++)
            for(int j = 0; j<req-i-1; j++)
                if(b[j] > b[j+1]){
                    x = b[j];
                    b[j] = b[j+1];
                    b[j+1] = x;
                }
        for(int i = 0; i<req; i++)
            if(b[i] < head)
                pos++;
        for(int i = 0; i<pos; i++)
            for(int j = 0; j < pos-i-1; j++)
                if(b[j] < b[j+1]){
                    x = b[j];
                    b[j] = b[j+1];
                    b[j+1] = x;
                }
        x = head;
        for(int i=0; i<pos; i++){
            count += difference(b[i],x);
            x = b[i];
            c[d++] = x;
        }
        count += difference(x,0);
        x = 0;
        c[d++] = x;
        for(int i = pos; i<req; i++){
            count += difference(b[i],x);
            x = b[i];
            c[d++] = x;
        }
    }
    else if(direc == 1){
        for(int i = 0; i<req; i++)
            for(int j = 0; j<req-i-1; j++)
                if(b[j] < b[j+1]){
                    x = b[j];
                    b[j] = b[j+1];
                    b[j+1] = x;
                }
        for(int i = 0; i<req; i++)
            if(b[i] > head)
                pos++;
        for(int i = 0; i<pos; i++)
            for(int j = 0; j < pos-i-1; j++)
                if(b[j] > b[j+1]){
                    x = b[j];
                    b[j] = b[j+1];
                    b[j+1] = x;
                }
        x = head;
        for(int i=0; i<pos; i++){
            count += difference(b[i],x);
            x = b[i];
            c[d++] = x;
        }
        count += difference(x,cyl-1);
        x = cyl-1;
        c[d++] = x;
        for(int i = pos; i<req; i++){
            count += difference(b[i],x);
            x = b[i];
            c[d++] = x;
        }
    }


    settextstyle(1,0,1);
    for(int i = 0; i<d; i++)
    {
        setlinestyle(3,0,1);        //dotted line
        line(leftgap+c[i],topgap,leftgap+c[i],my-bottomgap);
        sprintf(str,"%d",i+1);
        outtextxy(leftgap+c[i]-5,topgap-30,str);

        setlinestyle(0,0,1);        //for making solid line
        if(i==0)
            prev = head;
        else
            prev = c[i-1];
        line(leftgap+prev,i*linegap+topgap,leftgap+c[i],i*linegap+topgap+linegap);
        sprintf(str,"%d \t -- \t %ld",i+1,c[i]);
        outtextxy(leftgap/20,i*linegap+topgap+10,str);

        getch();
    }

    settextstyle(4,0,3);
    sprintf(str,"Total Head Movement : %ld Cylinders",count);
    outtextxy(mx/4,9*my/10,str);
    getch();
}
void DiskScheduling :: CSCAN()
{
    cleardevice();

    drawBoundries("CSCAN");

    for(int i = 0; i<req; i++)
        b[i] = a[i];

    if(direc == 0){
        for(int i = 0; i<req; i++)
            for(int j = 0; j<req-i-1; j++)
                if(b[j] < b[j+1]){
                    x = b[j];
                    b[j] = b[j+1];
                    b[j+1] = x;
                }
        for(int i = 0; i<req; i++)
            if(b[i] > head)
                pos++;
        x = head;
        for(int i = pos; i<req; i++){
            count += difference(x,b[i]);
            x = b[i];
            c[d++] = x;
        }
        count += difference(0,x);
        x = 0;
        c[d++] = x;
        c[d++] = cyl-1;
        x = cyl-1;
        count += cyl-1;
        for(int i = 0; i<pos; i++){
            count += difference(x,b[i]);
            x = b[i];
            c[d++] = x;
        }
    }
    else if(direc == 1){
        for(int i = 0; i<req; i++)
            for(int j = 0; j<req-i-1; j++)
                if(b[j] > b[j+1]){
                    x = b[j];
                    b[j] = b[j+1];
                    b[j+1] = x;
                }
        for(int i = 0; i<req; i++)
            if(b[i] < head)
                pos++;
        x = head;
        for(int i = pos; i<req; i++){
            count += difference(x,b[i]);
            x = b[i];
            c[d++] = x;
        }
        count += difference(cyl-1,x);
        x = cyl-1;
        c[d++] = x;
        c[d++] = 0;
        x = 0;
        count += cyl-1;
        for(int i = 0; i<pos; i++){
            count += difference(x,b[i]);
            x = b[i];
            c[d++] = x;
        }
    }


    settextstyle(1,0,1);
    for(int i = 0; i<d; i++)
    {
        setlinestyle(3,0,1);
        line(leftgap+c[i],topgap,leftgap+c[i],my-bottomgap);
        sprintf(str,"%d",i+1);
        outtextxy(leftgap+c[i]-5,topgap-30,str);
        setlinestyle(0,0,1);
        if(i == 0)
            prev = head;
        else
            prev = c[i-1];
        line(leftgap+prev,i*linegap+topgap,leftgap+c[i],i*linegap+topgap+linegap);
        sprintf(str,"%d \t -- \t %ld",i+1,c[i]);
        outtextxy(leftgap/20,i*linegap+topgap+10,str);
        getch();
    }

    settextstyle(4,0,3);
    sprintf(str,"Total Head Movement : %ld Cylinders",count);
    outtextxy(mx/4,9*my/10,str);
    getch();
}
void DiskScheduling :: LOOK(){
    cleardevice();

    drawBoundries("LOOK");

    for(int i = 0; i<req; i++)
        b[i] = a[i];

    if(direc == 0){
        for(int i = 0; i<req; i++)
            for(int j = 0; j<req-i-1; j++)
                if(b[j] > b[j+1]){
                    x = b[j];
                    b[j] = b[j+1];
                    b[j+1] = x;
                }
        for(int i = 0; i<req; i++)
            if(b[i] < head)
                pos++;
        for(int i = 0; i<pos; i++)
            for(int j = 0; j<pos-i-1; j++)
                if(b[j] < b[j+1]){
                    x = b[j];
                    b[j] = b[j+1];
                    b[j+1] = x;
                }
        x = head;
        for(int i = 0; i<pos; i++){
            count += difference(b[i],x);
            x = b[i];
            c[d++] = x;
        }
        for(int i = pos; i<req; i++){
            count += difference(b[i],x);
            x = b[i];
            c[d++] = x;
        }
    }
    else if(direc == 1){
        for(int i = 0; i<req; i++)
            for(int j = 0; j<req-i-1; j++)
                if(b[j] > b[j+1]){
                    x = b[j];
                    b[j] = b[j+1];
                    b[j+1] = x;
                }
        for(int i = 0; i<req; i++)
            if(b[i] < head)
                pos++;
        for(int i = 0; i<pos; i++)
            for(int j = 0; j<pos-i-1; j++)
                if(b[j] < b[j+1]){
                    x = b[j];
                    b[j] = b[j+1];
                    b[j+1] = x;
                }
        x = head;
        for(int i = pos; i<req; i++){
            count += difference(b[i],x);
            x = b[i];
            c[d++] = x;
        }
        for(int i = 0; i<pos; i++){
            count += difference(b[i],x);
            x = b[i];
            c[d++] = x;
        }

    }


    settextstyle(1,0,1);
    for(int i = 0; i<d; i++){

        setlinestyle(3,0,1);
        line(leftgap+c[i], topgap, leftgap+c[i], my - bottomgap);
        sprintf(str, "%d", i+1);
        outtextxy(leftgap+c[i]-5, topgap-30, str);

        setlinestyle(1,0,1);
        if(i == 0)
            prev = head;
        else
            prev = c[i-1];
        line(leftgap+prev,i*linegap+topgap,leftgap+c[i],i*linegap+topgap+linegap);
        sprintf(str,"%d \t -- \t %ld",i+1, c[i]);
        outtextxy(leftgap/20,i*linegap+topgap+10,str);

        getch();
    }

    settextstyle(4,0,3);
    sprintf(str,"Total Head Movement : %ld Cylinders",count);
    outtextxy(mx/4,9*my/10,str);
    getch();
}
void DiskScheduling :: CLOOK(){
    cleardevice();

    drawBoundries("CLOOK");

    for(int i = 0; i<req; i++)
        b[i] = a[i];


    if(direc == 0){
        for(int i = 0; i<req; i++)
            for(int j = 0; j<req-i-1; j++)
                if(b[j] > b[j+1]){
                    x = b[j];
                    b[j] = b[j+1];
                    b[j+1] = x;
                }
        for(int i = 0; i<req; i++)
            if(b[i] < head)
                pos++;
        for(int i = 0; i<pos; i++)
            for(int j = 0; j<pos-i-1; j++)
                if(b[j] < b[j+1]){
                    x = b[j];
                    b[j] = b[j+1];
                    b[j+1] = x;
                }
        for(int i = pos; i<req; i++)
            for(int j = pos; j<req-i-1+pos; j++)
                if(b[j] < b[j+1]){
                    x = b[j];
                    b[j] = b[j+1];
                    b[j+1] = x;
                }
        x = head;
        for(int i = 0; i<pos; i++){
            count += difference(b[i],x);
            x = b[i];
            c[d++] = x;
        }
        for(int i = pos; i<req; i++){
            count += difference(b[i],x);
            x = b[i];
            c[d++] = x;
        }
    }
    else if(direc == 1){
        for(int i = 0; i<req; i++)
            for(int j = 0; j<req-i-1; j++)
                if(b[j] > b[j+1]){
                    x = b[j];
                    b[j] = b[j+1];
                    b[j+1] = x;
                }
        for(int i = 0; i<req; i++)
            if(b[i] < head)
                pos++;
        x = head;
        for(int i = pos; i<req; i++){
            count += difference(b[i],x);
            x = b[i];
            c[d++] = x;
        }
        for(int i = 0; i<pos; i++){
            count += difference(b[i],x);
            x = b[i];
            c[d++] = x;
        }

    }


    settextstyle(1,0,1);
    for(int i = 0; i<d; i++){

        setlinestyle(3,0,1);
        line(leftgap+c[i], topgap, leftgap+c[i], my - bottomgap);
        sprintf(str, "%d", i+1);
        outtextxy(leftgap+c[i]-5, topgap-30, str);

        setlinestyle(1,0,1);
        if(i == 0)
            prev = head;
        else
            prev = c[i-1];
        line(leftgap+prev,i*linegap+topgap,leftgap+c[i],i*linegap+topgap+linegap);
        sprintf(str,"%d \t -- \t %ld",i+1, c[i]);
        outtextxy(leftgap/20,i*linegap+topgap+10,str);

        getch();
    }

    settextstyle(4,0,3);
    sprintf(str,"Total Head Movement : %ld Cylinders",count);
    outtextxy(mx/4,9*my/10,str);
    getch();
}

void frontPage(){
    cleardevice();
    setbkcolor(CYAN);
    setfillstyle(WIDE_DOT_FILL,LIGHTGRAY);
    floodfill(1,1,WHITE);
    settextstyle(0,0,3);
    setcolor(LIGHTGRAY);
    outtextxy(mx/4 - 50,my/8,"Disk Scheduling Analysis Software");
    int var = 30;
    for(int i = 0; i<3; i++, var--)
        line(mx/4 + 50, my/8 + var, 3*mx/4 - 50, my/8 + var);
    settextstyle(0,0,2);
    setcolor(BLACK);
    int left = mx/4, right = 3*mx/4, top = my/4 - 30, bottom = 3*my/4 - 30;
    for(int i = 0; i<5; i++,left--,right++,top--,bottom++)
        rectangle(left,top,right,bottom);
    setcolor(LIGHTGRAY);
    left = mx/4;
    right = 3*mx/4;
    top = my/4 - 30;
    bottom = 3*my/4 - 30;
    readimagefile("main.jpg", left, top, right, bottom);
    outtextxy(mx/4,18*my/24,"Created By:-");
    outtextxy(mx/2,19*my/24,"Akul Gupta (15103032)");
    outtextxy(mx/2,20*my/24,"Dhruv Mittal (15103038)");
    outtextxy(mx/2,21*my/24,"Harsh Gupta (15103039)");
    outtextxy(mx/2,22*my/24,"Sarthak Rana (15103051)");
    outtextxy(mx/2,23*my/24,"Shubham Agarwal (15103054)");
    getch();
    setcolor(WHITE);
    setbkcolor(BLACK);
}

int main(){
    int gdriver = VGA, gmode = VGAHI;
    long cyl, req, head, direc, i;
    char ch;

    initgraph(&gdriver, &gmode, "");
    initwindow(1360,700);
    frontPage();

    DiskScheduling DS;

    do{
        cleardevice();
        settextstyle(4,0,3);

        i=0;
        do{
            DS.firstmenu(i);
            ch=getch();
            if(ch==13) break;
            if(ch==27) exit(0);
            if(ch == KEY_UP) i--;
            if(ch == KEY_DOWN) i++;
            if(i == -1) i=2;
            if(i == 3) i=0;
        }while(1);

        setbkcolor(BLACK);

        switch(i){
            case 0: DS.initialize("random");
                    break;
            case 1: cleardevice();
                    settextstyle(3,0,3);

                    outtextxy(mx/8,200,"Enter the number of cylinders : ");
                    cyl = takeinput(3*mx/4,200);

                    outtextxy(mx/8,300,"Enter the number of requests :");
                    req = takeinput(3*mx/4,300);

                    outtextxy(mx/8,400,"Enter current position :");
                    head = takeinput(3*mx/4,400);

                    outtextxy(mx/8,500,"Enter direction (0 for inwards and 1 for outwards) :");
                    direc = takeinput(3*mx/4,500);

                    DS.initialize("non-random", cyl, req, head, direc);
                    break;
            case 2: exit(0);
                    break;
        }

        DS.start();

    }while(true);

    return 0;
}
