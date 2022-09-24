#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
namespace generals{
	using namespace std;
	const int cA=5;
	const int cB=3;
	const int ca=4;
	const int cb=1;
	const int cC=0;
	const int msize=16;
	const int mount=16;
	const int grey=16;
	const int pmain=2;
	const int lcnt=10;
	char cMap[msize][msize]; 
	int hp[msize][msize];
	int nCount,sx,sy;
	bool bVis[msize][msize];
	int dir[4][2]={1,0,-1,0,0,1,0,-1};
	struct dRet{
		int x;
		int y;
		int dx;
		int dy;
	};
	struct node{
		int x;
		int y;
		int step;
	};
	void vInit();
	void vMove(int dx,int dy);
	void vMoveNum(int dx,int dy,char A);
	void vMoveNum(int x,int y,int dx,int dy,char A);
	void vDiv(int dx,int dy,char A);
	void vDecide(char A);
	dRet bfs(int x,int y,char A);
	void vPlus();
	void vChange(int x,int y);
	void gotoxy(int x,int y);
	void color(int t,int b);
	void vMain0();
	void vMain1();
	void vMain2();
	bool vEnd();
	void gen_main(){
		int p; 
		cout<<"player:"<<endl;
		cin>>p;
		system("cls");
		if(p==0) vMain0();
		if(p==1) vMain1();
		if(p==2) vMain2();
	}
	void vMain0(){
		int in;
		bool cur=true;
		vInit();
		for(nCount=0;;nCount++){
			gotoxy(msize,0);
			color(15,0);
			cout<<"count="<<nCount<<endl;
			if(cur){
				do{
					in=getch();
					if(in==224){
						in=getch();
						if(in==72) vMove(-1,0);
						if(in==80) vMove(1,0);
						if(in==75) vMove(0,-1);
						if(in==77) vMove(0,1);
					}
				}while(in!=' '&&in!='f');
				if(in=='f') cur=false;
			}
			vDecide('A');
			vDecide('B');
			vPlus();
		}
	}
	void vMain1(){
		int in;
		vInit();
		for(nCount=0;;nCount++){
			gotoxy(msize,0);
			color(15,0);
			cout<<"count="<<nCount<<endl;
			do{
				in=getch();
				if(in==224){
					in=getch();
					if(in==72) vMove(-1,0);
					if(in==80) vMove(1,0);
					if(in==75) vMove(0,-1);
					if(in==77) vMove(0,1);
				}
			}while(in!='w'&&in!='s'&&in!='a'&&in!='d'&&in!='z'&&in!=' ');
			if(in=='w') vMoveNum(-1,0,'A');
			if(in=='s') vMoveNum(1,0,'A');
			if(in=='a') vMoveNum(0,-1,'A');
			if(in=='d') vMoveNum(0,1,'A');
			if(in=='z'){
				in=getch();
				if(in=='w') vDiv(-1,0,'A');
				if(in=='s') vDiv(1,0,'A');
				if(in=='a') vDiv(0,-1,'A');
				if(in=='d') vDiv(0,1,'A');
			}
			vDecide('B');
			vPlus();
		}
	}
	void vMain2(){
		int in;
		vInit();
		for(nCount=0;;nCount++){
			gotoxy(msize,0);
			color(15,0);
			cout<<"count="<<nCount;
			vMove(-sx,-sy);
			gotoxy(msize+1,0);
			cout<<"red ";
			do{
				in=getch();
				if(in=='w') vMove(-1,0);
				if(in=='s') vMove(1,0);
				if(in=='a') vMove(0,-1);
				if(in=='d') vMove(0,1);
			}while(in!='x'&&in!='z'&&in!=' ');
			if(in=='x'){
				in=getch();
				if(in=='w') vMoveNum(-1,0,'A');
				if(in=='s') vMoveNum(1,0,'A');
				if(in=='a') vMoveNum(0,-1,'A');
				if(in=='d') vMoveNum(0,1,'A');
			}
			else if(in=='z'){
				in=getch();
				if(in=='w') vDiv(-1,0,'A');
				if(in=='s') vDiv(1,0,'A');
				if(in=='a') vDiv(0,-1,'A');
				if(in=='d') vDiv(0,1,'A');
			}
			vEnd();
			vMove(msize-1-sx,msize-1-sy);
			gotoxy(msize+1,0);
			color(15,0);
			cout<<"blue";
			do{
				in=getch();
				if(in==224){
					in=getch();
					if(in==72) vMove(-1,0);
					if(in==80) vMove(1,0);
					if(in==75) vMove(0,-1);
					if(in==77) vMove(0,1);
				}
			}while(in!='n'&&in!='m'&&in!=' ');
			if(in=='m'){
				in=getch();
				if(in==224) {
					in=getch();
					if(in==72) vMoveNum(-1,0,'B');
					if(in==80) vMoveNum(1,0,'B');
					if(in==75) vMoveNum(0,-1,'B');
					if(in==77) vMoveNum(0,1,'B');
				}
			}
			else if(in=='n'){
				in=getch();
				if(in==224) {
					in=getch();
					if(in==72) vDiv(-1,0,'B');
					if(in==80) vDiv(1,0,'B');
					if(in==75) vDiv(0,-1,'B');
					if(in==77) vDiv(0,1,'B');
				}
			}
			vPlus();
		}
	}
	void vInit(){
		int i,j,x,y;
		string sSeed; 
		unsigned int sd=20190622;
		cout<<"seed:"<<endl;
		cin>>sSeed;
		system("cls");
		for(i=0;i<sSeed.size();i++) sd=sd*233+sSeed[i];
		srand(sd);
		cMap[0][0]='A';
		hp[0][0]=pmain;
		vChange(0,0);
		cMap[msize-1][msize-1]='B';
		hp[msize-1][msize-1]=pmain;
		vChange(msize-1,msize-1);
		for(i=1;i<=mount;i++){
			x=rand()%msize;
			y=rand()%msize;
			if(cMap[x][y]!=0) i--;
			else{
				cMap[x][y]='X';
				gotoxy(x,y*3);
				color(15,0);
				cout<<" X";
			}
		}
		for(i=1;i<=grey;i++){
			x=rand()%msize;
			y=rand()%msize;
			if(cMap[x][y]!=0) i--;
			else{
				cMap[x][y]='C';
				hp[x][y]=40+rand()%10;
				vChange(x,y);
			}
		}
		sx=sy=0;
		gotoxy(0,2);
		color(15,0);
		cout<<"<";
	}
	void vMove(int dx,int dy){
		color(15,0);
		dx+=sx;dy+=sy;
		if(!(dx>=0&&dx<msize&&dy>=0&&dy<msize)) return;
		gotoxy(sx,sy*3+2);
		cout<<" ";
		sx=dx;sy=dy;
		gotoxy(sx,sy*3+2);
		cout<<"<";
		gotoxy(msize+1,0);
		cout<<"cMap="<<cMap[dx][dy]<<",hp="<<hp[dx][dy]<<"            ";
	}
	void vMoveNum(int x,int y,int dx,int dy,char A){
		char a,B,b;
		a=A-'A'+'a';
		B=(A=='A')?'B':'A';
		b=B-'A'+'a';
		if(cMap[x][y]!=a&&cMap[x][y]!=A) return;
		dx+=x;dy+=y;
		if(!(dx>=0&&dx<msize&&dy>=0&&dy<msize&&cMap[dx][dy]!='X')) return;
		char &cd=cMap[dx][dy];
		int &hd=hp[dx][dy],&hs=hp[x][y];
		if(cd!=a&&cd!=A&&hd>=hs-1) return;
		if(cd==0){
			cd=a;
			hd=hs-1;
		}
		else if(cd==A||cd==a) hd+=hs-1;
		else if(cd==B||cd==b){
			if(B=='B') cd--;
			else cd++;
			hd=hs-1-hd;
		}
		else{
			cd=A;
			hd=hs-1-hd;
		}
		hs=1;
		vChange(dx,dy);
		vChange(x,y);
	}
	void vMoveNum(int dx,int dy,char A){
		vMoveNum(sx,sy,dx,dy,A);
		vMove(dx,dy);
	}
	void vDiv(int dx,int dy,char A){
		char a,B,b;
		a=A-'A'+'a';
		B=(A=='A')?'B':'A';
		b=B-'A'+'a';
		if(cMap[sx][sy]!=a&&cMap[sx][sy]!=A) return;
		dx+=sx;dy+=sy;
		if(!(dx>=0&&dx<msize&&dy>=0&&dy<msize&&cMap[dx][dy]!='X')) return;
		char &cd=cMap[dx][dy];
		int &hd=hp[dx][dy],&hs=hp[sx][sy],tmp=hs/2;
		if(tmp==0) return;
		if(cd!=a&&cd!=A&&hd>=tmp-1) return;
		if(cd==0){
			cd=a;
			hd=tmp;
		}
		else if(cd==A||cd==a) hd+=tmp;
		else if(cd==B||cd==b){
			if(B=='B') cd--;
			else cd++;
			hd=tmp-hd;
		}
		else{
			cd=A;
			hd=tmp-hd;
		}
		hs-=tmp;
		vChange(dx,dy);
		vChange(sx,sy);
		vMove(dx-sx,dy-sy);
	}
	void vDecide(char A){
		char a,B,b;
		a=A-'A'+'a';
		B=(A=='A')?'B':'A';
		b=B-'A'+'a';
		int i,j,k,x,y,dx,dy;
		dRet tmp,res;
		bool bd=false,bm=false;
		for(i=(A=='A')?0:(msize-1);(A=='A')?(i<=msize-1):(i>=0);(A=='A')?(i++):(i--)){
			for(j=(A=='A')?0:(msize-1);(A=='A')?(j<=msize-1):(j>=0);(A=='A')?(j++):(j--)){
				if(!bd&&(cMap[i][j]==B||cMap[i][j]=='C')){
					tmp=bfs(i,j,A);
					if(tmp.dx+tmp.dy==0) continue;
					bd=true;
					res=tmp;
				}
				if(!bd&&!bm&&(cMap[i][j]==A||cMap[i][j]==a)&&hp[i][j]>1){
					for(k=0;k<4;k++){
						dx=dir[k][0]+i;
						dy=dir[k][1]+j;
						if(!(dx>=0&&dx<msize&&dy>=0&&dy<msize)) continue;
						if((cMap[dx][dy]==0||cMap[dx][dy]==b)&&hp[dx][dy]<hp[i][j]-1){
							bm=true;
							res.dx=dir[k][0];
							res.dy=dir[k][1];
							res.x=i;
							res.y=j;
							break;
						}
					}
				}
				if(bd) break;
			}
			if(bd) break;
		}
		if(!bd&&!bm) return;
		vMoveNum(res.x,res.y,res.dx,res.dy,A);
	}
	dRet bfs(int x,int y,char A){
		char a,B,b;
		a=A-'A'+'a';
		B=(A=='A')?'B':'A';
		b=B-'A'+'a';
		int i,dx,dy;
		dRet ret;
		node now,nxt;
		queue<node>q;
		now.step=hp[x][y]+2;
		now.x=x;
		now.y=y;
		q.push(now);
		memset(bVis,false,sizeof bVis);
		bVis[x][y]=true;
		while(!q.empty()){
			now=q.front();
			q.pop();
			for(i=0;i<4;i++){
				dx=dir[i][0]+now.x;
				dy=dir[i][1]+now.y;
				if(dx>=0&&dx<msize&&dy>=0&&dy<msize&&!bVis[dx][dy]&&cMap[dx][dy]!='X'){
					bVis[dx][dy]=true;
					if(cMap[dx][dy]==0) nxt.step=now.step+1;
					if(cMap[dx][dy]==b||cMap[dx][dy]==B||cMap[dx][dy]=='C') nxt.step=now.step+hp[dx][dy]+2;
					else{
						nxt.step=now.step-hp[dx][dy]+1;
						if(nxt.step<-5&&(cMap[dx][dy]==A||cMap[dx][dy]==a)){
							ret.dx=-dir[i][0];
							ret.dy=-dir[i][1];
							ret.x=dx;
							ret.y=dy;
							return ret;
						}
					}
					nxt.x=dx;
					nxt.y=dy;
					q.push(nxt);
				}
			}
		}
		ret.dx=ret.dy=0;
		return ret;
	}
	void vPlus(){
		int i,j,aa=0,ba=0,al=0,bl=0;
		if(nCount%lcnt==0){
			for(i=0;i<msize;i++){
				for(j=0;j<msize;j++){
					if(cMap[i][j]=='a'||cMap[i][j]=='b'){
						hp[i][j]++;
						vChange(i,j);
					}
				}
			}
		}
		for(i=0;i<msize;i++){
			for(j=0;j<msize;j++){
				if(cMap[i][j]=='A'||cMap[i][j]=='B'){
					hp[i][j]+=pmain;
					vChange(i,j);
				}
				if(cMap[i][j]=='A'||cMap[i][j]=='a') al++,aa+=hp[i][j];
				if(cMap[i][j]=='B'||cMap[i][j]=='b') bl++,ba+=hp[i][j];
			}
		}
		color(15,0);
		gotoxy(msize+2,0);
		cout<<"red army:"<<aa<<"   "<<endl;
		cout<<"red land:"<<al<<"   "<<endl;
		cout<<"blue army:"<<ba<<"   "<<endl;
		cout<<"blue land:"<<bl<<"   "<<endl;
		if(vEnd()) return;
	}
	bool vEnd(){
		
		if(cMap[0][0]=='B'){
			cout<<"blue win"<<endl;
			return true;
		}
		if(cMap[msize-1][msize-1]=='A'){
			cout<<"red win"<<endl;
			return true;
		}
	}
	void vChange(int x,int y){
		int c;
		char cm=cMap[x][y];
		if(cm=='A') c=cA;
		if(cm=='a') c=ca;
		if(cm=='B') c=cB;
		if(cm=='b') c=cb;
		if(cm=='C') c=cC;
		gotoxy(x,y*3);
		color(15,c);
		int val=hp[x][y];
		if(val<10) cout<<" "<<val;
		else if(val<100) cout<<val;
		else if(val<1000) cout<<val/100<<"e";
		else if(val<10000) cout<<val/1000<<"k";
		else if(val<100000) cout<<val/10000<<"w";
		else cout<<"ju";
	}
	void gotoxy(int x,int y){
		COORD c;
		c.X=y;
		c.Y=x;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
	}
	void color(int t,int b){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),t+b*16);}
}
int main(){
	generals::gen_main();
}
