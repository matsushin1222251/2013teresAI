#include "Data.h"

int intro(AI_T *ai){
	AI_T *init_ai = ai;

	static int gametitle = LoadGraph("media\\chofu_fes2.bmp");

	static int start=0;
	if(start==0){
		start=1;
		
		//	テンプレ
		//	extern void !初期化関数名!(AI_T &myAi);
		//	!初期化関数名!(ai[!aiの番号!]);
		//	extern Action !移動関数名!(int view[2*VISIBLE+1][2*VISIBLE+1]);
		//	init_ai->moveFunc = !移動関数名!;
		//!!![重要]!!!!一番初め(aiSample)以外、最初にinit_ai++;を書く!!!!!!!!!!
		//関数名などが被ると駄目です　名前は早い者勝ちで(基本自分のハンドルネーム)


		/*AI追加欄
		init_ai++;
		extern void AI名Init(AI_T &myAi);
		AI名Init(*init_ai);
		extern Action AI名(int view[2*VISIBLE+1][2*VISIBLE+1]);
		init_ai->moveFunc=AI名;
		*/
	}

		int entryX=320,entryY=315;
		int startX=320,startY=360;
		
		static int step=0,window=0,input=0,time=0,bright=255;
		int mx,my;
		int en=0;
		GetMousePoint(&mx,&my);
		
		time++;
		if(time>30)time=0;
		
		if(step==0){
			if(GetMouseInput()==1){
				step=1;
			}
		}
		if(step==1){
			if(window<230)window+=23;
			if(GetMouseInput()==1 && input==0){
				if(window>=230){
					for(int i= 0; i < AI_NUM ;i++){
						int x=20+201*(i%3),y=70+50*(int)(i/3);
						if(mx>=x && mx<=x+200 && my>=y && my<=y+50){
							if(ai[i].entry==0)ai[i].entry=1;
							else ai[i].entry=0;
						}
					}
					if(mx>=30 && my>=400 && mx<=610 && my<=450){
						step=2;
						window=0;
					}
				}
			}
		}
		if(step==2){
			bright-=10;
			if(bright<=0){
				SetDrawBright(255,255,255);
			return 1;
		}
	}
	for(int i=0;i<AI_NUM;i++){
		if(ai[i].entry==1)en++;
	}
	if(GetMouseInput()==1 && input==0){
		input=1;
	}
	if(GetMouseInput()==0 && input==1){
		input=0;
	}
	
	ClearDrawScreen();
	SetDrawBright(bright,bright,bright);
	DrawGraph(0,0,gametitle,FALSE);
	int cr=GetColor(125,255,205);

	if(step==0){
		if(time%30<=15){
			DrawString(240,350,"Click to start",cr,0);
		}
	}
	/*
	DrawString(entryX,entryY,"ENTRY AI",cr,0);
	DrawBox(entryX-80,entryY-20,entryX+80,entryY+20,cr,0);
	
	cr=GetColor(255,100,50);
	DrawString(startX,startY,"START!",cr,0);
	DrawBox(startX-100,startY-20,startX+100,startY+20,cr,0);
	*/
	if(step==1){
		cr=GetColor(0,0,0);
		SetDrawBlendMode( DX_BLENDMODE_ALPHA,200);
		DrawBox(10,240-window,630,240+window,cr,1);
		SetDrawBlendMode( DX_BLENDMODE_ALPHA,255);
		cr=GetColor(255,255,255);
		DrawBox(10,240-window,630,240+window,cr,0);
		if(window>=230){
			cr=GetColor(125,255,205);
			DrawString(240,30,"ENTRY AI",cr,0);
			cr=GetColor(255,255,255);
			for(int i= 0; i < AI_NUM ;i++){
				if(ai[i].entry==0)
					SetDrawBright(100,100,100);
				int x=20+201*(i%3),y=70+50*(int)(i/3);
				DrawBox(x,y,x+200,y+50,cr,0);
				DrawBox(x,y,x+50,y+50,cr,0);
				DrawString(x+50,y+25,ai[i].name,GetColor(0,255,255),0);
				DrawRotaGraph(x+25,y+25,1,0,ai[i].Graph,FALSE,0);
				SetDrawBright(255,255,255);
			}
			cr=GetColor(255,100,50);
			DrawBox(30,400,610,450,cr,0);
			DrawString(240,425,"START!",cr,0);
		}
	}
	return 0;
	//WaitKey();
	//WaitTimer(1000/60);
}