#include <iostream>
#include <simplecpp>
#include <string>
using namespace std;
int m1,n1,k;//m coloumn,n row
double m,n;


//how store defining structure and all
//note all will row number,... will be indices. so 3rd row 2nd coloumn box in physical viewing will have index 2,1

//This class is for storing the data concerned to every player
struct player{
    bool currentplayer;//if this is the move of current player then its value is true otherwise false
    int current_number_of_move;//what is the next number of move of player
    int current_number_of_move1;//what is the next number of move1[player has two kind of moves.during any move(declared as move) he/she has two positions to choose.for each such position player need two moves.(declared as move1)]
    int *player_move1_rowarray_ptr=new int[(m1*n1+1)/2];//where index in array = number of move-1;in move1 means box number of move1 is stored
    int *player_move1_coloumnarray_ptr=new int[(m1*n1+1)/2];//where index in array = number of move-1;in move2 means box number of move2 is stored
    int *player_move2_rowarray_ptr=new int[(m1*n1+1)/2];//where index in array = number of move-1;in move1 means box number of move1 is stored
    int *player_move2_coloumnarray_ptr=new int[(m1*n1+1)/2];//where index in array = number of move-1;in move2 means box number of move2 is stored
    int score;//After the game is over the score will be stored
    string current_move_display_string="current move:";//displays the string as mentioned
    string current_score_display_string="score:";//displays the string as mentioned
    Rectangle current_move_display_rectangle;//shows at bottom of box grid which player has current move. if player has current move then colour of rectangle will be dark blue. otherwise light blue
    char current_move_number_display[4];//to display the move number at the time play
    char current_score_display_char[4];//to display the score of the player after the game is over
    Text current_move_display_text;//shows at bottom of box grid which player has current move. will be displayed under player which has current move
    Text name_of_player;//to show name of player at bottom of grid of box
    Text score_display;//to show score of player at bottom of gird of box
};

//for storing the data if player at that position is fixed
struct fixedmove{
    int number_of_player;//who's move will be is fixed in this box
    int number_of_move;//the move number of the player by which the position is occupied
};

//for storing the data of the corresponding to the position of the box
struct box{
    int *player1ptr=new int[(m1*n1+1)/2];
    int *player2ptr=new int[(m1*n1+1)/2];// each player's all move's number are stored in these array.initialised to -1
    int number_of_moves_by_player1;//in the corresponding box; initialised to 0
    int number_of_moves_by_player2;//in the corresponding box; initialised to 0
    bool is_move_of_box_fixed;
    fixedmove move0;//for storing the data corresponding to the box once fixed
    int row_number_of_box;
    int coloumn_number_of_box;
    Rectangle recctangle_display;//rectangle that will display box
};

//to store data once a loop is detected
struct loop{
    int box_row_number,box_coloumn_number;//due to last move loop is occured.so last player had moved(move1) at two boxes boxnumber is one of those box's number
    int number_of_player;//who's last move caused loop
    int number_of_move;//move number of last move
    int *rownumber_of_boxes_ptr=new int[m1*n1];//who's move is finalised due to this loop. initialized to -1
    int *coloumnnumber_of_boxes_ptr=new int[m1*n1];
};

//to display player 1's move
struct small_circle_display{
    int coloumn_of_box;
    int row_of_box;
    int coloumn_of_circle;//each and every box is itself divided into m rows and n coloumns
    int row_of_circle;
    small_circle_display *next;//to be used in the queue that are to be formed
    Circle *circle_display;
    string current_move_display_string="";
    char current_move_number_display[4];
    Text current_move_display_text;
};

//the display of 'X' is contained two lines
struct small_line1_display{
    int coloumn_of_box;
    int row_of_box;
    int coloumn_of_line1;
    int row_of_line1;
    small_line1_display *next;//to be used in the queue that are to be formed
    Line *line1_display;
    string current_move_display_string="";
    char current_move_number_display[4];
    Text current_move_display_text;
};

struct small_line2_display{
    int coloumn_of_box;
    int row_of_box;
    int coloumn_of_line2;
    int row_of_line2;
    small_line2_display *next;//to be used in the queue that are to be formed
    Line *line2_display;
    string current_move_display_string="";
    char current_move_number_display[4];
    Text current_move_display_text;
};

//inside the box the display of circles and lines are arranged in this queue
//pointers are used in this case as 'front' and 'end'
struct queue_in_box{
    int coloumn_of_box;
    int row_of_box;
    small_circle_display *front0;
    small_line1_display *front1;
    small_line2_display *front2;
    small_circle_display *end0;
    small_line1_display *end1;
    small_line2_display *end2;
};

//for the bigger circle to be displayed once the box position is occupied by player 1
struct final_circle_display{
    int coloumn_of_box;
    int row_of_box;
    final_circle_display *next;//to be used in the queue that are to be formed
    Circle *circle_display;
    string final_move_display_string="";
    char final_move_number_display[4];
    Text final_move_display_text;
};

//for the bigger line1 of 'x' to be displayed once the box position is occupied by player 2
struct final_line1_display{
    int coloumn_of_box;
    int row_of_box;
    final_line1_display *next;//to be used in the queue that are to be formed
    Line *line1_display;
    string final_move_display_string="";
    char final_move_number_display[4];
    Text final_move_display_text;
};

//for the bigger line 2 of'x' to be displayed once the box position is occupied by player 2
struct final_line2_display{
    int coloumn_of_box;
    int row_of_box;
    final_line2_display *next;//to be used in the queue that are to be formed
    Line *line2_display;
    string final_move_display_string="";
    char final_move_number_display[4];
    Text final_move_display_text;
};

//this queue contains the data of display once a loop is detected
struct final_queue{
    final_circle_display *front0;
    final_line1_display *front1;
    final_line2_display *front2;
    final_circle_display *end0;
    final_line1_display *end1;
    final_line2_display *end2;
    int number_of_objects;//in the queue which is being stored
};

//to be accessed if a continuity of the same player is fixed in either horizontal, vertical or diagonal for 'k' times
struct final_line{
    int number_of_player;//who's class is this
    bool is_player_winner;
    bool is_player_looser;//if both false hence tie and that colour code
    int *row_number_of_diagonal=new int[k];
    int *coloumn_number_of_diagonal=new int[k];
    final_line *next;//initialised to NULL like taxi example
};

//the data of formation of successful lines is stored in this queue
struct queue_of_final_line{
    int number_of_player;
    int number_of_elements;
    bool is_player_winner;
    bool is_player_looser;//if both false hence tie and that colour code
    final_line *front4;//initiallised to NULL every time before the funtion containing it is called
    final_line *end4;//initiallised to NULL every time before the funtion containing it is called
};

//to store data of number of horizontal, vertical or diagonals are formed for every player
struct count_line_type_player{
    int horizontal;
    int vertical;
    int diagonal1;//from north-west to south-east direction
    int diagonal2;//from north-east to south-west direction
};




//precondition: mousebutton click(pressing)(left or right or middle) must have occured within work area of initCanvas
bool mouseclick_was_in_valid_area(int const &clickposition_x_coordinate,int const &clickposition_y_coordinate,double &m,double &n,box** box_datastorage){
    if((clickposition_x_coordinate<2)||(clickposition_x_coordinate>(34*m*m-2))||(clickposition_y_coordinate<102)||(clickposition_y_coordinate>(34*n*n+100-2))){return false;}
    int approximate_coloumn_number_of_box,approximate_row_number_of_box;//where mouse is clicked
    approximate_coloumn_number_of_box=(clickposition_x_coordinate/m)/38;
    approximate_row_number_of_box=((clickposition_y_coordinate-100)/n)/34;
    if(((((approximate_coloumn_number_of_box+1)*38*m)+2-clickposition_x_coordinate)<4)||((((approximate_row_number_of_box+1)*34*n)+2-clickposition_y_coordinate+100)<4)){return false;}//to check clicked position is not in between gap of boxes
    if(box_datastorage[approximate_row_number_of_box][approximate_coloumn_number_of_box].is_move_of_box_fixed){return false;}
    return true;
}
//postconditions: returns true if click was done in area where box is is

//precondition:game is not over
void boxnumber_of_mouse_click_for_first_move(int &coloumn_number_of_box_for_first_move,int &row_number_of_box_for_first_move,double &m,double &n,box** box_datastorage){
    while(true){
        int clickposition=getClick();
        int clickposition_x_coordinate,clickposition_y_coordinate;
        clickposition_x_coordinate=clickposition/65536;
        clickposition_y_coordinate=clickposition%65536;
        if(mouseclick_was_in_valid_area(clickposition_x_coordinate,clickposition_y_coordinate,m,n,box_datastorage)){
            row_number_of_box_for_first_move=((clickposition_y_coordinate-100)/n)/34;
            coloumn_number_of_box_for_first_move=(clickposition_x_coordinate/m)/38;
            break;
            }
    }
    return;
}
//postcondition: if mouse click is valid row and coloumn nmber of box for for first move will be changed appropriately


//correction functions

//precondition:this must be first move1
void change_of_data_after_first_move_playerobjects(player &player1,player &player2,int row_number_of_box_for_first_move,int coloumn_number_of_box_for_first_move){
if(player1.currentplayer){
    player1.current_number_of_move1=2;
    for(int i=0;;i++){
        if(player1.player_move1_rowarray_ptr[i]==-1){
            player1.player_move1_rowarray_ptr[i]=row_number_of_box_for_first_move;
            player1.player_move1_coloumnarray_ptr[i]=coloumn_number_of_box_for_first_move;
            break;
        }
    }
    return;
}
else{
    player2.current_number_of_move1=2;
    for(int i=0;;i++){
        if(player2.player_move1_rowarray_ptr[i]==-1){
            player2.player_move1_rowarray_ptr[i]=row_number_of_box_for_first_move;
            player2.player_move1_coloumnarray_ptr[i]=coloumn_number_of_box_for_first_move;
            break;
        }
    }
    return;
}
}
//postcondition: appropriate data is changed in all releted objects of class player



//precondition:this must be first move1
//note function is valid for any of the move1 first or second
void change_of_data_after_move1_boxobjects(player &player1,player &player2,box &box_datastorage){
if(player1.currentplayer){
    for(int i=0;i<(m*n+1)/2;i++){
        if(box_datastorage.player1ptr[i]==-1){
            box_datastorage.player1ptr[i]=player1.current_number_of_move;
            break;
        }
    }
    box_datastorage.number_of_moves_by_player1+=1;
    return;
}
else{
 for(int i=0;;i++){
        if(box_datastorage.player2ptr[i]==-1){
            box_datastorage.player2ptr[i]=player2.current_number_of_move;
            break;
        }
    }
    box_datastorage.number_of_moves_by_player2+=1;
    return;
}
}
//postcondition: appropriate data is changed in all releted objects of class box
//take care while inserting last parameter. it is box element of concern box_starage[i][j]



//precondition:game is not over
void boxnumber_of_mouseclick_for_second_move(int const &coloumn_number_of_box_for_first_move,int const &row_number_of_box_for_first_move,int &coloumn_number_of_box_for_secondmove,int &row_number_of_box_for_secondmove,double &m,double &n,box** box_datastorage){
    while(true){
        int clickposition=getClick();
        int clickposition_x_coordinate,clickposition_y_coordinate;
        clickposition_x_coordinate=clickposition/65536;
        clickposition_y_coordinate=clickposition%65536;
        if(mouseclick_was_in_valid_area(clickposition_x_coordinate,clickposition_y_coordinate,m,n,box_datastorage)){
            int rownumberofbox=((clickposition_y_coordinate-100)/n)/34;
            int coloumnnumberofbox=(clickposition_x_coordinate/m)/38;
            if((coloumnnumberofbox==coloumn_number_of_box_for_first_move)&&(rownumberofbox==row_number_of_box_for_first_move)){continue;}//player can't play both moves in same box
            coloumn_number_of_box_for_secondmove=coloumnnumberofbox;
            row_number_of_box_for_secondmove=rownumberofbox;
            return;
        }
    }
}
//if mouse click is valid row and coloumn nmber of box for for first move will be changed appropriately
//postcondition: do appropriate changing in objects releted to clicking.those objects are box:that has been clicked; and both players.



//precondition:this must be first move1 second part
void change_of_data_after_second_move_playerobjects(player &player1,player &player2,int row_number_of_box_for_secondmove,int coloumn_number_of_box_for_secondmove){
if(player1.currentplayer){
    player1.currentplayer=false;
    player1.current_number_of_move1=1;
    player1.current_number_of_move+=1;
    for(int i=0;;i++){
        if(player1.player_move2_rowarray_ptr[i]==-1){
            player1.player_move2_rowarray_ptr[i]=row_number_of_box_for_secondmove;
            player1.player_move2_coloumnarray_ptr[i]=coloumn_number_of_box_for_secondmove;
            break;
        }
    }
    player2.currentplayer=true;
    return;
}
else{
    player2.currentplayer=false;
    player2.current_number_of_move1=1;
    player2.current_number_of_move+=1;
    for(int i=0;;i++){
        if(player2.player_move2_rowarray_ptr[i]==-1){
            player2.player_move2_rowarray_ptr[i]=row_number_of_box_for_secondmove;
            player2.player_move2_coloumnarray_ptr[i]=coloumn_number_of_box_for_secondmove;
            break;
        }
    }
    player1.currentplayer=true;
    return;
}
}
//postcondition: appropriate data is changed in all releted objects of class player



//precondition: this must be move1
Circle* moving_of_circle_after_move1_player1(player player1,box box0,Circle c0,int coloumn_number_of_box_for_first_move,int row_number_of_box_for_first_move,int m1,int n1){
    Circle *c1=new Circle;
    *c1=c0;
    int total_number_of_moves_in_box0=box0.number_of_moves_by_player1+box0.number_of_moves_by_player2+1;//including this move
    int i=total_number_of_moves_in_box0/m1;
    int j=total_number_of_moves_in_box0%m1;
    if(j==0){j=m1;i-=1;}
    c1->moveTo(2+4*coloumn_number_of_box_for_first_move+34*m1*coloumn_number_of_box_for_first_move+34*(j-1)+11,100+2+4*row_number_of_box_for_first_move+30*n1*row_number_of_box_for_first_move+30*(i)+11);

    return c1;
}
//postcondition:display of corresponding box will be changed
//note: pass parameter of function will be box_datastorage[i][j].


//precondition: this must be move1
Line* moving_of_line1_after_move1_player2(player player2,box box0,Line l10,int coloumn_number_of_box_for_first_move,int row_number_of_box_for_first_move,int m1,int n1){
    Line *l1=new Line;
    *l1=l10;
    int total_number_of_moves_in_box0=box0.number_of_moves_by_player1+box0.number_of_moves_by_player2+1;//including this move
    int i=total_number_of_moves_in_box0/m1;
    int j=total_number_of_moves_in_box0%m1;
    if(j==0){j=m1;i-=1;}
    l1->moveTo(2+4*coloumn_number_of_box_for_first_move+34*m1*coloumn_number_of_box_for_first_move+34*(j-1)+11,100+2+4*row_number_of_box_for_first_move+30*n1*row_number_of_box_for_first_move+30*(i)+11);
    return l1;
}
//postcondition:display of corresponding box will be changed
//note: pass parameter of function will be box_datastorage[i][j].


//precondition: this must be move1
Line* moving_of_line2_after_move1_player2(player player2,box box0,Line l20,int coloumn_number_of_box_for_first_move,int row_number_of_box_for_first_move,int m1,int n1){
    Line *l2=new Line;
    *l2=l20;
    int total_number_of_moves_in_box0=box0.number_of_moves_by_player1+box0.number_of_moves_by_player2+1;//including this move
    int i=total_number_of_moves_in_box0/m1;
    int j=total_number_of_moves_in_box0%m1;
    if(j==0){j=m1;i-=1;}
    l2->moveTo(2+4*coloumn_number_of_box_for_first_move+34*m1*coloumn_number_of_box_for_first_move+34*(j-1)+11,100+2+4*row_number_of_box_for_first_move+30*n1*row_number_of_box_for_first_move+30*(i)+11);
    return l2;
}
//postcondition:display of corresponding box will be changed
//note: pass parameter of function will be box_datastorage[i][j].


//c0,loop0
Circle *moving_of_final_circle(player player1,Circle c0,int m1,int n1,loop loop0,int i){
    Circle *c1=new Circle;
    *c1=c0;
    int minimum=(m1>n1)?n1:m1;//minimum of m1 and n1 is assigned to minimum for scaling of circle
    c1->moveTo(2+4*loop0.coloumnnumber_of_boxes_ptr[i]+34*m1*loop0.coloumnnumber_of_boxes_ptr[i]+17*m1,100+2+4*loop0.rownumber_of_boxes_ptr[i]+30*n1*loop0.rownumber_of_boxes_ptr[i]+15*n1);
    c1->scale(minimum);
    return c1;
}

//precondition: a loop of the players moves must be formed containing player2
Line *moving_of_final_line1(player player1,Line l10,int m1,int n1,loop loop0,int i){
    Line *l1=new Line;
    *l1=l10;
    int minimum=(m1>n1)?n1:m1;//minimum of m1 and n1 is assigned to minimum for scaling of circle
    l1->moveTo(2+4*loop0.coloumnnumber_of_boxes_ptr[i]+34*m1*loop0.coloumnnumber_of_boxes_ptr[i]+17*m1,100+2+4*loop0.rownumber_of_boxes_ptr[i]+30*n1*loop0.rownumber_of_boxes_ptr[i]+15*n1);
    l1->scale(minimum);
    return l1;
}
//post condition: the display has the first part of 'X' in the desired box

//precondition: a loop of the players moves must be formed containing player2
Line *moving_of_final_line2(player player1,Line l20,int m1,int n1,loop loop0,int i){
    Line *l2=new Line;
    *l2=l20;
    int minimum=(m1>n1)?n1:m1;//minimum of m1 and n1 is assigned to minimum for scaling of circle
    l2->moveTo(2+4*loop0.coloumnnumber_of_boxes_ptr[i]+34*m1*loop0.coloumnnumber_of_boxes_ptr[i]+17*m1,100+2+4*loop0.rownumber_of_boxes_ptr[i]+30*n1*loop0.rownumber_of_boxes_ptr[i]+15*n1);
    l2->scale(minimum);
    return l2;
}
//post condition: the diplay has the second line of the 'X' in the desired box


//player1,player2,queue[i][j](that is queue0),box[i][j](that is box0 written),text t0(which is title text),circle c0,line10,line20
void change_of_display_after_move1(player &player1,player &player2,queue_in_box &queue0,box &box0,Text title_text,Circle c0,Line l10,Line l20,int coloumn_number_of_box_for_first_move,int row_number_of_box_for_first_move,int m1,int n1){
if(player1.currentplayer){
    small_circle_display *small_circle_display1=new small_circle_display;
    small_circle_display1->circle_display=moving_of_circle_after_move1_player1(player1,box0,c0,coloumn_number_of_box_for_first_move,row_number_of_box_for_first_move,m1,n1);
    (*(small_circle_display1->circle_display)).show();
    small_circle_display1->coloumn_of_box=coloumn_number_of_box_for_first_move;
    small_circle_display1->row_of_box=row_number_of_box_for_first_move;
    int total_number_of_moves_in_box0=box0.number_of_moves_by_player1+box0.number_of_moves_by_player2+1;
    small_circle_display1->row_of_circle=total_number_of_moves_in_box0/m1;
    small_circle_display1->coloumn_of_circle=total_number_of_moves_in_box0%m1;

    if(small_circle_display1->coloumn_of_circle==0){small_circle_display1->coloumn_of_circle=m1;small_circle_display1->row_of_circle-=1;}

    small_circle_display1->current_move_display_text=title_text;
    int j;
    j=0;
    for(int i=10;;i*=10,j++){
        small_circle_display1->current_move_number_display[j]=((2*player1.current_number_of_move-1)%i)/(i/10)+48;
        if((2*player1.current_number_of_move-1)/i==0){break;}
    }
    small_circle_display1->current_move_number_display[j+1]='\0';
    for(int i=0;i<(j+1)/2;i++){
        char temp=small_circle_display1->current_move_number_display[i];
        small_circle_display1->current_move_number_display[i]=small_circle_display1->current_move_number_display[j-i];
        small_circle_display1->current_move_number_display[j-i]=temp;
    }
    small_circle_display1->current_move_display_string.append(small_circle_display1->current_move_number_display);
    small_circle_display1->current_move_display_text.reset(2+4*coloumn_number_of_box_for_first_move+34*m1*coloumn_number_of_box_for_first_move+34*(small_circle_display1->coloumn_of_circle-1)+11+16,100+2+4*row_number_of_box_for_first_move+30*n1*row_number_of_box_for_first_move+30*(small_circle_display1->row_of_circle)+11+14,small_circle_display1->current_move_display_string);
    small_circle_display1->current_move_display_text.setColor(COLOR("white"));
    small_circle_display1->current_move_display_text.show();


    small_circle_display1->next=NULL;
    if(queue0.end0==NULL){
        queue0.front0=small_circle_display1;
        queue0.end0=small_circle_display1;
    }
    else{
        (queue0.end0)->next=small_circle_display1;
        queue0.end0=small_circle_display1;
    }

}
else{
//for line1
    small_line1_display *small_line1_display1=new small_line1_display;
    small_line1_display1->line1_display=moving_of_line1_after_move1_player2(player2,box0,l10,coloumn_number_of_box_for_first_move,row_number_of_box_for_first_move,m1,n1);
    (*(small_line1_display1->line1_display)).show();
    small_line1_display1->coloumn_of_box=coloumn_number_of_box_for_first_move;
    small_line1_display1->row_of_box=row_number_of_box_for_first_move;
    int total_number_of_moves_in_box0=box0.number_of_moves_by_player1+box0.number_of_moves_by_player2+1;
    small_line1_display1->coloumn_of_line1=total_number_of_moves_in_box0%m1;
    small_line1_display1->row_of_line1=total_number_of_moves_in_box0/m1;
    if(small_line1_display1->coloumn_of_line1==0){small_line1_display1->row_of_line1-=1;small_line1_display1->coloumn_of_line1=m1;}

    small_line1_display1->current_move_display_text=title_text;
    int j;
    j=0;
    for(int i=10;;i*=10,j++){
        small_line1_display1->current_move_number_display[j]=((2*player2.current_number_of_move)%i)/(i/10)+48;
        if((2*player2.current_number_of_move)/i==0){break;}
    }
    small_line1_display1->current_move_number_display[j+1]='\0';
    for(int i=0;i<(j+1)/2;i++){
        char temp=small_line1_display1->current_move_number_display[i];
        small_line1_display1->current_move_number_display[i]=small_line1_display1->current_move_number_display[j-i];
        small_line1_display1->current_move_number_display[j-i]=temp;
    }
    small_line1_display1->current_move_display_string.append(small_line1_display1->current_move_number_display);
    small_line1_display1->current_move_display_text.reset(2+4*coloumn_number_of_box_for_first_move+34*m1*coloumn_number_of_box_for_first_move+34*(small_line1_display1->coloumn_of_line1-1)+11+16,100+2+4*row_number_of_box_for_first_move+30*n1*row_number_of_box_for_first_move+30*(small_line1_display1->row_of_line1)+11+14,small_line1_display1->current_move_display_string);
    small_line1_display1->current_move_display_text.setColor(COLOR("white"));
    small_line1_display1->current_move_display_text.show();


    small_line1_display1->next=NULL;
    if(queue0.end1==NULL){
        queue0.front1=small_line1_display1;
        queue0.end1=small_line1_display1;
    }
    else{
        (queue0.end1)->next=small_line1_display1;
        queue0.end1=small_line1_display1;
    }

//for line2
    small_line2_display *small_line2_display1=new small_line2_display;
    small_line2_display1->line2_display=moving_of_line2_after_move1_player2(player2,box0,l20,coloumn_number_of_box_for_first_move,row_number_of_box_for_first_move,m1,n1);
    (*(small_line2_display1->line2_display)).show();
    small_line2_display1->coloumn_of_box=coloumn_number_of_box_for_first_move;
    small_line2_display1->row_of_box=row_number_of_box_for_first_move;
    small_line2_display1->coloumn_of_line2=total_number_of_moves_in_box0%m1;
    small_line2_display1->row_of_line2=total_number_of_moves_in_box0/m1;
    if(small_line2_display1->coloumn_of_line2==0){small_line2_display1->row_of_line2-=1;small_line2_display1->coloumn_of_line2=m1;}

    small_line2_display1->current_move_display_text=title_text;
    j=0;
    for(int i=10;;i*=10,j++){
        small_line2_display1->current_move_number_display[j]=((2*player2.current_number_of_move)%i)/(i/10)+48;
        if((2*player2.current_number_of_move)/i==0){break;}
    }
    small_line2_display1->current_move_number_display[j+1]='\0';
    for(int i=0;i<(j+1)/2;i++){
        char temp=small_line2_display1->current_move_number_display[i];
        small_line2_display1->current_move_number_display[i]=small_line2_display1->current_move_number_display[j-i];
        small_line2_display1->current_move_number_display[j-i]=temp;
    }
    small_line2_display1->current_move_display_string.append(small_line2_display1->current_move_number_display);
    small_line2_display1->current_move_display_text.reset(2+4*coloumn_number_of_box_for_first_move+34*m1*coloumn_number_of_box_for_first_move+34*(small_line2_display1->coloumn_of_line2-1)+11+16,100+2+4*row_number_of_box_for_first_move+30*n1*row_number_of_box_for_first_move+30*(small_line2_display1->row_of_line2)+11+14,small_line2_display1->current_move_display_string);
    small_line2_display1->current_move_display_text.setColor(COLOR("white"));
    small_line2_display1->current_move_display_text.show();


    small_line2_display1->next=NULL;
    if(queue0.end2==NULL){
        queue0.front2=small_line2_display1;
        queue0.end2=small_line2_display1;
    }
    else{
        (queue0.end2)->next=small_line2_display1;
        queue0.end2=small_line2_display1;
    }

}
return;


}
//post condition: change of the display of the player's moves on the screen after move1 of a player;

//pre condition: entanglement occures
void change_of_display_of_current_player_rectangle(player &player1,player &player2){
if(player1.currentplayer){
    player1.current_move_display_rectangle.setColor(COLOR("dark blue"));
    player2.current_move_display_rectangle.setColor(COLOR("light blue"));
}
else{
    player2.current_move_display_rectangle.setColor(COLOR("dark blue"));
    player1.current_move_display_rectangle.setColor(COLOR("light blue"));
}
}
//post condition: change of the display of the rectangles once the entanglement occures

//pre condition: both moves of the player are played
void change_of_display_of_current_move_number(player &player1,player &player2,int width,int n1){
if(player1.currentplayer){
    player1.current_move_display_string="current move:";
    int j=0;
    for(int i=10;;i*=10,j++){
        player1.current_move_number_display[j]=((2*player1.current_number_of_move-1)%i)/(i/10)+48;
        if((2*player1.current_number_of_move-1)/i==0){break;}
    }
    player1.current_move_number_display[j+1]='\0';
    for(int i=0;i<(j+1)/2;i++){
        char temp=player1.current_move_number_display[i];
        player1.current_move_number_display[i]=player1.current_move_number_display[j-i];
        player1.current_move_number_display[j-i]=temp;
    }
    player1.current_move_display_string.append(player1.current_move_number_display);
    player1.current_move_display_text.reset((width)/4,(30*n*n+4*n)+100+(5*22.5)+15+7.5,player1.current_move_display_string);
    player1.current_move_display_text.show();
    player2.current_move_display_text.hide();
}
else{
    player2.current_move_display_string="current move:";
    int j=0;
    for(int i=10;;i*=10,j++){
        player2.current_move_number_display[j]=((2*player2.current_number_of_move)%i)/(i/10)+48;
        if((2*player2.current_number_of_move)/i==0){break;}
    }
    player2.current_move_number_display[j+1]='\0';
    for(int i=0;i<(j+1)/2;i++){
        char temp=player2.current_move_number_display[i];
        player2.current_move_number_display[i]=player2.current_move_number_display[j-i];
        player2.current_move_number_display[j-i]=temp;
    }
    player2.current_move_display_string.append(player2.current_move_number_display);
    player2.current_move_display_text.reset((width)*3/4,(30*n*n+4*n)+100+(5*22.5)+15+7.5,player2.current_move_display_string);
    player2.current_move_display_text.show();
    player1.current_move_display_text.hide();
}
}
//post condition: the display of the current player's move number

//pre condition: gave must be over
void change_of_display_of_score(player &player1,player &player2,int width,double n){
//for player1
    int j=0;
    for(int i=10;;i*=10,j++){
        player1.current_score_display_char[j]=(player1.score%i)/(i/10)+48;
        if(player1.score/i==0){break;}
    }
    player1.current_score_display_char[j+1]='\0';
    for(int i=0;i<(j+1)/2;i++){
        char temp=player1.current_score_display_char[i];
        player1.current_score_display_char[i]=player1.current_score_display_char[j-i];
        player1.current_score_display_char[j-i]=temp;
    }
    player1.current_score_display_string="score:";
    player1.current_score_display_string.append(player1.current_score_display_char);
    player1.score_display.reset((width)/4,(30*n*n+4*n)+100+45+22.5+15,player1.current_score_display_string);
//for player2
    j=0;
    for(int i=10;;i*=10,j++){
        player2.current_score_display_char[j]=(player2.score%i)/(i/10)+48;
        if(player2.score/i==0){break;}
    }
    player2.current_score_display_char[j+1]='\0';
    for(int i=0;i<(j+1)/2;i++){
        char temp=player2.current_score_display_char[i];
        player2.current_score_display_char[i]=player2.current_score_display_char[j-i];
        player2.current_score_display_char[j-i]=temp;
    }
    player2.current_score_display_string="score:";
    player2.current_score_display_string.append(player2.current_score_display_char);
    player2.score_display.reset((width)*3/4,(30*n*n+4*n)+100+45+22.5+15,player2.current_score_display_string);
}
//post condition: the scores are assigned to the players according to the rules and displayed like wise

//pre condition: the box to be checked; the box to be connected to; the previous box of connectivity;
//note: it is a function in a function type way
int function_used_in_checkloop(int x1, int x2, int y1, int y2, int z1, int z2, box** box, player player1, player player2)
{//to check for the existence of the loop in the boxes connected to the the box to checked
	for(int t=0;t< box[x1][x2].number_of_moves_by_player1 ;t++)
	{
		if(player1.player_move1_rowarray_ptr[box[x1][x2].player1ptr[t]-1]==x1 && player1.player_move1_coloumnarray_ptr[box[x1][x2].player1ptr[t]-1]==x2)
		{//whether to check in the move 1 or the move 2 of the player 1; for move 2;
			if(player1.player_move2_rowarray_ptr[box[x1][x2].player1ptr[t]-1]==y1 && player1.player_move2_coloumnarray_ptr[box[x1][x2].player1ptr[t]-1]==y2)
			{
				return 1;//if final box to be found maches the box to be connected
			}
		}
		else
		{//for move1
			if(player1.player_move1_rowarray_ptr[box[x1][x2].player1ptr[t]-1]==y1 && player1.player_move1_coloumnarray_ptr[box[x1][x2].player1ptr[t]-1]==y2)
			{
				return 1;
			}
		}
	}
	for(int t=0;t< box[x1][x2].number_of_moves_by_player2 ;t++)
	{
		if(player2.player_move1_rowarray_ptr[box[x1][x2].player2ptr[t]-1]==x1 && player2.player_move1_coloumnarray_ptr[box[x1][x2].player2ptr[t]-1]==x2)
		{//whether to check in the move 1 or the move 2 of the player 2; for move 2;
			if(player2.player_move2_rowarray_ptr[box[x1][x2].player2ptr[t]-1]==y1 && player2.player_move2_coloumnarray_ptr[box[x1][x2].player2ptr[t]-1]==y2)
			{
				return 1;
			}
		}
		else
		{//for move 1
			if(player2.player_move1_rowarray_ptr[box[x1][x2].player2ptr[t]-1]==y1 && player2.player_move1_coloumnarray_ptr[box[x1][x2].player2ptr[t]-1]==y2)
			{
				return 1;
			}
		}
	}

	if((box[x1][x2].number_of_moves_by_player1 + box[x1][x2].number_of_moves_by_player2)<2){return -1;}
	//there should be atleast 2 members in a box if that box is a part of any loop

	//to proceed to the checking of the loop by calling the function again
	for(int g=0;g< box[x1][x2].number_of_moves_by_player1 ;g++)
	{//player1 only
		if(player1.player_move1_rowarray_ptr[box[x1][x2].player1ptr[g]-1]==x1 && player1.player_move1_coloumnarray_ptr[box[x1][x2].player1ptr[g]-1]==x2)
		{//for move 2
			if(player1.player_move2_rowarray_ptr[box[x1][x2].player1ptr[g]-1]!=z1 || player1.player_move2_coloumnarray_ptr[box[x1][x2].player1ptr[g]-1]!=z2)
			{//should not be the box where we started the checking of the loop
				if(function_used_in_checkloop(player1.player_move2_rowarray_ptr[box[x1][x2].player1ptr[g]-1],player1.player_move2_coloumnarray_ptr[box[x1][x2].player1ptr[g]-1],y1,y2,x1,x2,box,player1,player2) != -1)
				{//call for the same function in the box connected to it
					return 1;
				}
			}
		}
		else
		{//for move 1
			if(player1.player_move1_rowarray_ptr[box[x1][x2].player1ptr[g]-1]!=z1 || player1.player_move1_coloumnarray_ptr[box[x1][x2].player1ptr[g]-1]!=z2)
			{
				if(function_used_in_checkloop(player1.player_move1_rowarray_ptr[box[x1][x2].player1ptr[g]-1],player1.player_move1_coloumnarray_ptr[box[x1][x2].player1ptr[g]-1],y1,y2,x1,x2,box,player1,player2) != -1)
				{
					return 1;
				}
			}
		}
	}
	for(int g=0;g< box[x1][x2].number_of_moves_by_player2 ;g++)
	{//only player 2
		if(player2.player_move1_rowarray_ptr[box[x1][x2].player2ptr[g]-1]==x1 && player2.player_move1_coloumnarray_ptr[box[x1][x2].player2ptr[g]-1]==x2)
		{//for move2
			if(player2.player_move2_rowarray_ptr[box[x1][x2].player2ptr[g]-1]!=z1 || player2.player_move2_coloumnarray_ptr[box[x1][x2].player2ptr[g]-1]!=z2)
			{
				if(function_used_in_checkloop(player2.player_move2_rowarray_ptr[box[x1][x2].player2ptr[g]-1],player2.player_move2_coloumnarray_ptr[box[x1][x2].player2ptr[g]-1],y1,y2,x1,x2,box,player1,player2) != -1)
				{
					return 1;
				}
			}
		}
		else
		{//move 1
			if(player2.player_move1_rowarray_ptr[box[x1][x2].player2ptr[g]-1]!=z1 || player2.player_move1_coloumnarray_ptr[box[x1][x2].player2ptr[g]-1]!=z2)
			{
				if(function_used_in_checkloop(player2.player_move1_rowarray_ptr[box[x1][x2].player2ptr[g]-1],player2.player_move1_coloumnarray_ptr[box[x1][x2].player2ptr[g]-1],y1,y2,x1,x2,box,player1,player2) != -1)
				{
					return 1;
				}
			}
		}
	}
	return -1;
}
//post condition: it will return 1 if a loop exists and -1 if loop is never seen



//precondition: the last two boxes where the player palced the move
bool CheckLoop(int coloumn_number_of_box_for_first_move, int row_number_of_box_for_first_move, int coloumn_number_of_box_for_second_move, int row_number_of_box_for_second_move,box** box_datastorage,player player1,player player2,loop &loop0)
{//changes required if loop is detected;
	loop0.coloumnnumber_of_boxes_ptr[0]=coloumn_number_of_box_for_first_move;
	loop0.rownumber_of_boxes_ptr[0]=row_number_of_box_for_first_move;
	loop0.coloumnnumber_of_boxes_ptr[1]=coloumn_number_of_box_for_second_move;
	loop0.rownumber_of_boxes_ptr[1]=row_number_of_box_for_second_move;
	if(player1.currentplayer==true){loop0.number_of_player=2;loop0.number_of_move=player2.current_number_of_move-1;}
	else{loop0.number_of_player=1;loop0.number_of_move=player1.current_number_of_move-1;}
	int cl;
	if(player1.currentplayer==false)
	{//for player 1
		for(int t=0;t<player1.current_number_of_move-2;t++)
			{//incase the loop formed is a two membered loop
				if((player1.player_move1_rowarray_ptr[t]==row_number_of_box_for_second_move && player1.player_move1_coloumnarray_ptr[t]==coloumn_number_of_box_for_second_move && player1.player_move2_rowarray_ptr[t]==row_number_of_box_for_first_move && player1.player_move2_coloumnarray_ptr[t]==coloumn_number_of_box_for_first_move) || (player1.player_move2_rowarray_ptr[t]==row_number_of_box_for_second_move && player1.player_move2_coloumnarray_ptr[t]==coloumn_number_of_box_for_second_move && player1.player_move1_rowarray_ptr[t]==row_number_of_box_for_first_move && player1.player_move1_coloumnarray_ptr[t]==coloumn_number_of_box_for_first_move))
				{
					cl=1;
					break;
				}
				else{cl=0;}
			}
    if(cl==1){return true;}
		for(int t=0;t<player2.current_number_of_move-1;t++)
			{//incase the loop formed is a two membered loop
				if((player2.player_move1_rowarray_ptr[t]==row_number_of_box_for_second_move && player2.player_move1_coloumnarray_ptr[t]==coloumn_number_of_box_for_second_move && player2.player_move2_rowarray_ptr[t]==row_number_of_box_for_first_move && player2.player_move2_coloumnarray_ptr[t]==coloumn_number_of_box_for_first_move) || (player2.player_move2_rowarray_ptr[t]==row_number_of_box_for_second_move && player2.player_move2_coloumnarray_ptr[t]==coloumn_number_of_box_for_second_move && player2.player_move1_rowarray_ptr[t]==row_number_of_box_for_first_move && player2.player_move1_coloumnarray_ptr[t]==coloumn_number_of_box_for_first_move)){cl=1;break;}
				else{cl=0;}
			}

	if(cl==1){return true;}

		if(cl != 1 && (box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].number_of_moves_by_player1 + box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].number_of_moves_by_player2)>1 && (box_datastorage[row_number_of_box_for_second_move][coloumn_number_of_box_for_second_move].number_of_moves_by_player1 + box_datastorage[row_number_of_box_for_second_move][coloumn_number_of_box_for_second_move].number_of_moves_by_player2)>1)
		{//loops bigger than two membered
			for(int t=0;t<box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].number_of_moves_by_player1-1;t++)
			{//player 1
				if(player1.player_move1_rowarray_ptr[box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].player1ptr[t]-1] == row_number_of_box_for_first_move && player1.player_move1_coloumnarray_ptr[box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].player1ptr[t]-1] == coloumn_number_of_box_for_first_move)
				{//move 2
					if(function_used_in_checkloop(player1.player_move2_rowarray_ptr[box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].player1ptr[t]-1],player1.player_move2_coloumnarray_ptr[box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].player1ptr[t]-1],row_number_of_box_for_second_move,coloumn_number_of_box_for_second_move,row_number_of_box_for_first_move,coloumn_number_of_box_for_first_move,box_datastorage,player1,player2) == 1)
					{
						return true;
					}
				}
				else
				{//move 1
					if(function_used_in_checkloop(player1.player_move1_rowarray_ptr[box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].player1ptr[t]-1],player1.player_move1_coloumnarray_ptr[box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].player1ptr[t]-1],row_number_of_box_for_second_move,coloumn_number_of_box_for_second_move,row_number_of_box_for_first_move,coloumn_number_of_box_for_first_move,box_datastorage,player1,player2) == 1)
					{
						return true;
					}
				}
			}
			for(int t=0;t<box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].number_of_moves_by_player2;t++)
			{//player 2
				if(player2.player_move1_rowarray_ptr[box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].player2ptr[t]-1] == row_number_of_box_for_first_move && player2.player_move1_coloumnarray_ptr[box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].player2ptr[t]-1] == coloumn_number_of_box_for_first_move)
				{//move 2
					if(function_used_in_checkloop(player2.player_move2_rowarray_ptr[box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].player2ptr[t]-1],player2.player_move2_coloumnarray_ptr[box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].player2ptr[t]-1],row_number_of_box_for_second_move,coloumn_number_of_box_for_second_move,row_number_of_box_for_first_move,coloumn_number_of_box_for_first_move,box_datastorage,player1,player2) == 1)
					{
						return true;
					}
				}
				else
				{//move 1
					if(function_used_in_checkloop(player2.player_move1_rowarray_ptr[box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].player2ptr[t]-1],player2.player_move1_coloumnarray_ptr[box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].player2ptr[t]-1],row_number_of_box_for_second_move,coloumn_number_of_box_for_second_move,row_number_of_box_for_first_move,coloumn_number_of_box_for_first_move,box_datastorage,player1,player2) == 1)
					{
						return true;
					}
				}
			}
		}
	}
	else
	{//player 2
		for(int t=0;t<player1.current_number_of_move-1;t++)
			{//incase the loop formed is a two membered loop
				if((player1.player_move1_rowarray_ptr[t]==row_number_of_box_for_second_move && player1.player_move1_coloumnarray_ptr[t]==coloumn_number_of_box_for_second_move && player1.player_move2_rowarray_ptr[t]==row_number_of_box_for_first_move && player1.player_move2_coloumnarray_ptr[t]==coloumn_number_of_box_for_first_move) || (player1.player_move2_rowarray_ptr[t]==row_number_of_box_for_second_move && player1.player_move2_coloumnarray_ptr[t]==coloumn_number_of_box_for_second_move && player1.player_move1_rowarray_ptr[t]==row_number_of_box_for_first_move && player1.player_move1_coloumnarray_ptr[t]==coloumn_number_of_box_for_first_move)){cl=1;break;}
				else{cl=0;}
			}
    if(cl==1){return true;}
		for(int t=0;t<player2.current_number_of_move-2;t++)
			{//incase the loop formed is a two membered loop
				if((player2.player_move1_rowarray_ptr[t]==row_number_of_box_for_second_move && player2.player_move1_coloumnarray_ptr[t]==coloumn_number_of_box_for_second_move && player2.player_move2_rowarray_ptr[t]==row_number_of_box_for_first_move && player2.player_move2_coloumnarray_ptr[t]==coloumn_number_of_box_for_first_move) || (player2.player_move2_rowarray_ptr[t]==row_number_of_box_for_second_move && player2.player_move2_coloumnarray_ptr[t]==coloumn_number_of_box_for_second_move && player2.player_move1_rowarray_ptr[t]==row_number_of_box_for_first_move && player2.player_move1_coloumnarray_ptr[t]==coloumn_number_of_box_for_first_move)){cl=1;break;}
				else{cl=0;}
			}
	if(cl==1){return true;}

		if(cl != 1 && (box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].number_of_moves_by_player2 + box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].number_of_moves_by_player2)>1 && (box_datastorage[row_number_of_box_for_second_move][coloumn_number_of_box_for_second_move].number_of_moves_by_player2 + box_datastorage[row_number_of_box_for_second_move][coloumn_number_of_box_for_second_move].number_of_moves_by_player2)>1)
		{
			for(int t=0;t<box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].number_of_moves_by_player2-1;t++)
			{//player 2
				if(player2.player_move1_rowarray_ptr[box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].player2ptr[t]-1] == row_number_of_box_for_first_move && player2.player_move1_coloumnarray_ptr[box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].player2ptr[t]-1] == coloumn_number_of_box_for_first_move)
				{//move 2
					if(function_used_in_checkloop(player2.player_move2_rowarray_ptr[box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].player2ptr[t]-1],player2.player_move2_coloumnarray_ptr[box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].player2ptr[t]-1],row_number_of_box_for_second_move,coloumn_number_of_box_for_second_move,row_number_of_box_for_first_move,coloumn_number_of_box_for_first_move,box_datastorage,player1,player2) == 1)
					{
						return true;
					}
				}
				else
				{//move 1
					if(function_used_in_checkloop(player2.player_move1_rowarray_ptr[box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].player2ptr[t]-1],player2.player_move1_coloumnarray_ptr[box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].player2ptr[t]-1],row_number_of_box_for_second_move,coloumn_number_of_box_for_second_move,row_number_of_box_for_first_move,coloumn_number_of_box_for_first_move,box_datastorage,player1,player2) == 1)
					{
						return true;
					}
				}
			}
			for(int t=0;t<box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].number_of_moves_by_player1;t++)
			{//player 1
				if(player1.player_move1_rowarray_ptr[box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].player1ptr[t]-1] == row_number_of_box_for_first_move && player1.player_move1_coloumnarray_ptr[box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].player1ptr[t]-1] == coloumn_number_of_box_for_first_move)
				{//move2
					if(function_used_in_checkloop(player1.player_move2_rowarray_ptr[box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].player1ptr[t]-1],player1.player_move2_coloumnarray_ptr[box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].player1ptr[t]-1],row_number_of_box_for_second_move,coloumn_number_of_box_for_second_move,row_number_of_box_for_first_move,coloumn_number_of_box_for_first_move,box_datastorage,player1,player2) == 1)
					{
						return true;
					}
				}
				else
				{//move 1
					if(function_used_in_checkloop(player1.player_move1_rowarray_ptr[box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].player1ptr[t]-1],player1.player_move1_coloumnarray_ptr[box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move].player1ptr[t]-1],row_number_of_box_for_second_move,coloumn_number_of_box_for_second_move,row_number_of_box_for_first_move,coloumn_number_of_box_for_first_move,box_datastorage,player1,player2) == 1)
					{
						return true;
					}
				}
			}
		}
	}
return false;
}
//post condition: returns true if a loop is actually formed; if not it returns false


//pre condition: loop formation must be confirmed
void boxnumber_of_mouseclick_after_loop_formation(loop &loop0,double m,double n,box** box_datastorage){
while(true){
    int click=getClick();
    int x,y;
    x=click/65536;
    y=click%65536;
    if(mouseclick_was_in_valid_area(x,y,m,n,box_datastorage)){
        int i=((y-100)/n)/34;
        int j=(x/m)/38;
        if((i==loop0.rownumber_of_boxes_ptr[0]&&j==loop0.coloumnnumber_of_boxes_ptr[0])||(i==loop0.rownumber_of_boxes_ptr[1]&&j==loop0.coloumnnumber_of_boxes_ptr[1])){
        loop0.box_row_number=i;
        loop0.box_coloumn_number=j;
        return ;
        }
    }
}
}
//post condition: gets the position of the box selected by the player for collapsing the entangled loop




//pre condition: loop must be formed
//note: only after a box is selected for collapsing the loop
void fix(int boxRow, int boxColoumn, int player_number, int move_number, box** &box_datastorage, player player1, player player2, loop &loop0, int &d)
{//if box is fixed make the necessary changes in the data storage
	box_datastorage[boxRow][boxColoumn].is_move_of_box_fixed=true;
	loop0.rownumber_of_boxes_ptr[d]=boxRow;
	loop0.coloumnnumber_of_boxes_ptr[d]=boxColoumn;
	d++;
	int p;
	if(player_number==1)
	{
		box_datastorage[boxRow][boxColoumn].move0.number_of_player=1;
		box_datastorage[boxRow][boxColoumn].move0.number_of_move=move_number;
	}
	else
	{
		box_datastorage[boxRow][boxColoumn].move0.number_of_player=2;
		box_datastorage[boxRow][boxColoumn].move0.number_of_move=move_number;
	}

if(player_number==1)
{
	for(p=0;p<box_datastorage[boxRow][boxColoumn].number_of_moves_by_player1;p++)
	{//player 1
		if(box_datastorage[boxRow][boxColoumn].player1ptr[p] != move_number)
		{//members of the loop other than the ones which are fixed
			if(player1.player_move1_rowarray_ptr[box_datastorage[boxRow][boxColoumn].player1ptr[p]-1] == boxRow && player1.player_move1_coloumnarray_ptr[box_datastorage[boxRow][boxColoumn].player1ptr[p]-1] == boxColoumn)
			{//move2
				if(box_datastorage[player1.player_move2_rowarray_ptr[box_datastorage[boxRow][boxColoumn].player1ptr[p]-1]][player1.player_move2_coloumnarray_ptr[box_datastorage[boxRow][boxColoumn].player1ptr[p]-1]].is_move_of_box_fixed==false)
				{//to fix a box only if the box was not fixed earlier
					fix(player1.player_move2_rowarray_ptr[box_datastorage[boxRow][boxColoumn].player1ptr[p]-1], player1.player_move2_coloumnarray_ptr[box_datastorage[boxRow][boxColoumn].player1ptr[p]-1], 1, box_datastorage[boxRow][boxColoumn].player1ptr[p], box_datastorage, player1, player2, loop0, d);
				}
			}
			else
			{//move 1
				if(box_datastorage[player1.player_move1_rowarray_ptr[box_datastorage[boxRow][boxColoumn].player1ptr[p]-1]][player1.player_move1_coloumnarray_ptr[box_datastorage[boxRow][boxColoumn].player1ptr[p]-1]].is_move_of_box_fixed==false)
				{
					fix(player1.player_move1_rowarray_ptr[box_datastorage[boxRow][boxColoumn].player1ptr[p]-1], player1.player_move1_coloumnarray_ptr[box_datastorage[boxRow][boxColoumn].player1ptr[p]-1], 1, box_datastorage[boxRow][boxColoumn].player1ptr[p], box_datastorage, player1, player2, loop0, d);
				}
			}
		}
	}
	for(p=0;p<box_datastorage[boxRow][boxColoumn].number_of_moves_by_player2;p++)
	{//player 2
		if(player2.player_move1_rowarray_ptr[box_datastorage[boxRow][boxColoumn].player2ptr[p]-1] == boxRow && player2.player_move1_coloumnarray_ptr[box_datastorage[boxRow][boxColoumn].player2ptr[p]-1] == boxColoumn)
		{//move2
			if(box_datastorage[player2.player_move2_rowarray_ptr[box_datastorage[boxRow][boxColoumn].player2ptr[p]-1]][player2.player_move2_coloumnarray_ptr[box_datastorage[boxRow][boxColoumn].player2ptr[p]-1]].is_move_of_box_fixed==false)
			{
				fix(player2.player_move2_rowarray_ptr[box_datastorage[boxRow][boxColoumn].player2ptr[p]-1], player2.player_move2_coloumnarray_ptr[box_datastorage[boxRow][boxColoumn].player2ptr[p]-1], 2, box_datastorage[boxRow][boxColoumn].player2ptr[p], box_datastorage, player1, player2, loop0, d);
			}
		}
		else
		{//move 1
			if(box_datastorage[player2.player_move1_rowarray_ptr[box_datastorage[boxRow][boxColoumn].player2ptr[p]-1]][player2.player_move1_coloumnarray_ptr[box_datastorage[boxRow][boxColoumn].player2ptr[p]-1]].is_move_of_box_fixed==false)
			{
				fix(player2.player_move1_rowarray_ptr[box_datastorage[boxRow][boxColoumn].player2ptr[p]-1], player2.player_move1_coloumnarray_ptr[box_datastorage[boxRow][boxColoumn].player2ptr[p]-1], 2, box_datastorage[boxRow][boxColoumn].player2ptr[p], box_datastorage, player1, player2, loop0, d);
			}
		}
	}
}
else
{
	for(p=0;p<box_datastorage[boxRow][boxColoumn].number_of_moves_by_player2;p++)
	{//player2
		if(box_datastorage[boxRow][boxColoumn].player2ptr[p] != move_number)
		{//members of the loop other than the ones which are fixed
			if(player2.player_move1_rowarray_ptr[box_datastorage[boxRow][boxColoumn].player2ptr[p]-1] == boxRow && player2.player_move1_coloumnarray_ptr[box_datastorage[boxRow][boxColoumn].player2ptr[p]-1] == boxColoumn)
			{//move2
				if(box_datastorage[player2.player_move2_rowarray_ptr[box_datastorage[boxRow][boxColoumn].player2ptr[p]-1]][player2.player_move2_coloumnarray_ptr[box_datastorage[boxRow][boxColoumn].player2ptr[p]-1]].is_move_of_box_fixed==false)
				{
					fix(player2.player_move2_rowarray_ptr[box_datastorage[boxRow][boxColoumn].player2ptr[p]-1], player2.player_move2_coloumnarray_ptr[box_datastorage[boxRow][boxColoumn].player2ptr[p]-1], 2, box_datastorage[boxRow][boxColoumn].player2ptr[p], box_datastorage, player1, player2, loop0, d);

				}
			}
			else
			{//move1
				if(box_datastorage[player2.player_move1_rowarray_ptr[box_datastorage[boxRow][boxColoumn].player2ptr[p]-1]][player2.player_move1_coloumnarray_ptr[box_datastorage[boxRow][boxColoumn].player2ptr[p]-1]].is_move_of_box_fixed==false)
				{
					fix(player2.player_move1_rowarray_ptr[box_datastorage[boxRow][boxColoumn].player2ptr[p]-1], player2.player_move1_coloumnarray_ptr[box_datastorage[boxRow][boxColoumn].player2ptr[p]-1], 2, box_datastorage[boxRow][boxColoumn].player2ptr[p], box_datastorage, player1, player2, loop0, d);
				}
			}
		}
	}
	for(p=0;p<box_datastorage[boxRow][boxColoumn].number_of_moves_by_player1;p++)
	{
		if(player1.player_move1_rowarray_ptr[box_datastorage[boxRow][boxColoumn].player1ptr[p]-1] == boxRow && player1.player_move1_coloumnarray_ptr[box_datastorage[boxRow][boxColoumn].player1ptr[p]-1] == boxColoumn)
		{//move2
			if(box_datastorage[player1.player_move2_rowarray_ptr[box_datastorage[boxRow][boxColoumn].player1ptr[p]-1]][player1.player_move2_coloumnarray_ptr[box_datastorage[boxRow][boxColoumn].player1ptr[p]-1]].is_move_of_box_fixed==false)
			{
				fix(player1.player_move2_rowarray_ptr[box_datastorage[boxRow][boxColoumn].player1ptr[p]-1], player1.player_move2_coloumnarray_ptr[box_datastorage[boxRow][boxColoumn].player1ptr[p]-1], 1, box_datastorage[boxRow][boxColoumn].player1ptr[p], box_datastorage, player1, player2, loop0, d);
			}
		}
		else
		{//move1
			if(box_datastorage[player1.player_move1_rowarray_ptr[box_datastorage[boxRow][boxColoumn].player1ptr[p]-1]][player1.player_move1_coloumnarray_ptr[box_datastorage[boxRow][boxColoumn].player1ptr[p]-1]].is_move_of_box_fixed==false)
			{
				fix(player1.player_move1_rowarray_ptr[box_datastorage[boxRow][boxColoumn].player1ptr[p]-1], player1.player_move1_coloumnarray_ptr[box_datastorage[boxRow][boxColoumn].player1ptr[p]-1], 1, box_datastorage[boxRow][boxColoumn].player1ptr[p], box_datastorage, player1, player2, loop0, d);
			}
		}
	}
}
return;
}
//post condition: all the data regarding the boxes to be fixed and the players which occupy those is updated




//pre condition: loop is detected and the change in data after the collapse is updated
void change_of_display_of_boxes_after_loop_is_finalized(loop &loop0,box** &box_datastorage,int &m1,int &n1,Circle c0,Line l10,Line l20,Text title_text,final_queue &queue0,queue_in_box** &queue_datastorage,int width,int height,player player1,player player2,Rectangle r0){

for(int i=0;(loop0.coloumnnumber_of_boxes_ptr[i]!=-1);i++){

for(int x=1;x<=box_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].number_of_moves_by_player2;x++)

//delete all 3 queues
    //line2
        if(queue_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].front2!=NULL){
        for(int j=1;;j++){
        small_line2_display *temp_small_line2_display1=new small_line2_display;
        temp_small_line2_display1=queue_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].front2;
        (*(queue_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].front2->line2_display)).hide();
        queue_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].front2->current_move_display_text.hide();

        queue_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].front2=temp_small_line2_display1->next;
        delete temp_small_line2_display1;
        if((box_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].number_of_moves_by_player2)==j){break;}
        }
        }
    //for line1
        if(queue_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].front1!=NULL){
        for(int j=1;;j++){
        small_line1_display *temp_small_line1_display1=new small_line1_display;
        temp_small_line1_display1=queue_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].front1;
        (*(queue_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].front1->line1_display)).hide();
        queue_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].front1->current_move_display_text.hide();
        queue_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].front1=temp_small_line1_display1->next;
        delete temp_small_line1_display1;
        if((box_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].number_of_moves_by_player2)==j){break;}

        }
        }
    //circle
        if(queue_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].front0!=NULL){
        small_circle_display *temp_small_circle_display1=new small_circle_display;
        for(int j=1;;j++){
        temp_small_circle_display1=queue_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].front0;
        (*(queue_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].front0->circle_display)).hide();
        queue_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].front0->current_move_display_text.hide();
        queue_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].front0=temp_small_circle_display1->next;
        delete temp_small_circle_display1;
        if((box_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].number_of_moves_by_player1)==j){break;}
        }
        }
if(box_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].move0.number_of_player==1){



        final_circle_display *final_circle_display1=new final_circle_display;
        final_circle_display1->circle_display=moving_of_final_circle(player1,c0,m1,n1,loop0,i);
        (*(final_circle_display1->circle_display)).show();

        final_circle_display1->coloumn_of_box=loop0.coloumnnumber_of_boxes_ptr[i];
        final_circle_display1->row_of_box=loop0.rownumber_of_boxes_ptr[i];

        //final_circle_display1->final_move_display_string=" ";
        int j=0;
        for(int k=10;;k*=10,j++){
            final_circle_display1->final_move_number_display[j]=((2*box_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].move0.number_of_move-1)%k)/(k/10)+48;
            if((2*box_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].move0.number_of_move-1)/k==0){break;}
        }
        final_circle_display1->final_move_number_display[j+1]='\0';
        for(int k=0;k<(j+1)/2;k++){
            char temp=final_circle_display1->final_move_number_display[k];
            final_circle_display1->final_move_number_display[k]=final_circle_display1->final_move_number_display[j-k];
            final_circle_display1->final_move_number_display[j-k]=temp;
        }
        final_circle_display1->final_move_display_text=title_text;
        int minimum=(m1>n1)?n1:m1;
        final_circle_display1->final_move_display_text.reset(2+4*loop0.coloumnnumber_of_boxes_ptr[i]+34*m1*loop0.coloumnnumber_of_boxes_ptr[i]+17*m1+minimum*(7+6),100+2+4*loop0.rownumber_of_boxes_ptr[i]+30*n1*loop0.rownumber_of_boxes_ptr[i]+15*n1+minimum*(7+4),final_circle_display1->final_move_number_display);
        final_circle_display1->final_move_display_text.setColor(COLOR("white"));
        final_circle_display1->final_move_display_text.show();

        final_circle_display1->next=NULL;
        if(queue0.end0==NULL){
            queue0.front0=final_circle_display1;
            queue0.end0=final_circle_display1;
        }
        else{
            (queue0.end0)->next=final_circle_display1;
            queue0.end0=final_circle_display1;
        }
        queue0.number_of_objects+=1;
}


    else{
    //for line1

        final_line1_display *final_line1_display1=new final_line1_display;
        final_line1_display1->line1_display=moving_of_final_line1(player1,l10,m1,n1,loop0,i);
        (*(final_line1_display1->line1_display)).show();

        final_line1_display1->coloumn_of_box=loop0.coloumnnumber_of_boxes_ptr[i];
        final_line1_display1->row_of_box=loop0.rownumber_of_boxes_ptr[i];

        final_line1_display1->final_move_display_string=" ";
        int j=0;
        for(int k=10;;k*=10,j++){
            final_line1_display1->final_move_number_display[j]=((2*box_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].move0.number_of_move)%k)/(k/10)+48;
            if((2*box_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].move0.number_of_move)/k==0){break;}
        }
        final_line1_display1->final_move_number_display[j+1]='\0';
        for(int k=0;k<(j+1)/2;k++){
            char temp=final_line1_display1->final_move_number_display[k];
            final_line1_display1->final_move_number_display[k]=final_line1_display1->final_move_number_display[j-k];
            final_line1_display1->final_move_number_display[j-k]=temp;
        }

        final_line1_display1->final_move_display_string.append(final_line1_display1->final_move_number_display);
        final_line1_display1->final_move_display_text=title_text;
        final_line1_display1->final_move_display_text.setColor(COLOR("white"));
        int minimum=(m1>n1)?n1:m1;

        final_line1_display1->final_move_display_text.reset(2+4*loop0.coloumnnumber_of_boxes_ptr[i]+34*m1*loop0.coloumnnumber_of_boxes_ptr[i]+17*m1+minimum*(7+6),100+2+4*loop0.rownumber_of_boxes_ptr[i]+30*n1*loop0.rownumber_of_boxes_ptr[i]+15*n1+minimum*(7+4),final_line1_display1->final_move_display_string);
        final_line1_display1->final_move_display_text.show();

        final_line1_display1->next=NULL;
        if(queue0.end1==NULL){
            queue0.front1=final_line1_display1;
            queue0.end1=final_line1_display1;
        }
        else{
            (queue0.end1)->next=final_line1_display1;
            queue0.end1=final_line1_display1;
        }
        queue0.number_of_objects+=1;





    //for line2



        final_line2_display *final_line2_display1=new final_line2_display;
        final_line2_display1->line2_display=moving_of_final_line2(player1,l20,m1,n1,loop0,i);
        (*(final_line2_display1->line2_display)).show();

        final_line2_display1->coloumn_of_box=loop0.coloumnnumber_of_boxes_ptr[i];
        final_line2_display1->row_of_box=loop0.rownumber_of_boxes_ptr[i];

        final_line2_display1->final_move_display_string=" ";
        j=0;
        for(int k=10;;k*=10,j++){
            final_line2_display1->final_move_number_display[j]=((2*box_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].move0.number_of_move)%k)/(k/10)+48;
            if((2*box_datastorage[loop0.rownumber_of_boxes_ptr[i]][loop0.coloumnnumber_of_boxes_ptr[i]].move0.number_of_move)/k==0){break;}
        }
        final_line2_display1->final_move_number_display[j+1]='\0';
        for(int k=0;k<(j+1)/2;k++){
            char temp=final_line2_display1->final_move_number_display[k];
            final_line2_display1->final_move_number_display[k]=final_line2_display1->final_move_number_display[j-k];
            final_line2_display1->final_move_number_display[j-k]=temp;
        }
        final_line2_display1->final_move_display_string.append(final_line2_display1->final_move_number_display);
        final_line2_display1->final_move_display_text=title_text;
        minimum=(m1>n1)?n1:m1;
        final_line2_display1->final_move_display_text.reset(2+4*loop0.coloumnnumber_of_boxes_ptr[i]+34*m1*loop0.coloumnnumber_of_boxes_ptr[i]+17*m1+minimum*(7+6),100+2+4*loop0.rownumber_of_boxes_ptr[i]+30*n1*loop0.rownumber_of_boxes_ptr[i]+15*n1+minimum*(7+4),final_line2_display1->final_move_display_string);
        final_line2_display1->final_move_display_text.setColor(COLOR("white"));
        final_line2_display1->final_move_display_text.show();

        final_line2_display1->next=NULL;
        if(queue0.end2==NULL){
            queue0.front2=final_line2_display1;
            queue0.end2=final_line2_display1;
        }
        else{
            (queue0.end2)->next=final_line2_display1;
            queue0.end2=final_line2_display1;
        }
        queue0.number_of_objects+=1;

    }
if((i==(m1*n1)-1)){return;}
}
return;
}
//post condition: the display according to the fixed boxes is changed
//note: no more click is allowed once a box is fixed



//pre condition: a scoreable line is formed after the loop is fixed
void change_of_colour_of_boxes_after_game_is_over(box** &box_datastorage,queue_of_final_line &queue_of_final_line1,queue_of_final_line &queue_of_final_line2,player &player1,player &player2){

//for who won lines:116,66,200

//for who lost; still line:and number of lines are equal:60,176,139

//for rest 159,226,191

for(int i=0;i<n1;i++){
    for(int j=0;j<m1;j++){
        box_datastorage[i][j].recctangle_display.setColor(COLOR(159,226,191));
    }
}


if(queue_of_final_line1.front4==NULL){//player2 exclusively wins
    for(int i=0;i<queue_of_final_line2.number_of_elements;i++){
        final_line *temp_final_line2=queue_of_final_line2.front4;
        queue_of_final_line2.front4=temp_final_line2->next;
        for(int j=0;j<k;j++){
            box_datastorage[temp_final_line2->row_number_of_diagonal[j]][temp_final_line2->coloumn_number_of_diagonal[j]].recctangle_display.setColor(COLOR(116,66,200));
        }
        delete temp_final_line2;
        player1.current_move_display_rectangle.setColor(COLOR(60,176,139));
        player2.current_move_display_rectangle.setColor(COLOR(116,66,200));
        return;
    }
}

if(queue_of_final_line2.front4==NULL){//playr1 exclusively wins
    for(int i=0;i<queue_of_final_line1.number_of_elements;i++){
        final_line *temp_final_line1=queue_of_final_line1.front4;
        queue_of_final_line1.front4=temp_final_line1->next;
        for(int j=0;j<k;j++){
            box_datastorage[temp_final_line1->row_number_of_diagonal[j]][temp_final_line1->coloumn_number_of_diagonal[j]].recctangle_display.setColor(COLOR(116,66,200));
        }
        delete temp_final_line1;
        player2.current_move_display_rectangle.setColor(COLOR(60,176,139));
        player1.current_move_display_rectangle.setColor(COLOR(116,66,200));

    }
    return ;
}
//none of these NULL then check who won with which number of lines in account and that order's display show: written here
//for player1
int p=0,q=0;


if((!(queue_of_final_line1.front4->is_player_looser))&&(!(queue_of_final_line1.front4->is_player_winner))){
for(int i=0;i<n1;i++){
    for(int j=0;j<m1;j++){
        box_datastorage[i][j].recctangle_display.setColor(COLOR("blue"));
    }

}
}


if((!(queue_of_final_line1.front4->is_player_looser))&&(!(queue_of_final_line1.front4->is_player_winner))){

    for(int i=0;i<queue_of_final_line1.number_of_elements;i++){
        final_line *temp_final_line1=queue_of_final_line1.front4;
        queue_of_final_line1.front4=temp_final_line1->next;
        for(int j=0;j<k;j++){
            box_datastorage[temp_final_line1->row_number_of_diagonal[j]][temp_final_line1->coloumn_number_of_diagonal[j]].recctangle_display.setColor(COLOR(60,176,139));
        }
        delete temp_final_line1;

    }
    p=1;
    }
if((!(queue_of_final_line2.front4->is_player_looser))&&(!(queue_of_final_line2.front4->is_player_winner))){
    for(int i=0;i<queue_of_final_line2.number_of_elements;i++){
        final_line *temp_final_line2=queue_of_final_line2.front4;
        queue_of_final_line2.front4=temp_final_line2->next;
        for(int j=0;j<k;j++){
            box_datastorage[temp_final_line2->row_number_of_diagonal[j]][temp_final_line2->coloumn_number_of_diagonal[j]].recctangle_display.setColor(COLOR(60,176,139));
        }
        delete temp_final_line2;
    }
    q=1;
    }

if((p==1)&&(q==1)){
    return;
}
if(queue_of_final_line1.front4->is_player_looser){
    for(int i=0;i<queue_of_final_line1.number_of_elements;i++){
        final_line *temp_final_line1=queue_of_final_line1.front4;
        queue_of_final_line1.front4=temp_final_line1->next;
        for(int j=0;j<k;j++){
            box_datastorage[temp_final_line1->row_number_of_diagonal[j]][temp_final_line1->coloumn_number_of_diagonal[j]].recctangle_display.setColor(COLOR(60,176,139));
        }
        delete temp_final_line1;
        player1.current_move_display_rectangle.setColor(COLOR(60,176,139));
        player2.current_move_display_rectangle.setColor(COLOR(116,66,200));

    }
    p=2;
}
if(queue_of_final_line2.front4->is_player_winner){
    for(int i=0;i<queue_of_final_line2.number_of_elements;i++){
        final_line *temp_final_line2=queue_of_final_line2.front4;
        queue_of_final_line2.front4=temp_final_line2->next;
        for(int j=0;j<k;j++){
            box_datastorage[temp_final_line2->row_number_of_diagonal[j]][temp_final_line2->coloumn_number_of_diagonal[j]].recctangle_display.setColor(COLOR(116,66,200));
        }
        delete temp_final_line2;
        player1.current_move_display_rectangle.setColor(COLOR(60,176,139));
        player2.current_move_display_rectangle.setColor(COLOR(116,66,200));

    }
q=2;
}

if(p==2&&q==2){return;}
//for player2


if(queue_of_final_line2.front4->is_player_looser){
    for(int i=0;i<queue_of_final_line2.number_of_elements;i++){
        final_line *temp_final_line2=queue_of_final_line2.front4;
        queue_of_final_line2.front4=temp_final_line2->next;
        for(int j=0;j<k;j++){
            box_datastorage[temp_final_line2->row_number_of_diagonal[j]][temp_final_line2->coloumn_number_of_diagonal[j]].recctangle_display.setColor(COLOR(60,176,139));
        }
        delete temp_final_line2;
        player2.current_move_display_rectangle.setColor(COLOR(60,176,139));
        player1.current_move_display_rectangle.setColor(COLOR(116,66,200));

    }
}



//if winner


if(queue_of_final_line1.front4->is_player_winner){
    for(int i=0;i<queue_of_final_line1.number_of_elements;i++){
        final_line *temp_final_line1=queue_of_final_line1.front4;
        queue_of_final_line1.front4=temp_final_line1->next;
        for(int j=0;j<k;j++){
            box_datastorage[temp_final_line1->row_number_of_diagonal[j]][temp_final_line1->coloumn_number_of_diagonal[j]].recctangle_display.setColor(COLOR(116,66,200));
        }
        delete temp_final_line1;
        player2.current_move_display_rectangle.setColor(COLOR(60,176,139));
        player1.current_move_display_rectangle.setColor(COLOR(116,66,200));
    }
    }

return;
}
//post condition: the colour of the boxes is changed where scoreable lines are formed




//pre condition: a loop is formed and has been collapsed
void number_of_lines(int m, int n, int k, box** box1, int &score1, int &score2, count_line_type_player &count_line_type_player1, count_line_type_player &count_line_type_player2, int &min1, int &min2)
{
	int a,b,c,d,t,k1,a1,b1;
	int matrix[n][m];
	for(int i=0;i<n;i++)//converting the data in box into an integer type matrix
	{
		for(int j=0;j<m;j++)
		{
			if(box1[i][j].is_move_of_box_fixed==false){ matrix[i][j]=-1;}
			else
			{
				if(box1[i][j].move0.number_of_player==1){matrix[i][j]=1;}
				else{if(box1[i][j].move0.number_of_player==2){matrix[i][j]=2;}}

			}
		}
	}
if((k>=m && k<=n) || (k>=n && k<=m))
{
// m <= k <=n
	if (m<=n && k==m)
	{
		for(a=0;a<n;a++)//horizontal
		{
			for(b=0;b<m-1;b++)
			{
				if(matrix[a][b]==matrix[a][b+1])
				{
					if(b==m-2)
					{
						if(matrix[a][b]==1){score1++;count_line_type_player1.horizontal++;
                            a1=a;b1=b+1;//min1 and min2 are used for the case of tie and filled up matrix for game over
                            for(k1=0;k1<k;k1++,b1--){
                            if(box1[a1][b1].move0.number_of_move<=min1){min1=box1[a1][b1].move0.number_of_move;}}
						}
						if(matrix[a][b]==2){score2++;count_line_type_player2.horizontal++;
                            a1=a;b1=b+1;
                            for(k1=0;k1<k;k1++,b1--){
                            if(box1[a1][b1].move0.number_of_move<=min2){min2=box1[a1][b1].move0.number_of_move;}}
						}
					}
				}
				else{break;}
			}
		}
		for(c=0;c<=(n-m);c++)//diagonal1
		{
			for(b=0,a=c;b<m-1;a++,b++)
			{
				if(matrix[a][b]==matrix[a+1][b+1])
				{
					if(b==m-2)
					{
						if(matrix[a][b]==1){score1++;count_line_type_player1.diagonal1++;
                            a1=a+1;b1=b+1;
                            for(k1=0;k1<k;k1++,b1--,a1--){
                            if(box1[a1][b1].move0.number_of_move<=min1){min1=box1[a1][b1].move0.number_of_move;}}
						}
						if(matrix[a][b]==2){score2++;count_line_type_player2.diagonal1++;
                            a1=a+1;b1=b+1;
                            for(k1=0;k1<k;k1++,b1--,a1--){
                            if(box1[a1][b1].move0.number_of_move<=min2){min2=box1[a1][b1].move0.number_of_move;}}
						}
					}
				}
				else{break;}
			}
		}
		for(c=0;c<=(n-m);c++)//diagonal2
		{
			for(b=m-1,a=c;b>0;a++,b--)
			{
				if(matrix[a][b]==matrix[a+1][b-1])
				{
					if(b==1)
					{
						if(matrix[a][b]==1){score1++;count_line_type_player1.diagonal2++;
                            a1=a+1;b1=b-1;
                            for(k1=0;k1<k;k1++,b1++,a1--){
                            if(box1[a1][b1].move0.number_of_move<=min1){min1=box1[a1][b1].move0.number_of_move;}}
						}
						if(matrix[a][b]==2){score2++;count_line_type_player2.diagonal2++;
                            a1=a+1;b1=b-1;
                            for(k1=0;k1<k;k1++,b1++,a1--){
                            if(box1[a1][b1].move0.number_of_move<=min2){min2=box1[a1][b1].move0.number_of_move;}}
						}
					}
				}
				else{break;}
			}
		}
	}
	if(m<=n)
	{//k need not be equal to m
		for(b=0;b<m;b++)//vertical
		{
			for(c=0;c<=(n-k);c++)
			{
				for(a=c,t=0;t<k-1;a++,t++)
				{
					if(matrix[a][b]==matrix[a+1][b])
					{
						if(t==k-2)
						{
							if(matrix[a][b]==1){score1++;count_line_type_player1.vertical++;
                            a1=a+1;b1=b;
                            for(k1=0;k1<k;k1++,a1--){
                            if(box1[a1][b1].move0.number_of_move<=min1){min1=box1[a1][b1].move0.number_of_move;}}
						}
							if(matrix[a][b]==2){score2++;count_line_type_player2.vertical++;
                            a1=a+1;b1=b;
                            for(k1=0;k1<k;k1++,a1--){
                            if(box1[a1][b1].move0.number_of_move<=min2){min2=box1[a1][b1].move0.number_of_move;}}
						}
						}
					}
					else{break;}
				}
			}
		}
	}
	if(m>n && k==n)
	{
		for(c=0;c<=(m-n);c++)//diagonal1
		{
			for(b=0,a=c;b<n-1;a++,b++)
			{
				if(matrix[b][a]==matrix[b+1][a+1])
				{
					if(b==n-2)
					{
						if(matrix[b][a]==1){score1++;count_line_type_player1.diagonal1++;
                            a1=a+1;b1=b+1;
                            for(k1=0;k1<k;k1++,b1--,a1--){
                            if(box1[b1][a1].move0.number_of_move<=min1){min1=box1[b1][a1].move0.number_of_move;}}
						}
						if(matrix[b][a]==2){score2++;count_line_type_player2.diagonal1++;
                            a1=a+1;b1=b+1;
                            for(k1=0;k1<k;k1++,b1--,a1--){
                            if(box1[b1][a1].move0.number_of_move<=min2){min2=box1[b1][a1].move0.number_of_move;}}
						}
					}
				}
				else{break;}
			}
		}
		for(c=0;c<=(m-n);c++)//diagonal2
		{
			for(b=n-1,a=c;b>0;a++,b--)
			{
				if(matrix[b][a]==matrix[b-1][a+1])
				{
					if(b==1)
					{
						if(matrix[b][a]==1){score1++;count_line_type_player1.diagonal2++;
                            a1=a+1;b1=b-1;
                            for(k1=0;k1<k;k1++,b1++,a1--){
                            if(box1[b1][a1].move0.number_of_move<=min1){min1=box1[b1][a1].move0.number_of_move;}}
						}
						if(matrix[b][a]==2){score2++;count_line_type_player2.diagonal2++;
                            a1=a+1;b1=b-1;
                            for(k1=0;k1<k;k1++,b1++,a1--){
                            if(box1[b1][a1].move0.number_of_move<=min2){min2=box1[b1][a1].move0.number_of_move;}}
						}
					}
				}
				else{break;}
			}
		}
		for(b=0;b<m;b++)//vertical
		{
			for(a=0;a<n-1;a++)
			{
				if(matrix[a][b]==matrix[a+1][b])
				{
					if(a==n-2)
					{
						if(matrix[a][b]==1){score1++;count_line_type_player1.vertical++;
                            a1=a+1;b1=b;
                            for(k1=0;k1<k;k1++,a1--){
                            if(box1[a1][b1].move0.number_of_move<=min1){min1=box1[a1][b1].move0.number_of_move;}}
						}
						if(matrix[a][b]==2){score2++;count_line_type_player2.vertical++;
                            a1=a+1;b1=b;
                            for(k1=0;k1<k;k1++,a1--){
                            if(box1[a1][b1].move0.number_of_move<=min2){min2=box1[a1][b1].move0.number_of_move;}}
						}
					}
				}
				else{break;}
			}
		}
	}
	if(m>n)
	{//k need not be equal to n
		for(a=0;a<n;a++)//horizontal
		{
			for(c=0;c<=(m-k);c++)
			{
				for(b=c,t=0;t<k-1;b++,t++)
				{
					if(matrix[a][b]==matrix[a][b+1])
					{
						if(t==k-2)
						{
							if(matrix[a][b]==1){score1++;count_line_type_player1.horizontal++;
                            a1=a;b1=b+1;
                            for(k1=0;k1<k;k1++,b1--){
                            if(box1[a1][b1].move0.number_of_move<=min1){min1=box1[a1][b1].move0.number_of_move;}}
						}
							if(matrix[a][b]==2){score2++;count_line_type_player2.horizontal++;
                            a1=a;b1=b+1;
                            for(k1=0;k1<k;k1++,b1--){
                            if(box1[a1][b1].move0.number_of_move<=min2){min2=box1[a1][b1].move0.number_of_move;}}
						}
						}
					}
					else{break;}
				}
			}
		}
	}
}
if((m>=n && k<n) || (m<=n && k<m))
{// for k less than minimum of m and n
	//vertical
	for(b=0;b<m;b++)
	{
		for(c=0;c<=(n-k);c++)
		{
			for(a=c,t=0;t<k-1;a++,t++)
			{
				if(matrix[a][b]==matrix[a+1][b])
				{
					if(t==k-2)
					{
						if(matrix[a][b]==1){score1++;count_line_type_player1.vertical++;
                            a1=a+1;b1=b;
                            for(k1=0;k1<k;k1++,a1--){
                            if(box1[a1][b1].move0.number_of_move<=min1){min1=box1[a1][b1].move0.number_of_move;}}
						}
						if(matrix[a][b]==2){score2++;count_line_type_player2.vertical++;
                            a1=a+1;b1=b;
                            for(k1=0;k1<k;k1++,a1--){
                            if(box1[a1][b1].move0.number_of_move<=min2){min2=box1[a1][b1].move0.number_of_move;}}
						}
					}
				}
				else{break;}
			}
		}
	}

	//horizontal
	for(a=0;a<n;a++)
	{
		for(c=0;c<=(m-k);c++)
		{
			for(b=c,t=0;t<k-1;t++,b++)
			{
				if(matrix[a][b]==matrix[a][b+1])
				{
					if(t==k-2)
					{
						if(matrix[a][b]==1){score1++;count_line_type_player1.horizontal++;
                            a1=a;b1=b+1;
                            for(k1=0;k1<k;k1++,b1--){
                            if(box1[a1][b1].move0.number_of_move<=min1){min1=box1[a1][b1].move0.number_of_move;}}
						}
						if(matrix[a][b]==2){score2++;count_line_type_player2.horizontal++;
                            a1=a;b1=b+1;
                            for(k1=0;k1<k;k1++,b1--){
                            if(box1[a1][b1].move0.number_of_move<=min2){min2=box1[a1][b1].move0.number_of_move;}}
						}
					}
				}
				else{break;}
			}
		}
	}

	//diagonal 1
	for(c=0;c<=n-k;c++)
	{
		for(d=0;d<=m-k;d++)
		{
			for(a=c,b=d,t=0;t<k-1;a++,b++,t++)
			{
				if(matrix[a][b]==matrix[a+1][b+1])
				{
					if(t==k-2)
					{
						if(matrix[a][b]==1){score1++;count_line_type_player1.diagonal1++;
                            a1=a+1;b1=b+1;
                            for(k1=0;k1<k;k1++,b1--,a1--){
                            if(box1[a1][b1].move0.number_of_move<=min1){min1=box1[a1][b1].move0.number_of_move;}}
						}
						if(matrix[a][b]==2){score2++;count_line_type_player2.diagonal1++;
                            a1=a+1;b1=b+1;
                            for(k1=0;k1<k;k1++,b1--,a1--){
                            if(box1[a1][b1].move0.number_of_move<=min2){min2=box1[a1][b1].move0.number_of_move;}}
						}
					}
				}
				else{break;}
			}
		}
	}

	//diagonal 2
	for(c=0;c<=n-k;c++)
	{
		for(d=m-1;d>=k-1;d--)
		{
			for(a=c,b=d,t=0;t<k-1;a++,b--,t++)
			{
				if(matrix[a][b]==matrix[a+1][b-1])
				{
					if(t==k-2)
					{
						if(matrix[a][b]==1){score1++;count_line_type_player1.diagonal2++;
                            a1=a+1;b1=b-1;
                            for(k1=0;k1<k;k1++,b1++,a1--){
                            if(box1[a1][b1].move0.number_of_move<=min1){min1=box1[a1][b1].move0.number_of_move;}}
						}
						if(matrix[a][b]==2){score2++;count_line_type_player2.diagonal2++;
                            a1=a+1;b1=b-1;
                            for(k1=0;k1<k;k1++,b1++,a1--){
                            if(box1[a1][b1].move0.number_of_move<=min2){min2=box1[a1][b1].move0.number_of_move;}}
						}
					}
				}
				else{break;}
			}
		}
	}
}
return;
}
//post condition: the count of the number of types of the successfull lines formed is stored



//pre condition: a loop has been successfully detected and collapsed
int is_game_over(int m, int n, int k, box **box_datastorage, int &score1, int &score2, count_line_type_player &count_line_type_player1, count_line_type_player &count_line_type_player2, int &min1, int &min2)
{//for return value: 0=game not over; 1=player1 is winner; 2=player2 is winner; 3=both have formed same number of successfull lines; 4=all_boxes_filled;
	number_of_lines(m,n,k,box_datastorage,score1,score2,count_line_type_player1,count_line_type_player2,min1,min2);
	if(score1>score2){return 1;}
	else
	{
		if(score1<score2){return 2;}
		else
		{
			if(score1>0){return 3;}
			else
			{
				int c=0;
				for(int i=0;i<n;i++)
				{
					for(int j=0;j<m;j++)
					{
						if(box_datastorage[i][j].is_move_of_box_fixed==false){c++;}
					}
				}
				if(c>1){return 0;}
				else{return 4;}
			}
		}
	}
}
//post condition: return value: 0=game not over; 1=player1 is winner; 2=player2 is winner; 3=both have formed same number of successfull lines; 4=all_boxes_filled



//pre condition: if scoreable lines are detected successfully
void change_of_data_gameover(int m, int n, int k, int d, box** box1, queue_of_final_line &queue_of_final_line1, queue_of_final_line &queue_of_final_line2,int min1, int min2, player &player1, player &player2)
{
	int a,b,c,d1,t,k1,a1,b1,cou=0,check=0;
	int matrix[n][m];
	for(int i=0;i<n;i++)//conversion of the box datastorage into an integer formated matrix
	{
		for(int j=0;j<m;j++)
		{
			if(box1[i][j].is_move_of_box_fixed==false){ matrix[i][j]=-1;}
			else
			{cou++;
				if(box1[i][j].move0.number_of_player==1){matrix[i][j]=1;}
				else{matrix[i][j]=2;}
			}
		}
	}
if((d==3)&&(cou>(m1*n1-k))){//for the condition when there is an equal number of successful lines of both the player and no more place for further line formation remains
    if(min1>min2){check=2;}
    if(min1<=min2){check=1;}
}
if(check==1){player1.score=2;player2.score=1;}
if(check==2){player2.score=2;player1.score=1;}

if((k>=m && k<=n) || (k>=n && k<=m))
{
// m <= k <=n
	if (m<=n && k==m)
	{
		for(a=0;a<n;a++)//horizontal
		{
			for(b=0;b<m-1;b++)
			{
				if(matrix[a][b]==matrix[a][b+1])
				{
					if(b==m-2)
					{
						if(matrix[a][b]==1){
							a1=a;b1=b+1;
							final_line *final_line1;final_line1= new final_line;

							final_line1->next=NULL;
							final_line1->is_player_winner=false;
							final_line1->is_player_looser=false;
							if(d==1 || check==1){final_line1->is_player_winner=true;}
							if(d==2 || check==2){final_line1->is_player_looser=true;}
							for(k1=0;k1<k;k1++,b1--){
							final_line1->row_number_of_diagonal[k1]=a1;
							final_line1->coloumn_number_of_diagonal[k1]=b1;}
							if(queue_of_final_line1.end4==NULL){queue_of_final_line1.front4=final_line1;queue_of_final_line1.end4=final_line1;queue_of_final_line1.number_of_elements++;}
							else{(queue_of_final_line1.end4)->next = final_line1;queue_of_final_line1.end4=final_line1;queue_of_final_line1.number_of_elements++;}
						}
						if(matrix[a][b]==2){
							a1=a;b1=b+1;
							final_line *final_line1;final_line1= new final_line;

							final_line1->next=NULL;
							final_line1->is_player_winner=false;
							final_line1->is_player_looser=false;
							if(d==2 || check==2){final_line1->is_player_winner=true;}
							if(d==1 || check==1){final_line1->is_player_looser=true;}
							for(k1=0;k1<k;k1++,b1--){
							final_line1->row_number_of_diagonal[k1]=a1;
							final_line1->coloumn_number_of_diagonal[k1]=b1;}
							if(queue_of_final_line2.end4==NULL){queue_of_final_line2.front4=final_line1;queue_of_final_line2.end4=final_line1;queue_of_final_line2.number_of_elements++;}
							else{(queue_of_final_line2.end4)->next = final_line1;queue_of_final_line2.end4=final_line1;queue_of_final_line2.number_of_elements++;}
						}
					}
				}
				else{break;}
			}
		}
		for(c=0;c<=(n-m);c++)//diagonal1
		{
			for(b=0,a=c;b<m-1;a++,b++)
			{
				if(matrix[a][b]==matrix[a+1][b+1])
				{
					if(b==m-2)
					{
						if(matrix[a][b]==1){
							a1=a+1;b1=b+1;
							final_line *final_line1;final_line1= new final_line;

							final_line1->next=NULL;
							final_line1->is_player_winner=false;
							final_line1->is_player_looser=false;
							if(d==1 || check==1){final_line1->is_player_winner=true;}
							if(d==2 || check==2){final_line1->is_player_looser=true;}
							for(k1=0;k1<k;k1++,b1--,a1--){
							final_line1->row_number_of_diagonal[k1]=a1;
							final_line1->coloumn_number_of_diagonal[k1]=b1;}
							if(queue_of_final_line1.end4==NULL){queue_of_final_line1.front4=final_line1;queue_of_final_line1.end4=final_line1;queue_of_final_line1.number_of_elements++;}
							else{(queue_of_final_line1.end4)->next = final_line1;queue_of_final_line1.end4=final_line1;queue_of_final_line1.number_of_elements++;}
						}
						if(matrix[a][b]==2){
							a1=a+1;b1=b+1;
							final_line *final_line1;final_line1= new final_line;

							final_line1->next=NULL;
							final_line1->is_player_winner=false;
							final_line1->is_player_looser=false;
							if(d==2 || check==2){final_line1->is_player_winner=true;}
							if(d==1 || check==1){final_line1->is_player_looser=true;}
							for(k1=0;k1<k;k1++,b1--,a1--){
							final_line1->row_number_of_diagonal[k1]=a1;
							final_line1->coloumn_number_of_diagonal[k1]=b1;}
							if(queue_of_final_line2.end4==NULL){queue_of_final_line2.front4=final_line1;queue_of_final_line2.end4=final_line1;queue_of_final_line2.number_of_elements++;}
							else{(queue_of_final_line2.end4)->next = final_line1;queue_of_final_line2.end4=final_line1;queue_of_final_line2.number_of_elements++;}
						}
					}
				}
				else{break;}
			}
		}
		for(c=0;c<=(n-m);c++)//diagonal2
		{
			for(b=m-1,a=c;b>0;a++,b--)
			{
				if(matrix[a][b]==matrix[a+1][b-1])
				{
					if(b==1)
					{
						if(matrix[a][b]==1){
							a1=a+1;b1=b-1;
							final_line *final_line1;final_line1= new final_line;

							final_line1->next=NULL;
							final_line1->is_player_winner=false;
							final_line1->is_player_looser=false;
							if(d==1 || check==1){final_line1->is_player_winner=true;}
							if(d==2 || check==2){final_line1->is_player_looser=true;}
							for(k1=0;k1<k;k1++,b1++,a1--){
							final_line1->row_number_of_diagonal[k1]=a1;
							final_line1->coloumn_number_of_diagonal[k1]=b1;}
							if(queue_of_final_line1.end4==NULL){queue_of_final_line1.front4=final_line1;queue_of_final_line1.end4=final_line1;queue_of_final_line1.number_of_elements++;}
							else{(queue_of_final_line1.end4)->next = final_line1;queue_of_final_line1.end4=final_line1;queue_of_final_line1.number_of_elements++;}
						}
						if(matrix[a][b]==2){
							a1=a+1;b1=b-1;
							final_line *final_line1;final_line1= new final_line;

							final_line1->next=NULL;
							final_line1->is_player_winner=false;
							final_line1->is_player_looser=false;
							if(d==2 || check==2){final_line1->is_player_winner=true;}
							if(d==1 || check==1){final_line1->is_player_looser=true;}
							for(k1=0;k1<k;k1++,b1++,a1--){
							final_line1->row_number_of_diagonal[k1]=a1;
							final_line1->coloumn_number_of_diagonal[k1]=b1;}
							if(queue_of_final_line2.end4==NULL){queue_of_final_line2.front4=final_line1;queue_of_final_line2.end4=final_line1;queue_of_final_line2.number_of_elements++;}
							else{(queue_of_final_line2.end4)->next = final_line1;queue_of_final_line2.end4=final_line1;queue_of_final_line2.number_of_elements++;}
						}
					}
				}
				else{break;}
			}
		}
	}
	if(m<=n)
	{
		for(b=0;b<m;b++)//vertical
		{
			for(c=0;c<=(n-k);c++)
			{
				for(a=c,t=0;t<k-1;a++,t++)
				{
					if(matrix[a][b]==matrix[a+1][b])
					{
						if(t==k-2)
						{
							if(matrix[a][b]==1){
								a1=a+1;b1=b;
								final_line *final_line1;final_line1= new final_line;

								final_line1->next=NULL;
								final_line1->is_player_winner=false;
								final_line1->is_player_looser=false;
                                if(d==1 || check==1){final_line1->is_player_winner=true;}
                                if(d==2 || check==2){final_line1->is_player_looser=true;}
								for(k1=0;k1<k;k1++,a1--){
								final_line1->row_number_of_diagonal[k1]=a1;
								final_line1->coloumn_number_of_diagonal[k1]=b1;}
								if(queue_of_final_line1.end4==NULL){queue_of_final_line1.front4=final_line1;queue_of_final_line1.end4=final_line1;queue_of_final_line1.number_of_elements++;}
								else{(queue_of_final_line1.end4)->next = final_line1;queue_of_final_line1.end4=final_line1;queue_of_final_line1.number_of_elements++;}
							}
							if(matrix[a][b]==2){
								a1=a+1;b1=b;
								final_line *final_line1;final_line1= new final_line;

								final_line1->next=NULL;
								final_line1->is_player_winner=false;
								final_line1->is_player_looser=false;
                                if(d==2 || check==2){final_line1->is_player_winner=true;}
                                if(d==1 || check==1){final_line1->is_player_looser=true;}
								for(k1=0;k1<k;k1++,a1--){
								final_line1->row_number_of_diagonal[k1]=a1;
								final_line1->coloumn_number_of_diagonal[k1]=b1;}
								if(queue_of_final_line2.end4==NULL){queue_of_final_line2.front4=final_line1;queue_of_final_line2.end4=final_line1;queue_of_final_line2.number_of_elements++;}
								else{(queue_of_final_line2.end4)->next = final_line1;queue_of_final_line2.end4=final_line1;queue_of_final_line2.number_of_elements++;}
							}
						}
					}
					else{break;}
				}
			}
		}
	}
	if(m>n && k==n)
	{
		for(c=0;c<=(m-n);c++)//diagonal1
		{
			for(b=0,a=c;b<n-1;a++,b++)
			{
				if(matrix[b][a]==matrix[b+1][a+1])
				{
					if(b==n-2)
					{
						if(matrix[b][a]==1){
							a1=a+1;b1=b+1;
							final_line *final_line1;final_line1= new final_line;

							final_line1->next=NULL;
							final_line1->is_player_winner=false;
							final_line1->is_player_looser=false;
							if(d==1 || check==1){final_line1->is_player_winner=true;}
							if(d==2 || check==2){final_line1->is_player_looser=true;}
							for(k1=0;k1<k;k1++,b1--,a1--){
							final_line1->row_number_of_diagonal[k1]=b1;
							final_line1->coloumn_number_of_diagonal[k1]=a1;}
							if(queue_of_final_line1.end4==NULL){queue_of_final_line1.front4=final_line1;queue_of_final_line1.end4=final_line1;queue_of_final_line1.number_of_elements++;}
							else{(queue_of_final_line1.end4)->next = final_line1;queue_of_final_line1.end4=final_line1;queue_of_final_line1.number_of_elements++;}
						}
						if(matrix[b][a]==2){
							a1=a+1;b1=b+1;
							final_line *final_line1;final_line1= new final_line;

							final_line1->next=NULL;
							final_line1->is_player_winner=false;
							final_line1->is_player_looser=false;
							if(d==2 || check==2){final_line1->is_player_winner=true;}
							if(d==1 || check==1){final_line1->is_player_looser=true;}
							for(k1=0;k1<k;k1++,b1--,a1--){
							final_line1->row_number_of_diagonal[k1]=b1;
							final_line1->coloumn_number_of_diagonal[k1]=a1;}
							if(queue_of_final_line2.end4==NULL){queue_of_final_line2.front4=final_line1;queue_of_final_line2.end4=final_line1;queue_of_final_line2.number_of_elements++;}
							else{(queue_of_final_line2.end4)->next = final_line1;queue_of_final_line2.end4=final_line1;queue_of_final_line2.number_of_elements++;}
						}
					}
				}
				else{break;}
			}
		}
		for(c=0;c<=(m-n);c++)//diagonal2
		{
			for(b=n-1,a=c;b>0;a++,b--)
			{
				if(matrix[b][a]==matrix[b-1][a+1])
				{
					if(b==1)
					{
						if(matrix[b][a]==1){
							a1=a+1;b1=b-1;
							final_line *final_line1;final_line1= new final_line;

							final_line1->next=NULL;
							final_line1->is_player_winner=false;
							final_line1->is_player_looser=false;
							if(d==1 || check==1){final_line1->is_player_winner=true;}
							if(d==2 || check==2){final_line1->is_player_looser=true;}
							for(k1=0;k1<k;k1++,b1++,a1--){
							final_line1->row_number_of_diagonal[k1]=b1;
							final_line1->coloumn_number_of_diagonal[k1]=a1;}
							if(queue_of_final_line1.end4==NULL){queue_of_final_line1.front4=final_line1;queue_of_final_line1.end4=final_line1;queue_of_final_line1.number_of_elements++;}
							else{(queue_of_final_line1.end4)->next = final_line1;queue_of_final_line1.end4=final_line1;queue_of_final_line1.number_of_elements++;}
						}
						if(matrix[b][a]==2){
							a1=a+1;b1=b-1;
							final_line *final_line1;final_line1= new final_line;

							final_line1->next=NULL;
							final_line1->is_player_winner=false;
							final_line1->is_player_looser=false;
							if(d==2 || check==2){final_line1->is_player_winner=true;}
							if(d==1 || check==1){final_line1->is_player_looser=true;}
							for(k1=0;k1<k;k1++,b1++,a1--){
							final_line1->row_number_of_diagonal[k1]=b1;
							final_line1->coloumn_number_of_diagonal[k1]=a1;}
							if(queue_of_final_line2.end4==NULL){queue_of_final_line2.front4=final_line1;queue_of_final_line2.end4=final_line1;queue_of_final_line2.number_of_elements++;}
							else{(queue_of_final_line2.end4)->next = final_line1;queue_of_final_line2.end4=final_line1;queue_of_final_line2.number_of_elements++;}
						}
					}
				}
				else{break;}
			}
		}
		for(b=0;b<m;b++)//vertical
		{
			for(a=0;a<n-1;a++)
			{
				if(matrix[a][b]==matrix[a+1][b])
				{
					if(a==n-2)
					{
						if(matrix[a][b]==1){
							a1=a+1;b1=b;
							final_line *final_line1;final_line1= new final_line;

							final_line1->next=NULL;
							final_line1->is_player_winner=false;
							final_line1->is_player_looser=false;
							if(d==1 || check==1){final_line1->is_player_winner=true;}
							if(d==2 || check==2){final_line1->is_player_looser=true;}
							for(k1=0;k1<k;k1++,a1--){
							final_line1->row_number_of_diagonal[k1]=a1;
							final_line1->coloumn_number_of_diagonal[k1]=b1;}
							if(queue_of_final_line1.end4==NULL){queue_of_final_line1.front4=final_line1;queue_of_final_line1.end4=final_line1;queue_of_final_line1.number_of_elements++;}
							else{(queue_of_final_line1.end4)->next = final_line1;queue_of_final_line1.end4=final_line1;queue_of_final_line1.number_of_elements++;}
						}
						if(matrix[a][b]==2){
							a1=a+1;b1=b;
							final_line *final_line1;final_line1= new final_line;

							final_line1->next=NULL;
							final_line1->is_player_winner=false;
							final_line1->is_player_looser=false;
							if(d==2 || check==2){final_line1->is_player_winner=true;}
							if(d==1 || check==1){final_line1->is_player_looser=true;}
							for(k1=0;k1<k;k1++,a1--){
							final_line1->row_number_of_diagonal[k1]=a1;
							final_line1->coloumn_number_of_diagonal[k1]=b1;}
							if(queue_of_final_line2.end4==NULL){queue_of_final_line2.front4=final_line1;queue_of_final_line2.end4=final_line1;queue_of_final_line2.number_of_elements++;}
							else{(queue_of_final_line2.end4)->next = final_line1;queue_of_final_line2.end4=final_line1;queue_of_final_line2.number_of_elements++;}
						}
					}
				}
				else{break;}
			}
		}
	}
	if(m>n)
	{
		for(a=0;a<n;a++)//horizontal
		{
			for(c=0;c<=(m-k);c++)
			{
				for(b=c,t=0;t<k-1;b++,t++)
				{
					if(matrix[a][b]==matrix[a][b+1])
					{
						if(t==k-2)
						{
							if(matrix[a][b]==1){
								a1=a;b1=b+1;
								final_line *final_line1;final_line1= new final_line;

								final_line1->next=NULL;
								final_line1->is_player_winner=false;
								final_line1->is_player_looser=false;
                                if(d==1 || check==1){final_line1->is_player_winner=true;}
                                if(d==2 || check==2){final_line1->is_player_looser=true;}
								for(k1=0;k1<k;k1++,b1--){
								final_line1->row_number_of_diagonal[k1]=a1;
								final_line1->coloumn_number_of_diagonal[k1]=b1;}
								if(queue_of_final_line1.end4==NULL){queue_of_final_line1.front4=final_line1;queue_of_final_line1.end4=final_line1;queue_of_final_line1.number_of_elements++;}
								else{(queue_of_final_line1.end4)->next = final_line1;queue_of_final_line1.end4=final_line1;queue_of_final_line1.number_of_elements++;}
							}
							if(matrix[a][b]==2){
								a1=a;b1=b+1;
								final_line *final_line1;final_line1= new final_line;

								final_line1->next=NULL;
								final_line1->is_player_winner=false;
								final_line1->is_player_looser=false;
                                if(d==2 || check==2){final_line1->is_player_winner=true;}
                                if(d==1 || check==1){final_line1->is_player_looser=true;}
								for(k1=0;k1<k;k1++,b1--){
								final_line1->row_number_of_diagonal[k1]=a1;
								final_line1->coloumn_number_of_diagonal[k1]=b1;}
								if(queue_of_final_line2.end4==NULL){queue_of_final_line2.front4=final_line1;queue_of_final_line2.end4=final_line1;queue_of_final_line2.number_of_elements++;}
							else{(queue_of_final_line2.end4)->next = final_line1;queue_of_final_line2.end4=final_line1;queue_of_final_line2.number_of_elements++;}
						}
						}
					}
					else{break;}
				}
			}
		}
	}
}
if((m>=n && k<n) || (m<=n && k<m))
{
	//vertical
	for(b=0;b<m;b++)
	{
		for(c=0;c<=(n-k);c++)
		{
			for(a=c,t=0;t<k-1;a++,t++)
			{
				if(matrix[a][b]==matrix[a+1][b])
				{
					if(t==k-2)
					{
						if(matrix[a][b]==1){
							a1=a+1;b1=b;
							final_line *final_line1;final_line1= new final_line;

							final_line1->next=NULL;
							final_line1->is_player_winner=false;
							final_line1->is_player_looser=false;
							if(d==1 || check==1){final_line1->is_player_winner=true;}
							if(d==2 || check==2){final_line1->is_player_looser=true;}
							for(k1=0;k1<k;k1++,a1--){
							final_line1->row_number_of_diagonal[k1]=a1;
							final_line1->coloumn_number_of_diagonal[k1]=b1;}
							if(queue_of_final_line1.end4==NULL){queue_of_final_line1.front4=final_line1;queue_of_final_line1.end4=final_line1;queue_of_final_line1.number_of_elements++;}
							else{(queue_of_final_line1.end4)->next = final_line1;queue_of_final_line1.end4=final_line1;queue_of_final_line1.number_of_elements++;}
						}
						if(matrix[a][b]==2){
							a1=a+1;b1=b;
							final_line *final_line1;final_line1= new final_line;

							final_line1->next=NULL;
							final_line1->is_player_winner=false;
							final_line1->is_player_looser=false;
							if(d==2 || check==2){final_line1->is_player_winner=true;}
							if(d==1 || check==1){final_line1->is_player_looser=true;}
							for(k1=0;k1<k;k1++,a1--){
							final_line1->row_number_of_diagonal[k1]=a1;
							final_line1->coloumn_number_of_diagonal[k1]=b1;}
							if(queue_of_final_line2.end4==NULL){queue_of_final_line2.front4=final_line1;queue_of_final_line2.end4=final_line1;queue_of_final_line2.number_of_elements++;}
							else{(queue_of_final_line2.end4)->next = final_line1;queue_of_final_line2.end4=final_line1;queue_of_final_line2.number_of_elements++;}
						}
					}
				}
				else{break;}
			}
		}
	}

	//horizontal
	for(a=0;a<n;a++)
	{
		for(c=0;c<=(m-k);c++)
		{
			for(b=c,t=0;t<k-1;t++,b++)
			{
				if(matrix[a][b]==matrix[a][b+1])
				{
					if(t==k-2)
					{
						if(matrix[a][b]==1){
							a1=a;b1=b+1;
							final_line *final_line1;final_line1= new final_line;

							final_line1->next=NULL;
							final_line1->is_player_winner=false;
							final_line1->is_player_looser=false;
							if(d==1 || check==1){final_line1->is_player_winner=true;}
							if(d==2 || check==2){final_line1->is_player_looser=true;}
							for(k1=0;k1<k;k1++,b1--){
							final_line1->row_number_of_diagonal[k1]=a1;
							final_line1->coloumn_number_of_diagonal[k1]=b1;}
							if(queue_of_final_line1.end4==NULL){queue_of_final_line1.front4=final_line1;queue_of_final_line1.end4=final_line1;queue_of_final_line1.number_of_elements++;}
							else{(queue_of_final_line1.end4)->next = final_line1;queue_of_final_line1.end4=final_line1;queue_of_final_line1.number_of_elements++;}
						}
						if(matrix[a][b]==2){
							a1=a;b1=b+1;
							final_line *final_line1;final_line1= new final_line;

							final_line1->next=NULL;
							final_line1->is_player_winner=false;
							final_line1->is_player_looser=false;
							if(d==2 || check==2){final_line1->is_player_winner=true;}
							if(d==1 || check==1){final_line1->is_player_looser=true;}
							for(k1=0;k1<k;k1++,b1--){
							final_line1->row_number_of_diagonal[k1]=a1;
							final_line1->coloumn_number_of_diagonal[k1]=b1;}
							if(queue_of_final_line2.end4==NULL){queue_of_final_line2.front4=final_line1;queue_of_final_line2.end4=final_line1;queue_of_final_line2.number_of_elements++;}
							else{(queue_of_final_line2.end4)->next = final_line1;queue_of_final_line2.end4=final_line1;queue_of_final_line2.number_of_elements++;}
						}
					}
				}
				else{break;}
			}
		}
	}

	//diagonal 1
	for(c=0;c<=n-k;c++)
	{
		for(d1=0;d1<=m-k;d1++)
		{
			for(a=c,b=d1,t=0;t<k-1;a++,b++,t++)
			{
				if(matrix[a][b]==matrix[a+1][b+1])
				{
					if(t==k-2)
					{
						if(matrix[a][b]==1){
							a1=a+1;b1=b+1;
							final_line *final_line1;final_line1= new final_line;

							final_line1->next=NULL;
							final_line1->is_player_winner=false;
							final_line1->is_player_looser=false;
							if(d==1 || check==1){final_line1->is_player_winner=true;}
							if(d==2 || check==2){final_line1->is_player_looser=true;}
							for(k1=0;k1<k;k1++,b1--,a1--){
							final_line1->row_number_of_diagonal[k1]=a1;
							final_line1->coloumn_number_of_diagonal[k1]=b1;}
							if(queue_of_final_line1.end4==NULL){queue_of_final_line1.front4=final_line1;queue_of_final_line1.end4=final_line1;queue_of_final_line1.number_of_elements++;}
							else{(queue_of_final_line1.end4)->next = final_line1;queue_of_final_line1.end4=final_line1;queue_of_final_line1.number_of_elements++;}
						}
						if(matrix[a][b]==2){
							a1=a+1;b1=b+1;
							final_line *final_line1;final_line1= new final_line;

							final_line1->next=NULL;
							final_line1->is_player_winner=false;
							final_line1->is_player_looser=false;
							if(d==2 || check==2){final_line1->is_player_winner=true;}
							if(d==1 || check==1){final_line1->is_player_looser=true;}
							for(k1=0;k1<k;k1++,b1--,a1--){
							final_line1->row_number_of_diagonal[k1]=a1;
							final_line1->coloumn_number_of_diagonal[k1]=b1;}
							if(queue_of_final_line2.end4==NULL){queue_of_final_line2.front4=final_line1;queue_of_final_line2.end4=final_line1;queue_of_final_line2.number_of_elements++;}
							else{(queue_of_final_line2.end4)->next = final_line1;queue_of_final_line2.end4=final_line1;queue_of_final_line2.number_of_elements++;}
						}
					}
				}
				else{break;}
			}
		}
	}

	//diagonal 2
	for(c=0;c<=n-k;c++)
	{
		for(d1=m-1;d1>=k-1;d1--)
		{
			for(a=c,b=d1,t=0;t<k-1;a++,b--,t++)
			{
				if(matrix[a][b]==matrix[a+1][b-1])
				{
					if(t==k-2)
					{
						if(matrix[a][b]==1){
							a1=a+1;b1=b-1;
							final_line *final_line1;final_line1= new final_line;

							final_line1->next=NULL;
							final_line1->is_player_winner=false;
							final_line1->is_player_looser=false;
							if(d==1 || check==1){final_line1->is_player_winner=true;}
							if(d==2 || check==2){final_line1->is_player_looser=true;}
							for(k1=0;k1<k;k1++,b1++,a1--){
							final_line1->row_number_of_diagonal[k1]=a1;
							final_line1->coloumn_number_of_diagonal[k1]=b1;}
							if(queue_of_final_line1.end4==NULL){queue_of_final_line1.front4=final_line1;queue_of_final_line1.end4=final_line1;queue_of_final_line1.number_of_elements++;}
							else{(queue_of_final_line1.end4)->next = final_line1;queue_of_final_line1.end4=final_line1;queue_of_final_line1.number_of_elements++;}
						}
						if(matrix[a][b]==2){
							a1=a+1;b1=b-1;
							final_line *final_line1;final_line1= new final_line;

							final_line1->next=NULL;
							final_line1->is_player_winner=false;
							final_line1->is_player_looser=false;
							if(d==2 || check==2){final_line1->is_player_winner=true;}
							if(d==1 || check==1){final_line1->is_player_looser=true;}
							for(k1=0;k1<k;k1++,b1++,a1--){
							final_line1->row_number_of_diagonal[k1]=a1;
							final_line1->coloumn_number_of_diagonal[k1]=b1;}
							if(queue_of_final_line2.end4==NULL){queue_of_final_line2.front4=final_line1;queue_of_final_line2.end4=final_line1;queue_of_final_line2.number_of_elements++;}
							else{(queue_of_final_line2.end4)->next = final_line1;queue_of_final_line2.end4=final_line1;queue_of_final_line2.number_of_elements++;}
						}
					}
				}
				else{break;}
			}
		}
	}
}
return;
}
//post condition: the scoreable lines of player1 and player 2 are stored in the queue
//note: along with it whether the lines belong to the winning or the loosing team is stored
//the final score which is to be outed is also determined in this function;



int main()
{

while(true){

cout<<"Give number of coloumns and number of rows of grid such that they are greater than or equal to 3:"<<endl;
while(true)
{
	cin>>m>>n;
	if(m<3){cout<<"number of coloumns is less than 3. Re-enter number of coloumns and number of rows:"<<endl;}
	else{if(n<3){cout<<"number of rows is less than 3. Re-enter number of coloumns and number of rows:"<<endl;}
	else{break;}}
}
cout<<"Give number of boxes  required to form a winning line such that number of boxes  required to form a winning line is greater than 3 and less or equal to the greatest of number of coloumns or npk:"<<endl;
while(true)
{
	cin>>k;
	if(k<3){cout<<"number of boxes  required to form a winning line should be greater than 3. Please re-enter: "<<endl;}
	else{
	if(m<=n && k>n){cout<<"Improper value of number of boxes  required to form a winning line. Please re-enter:"<<endl;}
	else{if(m>=n && k>m){cout<<"Improper value of number of boxes  required to form a winning line. Please re-enter:"<<endl;}
	else{break;}}}
}

m1=m;
n1=n;
int width=(34*m)*m+4*m,height=(30*n*n)+350+4*n;//of display
int d=0,score1=0,score2=0,min1=m1*n1,min2=m1*n1;
initCanvas("checking display",width,height);

Text title_text(width/2,30,"Quantum-Tic Tac Toe");
Text title_text2(width/2,60,"M x N");
title_text2.setColor(COLOR("blue"));
title_text.setColor(COLOR("blue"));
Text note1(width/2,height-20,"do not click near edges of box");
Text note2(width/2,height-10,"may end in incorrect box selection");
Text note3(width/2,height-45,"Slot 11 . Group 6");
note1.setColor(COLOR("red"));
note2.setColor(COLOR("red"));
note3.setColor(COLOR("orange"));




Circle c0(-200+11,-200+11,10);
c0.setColor(COLOR("white"));
Rectangle r0(-200,-200,34*m,34*n);//r0 standard rectangle representing Box rest will be reset from this. border not shown
r0.setColor(COLOR("blue"));
r0.setFill(true);
Line l10(-200+4,-200+4,-200+18,-200+18);
Line l20(-200+18,-200+4,-200+4,-200+18);
l10.setColor(COLOR("white"));
l20.setColor(COLOR("white"));



player player1,player2;
    //initialising data for player1
    if(player1.player_move1_coloumnarray_ptr==NULL){cout<<"memory allocation failure"<<endl;return -1;}
    if(player1.player_move1_rowarray_ptr==NULL){cout<<"memory allocation failure"<<endl;return -1;}
    if(player1.player_move2_coloumnarray_ptr==NULL){cout<<"memory allocation failure"<<endl;return -1;}
    if(player1.player_move2_rowarray_ptr==NULL){cout<<"memory allocation failure"<<endl;return -1;}
    player1.currentplayer=true;
    player1.current_number_of_move=1;
    player1.current_number_of_move1=1;
    int j=0;
    for(int i=10;;i*=10,j++){
        player1.current_move_number_display[j]=(player1.current_number_of_move%i)/(i/10)+48;
        if(player1.current_number_of_move/i==0){break;}
    }
    player1.current_move_number_display[j+1]='\0';
    for(int i=0;i<j/2;i++){
        char temp=player1.current_move_number_display[i];
        player1.current_move_number_display[i]=player1.current_move_number_display[j-i];
        player1.current_move_number_display[j-i]=temp;
    }
    for(int i=0;i<(m*n+1)/2;i++){
        player1.player_move1_rowarray_ptr[i]=-1;
        player1.player_move1_coloumnarray_ptr[i]=-1;
        player1.player_move2_rowarray_ptr[i]=-1;
        player1.player_move2_coloumnarray_ptr[i]=-1;
    }
    player1.current_move_display_string.append(player1.current_move_number_display);
    player1.current_move_display_rectangle=r0;
    player1.current_move_display_rectangle.reset((width)/4,(30*n*n)+4*n+100+15+(5*22.5/2),(width)/2-2,45+22.5+15);
    player1.current_move_display_rectangle.setFill(true);
    player1.current_move_display_rectangle.setColor(COLOR("dark blue"));
    player1.current_move_display_text=title_text;
    player1.current_move_display_text.reset((width)/4,(30*n*n+4*n)+100+(5*22.5)+15+7.5,player1.current_move_display_string);
    player1.current_move_display_text.show();
    player1.name_of_player=title_text;
    player1.score_display=title_text;
    player1.name_of_player.reset((width)/4,(30*n*n+4*n)+100+45,"Player1");
    player1.name_of_player.setColor(COLOR("white"));
    player1.score=0;
    player1.score_display.setColor(COLOR("white"));
    player1.score_display.reset((width)/4,(30*n*n+4*n)+100+45+22.5+15,"score : ");





    //initialising data for player2
    if(player2.player_move1_coloumnarray_ptr==NULL){cout<<"memory allocation failure"<<endl;return -1;}
    if(player2.player_move1_rowarray_ptr==NULL){cout<<"memory allocation failure"<<endl;return -1;}
    if(player2.player_move2_coloumnarray_ptr==NULL){cout<<"memory allocation failure"<<endl;return -1;}
    if(player2.player_move2_rowarray_ptr==NULL){cout<<"memory allocation failure"<<endl;return -1;}
    player2.currentplayer=false;
    player2.current_number_of_move=1;
    player2.current_number_of_move1=1;
    for(int i=10,j=0;;i*=10,j++){
        player2.current_move_number_display[j]=(player2.current_number_of_move%i)/(i/10)+48;
        if(player2.current_number_of_move/i==0){break;}
    }
    player2.current_move_number_display[j+1]='\0';
    for(int i=0;i<j/2;i++){
        char temp=player2.current_move_number_display[i];
        player2.current_move_number_display[i]=player2.current_move_number_display[j-i];
        player2.current_move_number_display[j-i]=temp;
    }
    for(int i=0;i<(m*n+1)/2;i++){
        player2.player_move1_rowarray_ptr[i]=-1;
        player2.player_move1_coloumnarray_ptr[i]=-1;
        player2.player_move2_rowarray_ptr[i]=-1;
        player2.player_move2_coloumnarray_ptr[i]=-1;
    }
    player2.current_move_display_string.append(player2.current_move_number_display);
    player2.current_move_display_rectangle=r0;
    player2.current_move_display_rectangle.reset((width)*3/4,(30*n*n+4*n)+100+15+(5*22.5/2),(width)/2-2,45+22.5+15);
    player2.current_move_display_rectangle.setFill(true);
    player2.current_move_display_rectangle.setColor(COLOR("light blue"));
    player2.current_move_display_text=title_text;
    player2.current_move_display_text.reset((width)*3/4,(30*n*n+4*n)+100+(5*22.5)+15+7.5,player2.current_move_display_string);
    player2.current_move_display_text.hide();
    player2.name_of_player=title_text;
    player2.score_display=title_text;
    player1.current_move_display_text.show();
    player2.name_of_player.reset((width)*3/4,(30*n*n+4*n)+100+45,"Player2");
    player2.name_of_player.setColor(COLOR("white"));
    player2.score_display.reset((width)*3/4,(30*n*n+4*n)+100+45+22.5+15,"score : ");
    player2.score_display.setColor(COLOR("white"));
    player2.score=0;


//initialization of the symbol of the player
Circle circle_near_player_name(((width)/4)+35,(30*n*n+4*n)+100+45,10);
circle_near_player_name.setColor(COLOR("white"));
circle_near_player_name.show();
Line line1_near_player_name(width*3/4+35-7,(30*n*n+4*n)+100+45-7,width*3/4+35+7,(30*n*n+4*n)+100+45+7);
line1_near_player_name.setColor(COLOR("white"));
line1_near_player_name.show();
Line line2_near_player_name(width*3/4+35+7,(30*n*n+4*n)+100+45-7,width*3/4+35-7,(30*n*n+4*n)+100+45+7);
line2_near_player_name.setColor(COLOR("white"));
line2_near_player_name.show();


//declaration of the box as a 2 dimensional matrix formed by using 'new' 2 times
box **box_datastorage = new box*[n1];
for(int i=0;i<n1;i++){
    box_datastorage[i]= new box[m1];
}
    //initialising data for each box
    for(int i=0;i<n1;i++){
        for(int j=0;j<m1;j++){
            if(box_datastorage[i][j].player1ptr==NULL){cout<<"memory allocation failure"<<endl;return -1;}
            if(box_datastorage[i][j].player2ptr==NULL){cout<<"memory allocation failure"<<endl;return -1;}
            for(int k=0;k<(m1*n1+1)/2;k++){
                box_datastorage[i][j].player1ptr[k]=-1;
                box_datastorage[i][j].player2ptr[k]=-1;
            }
            box_datastorage[i][j].number_of_moves_by_player1=0;
            box_datastorage[i][j].number_of_moves_by_player2=0;
            box_datastorage[i][j].is_move_of_box_fixed=false;
            box_datastorage[i][j].move0.number_of_player=-1;
            box_datastorage[i][j].move0.number_of_move=-1;
            box_datastorage[i][j].row_number_of_box=i;
            box_datastorage[i][j].coloumn_number_of_box=j;
            box_datastorage[i][j].recctangle_display=r0;
            box_datastorage[i][j].recctangle_display.reset((34*m*j)+(4*j)+17*m+2,(30*n*i)+(4*i)+100+15*n+2,34*m,30*n);
            }
    }




//declaration of the queue in the box as a 2 dimensional matrix formed by using 'new' 2 times
queue_in_box **queue_datastorage = new queue_in_box*[n1];
for(int i=0;i<n1;i++){
    queue_datastorage[i]= new queue_in_box[m1];
}

    //inintialising each queue_in_box
    for(int i=0;i<n1;i++){
        for(int j=0;j<m1;j++){
            queue_datastorage[i][j].row_of_box=i;
            queue_datastorage[i][j].coloumn_of_box=j;
            queue_datastorage[i][j].front0=NULL;
            queue_datastorage[i][j].front1=NULL;
            queue_datastorage[i][j].front1=NULL;
            queue_datastorage[i][j].end0=NULL;
            queue_datastorage[i][j].end1=NULL;
            queue_datastorage[i][j].end2=NULL;
        }
    }

//declaration of loop0 of data type loop
loop loop0;
//initialization of loop0
loop0.box_coloumn_number=-1;
loop0.box_row_number=-1;
if(loop0.coloumnnumber_of_boxes_ptr==NULL){cout<<"Memory Location Failure"<<endl;return -1;}
if(loop0.rownumber_of_boxes_ptr==NULL){cout<<"Memory Location Failure"<<endl;return -1;}
for(int i=0;i<m1*n1;i++){
    loop0.coloumnnumber_of_boxes_ptr[i]=-1;
    loop0.rownumber_of_boxes_ptr[i]=-1;
}
loop0.number_of_move=-1;
loop0.number_of_player=-1;

//initialization of final_queue
final_queue final_queue0;
final_queue0.end0=NULL;
final_queue0.end1=NULL;
final_queue0.end2=NULL;
final_queue0.front0=NULL;
final_queue0.front1=NULL;
final_queue0.front2=NULL;
final_queue0.number_of_objects=0;

change_of_display_of_score(player1,player2,width,n);

//declaration of counting number of lines for player 1 and player 2
count_line_type_player count_line_type_player1;
count_line_type_player count_line_type_player2;










//a while loop is followed if the game is not over
//it iterates after every 2 moves of the respective player
//the loop breaks if the conditions for game over are satisfied
while(true){

//move start

int coloumn_number_of_box_for_first_move=-1;//initialized to -1
int row_number_of_box_for_first_move=-1;//initialized to -1
int coloumn_number_of_box_for_secondmove=-1;
int row_number_of_box_for_secondmove=-1;


boxnumber_of_mouse_click_for_first_move(coloumn_number_of_box_for_first_move,row_number_of_box_for_first_move,m,n,box_datastorage);

change_of_display_after_move1(player1,player2,queue_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move],box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move],title_text,c0,l10,l20,coloumn_number_of_box_for_first_move,row_number_of_box_for_first_move,m1,n1);

change_of_data_after_move1_boxobjects(player1,player2,box_datastorage[row_number_of_box_for_first_move][coloumn_number_of_box_for_first_move]);

change_of_data_after_first_move_playerobjects(player1,player2,row_number_of_box_for_first_move,coloumn_number_of_box_for_first_move);

boxnumber_of_mouseclick_for_second_move(coloumn_number_of_box_for_first_move,row_number_of_box_for_first_move,coloumn_number_of_box_for_secondmove,row_number_of_box_for_secondmove,m,n,box_datastorage);

change_of_display_after_move1(player1,player2,queue_datastorage[row_number_of_box_for_secondmove][coloumn_number_of_box_for_secondmove],box_datastorage[row_number_of_box_for_secondmove][coloumn_number_of_box_for_secondmove],title_text,c0,l10,l20,coloumn_number_of_box_for_secondmove,row_number_of_box_for_secondmove,m1,n1);

change_of_data_after_move1_boxobjects(player1,player2,box_datastorage[row_number_of_box_for_secondmove][coloumn_number_of_box_for_secondmove]);

change_of_data_after_second_move_playerobjects(player1,player2,row_number_of_box_for_secondmove,coloumn_number_of_box_for_secondmove);

change_of_display_of_current_player_rectangle(player1,player2);

change_of_display_of_current_move_number(player1,player2,width,n1);


















//if loop formed
if(!CheckLoop(coloumn_number_of_box_for_first_move,row_number_of_box_for_first_move,coloumn_number_of_box_for_secondmove,row_number_of_box_for_secondmove,box_datastorage,player1,player2,loop0)){continue;}

//redefining bottom display
Rectangle check_rectangle(width/2,height-125-20,width-20,170);
check_rectangle.setColor(COLOR("blue"));
check_rectangle.setFill(true);
Text check_text1(width/2,height-250+51,"Entanglement Has Occured !!!");
check_text1.setColor(COLOR("green"));
Text check_text3(width/2,height-250+122+4,"Select Where To Collapse");
check_text3.setColor(COLOR("green"));

//colour of boxes change at begning
for(int i=0;i<n1;i++){
    for(int j=0;j<m1;j++){
        box_datastorage[i][j].recctangle_display.setColor(COLOR("light blue"));
        if((i==loop0.rownumber_of_boxes_ptr[0]&&j==loop0.coloumnnumber_of_boxes_ptr[0])||(i==loop0.rownumber_of_boxes_ptr[1]&&j==loop0.coloumnnumber_of_boxes_ptr[1])){
            box_datastorage[i][j].recctangle_display.setColor(COLOR("blue"));
        }
    }
}

//what to show at bottom of text (in new defined bottom 4th line)which move to be fixed in one of the boxes


Line check_line1(0,0,0,0);
Line check_line2(0,0,0,0);
Circle check_circle(0,0,0);

Text *t2=new Text;
Text *t4=new Text;
if(loop0.number_of_player==1){
    //move of player 1 caused loop formation
    Text check_text2(width/2,height-250+89+4,"Player 2");
    check_text2.setColor(COLOR("green"));
    check_text2.show();
    player1.current_number_of_move-=1;
    check_circle.reset(width/2,height-40-25-17-10+4,10);
    check_circle.setColor(COLOR("green"));
    check_circle.show();
    int j=0;
    for(int i=10;;i*=10,j++){
        player1.current_move_number_display[j]=((2*player1.current_number_of_move-1)%i)/(i/10)+48;
        if((2*player1.current_number_of_move-1)/i==0){break;}
    }
    player1.current_move_number_display[j+1]='\0';
    for(int i=0;i<j/2;i++){
        char temp=player1.current_move_number_display[i];
        player1.current_move_number_display[i]=player1.current_move_number_display[j-i];
        player1.current_move_number_display[j-i]=temp;
    }
    Text check_text4(width/2+16,height-40-25-17+14-10+4,player1.current_move_number_display);
    check_text4.setColor(COLOR("green"));
    check_text4.show();
    player1.current_number_of_move+=1;
    for(int i=10,j=0;;i*=10,j++){
        player1.current_move_number_display[j]=((2*player1.current_number_of_move-1)%i)/(i/10)+48;
        if((2*player1.current_number_of_move-1)/i==0){break;}
    }
    player1.current_move_number_display[j+1]='\0';
    for(int i=0;i<j/2;i++){
        char temp=player1.current_move_number_display[i];
        player1.current_move_number_display[i]=player1.current_move_number_display[j-i];
        player1.current_move_number_display[j-i]=temp;
    }
    *t2=check_text2;
    *t4=check_text4;
}
else{
    //player 2 was the player whose move caused loop formation
    Text check_text2(width/2,height-250+89+4,"Player 1");
    check_text2.setColor(COLOR("green"));
    check_text2.show();
    player2.current_number_of_move-=1;
    int j=0;
    for(int i=10;;i*=10,j++){
        player2.current_move_number_display[j]=((2*player2.current_number_of_move)%i)/(i/10)+48;
        if((2*player2.current_number_of_move)/i==0){break;}
    }
    player2.current_move_number_display[j+1]='\0';
    for(int i=0;i<j/2;i++){
        char temp=player2.current_move_number_display[i];
        player2.current_move_number_display[i]=player2.current_move_number_display[j-i];
        player2.current_move_number_display[j-i]=temp;
    }
    Text check_text4(width/2+16,height-40-25-17+14-10+4,player2.current_move_number_display);
    check_text4.setColor(COLOR("green"));
    check_line1.reset(width/2-7,height-40-25-17-10-7+4,width/2+7,height-40-25-17-10+7+4);
    check_line2.reset(width/2+7,height-40-25-17-10-7+4,width/2-7,height-40-25-17-10+7+4);
    check_line1.setColor(COLOR("green"));
    check_line2.setColor(COLOR("green"));
    check_line1.show();
    check_line2.show();
    //check_text4.show();
    player2.current_number_of_move+=1;
    for(int i=10,j=0;;i*=10,j++){
        player2.current_move_number_display[j]=((2*player2.current_number_of_move)%i)/(i/10)+48;
        if((2*player2.current_number_of_move)/i==0){break;}
    }
    player2.current_move_number_display[j+1]='\0';
    for(int i=0;i<j/2;i++){
        char temp=player2.current_move_number_display[i];
        player2.current_move_number_display[i]=player2.current_move_number_display[j-i];
        player2.current_move_number_display[j-i]=temp;
    }
    *t2=check_text2;
    *t4=check_text4;
}
//show-hide changes at begning
check_rectangle.show();
check_text1.show();
t2->show();
check_text3.show();
t4->show();
player1.current_move_display_rectangle.hide();
player2.current_move_display_rectangle.hide();
player1.name_of_player.hide();
player2.name_of_player.hide();
circle_near_player_name.hide();
line1_near_player_name.hide();
line2_near_player_name.hide();
player1.score_display.hide();
player2.score_display.hide();
player1.current_move_display_text.hide();
player2.current_move_display_text.hide();



//get click
boxnumber_of_mouseclick_after_loop_formation(loop0,m,n,box_datastorage);

//hide changes at end
check_rectangle.hide();
check_text1.hide();
t2->hide();
check_text3.hide();
t4->hide();
check_line1.hide();
check_line2.hide();
check_circle.hide();
// wait till process text
Text *wait_till_processing_ends=new Text;
*wait_till_processing_ends=title_text;
(*wait_till_processing_ends).reset(width/2,height-125,"wait till procesing ends");
(*wait_till_processing_ends).show();
//rearranging and fixing position of boxes (inside)- Neeladri
d=0;
fix(loop0.box_row_number,loop0.box_coloumn_number,loop0.number_of_player,loop0.number_of_move,box_datastorage,player1,player2,loop0,d);


//change display of all fixed boxes
change_of_display_of_boxes_after_loop_is_finalized(loop0,box_datastorage,m1,n1,c0,l10,l20,title_text,final_queue0,queue_datastorage,width,height,player1,player2,r0);

//color change of boxes at end
for(int i=0;i<n1;i++){
    for(int j=0;j<m1;j++){
        box_datastorage[i][j].recctangle_display.setColor(COLOR("blue"));
    }
}

//remove wait till process text
delete wait_till_processing_ends;

//show changes at end
player1.current_move_display_rectangle.show();
player2.current_move_display_rectangle.show();
player1.name_of_player.show();
player2.name_of_player.show();
circle_near_player_name.show();
line1_near_player_name.show();
line2_near_player_name.show();
player1.score_display.show();
player2.score_display.show();
player1.current_move_display_text.show();
player2.current_move_display_text.show();

//reinitialising loop0 : there could be changes in it due to the while loop
loop0.box_coloumn_number=-1;
loop0.box_row_number=-1;
if(loop0.coloumnnumber_of_boxes_ptr==NULL){cout<<"Memory Location Failure"<<endl;return -1;}
if(loop0.rownumber_of_boxes_ptr==NULL){cout<<"Memory Location Failure"<<endl;return -1;}
for(int i=0;i<m1*n1;i++){
    loop0.coloumnnumber_of_boxes_ptr[i]=-1;
    loop0.rownumber_of_boxes_ptr[i]=-1;
}
loop0.number_of_move=-1;
loop0.number_of_player=-1;

//these values should be reinitialized before calling of the functions which use the values
//changes come after every time the loop is iterated
d=0;
score1=0;score2=0;
min1=m1*n1;min2=m1*n1;














//reinitializing this because the values change after every iteration in the while loop
count_line_type_player1.horizontal=0;
count_line_type_player1.vertical=0;
count_line_type_player1.diagonal1=0;
count_line_type_player1.diagonal2=0;
count_line_type_player2.horizontal=0;
count_line_type_player2.vertical=0;
count_line_type_player2.diagonal1=0;
count_line_type_player2.diagonal2=0;



//function to check the partial game over condition is called
d=is_game_over(m1,n1,k,box_datastorage,score1,score2,count_line_type_player1,count_line_type_player2,min1,min2);

if(!d){continue;}
//initialising
    queue_of_final_line queue_of_final_line1;
	queue_of_final_line1.front4=NULL;queue_of_final_line1.end4=NULL;
	queue_of_final_line queue_of_final_line2;
	queue_of_final_line2.front4=NULL;queue_of_final_line2.end4=NULL;
	queue_of_final_line1.number_of_elements=0;
	queue_of_final_line2.number_of_elements=0;

//change of coresponding data
change_of_data_gameover(m1,n1,k,d,box_datastorage,queue_of_final_line1,queue_of_final_line2,min1,min2,player1,player2);
int a=0;
for(int i=0;i<n1;i++){
    for(int j=0;j<m1;j++){
    if(box_datastorage[i][j].is_move_of_box_fixed){a++;}
    }
}

//change of colour of rectangles
change_of_colour_of_boxes_after_game_is_over(box_datastorage,queue_of_final_line1,queue_of_final_line2,player1,player2);


//following are the conditions for game over
//the player scores are updated accordingly
if(d==1){player1.score=2;}
if(d==2){player2.score=2;}



if((d!=3)||((d==3)&&(a>(m1*n1-k)))){
change_of_display_of_score(player1,player2,width,n);



//this is to display the number of lines and their type of every player

player1.current_move_display_rectangle.reset(width/4,height-152,(width/2)-4,136);
player2.current_move_display_rectangle.reset(width*3/4,height-152,(width/2)-4,136);
player1.name_of_player.moveTo(width/4,height-206);
player2.name_of_player.moveTo(width*3/4,height-206);
player1.score_display.moveTo(width/4,height-206+14+8+10);
player2.score_display.moveTo(width*3/4,height-206+14+8+10);
circle_near_player_name.moveTo(width/2-15,height-206);
line1_near_player_name.moveTo(width-15,height-206);
line2_near_player_name.moveTo(width-15,height-206);
player1.current_move_display_text.hide();
player2.current_move_display_text.hide();

//player1 number of lines show
char player1_horizontal_string[4];
string player1_horizontal_string1="no of horizontal line:";

int j=0;
for(int i=10;;i*=10,j++){
    player1_horizontal_string[j]=(count_line_type_player1.horizontal%i)/(i/10)+48;
    if(count_line_type_player1.horizontal/i==0){break;}
}
player1_horizontal_string[j+1]='\0';
for(int i=0;i<(j+1)/2;i++){
    char temp=player1_horizontal_string[i];
    player1_horizontal_string[i]=player1_horizontal_string[j-i];
    player1_horizontal_string[j-i]=temp;
}

player1_horizontal_string1.append(player1_horizontal_string);
Text player1_horizontal_text(width/4,height-206+14+8+20+5,player1_horizontal_string1);
player1_horizontal_text.show();



char player1_vertical_string[4];
string player1_vertical_string1="no of vertical line:";

j=0;
for(int i=10;;i*=10,j++){
    player1_vertical_string[j]=(count_line_type_player1.vertical%i)/(i/10)+48;
    if(count_line_type_player1.vertical/i==0){break;}
}
player1_vertical_string[j+1]='\0';
for(int i=0;i<(j+1)/2;i++){
    char temp=player1_vertical_string[i];
    player1_vertical_string[i]=player1_vertical_string[j-i];
    player1_vertical_string[j-i]=temp;
}

player1_vertical_string1.append(player1_vertical_string);
Text player1_vertical_text(width/4,height-206+14+8+20+25,player1_vertical_string1);
player1_vertical_text.show();



char player1_diagonal1_string[4];
string player1_diagonal1_string1="no of diagonal1 line:";

j=0;
for(int i=10;;i*=10,j++){
    player1_diagonal1_string[j]=(count_line_type_player1.diagonal1%i)/(i/10)+48;
    if(count_line_type_player1.diagonal1/i==0){break;}
}
player1_diagonal1_string[j+1]='\0';
for(int i=0;i<(j+1)/2;i++){
    char temp=player1_diagonal1_string[i];
    player1_diagonal1_string[i]=player1_diagonal1_string[j-i];
    player1_diagonal1_string[j-i]=temp;
}

player1_diagonal1_string1.append(player1_diagonal1_string);
Text player1_diagonal1_text(width/4,height-206+14+8+20+45,player1_diagonal1_string1);
player1_diagonal1_text.show();



char player1_diagonal2_string[4];
string player1_diagonal2_string1="no of diagonal2 line:";

j=0;
for(int i=10;;i*=10,j++){
    player1_diagonal2_string[j]=(count_line_type_player1.diagonal2%i)/(i/10)+48;
    if(count_line_type_player1.diagonal2/i==0){break;}
}
player1_diagonal2_string[j+1]='\0';
for(int i=0;i<(j+1)/2;i++){
    char temp=player1_diagonal2_string[i];
    player1_diagonal2_string[i]=player1_diagonal2_string[j-i];
    player1_diagonal2_string[j-i]=temp;
}

player1_diagonal2_string1.append(player1_diagonal2_string);
Text player1_diagonal2_text(width/4,height-206+14+8+20+65,player1_diagonal2_string1);
player1_diagonal2_text.show();



//player2 number of lines show
char player2_horizontal_string[4];
string player2_horizontal_string1="no of horizontal line:";

j=0;
for(int i=10;;i*=10,j++){
    player2_horizontal_string[j]=(count_line_type_player2.horizontal%i)/(i/10)+48;
    if(count_line_type_player2.horizontal/i==0){break;}
}
player2_horizontal_string[j+1]='\0';
for(int i=0;i<(j+1)/2;i++){
    char temp=player2_horizontal_string[i];
    player2_horizontal_string[i]=player2_horizontal_string[j-i];
    player2_horizontal_string[j-i]=temp;
}

player2_horizontal_string1.append(player2_horizontal_string);
Text player2_horizontal_text(width*3/4,height-206+14+8+20+5,player2_horizontal_string1);
player2_horizontal_text.show();



char player2_vertical_string[4];
string player2_vertical_string1="no of vertical line:";

j=0;
for(int i=10;;i*=10,j++){
    player2_vertical_string[j]=(count_line_type_player2.vertical%i)/(i/10)+48;
    if(count_line_type_player2.vertical/i==0){break;}
}
player2_vertical_string[j+1]='\0';
for(int i=0;i<(j+1)/2;i++){
    char temp=player2_vertical_string[i];
    player2_vertical_string[i]=player2_vertical_string[j-i];
    player2_vertical_string[j-i]=temp;
}

player2_vertical_string1.append(player2_vertical_string);
Text player2_vertical_text(width*3/4,height-206+14+8+20+25,player2_vertical_string1);
player2_vertical_text.show();



char player2_diagonal1_string[4];
string player2_diagonal1_string1="no of diagonal1 line:";

j=0;
for(int i=10;;i*=10,j++){
    player2_diagonal1_string[j]=(count_line_type_player2.diagonal1%i)/(i/10)+48;
    if(count_line_type_player2.diagonal1/i==0){break;}
}
player2_diagonal1_string[j+1]='\0';
for(int i=0;i<(j+1)/2;i++){
    char temp=player2_diagonal1_string[i];
    player2_diagonal1_string[i]=player2_diagonal1_string[j-i];
    player2_diagonal1_string[j-i]=temp;
}

player2_diagonal1_string1.append(player2_diagonal1_string);
Text player2_diagonal1_text(width*3/4,height-206+14+8+20+45,player2_diagonal1_string1);
player2_diagonal1_text.show();



char player2_diagonal2_string[4];
string player2_diagonal2_string1="no of diagonal2 line:";

j=0;
for(int i=10;;i*=10,j++){
    player2_diagonal2_string[j]=(count_line_type_player2.diagonal2%i)/(i/10)+48;
    if(count_line_type_player2.diagonal2/i==0){break;}
}
player2_diagonal2_string[j+1]='\0';
for(int i=0;i<(j+1)/2;i++){
    char temp=player2_diagonal2_string[i];
    player2_diagonal2_string[i]=player2_diagonal2_string[j-i];
    player2_diagonal2_string[j-i]=temp;
}

player2_diagonal2_string1.append(player2_diagonal2_string);
Text player2_diagonal2_text(width*3/4,height-206+14+8+20+65,player2_diagonal2_string1);
player2_diagonal2_text.show();




note1.hide();
note2.hide();
//note3.hide();
Rectangle new_game_rectangle(width/4,height-25,120,20);
Text new_game_text(width/4,height-25,"New Game");
Rectangle exit(width*3/4,height-25,120,20);
Text exit_text(width*3/4,height-25,"Exit");
new_game_rectangle.setFill(false);
exit.setFill(false);
new_game_rectangle.setColor(COLOR("black"));
exit.setColor(COLOR("black"));
new_game_text.setColor(COLOR("blue"));
exit_text.setColor(COLOR("blue"));
new_game_rectangle.show();
new_game_text.show();
exit.show();
exit_text.show();
Text message_show(width/2,height-65,"If New Game Refer to Terminal Window");
message_show.show();
message_show.setColor(COLOR("orange"));

while(true){
int z=getClick();
int x3,y3;
x3=z/65536;
y3=z%65536;
if((x3>((width/4)-60))&&(x3<(width/4+60))&&(y3>(height-35))&&(y3<(height-15))){break;}
if((x3>(width*3/4-60))&&(x3<(width*3/4+60))&&(y3>(height-35))&&(y3<(height-15))){return 0;}
}
break;
}




d=0;
score1=0;score2=0;
}//of while loop of starting








}








//score do not change rest all reinitialise and for loop contiues->boxes write under for loop
closeCanvas();
return 0;
}
