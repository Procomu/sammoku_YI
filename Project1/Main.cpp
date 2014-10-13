#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int board[3][3];	
int stone;
int player;			
char row;
int column;
int temp_row;
int judge;
int putable;
int cont;		/*ゲーム継続可能性*/

/*全マス目を初期値(8)にする関数*/
void initBoard(){
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			board[i][j] = 8;
		}
	}
};

/*ゲームボードを表示する関数*/
void showBoard(){
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			printf("%d", board[i][j]);
		}
		printf("\n");
	}
};


/*石の色を初期化する関数*/
void initStone(){
	stone = 1;
}

/*プレーヤーを初期化する関数*/
void initPlayer(){
	player = 0;
}

/*選択されたマス目のavailabilityを確認して石を置く関数*/
void putableStone(){
	if (board[temp_row][column] == 8){
		putable = 1;
	} else {
		putable = 0;
	}
}

/*マス目を選び石を置く関数*/
void input(){
	printf("Player%d: Choose a row (a, b or c)\n", player + 1);
	fflush(stdin);
	scanf("%c", &row);		/*row番号の取得*/

	switch (row){
		case 'a': temp_row = 0;
			break;
		case 'b': temp_row = 1;
			break;
		case 'c': temp_row = 2;
			break;
		default: printf("error\n");
	}						/*row番号の整数化*/
	/*printf("You chose %c.\n", row);*/

	printf("Player%d: Choose a column (0, 1 or 2)\n", player + 1);
	scanf("%d", &column);	/*column番号の取得*/
	/*printf("You chose %d.\n", column);*/

	putableStone();			/*選択されたマス目が空か（8か）確認し空なら石を置く、空でなければinput呼び出す*/

	if (putable == 1){
		board[temp_row][column] = stone;
	}else{
		printf("choose other cell\n");
		input();
	}
}


/*勝者判定の関数：どこか一列の合計の絶対値が3になっているか*/
void checkWin(){
	if(	board[0][0]+board[0][1]+board[0][2] == 3 || 
		board[0][0]+board[0][1]+board[0][2] == -3 ||
		board[1][0]+board[1][1]+board[1][2] == 3 ||
		board[1][0]+board[1][1]+board[1][2] == -3 ||
		board[2][0]+board[2][1]+board[2][2] == 3 ||
		board[2][0]+board[2][1]+board[2][2] == -3 ||
		board[0][0]+board[1][0]+board[2][0] == 3 ||
		board[0][0]+board[1][0]+board[2][0] == -3 ||
		board[0][1]+board[1][1]+board[2][1] == 3 ||
		board[0][1]+board[1][1]+board[2][1] == -3 ||
		board[0][2]+board[1][2]+board[2][2] == 3 ||
		board[0][2]+board[1][2]+board[2][2] == -3 ||
		board[0][0]+board[1][1]+board[2][2] == 3 ||
		board[0][0]+board[1][1]+board[2][2] == -3 ||
		board[0][2]+board[1][1]+board[2][0] == 3 ||
		board[0][2]+board[1][1]+board[2][0] == -3){
			judge = 1;
		}else{
			judge = 0;
		}
	}

/*勝者表示の関数*/
void dispWinner(){
	if (judge == 1){
		printf("Player%d won!\n", player + 1);
	} else {
		printf("Draw!");
	}
}

/*石の切り替えの関数*/
void changeStone(){
	if (stone == 1){
		stone = -1;
	}else{
		stone = 1;
	}
}

/*プレーヤーの切り替えの関数*/
void changePlayer(){
	if (player == 0){
		player = 1;
	}else{
		player = 0;
	}
}

/*空きマス目の有無チェック*/
void check(){
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			if (board[i][j] == 8){
				cont = 1;
				goto OUT;
			} else {
				cont = 0;
			}
		}
	}
OUT: ;
}



int main (){
	printf("Start game\n");
	initBoard();			/*ボードの初期化*/
	showBoard();			/*ボードの表示*/
	initStone();			/*石の初期化*/
	initPlayer();			/*プレーヤーの初期化*/

	cont = 1;				/*継続判定の初期化*/
	judge = 0;				/*勝ち判定初期化*/
	printf("\n");

	while (cont == 1){
		input();			/*マス目の選択受付*/
		showBoard();		
		checkWin();			/*勝ち判定*/
		if (judge == 1){
			break;			/*勝ち判定ありの場合、ループ脱出*/
		} else {
			check();		/*ゲーム継続可能性（空きマスがあるか）の判定*/
			changeStone();	
			changePlayer();
			printf("\n");
		}
	}

	printf("\n");
	dispWinner();			/*judgeの値により勝者表示OR引分宣言*/

		return 0;

}
